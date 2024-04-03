/*
 *  ARM pids
 *
 *  Copyright (c) 2003 Fabrice Bellard
 *  Copyright (c) 2005-2007 CodeSourcery
 *  Copyright (c) 2007 OpenedHand, Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include "qemu/osdep.h"

#include "cpu.h"
#include "internals.h"
#include "disas/disas.h"
#include "exec/exec-all.h"
#include "tcg-op.h"
#include "tcg-op-gvec.h"
#include "qemu/log.h"
#include "qemu/bitops.h"
#include "arm_ldst.h"
#include "hw/semihosting/semihost.h"

#include "exec/helper-proto.h"
#include "exec/helper-gen.h"

#include "trace-tcg.h"
#include "exec/log.h"

#include "translate.h"

#include "exec/qr_head.h"


#ifdef TEST5
#define HAVE_NS_LEVEL
#define TASK_PIDS_PID (976)
#define PID_LEVEL_OFF (4)
#define NS_LEVEL_OFF (2096)
#define PIDLINK_SZ  (24)
#define PIDLINK_PID_OFF (16)
#define PID_NUMBER_OFF (48)
#define SZ_UPID (32)
#define group_leader_off (920)
#define PIDLINK_PID_OFF (16)
#define PIDLINK_SZ  (24)
#define HAVE_NS_LEVEL /* use ns->level, slow */
#endif

#ifdef  LINUX5
#define HAVE_NS_LEVEL
#define TASK_PIDS_PID (976)
#define PID_LEVEL_OFF (4)
#define NS_LEVEL_OFF (2096)
#define PIDLINK_SZ  (24)
#define PIDLINK_PID_OFF (16)
#define PID_NUMBER_OFF (48)
#define SZ_UPID (32)
#define NR_UPID (48)
#define group_leader_off (920)
#define PIDLINK_PID_OFF (16)
#define PIDLINK_SZ  (24)
#define HAVE_NS_LEVEL /* use ns->level, slow */
#endif

#ifdef  UBUNTU4
#define TASK_PIDS_PID (1168)  /* with LINK_PID_OFF */
#define PID_LEVEL_OFF (4)
#define NS_LEVEL_OFF (2096)
#define PIDLINK_SZ  (24)
#define PIDLINK_PID_OFF (16)
#define PID_NUMBER_OFF (48)
#define SZ_UPID (32)
#define NR_UPID (48)
#define group_leader_off (1112)
#endif

extern int i_idx;

static uint64_t task_active_pid_ns( CPUState *cpu,uint64_t task)
{
    uint32_t pid_level;
    uint64_t pid_struct,ns_struct;

    /* task->pids[PIDTYPE_PID].pid */
    cpu_memory_rw_debug(cpu, (task+TASK_PIDS_PID+PIDLINK_PID_OFF), (uint8_t *)&pid_struct, 8, 0);
    pid_struct = bswap64(pid_struct);

    /* get pid_level */
    cpu_memory_rw_debug(cpu, (pid_struct+PID_LEVEL_OFF), (uint8_t *)&pid_level, 4, 0);
    pid_level = bswap32(pid_level);

    /* ns = pid + off + pid->level*sz  */
    cpu_memory_rw_debug(cpu, (pid_struct+PID_NUMBER_OFF+pid_level*SZ_UPID), (uint8_t *)&ns_struct, 8, 0);
    ns_struct = bswap64(ns_struct);

    return ns_struct;
}

#ifdef LINUX5
static uint32_t pid_nr_ns( CPUState *cpu,uint64_t pid, uint64_t ns)
{
    uint32_t pid_level=0,nr=0,ns_level;

    /* get pid_level */
    cpu_memory_rw_debug(cpu, (pid+PID_LEVEL_OFF), (uint8_t *)&pid_level, 4, 0);
    pid_level = bswap32(pid_level);

    /* get ns_level */
    cpu_memory_rw_debug(cpu, (ns+NS_LEVEL_OFF), (uint8_t *)&ns_level, 4, 0);
    ns_level = bswap32(ns_level);

    /* nr = pid->numbers[ns->level].nr  */
    cpu_memory_rw_debug(cpu, (pid+PID_NUMBER_OFF+ns_level*SZ_UPID+NR_UPID), (uint8_t *)&nr, 4, 0);
    nr = bswap32(nr);

    /*
    if ( i_idx <200 ) {
        i_idx ++;
        printf("pid[%#lx] nsl[%d] nr[%d]\n",pid,ns_level,nr);
    }
    */

    return nr;

}
#endif

int task_pid_vnr(CPUARMState *env,uint64_t task, int type);
int task_pid_vnr(CPUARMState *env,uint64_t task, int type)
{
    uint32_t nr=0;
    uint64_t ns_active,pid_struct,task_nr;
    CPUState *cpu = env_cpu(env);

#ifdef LINUX5
    ns_active = task_active_pid_ns(cpu,task);
#endif

    if (type != PIDTYPE_PID){
    	cpu_memory_rw_debug(cpu, (task+group_leader_off), (uint8_t *)&task_nr, 8, 0);
#ifdef LINUX5
    	task_nr = bswap64(task_nr);
#endif
    } else {
	task_nr = task;
    }
    /* task->pids[type=PIDTYPE_PID].pid */
#ifdef LINUX5
    cpu_memory_rw_debug(cpu, (task_nr+TASK_PIDS_PID+type*PIDLINK_SZ),
		    (uint8_t *)&pid_struct, 8, 0);
    pid_struct = bswap64(pid_struct);
    nr = pid_nr_ns(cpu,pid_struct,ns_active);
#else
    /* get ns_level */
    uint32_t ns_level=0;
    //cpu_memory_rw_debug(cpu, (ns_active+NS_LEVEL_OFF), (uint8_t *)&ns_level, 4, 0);
    cpu_memory_rw_debug(cpu, (task_nr+TASK_PIDS_PID), (uint8_t *)&pid_struct, 8, 0);
    cpu_memory_rw_debug(cpu, (pid_struct+PID_NUMBER_OFF+ns_level*SZ_UPID), (uint8_t *)&nr, 4, 0);
#endif


    /*
    if ( i_idx <200 ) {
        printf("task[%#lx] pid[%#lx] \n",task,pid_struct);
    }
    */


    return nr;
}
