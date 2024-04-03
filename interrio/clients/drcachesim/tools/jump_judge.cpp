/* **********************************************************
 * Copyright (c) 2017-2019 Google, Inc.  All rights reserved.
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
 * * Neither the name of Google, Inc. nor the names of its contributors may be
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

#include "dr_api.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string.h>
#include <stdint.h>
#include "jump_judge.h"
#include "../common/utils.h"
#include "ipc_reader.h"
#include "decode_opcode.h"

using namespace std;
bool judge = 0;
int branch_opc = 0;
int jump_flag = 0;
unsigned long src_pc = 0;
unsigned long des_pc = 0;

static unsigned long one_pre_cnt_core[16] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0 };
static unsigned long two_pre_cnt_core[16] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0 };

static unsigned long one_pre_usr = 1;
static unsigned long two_pre_usr = 3;
static unsigned long one_pre_cnt_usr = 0;
static unsigned long two_pre_cnt_usr = 0;

static unsigned long one_pre_sys = 1;
static unsigned long two_pre_sys = 3;
static unsigned long one_pre_cnt_sys = 0;
static unsigned long two_pre_cnt_sys = 0;

static unsigned long two_level_cnt = 0;
static unsigned long tables[256];
static unsigned long local_predictor = 0;
static unsigned char history_vector = 0;
const std::string jump_judge_t::TOOL_NAME = "Jump judge tool";
struct bht_node {
    int tid;
    int one_pre;
    unsigned long src_pc;
    int two_pre;
    unsigned long des_pc;
    bht_node()
    {
        one_pre = 1;
        two_pre = 3;
        src_pc = 0;
        des_pc = 0;
    }
};
#define BHT_SIZE 256
// struct bht_node bht[256];
vector<bht_node> bht;

analysis_tool_t *
jump_judge_tool_create(unsigned int verbose)
{
    return new jump_judge_t(verbose);
}

jump_judge_t::jump_judge_t(unsigned int verbose)
    : knob_verbose_(verbose)
{
    // Empty.
}

jump_judge_t::~jump_judge_t()
{
    for (auto &iter : shard_map_) {
        delete iter.second;
    }
}

bool
jump_judge_t::parallel_shard_supported()
{
    return true;
}

void *
jump_judge_t::parallel_shard_init(int shard_index, void *worker_data)
{
    auto counters = new counters_t;
    std::lock_guard<std::mutex> guard(shard_map_mutex_);
    shard_map_[shard_index] = counters;
    return reinterpret_cast<void *>(counters);
}

bool
jump_judge_t::parallel_shard_exit(void *shard_data)
{
    // Nothing (we read the shard data in print_results).
    return true;
}

std::string
jump_judge_t::parallel_shard_error(void *shard_data)
{
    counters_t *counters = reinterpret_cast<counters_t *>(shard_data);
    return counters->error;
}

void
two_level_predictor(bool judge)
{
    local_predictor = tables[history_vector];
    if (local_predictor != judge) {
        two_level_cnt++;
        tables[(unsigned long)history_vector] = judge;
    }
    history_vector = (unsigned char)((history_vector << 1) | (judge & 0x1)) & 0xFF;
}

bool
travel_bht(int core, unsigned long src, unsigned long des)
{
    for (vector<bht_node>::iterator iter = bht.begin(); iter != bht.end(); ++iter) {
        if (src == iter->src_pc && core == iter->tid) {
            iter->des_pc = des;
            if (judge) {
                if (iter->one_pre != 1)
                    one_pre_cnt_core[core]++;
                iter->one_pre = 1;
                if (iter->two_pre < 2) {
                    two_pre_cnt_core[core]++;
                    iter->two_pre++;
                }
                if (iter->two_pre == 2) {
                    iter->two_pre++;
                }
            }
            if (!judge) {
                if (iter->one_pre == 1)
                    one_pre_cnt_core[core]++;
                iter->one_pre = 0;
                if (iter->two_pre > 1) {
                    two_pre_cnt_core[core]++;
                    iter->two_pre--;
                }
                if (iter->two_pre == 1) {
                    iter->two_pre--;
                }
            }
            return true;
        }
    }
    return false;
}
void
dobranch_core(bool judge, int core, unsigned long src, unsigned long des)
{
    if (bht.size() <= BHT_SIZE) {
        if (travel_bht(core, src, des)) {

        } else {
            struct bht_node bn;
            bn.tid = core;
            bn.src_pc = src;
            bn.des_pc = des;
            if (!judge) {
                one_pre_cnt_core[core]++;
                bn.one_pre = 0;
                two_pre_cnt_core[core]++;
                bn.two_pre--;
            }

            bht.push_back(bn);
        }
    }
    if (bht.size() == BHT_SIZE + 1) {
        vector<bht_node>::iterator k = bht.begin();
        bht.erase(k);
    }
}
void
dobranch_usr(bool judge)
{
    if (judge) {
        if (one_pre_usr != 1)
            one_pre_cnt_usr++;
        one_pre_usr = 1;
        if (two_pre_usr < 2) {
            two_pre_cnt_usr++;
            two_pre_usr++;
        }
        if (two_pre_usr == 2) {
            two_pre_usr++;
        }
    }
    if (!judge) {
        if (one_pre_usr == 1)
            one_pre_cnt_usr++;
        one_pre_usr = 0;
        if (two_pre_usr > 1) {
            two_pre_cnt_usr++;
            two_pre_usr--;
        }
        if (two_pre_usr == 1) {
            two_pre_usr--;
        }
    }
}
void
dobranch_sys(bool judge)
{
    if (judge) {
        if (one_pre_sys != 1)
            one_pre_cnt_sys++;
        one_pre_sys = 1;
        if (two_pre_sys < 2) {
            two_pre_cnt_sys++;
            two_pre_sys++;
        }
        if (two_pre_sys == 2) {
            two_pre_sys++;
        }
    }
    if (!judge) {
        if (one_pre_sys == 1)
            one_pre_cnt_sys++;
        one_pre_sys = 0;
        if (two_pre_sys > 1) {
            two_pre_cnt_sys++;
            two_pre_sys--;
        }
        if (two_pre_sys == 1) {
            two_pre_sys--;
        }
    }
}
bool
jump_judge_t::parallel_shard_memref(void *shard_data, const memref_t &memref)
{
    counters_t *counters = reinterpret_cast<counters_t *>(shard_data);
    if (type_is_instr(memref.instr.type)) {
        ++counters->instrs;
        counters->unique_pc_addrs.insert(memref.instr.addr);
    } else if (memref.data.type == TRACE_TYPE_THREAD_EXIT) {
        counters->tid = memref.exit.tid;
    }

    if (!type_is_instr(memref.instr.type) &&
        memref.data.type != TRACE_TYPE_INSTR_NO_FETCH) {
        return true;
    }

    ++counters->instr_count;
    if (memref.instr.el_type == 0)
        ++counters->instr_count_usr;
    else
        ++counters->instr_count_sys;

    if ((memref.instr.is_bb_end == 2 || memref.instr.is_bb_end == 3) && jump_flag == 1) {
        des_pc = memref.instr.pc;
        // if (memref.instr.el_type == 0)
        //     printf("%016lx:%016lx-%dT%d|\n", src_pc, des_pc, branch_opc,
        //     memref.data.tid);
        if (des_pc < src_pc) {
            ++counters->backwardBranch_count;
            if (memref.instr.el_type == 0)
                ++counters->backwardBranch_count_usr;
            else
                ++counters->backwardBranch_count_sys;
        }
        if (des_pc > src_pc + 4) {
            ++counters->forwardBranch_count;
            if (memref.instr.el_type == 0)
                ++counters->forwardBranch_count_usr;
            else
                ++counters->forwardBranch_count_sys;
        }
        if (des_pc == src_pc + 4) {
            judge = 0;
        } else {
            judge = 1;
        }
        // dobranch(judge);
        if (memref.instr.el_type == 0)
            dobranch_usr(judge);
        else
            dobranch_sys(judge);
        if (memref.instr.el_type == 0)
            dobranch_core(judge, memref.instr.tid, src_pc, des_pc);

        jump_flag = 0;
    }
    // printf("core = %d\n",memref.instr.tid);

    app_pc mapped_pc;

    const app_pc trace_pc = reinterpret_cast<app_pc>(memref.instr.addr);
    mapped_pc = trace_pc;

    int opcode = decode_opcode(*(uint *)mapped_pc);
    switch (opcode) {
    case 16:
        ++counters->branch_count;
        ++counters->b_count;
        if (memref.instr.el_type == 0) {
            ++counters->branch_count_usr;
            ++counters->b_count_usr;
            src_pc = memref.instr.pc;
        } else {
            ++counters->branch_count_sys;
            ++counters->b_count_sys;
        }

        jump_flag = 1;
        branch_opc = 16;
        break;
    case 17:
        ++counters->branch_count;
        ++counters->bcond_count;
        if (memref.instr.el_type == 0) {
            ++counters->branch_count_usr;
            ++counters->bcond_count_usr;
            src_pc = memref.instr.pc;
        } else {
            ++counters->branch_count_sys;
            ++counters->bcond_count_sys;
        }

        jump_flag = 1;
        branch_opc = 17;
        break;
    case 23:
        ++counters->branch_count;
        ++counters->bl_count;
        if (memref.instr.el_type == 0) {
            ++counters->branch_count_usr;
            ++counters->bl_count_usr;
            src_pc = memref.instr.pc;
        } else {
            ++counters->branch_count_sys;
            ++counters->bl_count_sys;
        }
        jump_flag = 1;
        branch_opc = 23;
        break;
    case 24:
        ++counters->branch_count;
        ++counters->blr_count;
        if (memref.instr.el_type == 0) {
            ++counters->branch_count_usr;
            ++counters->blr_count_usr;
            src_pc = memref.instr.pc;
        } else {
            ++counters->branch_count_sys;
            ++counters->blr_count_sys;
        }
        jump_flag = 1;
        branch_opc = 24;
        break;
    case 25:
        ++counters->branch_count;
        ++counters->br_count;
        if (memref.instr.el_type == 0) {
            ++counters->branch_count_usr;
            ++counters->br_count_usr;
            src_pc = memref.instr.pc;
        } else {
            ++counters->branch_count_sys;
            ++counters->br_count_sys;
        }
        jump_flag = 1;
        branch_opc = 25;
        break;
    case 44:
        ++counters->branch_count;
        ++counters->cbnz_count;
        if (memref.instr.el_type == 0) {
            ++counters->branch_count_usr;
            ++counters->cbnz_count_usr;
            src_pc = memref.instr.pc;
        } else {
            ++counters->branch_count_sys;
            ++counters->cbnz_count_sys;
        }
        jump_flag = 1;
        branch_opc = 44;
        break;
    case 45:
        ++counters->branch_count;
        ++counters->cbz_count;
        if (memref.instr.el_type == 0) {
            ++counters->branch_count_usr;
            ++counters->cbz_count_usr;
            src_pc = memref.instr.pc;
        } else {
            ++counters->branch_count_sys;
            ++counters->cbz_count_sys;
        }
        jump_flag = 1;
        branch_opc = 45;
        break;
    case 281:
        ++counters->branch_count;
        ++counters->ret_count;
        if (memref.instr.el_type == 0) {
            ++counters->branch_count_usr;
            ++counters->ret_count_usr;
            src_pc = memref.instr.pc;
        } else {
            ++counters->branch_count_sys;
            ++counters->ret_count_sys;
        }
        jump_flag = 1;
        branch_opc = 281;
        break;
    case 383:
        ++counters->branch_count;
        ++counters->tbnz_count;
        if (memref.instr.el_type == 0) {
            ++counters->branch_count_usr;
            ++counters->tbnz_count_usr;
            src_pc = memref.instr.pc;
        } else {
            ++counters->branch_count_sys;
            ++counters->tbnz_count_sys;
        }
        jump_flag = 1;
        branch_opc = 383;
        break;
    case 384:
        ++counters->branch_count;
        ++counters->tbz_count;
        if (memref.instr.el_type == 0) {
            ++counters->branch_count_usr;
            ++counters->tbz_count_usr;
            src_pc = memref.instr.pc;
        } else {
            ++counters->branch_count_sys;
            ++counters->tbz_count_sys;
        }
        jump_flag = 1;
        branch_opc = 384;
        break;
    }
    // dobranch(jump_flag);
    //++counters->opcode_counts_by_core[memref.data.tid][opcode];
    // printf("opcode name  : %d %s\n",opcode,decode_opcode_name(opcode));

    return true;
}

bool
jump_judge_t::process_memref(const memref_t &memref)
{
    // std::cerr<<"in jump_judge  process_memref \n"<<std::endl;
    counters_t *counters;
    const auto &lookup = shard_map_.find(memref.data.tid);
    if (lookup == shard_map_.end()) {
        counters = new counters_t;
        counters->tid = memref.data.tid;
        shard_map_[memref.data.tid] = counters;
    } else
        counters = lookup->second;
    if (!parallel_shard_memref(reinterpret_cast<void *>(counters), memref)) {
        error_string_ = counters->error;
        return false;
    }

    return true;
}

bool
jump_judge_t::cmp_counters(const std::pair<memref_tid_t, counters_t *> &l,
                           const std::pair<memref_tid_t, counters_t *> &r)
{
    return (l.second->instrs > r.second->instrs);
}

bool
jump_judge_t::print_results()
{
    counters_t total;
    // for (const auto &shard : shard_map_) {
    //    total.instr_count += shard.second->instr_count;
    //}

    // counters_t total(0);
    for (const auto &shard : shard_map_) {
        total += *shard.second;
    }
    /*
        for ( int i = 0 ; i <= 256 ; i++ ) {
            printf("tid=[%d] , one_pre=[%d] , src_pc=[%016lx] , des_pc=[%016lx] ,
       two_pre=[%x]\n",bht[i].tid,bht[i].one_pre,bht[i].src_pc,bht[i].des_pc,bht[i].two_pre);
        }
    */
    std::cerr << std::fixed << std::setprecision(2);
    std::cerr << TOOL_NAME << " results:\n";
    std::cerr << std::setw(12) << total.instr_count << " total (fetched) instructions\n";
    // taken forward + not-taken forward
    int_least64_t all_forward_branch = total.branch_count - total.backwardBranch_count;
    std::cerr << std::setw(12) << all_forward_branch << " ("
              << (float)all_forward_branch / total.instr_count * 100
              << "%) forward branches\n";
    // taken forward + taken backward
    int_least64_t taken_branch = total.forwardBranch_count + total.backwardBranch_count;
    std::cerr << std::setw(12) << taken_branch << " ("
              << (float)taken_branch / total.instr_count * 100 << "%) taken branches\n";

    std::cerr << std::setw(12) << total.forwardBranch_count << " ("
              << (float)total.forwardBranch_count / total.instr_count * 100
              << "%) taken forward branches\n";
    std::cerr << std::setw(12) << total.backwardBranch_count << " ("
              << (float)total.backwardBranch_count / total.instr_count * 100
              << "%) taken backward branches\n";
    std::cerr << std::setw(12) << total.instrs / total.branch_count
              << " average basic block size \n";

    return true;
}
