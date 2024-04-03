/*
 * QEMU AArch64 CPU
 *
 * Copyright (c) 2013 Linaro Ltd
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see
 * <http://www.gnu.org/licenses/gpl-2.0.html>
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "cpu.h"
#include "qemu/module.h"
#if !defined(CONFIG_USER_ONLY)
#include "hw/loader.h"
#endif
#include "sysemu/sysemu.h"
#include "sysemu/kvm.h"
#include "kvm_arm.h"
#include "qapi/visitor.h"
#include "exec/qr_head.h"
#include "exec/ring_buf.h"
#include "exec/shm_slim.h"
#include <pthread.h>

#ifdef PPI_QR_FUNC
#define MEM_TOOL_NUMBER 2
#define INSN_TOOL_NUMBER 3
#define BOTH_TOOL_NUMBER 6
#define TOOL_NAME_LENGTH 20
int bind_cpu_num = 1;
extern int set_bind_cpu;
extern int config_bind_cpu[64];
int channel_d = 1;
extern pthread_mutex_t filter_mutex;
#ifdef _QR_Q_TB_COUNT_
extern pthread_mutex_t mutex;
#endif
#include "hw/boards.h"
#include "qemu/option.h"
#endif
static inline void set_feature(CPUARMState *env, int feature)
{
    env->features |= 1ULL << feature;
}

static inline void unset_feature(CPUARMState *env, int feature)
{
    env->features &= ~(1ULL << feature);
}

#ifndef CONFIG_USER_ONLY
static uint64_t a57_a53_l2ctlr_read(CPUARMState *env, const ARMCPRegInfo *ri)
{
    ARMCPU *cpu = env_archcpu(env);

    /* Number of cores is in [25:24]; otherwise we RAZ */
    return (cpu->core_count - 1) << 24;
}
#endif

static const ARMCPRegInfo cortex_a72_a57_a53_cp_reginfo[] = {
#ifndef CONFIG_USER_ONLY
    { .name = "L2CTLR_EL1", .state = ARM_CP_STATE_AA64,
      .opc0 = 3, .opc1 = 1, .crn = 11, .crm = 0, .opc2 = 2,
      .access = PL1_RW, .readfn = a57_a53_l2ctlr_read,
      .writefn = arm_cp_write_ignore },
    { .name = "L2CTLR",
      .cp = 15, .opc1 = 1, .crn = 9, .crm = 0, .opc2 = 2,
      .access = PL1_RW, .readfn = a57_a53_l2ctlr_read,
      .writefn = arm_cp_write_ignore },
#endif
    { .name = "L2ECTLR_EL1", .state = ARM_CP_STATE_AA64,
      .opc0 = 3, .opc1 = 1, .crn = 11, .crm = 0, .opc2 = 3,
      .access = PL1_RW, .type = ARM_CP_CONST, .resetvalue = 0 },
    { .name = "L2ECTLR",
      .cp = 15, .opc1 = 1, .crn = 9, .crm = 0, .opc2 = 3,
      .access = PL1_RW, .type = ARM_CP_CONST, .resetvalue = 0 },
    { .name = "L2ACTLR", .state = ARM_CP_STATE_BOTH,
      .opc0 = 3, .opc1 = 1, .crn = 15, .crm = 0, .opc2 = 0,
      .access = PL1_RW, .type = ARM_CP_CONST, .resetvalue = 0 },
    { .name = "CPUACTLR_EL1", .state = ARM_CP_STATE_AA64,
      .opc0 = 3, .opc1 = 1, .crn = 15, .crm = 2, .opc2 = 0,
      .access = PL1_RW, .type = ARM_CP_CONST, .resetvalue = 0 },
    { .name = "CPUACTLR",
      .cp = 15, .opc1 = 0, .crm = 15,
      .access = PL1_RW, .type = ARM_CP_CONST | ARM_CP_64BIT, .resetvalue = 0 },
    { .name = "CPUECTLR_EL1", .state = ARM_CP_STATE_AA64,
      .opc0 = 3, .opc1 = 1, .crn = 15, .crm = 2, .opc2 = 1,
      .access = PL1_RW, .type = ARM_CP_CONST, .resetvalue = 0 },
    { .name = "CPUECTLR",
      .cp = 15, .opc1 = 1, .crm = 15,
      .access = PL1_RW, .type = ARM_CP_CONST | ARM_CP_64BIT, .resetvalue = 0 },
    { .name = "CPUMERRSR_EL1", .state = ARM_CP_STATE_AA64,
      .opc0 = 3, .opc1 = 1, .crn = 15, .crm = 2, .opc2 = 2,
      .access = PL1_RW, .type = ARM_CP_CONST, .resetvalue = 0 },
    { .name = "CPUMERRSR",
      .cp = 15, .opc1 = 2, .crm = 15,
      .access = PL1_RW, .type = ARM_CP_CONST | ARM_CP_64BIT, .resetvalue = 0 },
    { .name = "L2MERRSR_EL1", .state = ARM_CP_STATE_AA64,
      .opc0 = 3, .opc1 = 1, .crn = 15, .crm = 2, .opc2 = 3,
      .access = PL1_RW, .type = ARM_CP_CONST, .resetvalue = 0 },
    { .name = "L2MERRSR",
      .cp = 15, .opc1 = 3, .crm = 15,
      .access = PL1_RW, .type = ARM_CP_CONST | ARM_CP_64BIT, .resetvalue = 0 },
    REGINFO_SENTINEL
};

static void aarch64_a57_initfn(Object *obj)
{
    ARMCPU *cpu = ARM_CPU(obj);

    cpu->dtb_compatible = "arm,cortex-a57";
    set_feature(&cpu->env, ARM_FEATURE_V8);
    set_feature(&cpu->env, ARM_FEATURE_VFP4);
    set_feature(&cpu->env, ARM_FEATURE_NEON);
    set_feature(&cpu->env, ARM_FEATURE_GENERIC_TIMER);
    set_feature(&cpu->env, ARM_FEATURE_AARCH64);
    set_feature(&cpu->env, ARM_FEATURE_CBAR_RO);
    set_feature(&cpu->env, ARM_FEATURE_EL2);
    set_feature(&cpu->env, ARM_FEATURE_EL3);
    set_feature(&cpu->env, ARM_FEATURE_PMU);
    cpu->kvm_target = QEMU_KVM_ARM_TARGET_CORTEX_A57;
    cpu->midr = 0x411fd070;
    cpu->revidr = 0x00000000;
    cpu->reset_fpsid = 0x41034070;
    cpu->isar.mvfr0 = 0x10110222;
    cpu->isar.mvfr1 = 0x12111111;
    cpu->isar.mvfr2 = 0x00000043;
    cpu->ctr = 0x8444c004;
    cpu->reset_sctlr = 0x00c50838;
    cpu->id_pfr0 = 0x00000131;
    cpu->id_pfr1 = 0x00011011;
    cpu->id_dfr0 = 0x03010066;
    cpu->id_afr0 = 0x00000000;
    cpu->id_mmfr0 = 0x10101105;
    cpu->id_mmfr1 = 0x40000000;
    cpu->id_mmfr2 = 0x01260000;
    cpu->id_mmfr3 = 0x02102211;
    cpu->isar.id_isar0 = 0x02101110;
    cpu->isar.id_isar1 = 0x13112111;
    cpu->isar.id_isar2 = 0x21232042;
    cpu->isar.id_isar3 = 0x01112131;
    cpu->isar.id_isar4 = 0x00011142;
    cpu->isar.id_isar5 = 0x00011121;
    cpu->isar.id_isar6 = 0;
    cpu->isar.id_aa64pfr0 = 0x00002222;
    cpu->id_aa64dfr0 = 0x10305106;
    cpu->isar.id_aa64isar0 = 0x00011120;
    cpu->isar.id_aa64mmfr0 = 0x00001124;
    cpu->dbgdidr = 0x3516d000;
    cpu->clidr = 0x0a200023;
    cpu->ccsidr[0] = 0x701fe00a; /* 32KB L1 dcache */
    cpu->ccsidr[1] = 0x201fe012; /* 48KB L1 icache */
    cpu->ccsidr[2] = 0x70ffe07a; /* 2048KB L2 cache */
    cpu->dcz_blocksize = 4; /* 64 bytes */
    cpu->gic_num_lrs = 4;
    cpu->gic_vpribits = 5;
    cpu->gic_vprebits = 5;
    define_arm_cp_regs(cpu, cortex_a72_a57_a53_cp_reginfo);
}

static void aarch64_a53_initfn(Object *obj)
{
    ARMCPU *cpu = ARM_CPU(obj);

    cpu->dtb_compatible = "arm,cortex-a53";
    set_feature(&cpu->env, ARM_FEATURE_V8);
    set_feature(&cpu->env, ARM_FEATURE_VFP4);
    set_feature(&cpu->env, ARM_FEATURE_NEON);
    set_feature(&cpu->env, ARM_FEATURE_GENERIC_TIMER);
    set_feature(&cpu->env, ARM_FEATURE_AARCH64);
    set_feature(&cpu->env, ARM_FEATURE_CBAR_RO);
    set_feature(&cpu->env, ARM_FEATURE_EL2);
    set_feature(&cpu->env, ARM_FEATURE_EL3);
    set_feature(&cpu->env, ARM_FEATURE_PMU);
    cpu->kvm_target = QEMU_KVM_ARM_TARGET_CORTEX_A53;
    cpu->midr = 0x410fd034;
    cpu->revidr = 0x00000000;
    cpu->reset_fpsid = 0x41034070;
    cpu->isar.mvfr0 = 0x10110222;
    cpu->isar.mvfr1 = 0x12111111;
    cpu->isar.mvfr2 = 0x00000043;
    cpu->ctr = 0x84448004; /* L1Ip = VIPT */
    cpu->reset_sctlr = 0x00c50838;
    cpu->id_pfr0 = 0x00000131;
    cpu->id_pfr1 = 0x00011011;
    cpu->id_dfr0 = 0x03010066;
    cpu->id_afr0 = 0x00000000;
    cpu->id_mmfr0 = 0x10101105;
    cpu->id_mmfr1 = 0x40000000;
    cpu->id_mmfr2 = 0x01260000;
    cpu->id_mmfr3 = 0x02102211;
    cpu->isar.id_isar0 = 0x02101110;
    cpu->isar.id_isar1 = 0x13112111;
    cpu->isar.id_isar2 = 0x21232042;
    cpu->isar.id_isar3 = 0x01112131;
    cpu->isar.id_isar4 = 0x00011142;
    cpu->isar.id_isar5 = 0x00011121;
    cpu->isar.id_isar6 = 0;
    cpu->isar.id_aa64pfr0 = 0x00002222;
    cpu->id_aa64dfr0 = 0x10305106;
    cpu->isar.id_aa64isar0 = 0x00011120;
    cpu->isar.id_aa64mmfr0 = 0x00001122; /* 40 bit physical addr */
    cpu->dbgdidr = 0x3516d000;
    cpu->clidr = 0x0a200023;
    cpu->ccsidr[0] = 0x700fe01a; /* 32KB L1 dcache */
    cpu->ccsidr[1] = 0x201fe00a; /* 32KB L1 icache */
    cpu->ccsidr[2] = 0x707fe07a; /* 1024KB L2 cache */
    cpu->dcz_blocksize = 4; /* 64 bytes */
    cpu->gic_num_lrs = 4;
    cpu->gic_vpribits = 5;
    cpu->gic_vprebits = 5;
    define_arm_cp_regs(cpu, cortex_a72_a57_a53_cp_reginfo);
}

static void aarch64_a72_initfn(Object *obj)
{
    ARMCPU *cpu = ARM_CPU(obj);

    cpu->dtb_compatible = "arm,cortex-a72";
    set_feature(&cpu->env, ARM_FEATURE_V8);
    set_feature(&cpu->env, ARM_FEATURE_VFP4);
    set_feature(&cpu->env, ARM_FEATURE_NEON);
    set_feature(&cpu->env, ARM_FEATURE_GENERIC_TIMER);
    set_feature(&cpu->env, ARM_FEATURE_AARCH64);
    set_feature(&cpu->env, ARM_FEATURE_CBAR_RO);
    set_feature(&cpu->env, ARM_FEATURE_EL2);
    set_feature(&cpu->env, ARM_FEATURE_EL3);
    set_feature(&cpu->env, ARM_FEATURE_PMU);
    cpu->midr = 0x410fd083;
    cpu->revidr = 0x00000000;
    cpu->reset_fpsid = 0x41034080;
    cpu->isar.mvfr0 = 0x10110222;
    cpu->isar.mvfr1 = 0x12111111;
    cpu->isar.mvfr2 = 0x00000043;
    cpu->ctr = 0x8444c004;
    cpu->reset_sctlr = 0x00c50838;
    cpu->id_pfr0 = 0x00000131;
    cpu->id_pfr1 = 0x00011011;
    cpu->id_dfr0 = 0x03010066;
    cpu->id_afr0 = 0x00000000;
    cpu->id_mmfr0 = 0x10201105;
    cpu->id_mmfr1 = 0x40000000;
    cpu->id_mmfr2 = 0x01260000;
    cpu->id_mmfr3 = 0x02102211;
    cpu->isar.id_isar0 = 0x02101110;
    cpu->isar.id_isar1 = 0x13112111;
    cpu->isar.id_isar2 = 0x21232042;
    cpu->isar.id_isar3 = 0x01112131;
    cpu->isar.id_isar4 = 0x00011142;
    cpu->isar.id_isar5 = 0x00011121;
    cpu->isar.id_aa64pfr0 = 0x00002222;
    cpu->id_aa64dfr0 = 0x10305106;
    cpu->isar.id_aa64isar0 = 0x00011120;
    cpu->isar.id_aa64mmfr0 = 0x00001124;
    cpu->dbgdidr = 0x3516d000;
    cpu->clidr = 0x0a200023;
    cpu->ccsidr[0] = 0x701fe00a; /* 32KB L1 dcache */
    cpu->ccsidr[1] = 0x201fe012; /* 48KB L1 icache */
    cpu->ccsidr[2] = 0x707fe07a; /* 1MB L2 cache */
    cpu->dcz_blocksize = 4; /* 64 bytes */
    cpu->gic_num_lrs = 4;
    cpu->gic_vpribits = 5;
    cpu->gic_vprebits = 5;
    define_arm_cp_regs(cpu, cortex_a72_a57_a53_cp_reginfo);
}

static void cpu_max_get_sve_vq(Object *obj, Visitor *v, const char *name,
                               void *opaque, Error **errp)
{
    ARMCPU *cpu = ARM_CPU(obj);
    visit_type_uint32(v, name, &cpu->sve_max_vq, errp);
}

static void cpu_max_set_sve_vq(Object *obj, Visitor *v, const char *name,
                               void *opaque, Error **errp)
{
    ARMCPU *cpu = ARM_CPU(obj);
    Error *err = NULL;

    visit_type_uint32(v, name, &cpu->sve_max_vq, &err);

    if (!err && (cpu->sve_max_vq == 0 || cpu->sve_max_vq > ARM_MAX_VQ)) {
        error_setg(&err, "unsupported SVE vector length");
        error_append_hint(&err, "Valid sve-max-vq in range [1-%d]\n",
                          ARM_MAX_VQ);
    }
    error_propagate(errp, err);
}

/* -cpu max: if KVM is enabled, like -cpu host (best possible with this host);
 * otherwise, a CPU with as many features enabled as our emulation supports.
 * The version of '-cpu max' for qemu-system-arm is defined in cpu.c;
 * this only needs to handle 64 bits.
 */
static void aarch64_max_initfn(Object *obj)
{
    ARMCPU *cpu = ARM_CPU(obj);

    if (kvm_enabled()) {
        kvm_arm_set_cpu_features_from_host(cpu);
    } else {
        uint64_t t;
        uint32_t u;
        aarch64_a57_initfn(obj);

        t = cpu->isar.id_aa64isar0;
        t = FIELD_DP64(t, ID_AA64ISAR0, AES, 2); /* AES + PMULL */
        t = FIELD_DP64(t, ID_AA64ISAR0, SHA1, 1);
        t = FIELD_DP64(t, ID_AA64ISAR0, SHA2, 2); /* SHA512 */
        t = FIELD_DP64(t, ID_AA64ISAR0, CRC32, 1);
        t = FIELD_DP64(t, ID_AA64ISAR0, ATOMIC, 2);
        t = FIELD_DP64(t, ID_AA64ISAR0, RDM, 1);
        t = FIELD_DP64(t, ID_AA64ISAR0, SHA3, 1);
        t = FIELD_DP64(t, ID_AA64ISAR0, SM3, 1);
        t = FIELD_DP64(t, ID_AA64ISAR0, SM4, 1);
        t = FIELD_DP64(t, ID_AA64ISAR0, DP, 1);
        t = FIELD_DP64(t, ID_AA64ISAR0, FHM, 1);
        t = FIELD_DP64(t, ID_AA64ISAR0, TS, 2); /* v8.5-CondM */
        t = FIELD_DP64(t, ID_AA64ISAR0, RNDR, 1);
        cpu->isar.id_aa64isar0 = t;

        t = cpu->isar.id_aa64isar1;
        t = FIELD_DP64(t, ID_AA64ISAR1, JSCVT, 1);
        t = FIELD_DP64(t, ID_AA64ISAR1, FCMA, 1);
        t = FIELD_DP64(t, ID_AA64ISAR1, APA, 1); /* PAuth, architected only */
        t = FIELD_DP64(t, ID_AA64ISAR1, API, 0);
        t = FIELD_DP64(t, ID_AA64ISAR1, GPA, 1);
        t = FIELD_DP64(t, ID_AA64ISAR1, GPI, 0);
        t = FIELD_DP64(t, ID_AA64ISAR1, SB, 1);
        t = FIELD_DP64(t, ID_AA64ISAR1, SPECRES, 1);
        t = FIELD_DP64(t, ID_AA64ISAR1, FRINTTS, 1);
        cpu->isar.id_aa64isar1 = t;

        t = cpu->isar.id_aa64pfr0;
        t = FIELD_DP64(t, ID_AA64PFR0, SVE, 1);
        t = FIELD_DP64(t, ID_AA64PFR0, FP, 1);
        t = FIELD_DP64(t, ID_AA64PFR0, ADVSIMD, 1);
        cpu->isar.id_aa64pfr0 = t;

        t = cpu->isar.id_aa64pfr1;
        t = FIELD_DP64(t, ID_AA64PFR1, BT, 1);
        cpu->isar.id_aa64pfr1 = t;

        t = cpu->isar.id_aa64mmfr1;
        t = FIELD_DP64(t, ID_AA64MMFR1, HPDS, 1); /* HPD */
        t = FIELD_DP64(t, ID_AA64MMFR1, LO, 1);
        cpu->isar.id_aa64mmfr1 = t;

        /* Replicate the same data to the 32-bit id registers.  */
        u = cpu->isar.id_isar5;
        u = FIELD_DP32(u, ID_ISAR5, AES, 2); /* AES + PMULL */
        u = FIELD_DP32(u, ID_ISAR5, SHA1, 1);
        u = FIELD_DP32(u, ID_ISAR5, SHA2, 1);
        u = FIELD_DP32(u, ID_ISAR5, CRC32, 1);
        u = FIELD_DP32(u, ID_ISAR5, RDM, 1);
        u = FIELD_DP32(u, ID_ISAR5, VCMA, 1);
        cpu->isar.id_isar5 = u;

        u = cpu->isar.id_isar6;
        u = FIELD_DP32(u, ID_ISAR6, JSCVT, 1);
        u = FIELD_DP32(u, ID_ISAR6, DP, 1);
        u = FIELD_DP32(u, ID_ISAR6, FHM, 1);
        u = FIELD_DP32(u, ID_ISAR6, SB, 1);
        u = FIELD_DP32(u, ID_ISAR6, SPECRES, 1);
        cpu->isar.id_isar6 = u;

        /*
         * FIXME: We do not yet support ARMv8.2-fp16 for AArch32 yet,
         * so do not set MVFR1.FPHP.  Strictly speaking this is not legal,
         * but it is also not legal to enable SVE without support for FP16,
         * and enabling SVE in system mode is more useful in the short term.
         */

#ifdef CONFIG_USER_ONLY
        /* For usermode -cpu max we can use a larger and more efficient DCZ
         * blocksize since we don't have to follow what the hardware does.
         */
        cpu->ctr = 0x80038003; /* 32 byte I and D cacheline size, VIPT icache */
        cpu->dcz_blocksize = 7; /*  512 bytes */
#endif

        cpu->sve_max_vq = ARM_MAX_VQ;
        object_property_add(obj, "sve-max-vq", "uint32", cpu_max_get_sve_vq,
                            cpu_max_set_sve_vq, NULL, NULL, &error_fatal);
    }
}

struct ARMCPUInfo {
    const char *name;
    void (*initfn)(Object *obj);
    void (*class_init)(ObjectClass *oc, void *data);
};

static const ARMCPUInfo aarch64_cpus[] = {
    { .name = "cortex-a57",         .initfn = aarch64_a57_initfn },
    { .name = "cortex-a53",         .initfn = aarch64_a53_initfn },
    { .name = "cortex-a72",         .initfn = aarch64_a72_initfn },
    { .name = "max",                .initfn = aarch64_max_initfn },
    { .name = NULL }
};

static bool aarch64_cpu_get_aarch64(Object *obj, Error **errp)
{
    ARMCPU *cpu = ARM_CPU(obj);
    return arm_feature(&cpu->env, ARM_FEATURE_AARCH64);
}

static void aarch64_cpu_set_aarch64(Object *obj, bool value, Error **errp)
{
    ARMCPU *cpu = ARM_CPU(obj);

    /* At this time, this property is only allowed if KVM is enabled.  This
     * restriction allows us to avoid fixing up functionality that assumes a
     * uniform execution state like do_interrupt.
     */
    if (!kvm_enabled()) {
        error_setg(errp, "'aarch64' feature cannot be disabled "
                         "unless KVM is enabled");
        return;
    }

    if (value == false) {
        unset_feature(&cpu->env, ARM_FEATURE_AARCH64);
    } else {
        set_feature(&cpu->env, ARM_FEATURE_AARCH64);
    }
}
#ifdef PPI_QR_FUNC
void configure_channel(QemuOpts *opts)
{
     const char *option;
     option = qemu_opt_get(opts, "channel_d");
     errno = 0;
     channel_d = atoi(option);
     printf("channel_d = %d\n",channel_d);
     if (errno != 0 || !strlen(option)) {
            fprintf(stderr, "rate: Invalid value");
     }
     /* do ipcrm before create ringbuff */
     printf("do ipcrm\n");
     char path_rb[128];
     sprintf(path_rb,"%s/qr/fok_insoff.key",getenv("HOME"));
     key_t key_insoff = ftok(path_rb,0x03);

     char channel_ipcrm[128];
     sprintf(channel_ipcrm,"ipcrm -M %d",key_insoff+channel_d);
     int sysRet_channel_ipcrm = system(channel_ipcrm);
     if (sysRet_channel_ipcrm == -1) {
	     //The system method failed
     }
     char channel_delete_shmfile[128];
     sprintf(channel_delete_shmfile,"rm -rf %s/qr/%d/shm_temp_file_%d",getenv("HOME"),channel_d,channel_d);
     int sysRet_channel_delete_shmfile = system(channel_delete_shmfile);
     if ( sysRet_channel_delete_shmfile == -1 ) {
	     //The system method failed
     }
     int sysRet_ipcs = system("ipcs");
     if ( sysRet_ipcs == -1 ) {
	     //The system method failed
     }
     /* delete channel_d and mkdir channel_d and cp config to channel_d */
     char channel_clean[128],channel_mkdir[128],channel_cp[128];
     sprintf(channel_clean,"rm -rf %s/qr/%d",getenv("HOME"),channel_d);
     int sysRet_channel_clean = system(channel_clean);
     if ( sysRet_channel_clean == -1 ) {
	     //The system method failed
     }
     sprintf(channel_mkdir,"mkdir -p %s/qr/%d",getenv("HOME"),channel_d);
     int sysRet_channel_mkdir = system(channel_mkdir);
     if ( sysRet_channel_mkdir == -1 ) { 
	     //The system method failed
     }
     sprintf(channel_cp,"cp %s/qr/bind_cpu.config %s/qr/%d/bind_cpu_%d.config",getenv("HOME"),getenv("HOME"),channel_d,channel_d);
     int sysRet_channel_cp = system(channel_cp);
     if ( sysRet_channel_cp == -1 ) {
	     //The system method failed
     }
     return;
}
#endif
static void aarch64_cpu_initfn(Object *obj)
{
#ifdef _QR_Q_BIND_CPU_
    if ( set_bind_cpu == 1 ) {
	cpu_set_t mask;
   	CPU_ZERO(&mask);
	CPU_SET(config_bind_cpu[bind_cpu_num-1], &mask);
	if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
		printf("Set CPU affinity failue, ERROR:%s\n", strerror(errno));
		exit(1);
	}
	printf("bind cpus %d success!  \n",config_bind_cpu[bind_cpu_num-1]);
	bind_cpu_num++;

    } else if ( set_bind_cpu == 0 ) {
        int cpus = sysconf(_SC_NPROCESSORS_ONLN)-1;  //cpu0 cannot be used
    	MachineState *ms = MACHINE(qdev_get_machine());
    	unsigned int smp_cpus = ms->smp.cpus;
    	printf("system free cpus = %d\n",cpus);
    	printf("usr config smp_cpus = %d\n",smp_cpus);
    	if ( cpus > smp_cpus) {
	    printf("cpu is enough\n");
    	    cpu_set_t mask;

    	    CPU_ZERO(&mask);  
    	    CPU_SET(bind_cpu_num, &mask);
    	    if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
                printf("Set CPU affinity failue, ERROR:%s\n", strerror(errno));
                exit(1);
    	    }
    	    printf("bind cpus %d success!  \n",bind_cpu_num);
    	    bind_cpu_num++;
    	} else {
	    printf("cpu is not enough\n");
	    cpu_set_t mask;
	    CPU_ZERO(&mask);
	    CPU_SET(bind_cpu_num, &mask);
	    if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
	        printf("Set CPU affinity failue, ERROR:%s\n", strerror(errno));
	        exit(1);
  	    }
	    printf("bind cpus %d success!  \n",bind_cpu_num);
	    bind_cpu_num++;
            bind_cpu_num = bind_cpu_num%cpus;
        }
    }
#endif	
#ifdef PPI_QR_FUNC
    key_t key_insoff;
    char path_rb[64];
    ARMCPU *cpu = ARM_CPU(obj);

    sprintf(path_rb,"%s/qr/fok_insoff.key",getenv("HOME"));
    printf("path = %s\n",path_rb);
    key_insoff = ftok(path_rb,0x03);
    if(key_insoff==-1)
    {   
        perror("ftok error");
        exit(1);
    }
    printf("keyinoff + channel_d = %lx\n",key_insoff+channel_d);
    /*
    char channel_ipcrm[128];
    sprintf(channel_ipcrm,"ipcrm -M %d",key_insoff+channel_d);
    system(channel_ipcrm);
    printf("do ipcrm\n");
    */
    ringbuf_init(sizeof(struct qrio_buff),RB_SIZE,key_insoff+channel_d);
    printf("ringbuf init sucess\n");
    
#endif
#ifdef PPI_QR_FUNC
    bool retval;
    char path[128];

    if ( get_shm_user_base() == NULL ){

         sprintf(path,"%s/qr/%d/shm_temp_file_%d",getenv("HOME"),channel_d,channel_d);
         printf("shm file path cpu64.c = %s\n",path);
         retval = shm_init(NULL, path);
         if (retval == false) {
                 fprintf(stderr, "shm_init() failed!");
                 exit(EXIT_FAILURE);
         }
         printf("alloc shm\n");
    }
    
    cpu->env.checkout = 0;
    cpu->env.needsend = 0;
    cpu->env.needcount = 0;
    cpu->env.sendbuf = NULL;

    cpu->env.mem_need_send = 0;
    cpu->env.insn_need_send = 0;
    char tools_config_path[128];
    sprintf(tools_config_path,"%s/qr/tools.config",getenv("HOME"));
    FILE *in = fopen(tools_config_path,"r");
    char mem_tool_names_[MEM_TOOL_NUMBER][TOOL_NAME_LENGTH] = {{"reuse_time"}};
    char insn_tool_names_[INSN_TOOL_NUMBER][TOOL_NAME_LENGTH] = {{"call_graph"},{"hot_spot"},{"opcode_mix"}};
    char both_tool_names_[BOTH_TOOL_NUMBER][TOOL_NAME_LENGTH] = {{"reuse_distance"},{"basic_counts"},{"func_view"},{"histogram"},{"jump_judge"},{"cache"}};
    if(in < 0){
        printf("config file error\n");
    }
    char temp[1000];
    while(fgets(temp, 1000,in)!=NULL){
        char *tool_name  = temp;
        tool_name=strtok(tool_name,"\n");
        tool_name=strtok(tool_name," ");
        int i = 0;
        for(; i < MEM_TOOL_NUMBER; i++ ){
          if(strcmp(mem_tool_names_[i], tool_name) == 0){
            printf("need to send mem info\n");
            cpu->env.mem_need_send = 1;
          }
        }
        for(i = 0; i < INSN_TOOL_NUMBER; i++ ){
          if(strcmp(insn_tool_names_[i], tool_name) == 0){
            printf("need to send instr info\n");
            cpu->env.insn_need_send = 1;
          }
        }
        for(i = 0; i < BOTH_TOOL_NUMBER; i++ ){
          if(strcmp(both_tool_names_[i], tool_name) == 0){
            printf("need to send both mem and instr info\n");
            cpu->env.mem_need_send = 1;
            cpu->env.insn_need_send = 1;
          }
        }
    }
#endif
    object_property_add_bool(obj, "aarch64", aarch64_cpu_get_aarch64,
                             aarch64_cpu_set_aarch64, NULL);
    object_property_set_description(obj, "aarch64",
                                    "Set on/off to enable/disable aarch64 "
                                    "execution state ",
                                    NULL);
}

static void aarch64_cpu_finalizefn(Object *obj)
{
}

static gchar *aarch64_gdb_arch_name(CPUState *cs)
{
    return g_strdup("aarch64");
}

#ifdef PPI_QR_FUNC
extern struct tracepid gtracepid;
#endif
static void aarch64_cpu_class_init(ObjectClass *oc, void *data)
{
#ifdef PPI_QR_FUNC
    int idx;
#endif
    CPUClass *cc = CPU_CLASS(oc);

    cc->cpu_exec_interrupt = arm_cpu_exec_interrupt;
    cc->gdb_read_register = aarch64_cpu_gdb_read_register;
    cc->gdb_write_register = aarch64_cpu_gdb_write_register;
    cc->gdb_num_core_regs = 34;
    cc->gdb_core_xml_file = "aarch64-core.xml";
    cc->gdb_arch_name = aarch64_gdb_arch_name;
#ifdef PPI_QR_FUNC
    for ( idx=0; idx<PPI_CORES; idx++ ){
    	gtracepid.po_app[idx] =  g_hash_table_new(g_int_hash,g_int_equal);
    	gtracepid.po_sys[idx] =  g_hash_table_new(g_int_hash,g_int_equal);
#ifdef PPI_QR_REG
	gtracepid.po_status[idx] = POS_INIT;
	gtracepid.po_stimes[idx] = 0;
    	gtracepid.po_reg[idx] =  g_hash_table_new(g_int_hash,g_int_equal);
#endif
    }
    pthread_mutex_init(&filter_mutex,NULL);
#ifdef _QR_Q_PIDMAP_
    pthread_mutex_init(&mutex,NULL);
#endif
#ifdef GET_PID_IMMEDIATE
    memset( gtracepid.po_need_getpid,0,PPI_CORES*sizeof(uint32_t));
#endif
#endif
}

static void aarch64_cpu_instance_init(Object *obj)
{
    ARMCPUClass *acc = ARM_CPU_GET_CLASS(obj);

    acc->info->initfn(obj);
    arm_cpu_post_init(obj);
}

static void cpu_register_class_init(ObjectClass *oc, void *data)
{
    ARMCPUClass *acc = ARM_CPU_CLASS(oc);

    acc->info = data;
}

static void aarch64_cpu_register(const ARMCPUInfo *info)
{
    TypeInfo type_info = {
        .parent = TYPE_AARCH64_CPU,
        .instance_size = sizeof(ARMCPU),
        .instance_init = aarch64_cpu_instance_init,
        .class_size = sizeof(ARMCPUClass),
        .class_init = info->class_init ?: cpu_register_class_init,
        .class_data = (void *)info,
    };

    type_info.name = g_strdup_printf("%s-" TYPE_ARM_CPU, info->name);
    type_register(&type_info);
    g_free((void *)type_info.name);
}

static const TypeInfo aarch64_cpu_type_info = {
    .name = TYPE_AARCH64_CPU,
    .parent = TYPE_ARM_CPU,
    .instance_size = sizeof(ARMCPU),
    .instance_init = aarch64_cpu_initfn,
    .instance_finalize = aarch64_cpu_finalizefn,
    .abstract = true,
    .class_size = sizeof(AArch64CPUClass),
    .class_init = aarch64_cpu_class_init,
};

static void aarch64_cpu_register_types(void)
{
    const ARMCPUInfo *info = aarch64_cpus;

    type_register_static(&aarch64_cpu_type_info);

    while (info->name) {
        aarch64_cpu_register(info);
        info++;
    }
}

type_init(aarch64_cpu_register_types)
