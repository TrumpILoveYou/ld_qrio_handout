/* **********************************************************
 * Copyright (c) 2010-2011 Google, Inc.  All rights reserved.
 * Copyright (c) 2002-2010 VMware, Inc.  All rights reserved.
 * **********************************************************/

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of VMware, Inc. nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL VMWARE, INC. OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#ifndef _DR_IR_OPCODES_AARCH64_H_
#define _DR_IR_OPCODES_AARCH64_H_ 1


/****************************************************************************
 * OPCODES
 */
/**
 * @file dr_ir_opcodes_aarch64.h
 * @brief Instruction opcode constants for AArch64.
 */
/** Opcode constants for use in the instr_t data structure. */
enum {
/*   0 */     OP_INVALID, /**< INVALID opcode */
/*   1 */     OP_UNDECODED, /**< UNDECODED opcode */
/*   2 */     OP_CONTD, /**< CONTD opcode */
/*   3 */     OP_LABEL, /**< LABEL opcode */

/*   4 */     OP_adc,             /**< AArch64 adc opcode.*/
/*   5 */     OP_adcs,            /**< AArch64 adcs opcode.*/
/*   6 */     OP_add,             /**< AArch64 add opcode.*/
/*   7 */     OP_addhn,           /**< AArch64 addhn opcode.*/
/*   8 */     OP_addhn2,          /**< AArch64 addhn2 opcode.*/
/*   9 */     OP_addp,            /**< AArch64 addp opcode.*/
/*  10 */     OP_adds,            /**< AArch64 adds opcode.*/
/*  11 */     OP_adr,             /**< AArch64 adr opcode.*/
/*  12 */     OP_adrp,            /**< AArch64 adrp opcode.*/
/*  13 */     OP_and,             /**< AArch64 and opcode.*/
/*  14 */     OP_ands,            /**< AArch64 ands opcode.*/
/*  15 */     OP_asrv,            /**< AArch64 asrv opcode.*/
/*  16 */     OP_b,               /**< AArch64 b opcode.*/
/*  17 */     OP_bcond,           /**< AArch64 bcond opcode.*/
/*  18 */     OP_bfm,             /**< AArch64 bfm opcode.*/
/*  19 */     OP_bic,             /**< AArch64 bic opcode.*/
/*  20 */     OP_bics,            /**< AArch64 bics opcode.*/
/*  21 */     OP_bif,             /**< AArch64 bif opcode.*/
/*  22 */     OP_bit,             /**< AArch64 bit opcode.*/
/*  23 */     OP_bl,              /**< AArch64 bl opcode.*/
/*  24 */     OP_blr,             /**< AArch64 blr opcode.*/
/*  25 */     OP_br,              /**< AArch64 br opcode.*/
/*  26 */     OP_brk,             /**< AArch64 brk opcode.*/
/*  27 */     OP_bsl,             /**< AArch64 bsl opcode.*/
/*  28 */     OP_cas,             /**< AArch64 cas opcode.*/
/*  29 */     OP_casa,            /**< AArch64 casa opcode.*/
/*  30 */     OP_casab,           /**< AArch64 casab opcode.*/
/*  31 */     OP_casah,           /**< AArch64 casah opcode.*/
/*  32 */     OP_casal,           /**< AArch64 casal opcode.*/
/*  33 */     OP_casalb,          /**< AArch64 casalb opcode.*/
/*  34 */     OP_casalh,          /**< AArch64 casalh opcode.*/
/*  35 */     OP_casb,            /**< AArch64 casb opcode.*/
/*  36 */     OP_cash,            /**< AArch64 cash opcode.*/
/*  37 */     OP_casl,            /**< AArch64 casl opcode.*/
/*  38 */     OP_caslb,           /**< AArch64 caslb opcode.*/
/*  39 */     OP_caslh,           /**< AArch64 caslh opcode.*/
/*  40 */     OP_casp,            /**< AArch64 casp opcode.*/
/*  41 */     OP_caspa,           /**< AArch64 caspa opcode.*/
/*  42 */     OP_caspal,          /**< AArch64 caspal opcode.*/
/*  43 */     OP_caspl,           /**< AArch64 caspl opcode.*/
/*  44 */     OP_cbnz,            /**< AArch64 cbnz opcode.*/
/*  45 */     OP_cbz,             /**< AArch64 cbz opcode.*/
/*  46 */     OP_ccmn,            /**< AArch64 ccmn opcode.*/
/*  47 */     OP_ccmp,            /**< AArch64 ccmp opcode.*/
/*  48 */     OP_clrex,           /**< AArch64 clrex opcode.*/
/*  49 */     OP_cls,             /**< AArch64 cls opcode.*/
/*  50 */     OP_clz,             /**< AArch64 clz opcode.*/
/*  51 */     OP_cmeq,            /**< AArch64 cmeq opcode.*/
/*  52 */     OP_cmge,            /**< AArch64 cmge opcode.*/
/*  53 */     OP_cmgt,            /**< AArch64 cmgt opcode.*/
/*  54 */     OP_cmhi,            /**< AArch64 cmhi opcode.*/
/*  55 */     OP_cmhs,            /**< AArch64 cmhs opcode.*/
/*  56 */     OP_cmtst,           /**< AArch64 cmtst opcode.*/
/*  57 */     OP_crc32b,          /**< AArch64 crc32b opcode.*/
/*  58 */     OP_crc32cb,         /**< AArch64 crc32cb opcode.*/
/*  59 */     OP_crc32ch,         /**< AArch64 crc32ch opcode.*/
/*  60 */     OP_crc32cw,         /**< AArch64 crc32cw opcode.*/
/*  61 */     OP_crc32cx,         /**< AArch64 crc32cx opcode.*/
/*  62 */     OP_crc32h,          /**< AArch64 crc32h opcode.*/
/*  63 */     OP_crc32w,          /**< AArch64 crc32w opcode.*/
/*  64 */     OP_crc32x,          /**< AArch64 crc32x opcode.*/
/*  65 */     OP_csel,            /**< AArch64 csel opcode.*/
/*  66 */     OP_csinc,           /**< AArch64 csinc opcode.*/
/*  67 */     OP_csinv,           /**< AArch64 csinv opcode.*/
/*  68 */     OP_csneg,           /**< AArch64 csneg opcode.*/
/*  69 */     OP_dmb,             /**< AArch64 dmb opcode.*/
/*  70 */     OP_dsb,             /**< AArch64 dsb opcode.*/
/*  71 */     OP_eon,             /**< AArch64 eon opcode.*/
/*  72 */     OP_eor,             /**< AArch64 eor opcode.*/
/*  73 */     OP_extr,            /**< AArch64 extr opcode.*/
/*  74 */     OP_fabd,            /**< AArch64 fabd opcode.*/
/*  75 */     OP_fabs,            /**< AArch64 fabs opcode.*/
/*  76 */     OP_facge,           /**< AArch64 facge opcode.*/
/*  77 */     OP_facgt,           /**< AArch64 facgt opcode.*/
/*  78 */     OP_fadd,            /**< AArch64 fadd opcode.*/
/*  79 */     OP_faddp,           /**< AArch64 faddp opcode.*/
/*  80 */     OP_fcmeq,           /**< AArch64 fcmeq opcode.*/
/*  81 */     OP_fcmge,           /**< AArch64 fcmge opcode.*/
/*  82 */     OP_fcmgt,           /**< AArch64 fcmgt opcode.*/
/*  83 */     OP_fcvt,            /**< AArch64 fcvt opcode.*/
/*  84 */     OP_fdiv,            /**< AArch64 fdiv opcode.*/
/*  85 */     OP_fmadd,           /**< AArch64 fmadd opcode.*/
/*  86 */     OP_fmax,            /**< AArch64 fmax opcode.*/
/*  87 */     OP_fmaxnm,          /**< AArch64 fmaxnm opcode.*/
/*  88 */     OP_fmaxnmp,         /**< AArch64 fmaxnmp opcode.*/
/*  89 */     OP_fmaxp,           /**< AArch64 fmaxp opcode.*/
/*  90 */     OP_fmin,            /**< AArch64 fmin opcode.*/
/*  91 */     OP_fminnm,          /**< AArch64 fminnm opcode.*/
/*  92 */     OP_fminnmp,         /**< AArch64 fminnmp opcode.*/
/*  93 */     OP_fminp,           /**< AArch64 fminp opcode.*/
/*  94 */     OP_fmla,            /**< AArch64 fmla opcode.*/
/*  95 */     OP_fmlal,           /**< AArch64 fmlal opcode.*/
/*  96 */     OP_fmlal2,          /**< AArch64 fmlal2 opcode.*/
/*  97 */     OP_fmls,            /**< AArch64 fmls opcode.*/
/*  98 */     OP_fmlsl,           /**< AArch64 fmlsl opcode.*/
/*  99 */     OP_fmlsl2,          /**< AArch64 fmlsl2 opcode.*/
/* 100 */     OP_fmov,            /**< AArch64 fmov opcode.*/
/* 101 */     OP_fmsub,           /**< AArch64 fmsub opcode.*/
/* 102 */     OP_fmul,            /**< AArch64 fmul opcode.*/
/* 103 */     OP_fmulx,           /**< AArch64 fmulx opcode.*/
/* 104 */     OP_fneg,            /**< AArch64 fneg opcode.*/
/* 105 */     OP_fnmadd,          /**< AArch64 fnmadd opcode.*/
/* 106 */     OP_fnmsub,          /**< AArch64 fnmsub opcode.*/
/* 107 */     OP_fnmul,           /**< AArch64 fnmul opcode.*/
/* 108 */     OP_frecps,          /**< AArch64 frecps opcode.*/
/* 109 */     OP_frinta,          /**< AArch64 frinta opcode.*/
/* 110 */     OP_frinti,          /**< AArch64 frinti opcode.*/
/* 111 */     OP_frintm,          /**< AArch64 frintm opcode.*/
/* 112 */     OP_frintn,          /**< AArch64 frintn opcode.*/
/* 113 */     OP_frintp,          /**< AArch64 frintp opcode.*/
/* 114 */     OP_frintx,          /**< AArch64 frintx opcode.*/
/* 115 */     OP_frintz,          /**< AArch64 frintz opcode.*/
/* 116 */     OP_frsqrts,         /**< AArch64 frsqrts opcode.*/
/* 117 */     OP_fsqrt,           /**< AArch64 fsqrt opcode.*/
/* 118 */     OP_fsub,            /**< AArch64 fsub opcode.*/
/* 119 */     OP_hlt,             /**< AArch64 hlt opcode.*/
/* 120 */     OP_hvc,             /**< AArch64 hvc opcode.*/
/* 121 */     OP_isb,             /**< AArch64 isb opcode.*/
/* 122 */     OP_ld1,             /**< AArch64 ld1 opcode.*/
/* 123 */     OP_ld1r,            /**< AArch64 ld1r opcode.*/
/* 124 */     OP_ld2,             /**< AArch64 ld2 opcode.*/
/* 125 */     OP_ld2r,            /**< AArch64 ld2r opcode.*/
/* 126 */     OP_ld3,             /**< AArch64 ld3 opcode.*/
/* 127 */     OP_ld3r,            /**< AArch64 ld3r opcode.*/
/* 128 */     OP_ld4,             /**< AArch64 ld4 opcode.*/
/* 129 */     OP_ld4r,            /**< AArch64 ld4r opcode.*/
/* 130 */     OP_ldadd,           /**< AArch64 ldadd opcode.*/
/* 131 */     OP_ldadda,          /**< AArch64 ldadda opcode.*/
/* 132 */     OP_ldaddab,         /**< AArch64 ldaddab opcode.*/
/* 133 */     OP_ldaddah,         /**< AArch64 ldaddah opcode.*/
/* 134 */     OP_ldaddal,         /**< AArch64 ldaddal opcode.*/
/* 135 */     OP_ldaddalb,        /**< AArch64 ldaddalb opcode.*/
/* 136 */     OP_ldaddalh,        /**< AArch64 ldaddalh opcode.*/
/* 137 */     OP_ldaddb,          /**< AArch64 ldaddb opcode.*/
/* 138 */     OP_ldaddh,          /**< AArch64 ldaddh opcode.*/
/* 139 */     OP_ldaddl,          /**< AArch64 ldaddl opcode.*/
/* 140 */     OP_ldaddlb,         /**< AArch64 ldaddlb opcode.*/
/* 141 */     OP_ldaddlh,         /**< AArch64 ldaddlh opcode.*/
/* 142 */     OP_ldar,            /**< AArch64 ldar opcode.*/
/* 143 */     OP_ldarb,           /**< AArch64 ldarb opcode.*/
/* 144 */     OP_ldarh,           /**< AArch64 ldarh opcode.*/
/* 145 */     OP_ldaxp,           /**< AArch64 ldaxp opcode.*/
/* 146 */     OP_ldaxr,           /**< AArch64 ldaxr opcode.*/
/* 147 */     OP_ldaxrb,          /**< AArch64 ldaxrb opcode.*/
/* 148 */     OP_ldaxrh,          /**< AArch64 ldaxrh opcode.*/
/* 149 */     OP_ldclr,           /**< AArch64 ldclr opcode.*/
/* 150 */     OP_ldclra,          /**< AArch64 ldclra opcode.*/
/* 151 */     OP_ldclrab,         /**< AArch64 ldclrab opcode.*/
/* 152 */     OP_ldclrah,         /**< AArch64 ldclrah opcode.*/
/* 153 */     OP_ldclral,         /**< AArch64 ldclral opcode.*/
/* 154 */     OP_ldclralb,        /**< AArch64 ldclralb opcode.*/
/* 155 */     OP_ldclralh,        /**< AArch64 ldclralh opcode.*/
/* 156 */     OP_ldclrb,          /**< AArch64 ldclrb opcode.*/
/* 157 */     OP_ldclrh,          /**< AArch64 ldclrh opcode.*/
/* 158 */     OP_ldclrl,          /**< AArch64 ldclrl opcode.*/
/* 159 */     OP_ldclrlb,         /**< AArch64 ldclrlb opcode.*/
/* 160 */     OP_ldclrlh,         /**< AArch64 ldclrlh opcode.*/
/* 161 */     OP_ldeor,           /**< AArch64 ldeor opcode.*/
/* 162 */     OP_ldeora,          /**< AArch64 ldeora opcode.*/
/* 163 */     OP_ldeorab,         /**< AArch64 ldeorab opcode.*/
/* 164 */     OP_ldeorah,         /**< AArch64 ldeorah opcode.*/
/* 165 */     OP_ldeoral,         /**< AArch64 ldeoral opcode.*/
/* 166 */     OP_ldeoralb,        /**< AArch64 ldeoralb opcode.*/
/* 167 */     OP_ldeoralh,        /**< AArch64 ldeoralh opcode.*/
/* 168 */     OP_ldeorb,          /**< AArch64 ldeorb opcode.*/
/* 169 */     OP_ldeorh,          /**< AArch64 ldeorh opcode.*/
/* 170 */     OP_ldeorl,          /**< AArch64 ldeorl opcode.*/
/* 171 */     OP_ldeorlb,         /**< AArch64 ldeorlb opcode.*/
/* 172 */     OP_ldeorlh,         /**< AArch64 ldeorlh opcode.*/
/* 173 */     OP_ldnp,            /**< AArch64 ldnp opcode.*/
/* 174 */     OP_ldp,             /**< AArch64 ldp opcode.*/
/* 175 */     OP_ldpsw,           /**< AArch64 ldpsw opcode.*/
/* 176 */     OP_ldr,             /**< AArch64 ldr opcode.*/
/* 177 */     OP_ldrb,            /**< AArch64 ldrb opcode.*/
/* 178 */     OP_ldrh,            /**< AArch64 ldrh opcode.*/
/* 179 */     OP_ldrsb,           /**< AArch64 ldrsb opcode.*/
/* 180 */     OP_ldrsh,           /**< AArch64 ldrsh opcode.*/
/* 181 */     OP_ldrsw,           /**< AArch64 ldrsw opcode.*/
/* 182 */     OP_ldset,           /**< AArch64 ldset opcode.*/
/* 183 */     OP_ldseta,          /**< AArch64 ldseta opcode.*/
/* 184 */     OP_ldsetab,         /**< AArch64 ldsetab opcode.*/
/* 185 */     OP_ldsetah,         /**< AArch64 ldsetah opcode.*/
/* 186 */     OP_ldsetal,         /**< AArch64 ldsetal opcode.*/
/* 187 */     OP_ldsetalb,        /**< AArch64 ldsetalb opcode.*/
/* 188 */     OP_ldsetalh,        /**< AArch64 ldsetalh opcode.*/
/* 189 */     OP_ldsetb,          /**< AArch64 ldsetb opcode.*/
/* 190 */     OP_ldseth,          /**< AArch64 ldseth opcode.*/
/* 191 */     OP_ldsetl,          /**< AArch64 ldsetl opcode.*/
/* 192 */     OP_ldsetlb,         /**< AArch64 ldsetlb opcode.*/
/* 193 */     OP_ldsetlh,         /**< AArch64 ldsetlh opcode.*/
/* 194 */     OP_ldsmax,          /**< AArch64 ldsmax opcode.*/
/* 195 */     OP_ldsmaxa,         /**< AArch64 ldsmaxa opcode.*/
/* 196 */     OP_ldsmaxab,        /**< AArch64 ldsmaxab opcode.*/
/* 197 */     OP_ldsmaxah,        /**< AArch64 ldsmaxah opcode.*/
/* 198 */     OP_ldsmaxal,        /**< AArch64 ldsmaxal opcode.*/
/* 199 */     OP_ldsmaxalb,       /**< AArch64 ldsmaxalb opcode.*/
/* 200 */     OP_ldsmaxalh,       /**< AArch64 ldsmaxalh opcode.*/
/* 201 */     OP_ldsmaxb,         /**< AArch64 ldsmaxb opcode.*/
/* 202 */     OP_ldsmaxh,         /**< AArch64 ldsmaxh opcode.*/
/* 203 */     OP_ldsmaxl,         /**< AArch64 ldsmaxl opcode.*/
/* 204 */     OP_ldsmaxlb,        /**< AArch64 ldsmaxlb opcode.*/
/* 205 */     OP_ldsmaxlh,        /**< AArch64 ldsmaxlh opcode.*/
/* 206 */     OP_ldsmin,          /**< AArch64 ldsmin opcode.*/
/* 207 */     OP_ldsmina,         /**< AArch64 ldsmina opcode.*/
/* 208 */     OP_ldsminab,        /**< AArch64 ldsminab opcode.*/
/* 209 */     OP_ldsminah,        /**< AArch64 ldsminah opcode.*/
/* 210 */     OP_ldsminal,        /**< AArch64 ldsminal opcode.*/
/* 211 */     OP_ldsminalb,       /**< AArch64 ldsminalb opcode.*/
/* 212 */     OP_ldsminalh,       /**< AArch64 ldsminalh opcode.*/
/* 213 */     OP_ldsminb,         /**< AArch64 ldsminb opcode.*/
/* 214 */     OP_ldsminh,         /**< AArch64 ldsminh opcode.*/
/* 215 */     OP_ldsminl,         /**< AArch64 ldsminl opcode.*/
/* 216 */     OP_ldsminlb,        /**< AArch64 ldsminlb opcode.*/
/* 217 */     OP_ldsminlh,        /**< AArch64 ldsminlh opcode.*/
/* 218 */     OP_ldtr,            /**< AArch64 ldtr opcode.*/
/* 219 */     OP_ldtrb,           /**< AArch64 ldtrb opcode.*/
/* 220 */     OP_ldtrh,           /**< AArch64 ldtrh opcode.*/
/* 221 */     OP_ldtrsb,          /**< AArch64 ldtrsb opcode.*/
/* 222 */     OP_ldtrsh,          /**< AArch64 ldtrsh opcode.*/
/* 223 */     OP_ldtrsw,          /**< AArch64 ldtrsw opcode.*/
/* 224 */     OP_ldumax,          /**< AArch64 ldumax opcode.*/
/* 225 */     OP_ldumaxa,         /**< AArch64 ldumaxa opcode.*/
/* 226 */     OP_ldumaxab,        /**< AArch64 ldumaxab opcode.*/
/* 227 */     OP_ldumaxah,        /**< AArch64 ldumaxah opcode.*/
/* 228 */     OP_ldumaxal,        /**< AArch64 ldumaxal opcode.*/
/* 229 */     OP_ldumaxalb,       /**< AArch64 ldumaxalb opcode.*/
/* 230 */     OP_ldumaxalh,       /**< AArch64 ldumaxalh opcode.*/
/* 231 */     OP_ldumaxb,         /**< AArch64 ldumaxb opcode.*/
/* 232 */     OP_ldumaxh,         /**< AArch64 ldumaxh opcode.*/
/* 233 */     OP_ldumaxl,         /**< AArch64 ldumaxl opcode.*/
/* 234 */     OP_ldumaxlb,        /**< AArch64 ldumaxlb opcode.*/
/* 235 */     OP_ldumaxlh,        /**< AArch64 ldumaxlh opcode.*/
/* 236 */     OP_ldumin,          /**< AArch64 ldumin opcode.*/
/* 237 */     OP_ldumina,         /**< AArch64 ldumina opcode.*/
/* 238 */     OP_lduminab,        /**< AArch64 lduminab opcode.*/
/* 239 */     OP_lduminah,        /**< AArch64 lduminah opcode.*/
/* 240 */     OP_lduminal,        /**< AArch64 lduminal opcode.*/
/* 241 */     OP_lduminalb,       /**< AArch64 lduminalb opcode.*/
/* 242 */     OP_lduminalh,       /**< AArch64 lduminalh opcode.*/
/* 243 */     OP_lduminb,         /**< AArch64 lduminb opcode.*/
/* 244 */     OP_lduminh,         /**< AArch64 lduminh opcode.*/
/* 245 */     OP_lduminl,         /**< AArch64 lduminl opcode.*/
/* 246 */     OP_lduminlb,        /**< AArch64 lduminlb opcode.*/
/* 247 */     OP_lduminlh,        /**< AArch64 lduminlh opcode.*/
/* 248 */     OP_ldur,            /**< AArch64 ldur opcode.*/
/* 249 */     OP_ldurb,           /**< AArch64 ldurb opcode.*/
/* 250 */     OP_ldurh,           /**< AArch64 ldurh opcode.*/
/* 251 */     OP_ldursb,          /**< AArch64 ldursb opcode.*/
/* 252 */     OP_ldursh,          /**< AArch64 ldursh opcode.*/
/* 253 */     OP_ldursw,          /**< AArch64 ldursw opcode.*/
/* 254 */     OP_ldxp,            /**< AArch64 ldxp opcode.*/
/* 255 */     OP_ldxr,            /**< AArch64 ldxr opcode.*/
/* 256 */     OP_ldxrb,           /**< AArch64 ldxrb opcode.*/
/* 257 */     OP_ldxrh,           /**< AArch64 ldxrh opcode.*/
/* 258 */     OP_lslv,            /**< AArch64 lslv opcode.*/
/* 259 */     OP_lsrv,            /**< AArch64 lsrv opcode.*/
/* 260 */     OP_madd,            /**< AArch64 madd opcode.*/
/* 261 */     OP_mla,             /**< AArch64 mla opcode.*/
/* 262 */     OP_mls,             /**< AArch64 mls opcode.*/
/* 263 */     OP_movk,            /**< AArch64 movk opcode.*/
/* 264 */     OP_movn,            /**< AArch64 movn opcode.*/
/* 265 */     OP_movz,            /**< AArch64 movz opcode.*/
/* 266 */     OP_mrs,             /**< AArch64 mrs opcode.*/
/* 267 */     OP_msr,             /**< AArch64 msr opcode.*/
/* 268 */     OP_msub,            /**< AArch64 msub opcode.*/
/* 269 */     OP_mul,             /**< AArch64 mul opcode.*/
/* 270 */     OP_nop,             /**< AArch64 nop opcode.*/
/* 271 */     OP_orn,             /**< AArch64 orn opcode.*/
/* 272 */     OP_orr,             /**< AArch64 orr opcode.*/
/* 273 */     OP_pmul,            /**< AArch64 pmul opcode.*/
/* 274 */     OP_pmull,           /**< AArch64 pmull opcode.*/
/* 275 */     OP_pmull2,          /**< AArch64 pmull2 opcode.*/
/* 276 */     OP_prfm,            /**< AArch64 prfm opcode.*/
/* 277 */     OP_prfum,           /**< AArch64 prfum opcode.*/
/* 278 */     OP_raddhn,          /**< AArch64 raddhn opcode.*/
/* 279 */     OP_raddhn2,         /**< AArch64 raddhn2 opcode.*/
/* 280 */     OP_rbit,            /**< AArch64 rbit opcode.*/
/* 281 */     OP_ret,             /**< AArch64 ret opcode.*/
/* 282 */     OP_rev,             /**< AArch64 rev opcode.*/
/* 283 */     OP_rev16,           /**< AArch64 rev16 opcode.*/
/* 284 */     OP_rev32,           /**< AArch64 rev32 opcode.*/
/* 285 */     OP_rorv,            /**< AArch64 rorv opcode.*/
/* 286 */     OP_rsubhn,          /**< AArch64 rsubhn opcode.*/
/* 287 */     OP_rsubhn2,         /**< AArch64 rsubhn2 opcode.*/
/* 288 */     OP_saba,            /**< AArch64 saba opcode.*/
/* 289 */     OP_sabal,           /**< AArch64 sabal opcode.*/
/* 290 */     OP_sabal2,          /**< AArch64 sabal2 opcode.*/
/* 291 */     OP_sabd,            /**< AArch64 sabd opcode.*/
/* 292 */     OP_sabdl,           /**< AArch64 sabdl opcode.*/
/* 293 */     OP_sabdl2,          /**< AArch64 sabdl2 opcode.*/
/* 294 */     OP_saddl,           /**< AArch64 saddl opcode.*/
/* 295 */     OP_saddl2,          /**< AArch64 saddl2 opcode.*/
/* 296 */     OP_saddw,           /**< AArch64 saddw opcode.*/
/* 297 */     OP_saddw2,          /**< AArch64 saddw2 opcode.*/
/* 298 */     OP_sbc,             /**< AArch64 sbc opcode.*/
/* 299 */     OP_sbcs,            /**< AArch64 sbcs opcode.*/
/* 300 */     OP_sbfm,            /**< AArch64 sbfm opcode.*/
/* 301 */     OP_sdiv,            /**< AArch64 sdiv opcode.*/
/* 302 */     OP_sev,             /**< AArch64 sev opcode.*/
/* 303 */     OP_sevl,            /**< AArch64 sevl opcode.*/
/* 304 */     OP_shadd,           /**< AArch64 shadd opcode.*/
/* 305 */     OP_shsub,           /**< AArch64 shsub opcode.*/
/* 306 */     OP_smaddl,          /**< AArch64 smaddl opcode.*/
/* 307 */     OP_smax,            /**< AArch64 smax opcode.*/
/* 308 */     OP_smaxp,           /**< AArch64 smaxp opcode.*/
/* 309 */     OP_smc,             /**< AArch64 smc opcode.*/
/* 310 */     OP_smin,            /**< AArch64 smin opcode.*/
/* 311 */     OP_sminp,           /**< AArch64 sminp opcode.*/
/* 312 */     OP_smlal,           /**< AArch64 smlal opcode.*/
/* 313 */     OP_smlal2,          /**< AArch64 smlal2 opcode.*/
/* 314 */     OP_smlsl,           /**< AArch64 smlsl opcode.*/
/* 315 */     OP_smlsl2,          /**< AArch64 smlsl2 opcode.*/
/* 316 */     OP_smsubl,          /**< AArch64 smsubl opcode.*/
/* 317 */     OP_smulh,           /**< AArch64 smulh opcode.*/
/* 318 */     OP_smull,           /**< AArch64 smull opcode.*/
/* 319 */     OP_smull2,          /**< AArch64 smull2 opcode.*/
/* 320 */     OP_sqadd,           /**< AArch64 sqadd opcode.*/
/* 321 */     OP_sqdmlal,         /**< AArch64 sqdmlal opcode.*/
/* 322 */     OP_sqdmlal2,        /**< AArch64 sqdmlal2 opcode.*/
/* 323 */     OP_sqdmlsl,         /**< AArch64 sqdmlsl opcode.*/
/* 324 */     OP_sqdmlsl2,        /**< AArch64 sqdmlsl2 opcode.*/
/* 325 */     OP_sqdmulh,         /**< AArch64 sqdmulh opcode.*/
/* 326 */     OP_sqdmull,         /**< AArch64 sqdmull opcode.*/
/* 327 */     OP_sqdmull2,        /**< AArch64 sqdmull2 opcode.*/
/* 328 */     OP_sqrdmulh,        /**< AArch64 sqrdmulh opcode.*/
/* 329 */     OP_sqrshl,          /**< AArch64 sqrshl opcode.*/
/* 330 */     OP_sqshl,           /**< AArch64 sqshl opcode.*/
/* 331 */     OP_sqsub,           /**< AArch64 sqsub opcode.*/
/* 332 */     OP_srhadd,          /**< AArch64 srhadd opcode.*/
/* 333 */     OP_srshl,           /**< AArch64 srshl opcode.*/
/* 334 */     OP_sshl,            /**< AArch64 sshl opcode.*/
/* 335 */     OP_ssubl,           /**< AArch64 ssubl opcode.*/
/* 336 */     OP_ssubl2,          /**< AArch64 ssubl2 opcode.*/
/* 337 */     OP_ssubw,           /**< AArch64 ssubw opcode.*/
/* 338 */     OP_ssubw2,          /**< AArch64 ssubw2 opcode.*/
/* 339 */     OP_st1,             /**< AArch64 st1 opcode.*/
/* 340 */     OP_st2,             /**< AArch64 st2 opcode.*/
/* 341 */     OP_st3,             /**< AArch64 st3 opcode.*/
/* 342 */     OP_st4,             /**< AArch64 st4 opcode.*/
/* 343 */     OP_stlr,            /**< AArch64 stlr opcode.*/
/* 344 */     OP_stlrb,           /**< AArch64 stlrb opcode.*/
/* 345 */     OP_stlrh,           /**< AArch64 stlrh opcode.*/
/* 346 */     OP_stlxp,           /**< AArch64 stlxp opcode.*/
/* 347 */     OP_stlxr,           /**< AArch64 stlxr opcode.*/
/* 348 */     OP_stlxrb,          /**< AArch64 stlxrb opcode.*/
/* 349 */     OP_stlxrh,          /**< AArch64 stlxrh opcode.*/
/* 350 */     OP_stnp,            /**< AArch64 stnp opcode.*/
/* 351 */     OP_stp,             /**< AArch64 stp opcode.*/
/* 352 */     OP_str,             /**< AArch64 str opcode.*/
/* 353 */     OP_strb,            /**< AArch64 strb opcode.*/
/* 354 */     OP_strh,            /**< AArch64 strh opcode.*/
/* 355 */     OP_sttr,            /**< AArch64 sttr opcode.*/
/* 356 */     OP_sttrb,           /**< AArch64 sttrb opcode.*/
/* 357 */     OP_sttrh,           /**< AArch64 sttrh opcode.*/
/* 358 */     OP_stur,            /**< AArch64 stur opcode.*/
/* 359 */     OP_sturb,           /**< AArch64 sturb opcode.*/
/* 360 */     OP_sturh,           /**< AArch64 sturh opcode.*/
/* 361 */     OP_stxp,            /**< AArch64 stxp opcode.*/
/* 362 */     OP_stxr,            /**< AArch64 stxr opcode.*/
/* 363 */     OP_stxrb,           /**< AArch64 stxrb opcode.*/
/* 364 */     OP_stxrh,           /**< AArch64 stxrh opcode.*/
/* 365 */     OP_sub,             /**< AArch64 sub opcode.*/
/* 366 */     OP_subhn,           /**< AArch64 subhn opcode.*/
/* 367 */     OP_subhn2,          /**< AArch64 subhn2 opcode.*/
/* 368 */     OP_subs,            /**< AArch64 subs opcode.*/
/* 369 */     OP_svc,             /**< AArch64 svc opcode.*/
/* 370 */     OP_swp,             /**< AArch64 swp opcode.*/
/* 371 */     OP_swpa,            /**< AArch64 swpa opcode.*/
/* 372 */     OP_swpab,           /**< AArch64 swpab opcode.*/
/* 373 */     OP_swpah,           /**< AArch64 swpah opcode.*/
/* 374 */     OP_swpal,           /**< AArch64 swpal opcode.*/
/* 375 */     OP_swpalb,          /**< AArch64 swpalb opcode.*/
/* 376 */     OP_swpalh,          /**< AArch64 swpalh opcode.*/
/* 377 */     OP_swpb,            /**< AArch64 swpb opcode.*/
/* 378 */     OP_swph,            /**< AArch64 swph opcode.*/
/* 379 */     OP_swpl,            /**< AArch64 swpl opcode.*/
/* 380 */     OP_swplb,           /**< AArch64 swplb opcode.*/
/* 381 */     OP_swplh,           /**< AArch64 swplh opcode.*/
/* 382 */     OP_sys,             /**< AArch64 sys opcode.*/
/* 383 */     OP_tbnz,            /**< AArch64 tbnz opcode.*/
/* 384 */     OP_tbz,             /**< AArch64 tbz opcode.*/
/* 385 */     OP_uaba,            /**< AArch64 uaba opcode.*/
/* 386 */     OP_uabal,           /**< AArch64 uabal opcode.*/
/* 387 */     OP_uabal2,          /**< AArch64 uabal2 opcode.*/
/* 388 */     OP_uabd,            /**< AArch64 uabd opcode.*/
/* 389 */     OP_uabdl,           /**< AArch64 uabdl opcode.*/
/* 390 */     OP_uabdl2,          /**< AArch64 uabdl2 opcode.*/
/* 391 */     OP_uaddl,           /**< AArch64 uaddl opcode.*/
/* 392 */     OP_uaddl2,          /**< AArch64 uaddl2 opcode.*/
/* 393 */     OP_uaddw,           /**< AArch64 uaddw opcode.*/
/* 394 */     OP_uaddw2,          /**< AArch64 uaddw2 opcode.*/
/* 395 */     OP_ubfm,            /**< AArch64 ubfm opcode.*/
/* 396 */     OP_udiv,            /**< AArch64 udiv opcode.*/
/* 397 */     OP_uhadd,           /**< AArch64 uhadd opcode.*/
/* 398 */     OP_uhsub,           /**< AArch64 uhsub opcode.*/
/* 399 */     OP_umaddl,          /**< AArch64 umaddl opcode.*/
/* 400 */     OP_umax,            /**< AArch64 umax opcode.*/
/* 401 */     OP_umaxp,           /**< AArch64 umaxp opcode.*/
/* 402 */     OP_umin,            /**< AArch64 umin opcode.*/
/* 403 */     OP_uminp,           /**< AArch64 uminp opcode.*/
/* 404 */     OP_umlal,           /**< AArch64 umlal opcode.*/
/* 405 */     OP_umlal2,          /**< AArch64 umlal2 opcode.*/
/* 406 */     OP_umlsl,           /**< AArch64 umlsl opcode.*/
/* 407 */     OP_umlsl2,          /**< AArch64 umlsl2 opcode.*/
/* 408 */     OP_umsubl,          /**< AArch64 umsubl opcode.*/
/* 409 */     OP_umulh,           /**< AArch64 umulh opcode.*/
/* 410 */     OP_umull,           /**< AArch64 umull opcode.*/
/* 411 */     OP_umull2,          /**< AArch64 umull2 opcode.*/
/* 412 */     OP_uqadd,           /**< AArch64 uqadd opcode.*/
/* 413 */     OP_uqrshl,          /**< AArch64 uqrshl opcode.*/
/* 414 */     OP_uqshl,           /**< AArch64 uqshl opcode.*/
/* 415 */     OP_uqsub,           /**< AArch64 uqsub opcode.*/
/* 416 */     OP_urhadd,          /**< AArch64 urhadd opcode.*/
/* 417 */     OP_urshl,           /**< AArch64 urshl opcode.*/
/* 418 */     OP_ushl,            /**< AArch64 ushl opcode.*/
/* 419 */     OP_usubl,           /**< AArch64 usubl opcode.*/
/* 420 */     OP_usubl2,          /**< AArch64 usubl2 opcode.*/
/* 421 */     OP_usubw,           /**< AArch64 usubw opcode.*/
/* 422 */     OP_usubw2,          /**< AArch64 usubw2 opcode.*/
/* 423 */     OP_wfe,             /**< AArch64 wfe opcode.*/
/* 424 */     OP_wfi,             /**< AArch64 wfi opcode.*/
/* 425 */     OP_yield,           /**< AArch64 yield opcode.*/

    OP_ldstex,
    OP_xx,

    OP_AFTER_LAST,
    OP_FIRST = OP_LABEL + 1,      /**< First real opcode. */
    OP_LAST  = OP_AFTER_LAST - 1, /**< Last real opcode. */
};

/* alternative names */
#define OP_jmp       OP_b      /**< Platform-independent opcode name for jump. */
#define OP_jmp_short OP_b      /**< Platform-independent opcode name for short jump. */
#define OP_load      OP_ldr    /**< Platform-independent opcode name for load. */
#define OP_store     OP_str    /**< Platform-independent opcode name for store. */

/****************************************************************************/



#endif /* _DR_IR_OPCODES_AARCH64_H_ */
