/* **********************************************************
 * Copyright (c) 2017-2020 Google, Inc.  All rights reserved.
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

#ifndef _BASIC_COUNTS_H_
#define _BASIC_COUNTS_H_ 1

#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "analysis_tool.h"

class jump_judge_t : public analysis_tool_t {
public:
    jump_judge_t(unsigned int verbose);
    ~jump_judge_t() override;
    bool
    process_memref(const memref_t &memref) override;
    bool
    print_results() override;
    bool
    parallel_shard_supported() override;
    void *
    parallel_shard_init(int shard_index, void *worker_data) override;
    bool
    parallel_shard_exit(void *shard_data) override;
    bool
    parallel_shard_memref(void *shard_data, const memref_t &memref) override;
    std::string
    parallel_shard_error(void *shard_data) override;

protected:
    struct counters_t {
        counters_t()
        {
        }
        counters_t &
        operator+=(counters_t &rhs)
        {
            instrs += rhs.instrs;
            instrs_nofetch += rhs.instrs_nofetch;
            prefetches += rhs.prefetches;
            instr_count += rhs.instr_count;
            branch_count += rhs.branch_count;
            b_count += rhs.b_count;
            bcond_count += rhs.bcond_count;
            bl_count += rhs.bl_count;
            blr_count += rhs.blr_count;
            br_count += rhs.br_count;
            cbnz_count += rhs.cbnz_count;
            cbz_count += rhs.cbz_count;
            tbnz_count += rhs.tbnz_count;
            tbz_count += rhs.tbz_count;
            ret_count += rhs.ret_count;

            backwardBranch_count += rhs.backwardBranch_count;
            forwardBranch_count += rhs.forwardBranch_count;

            // usr
            instr_count_usr += rhs.instr_count_usr;
            branch_count_usr += rhs.branch_count_usr;
            b_count_usr += rhs.b_count_usr;
            bcond_count_usr += rhs.bcond_count_usr;
            bl_count_usr += rhs.bl_count_usr;
            blr_count_usr += rhs.blr_count_usr;
            br_count_usr += rhs.br_count_usr;
            cbnz_count_usr += rhs.cbnz_count_usr;
            cbz_count_usr += rhs.cbz_count_usr;
            tbnz_count_usr += rhs.tbnz_count_usr;
            tbz_count_usr += rhs.tbz_count_usr;
            ret_count_usr += rhs.ret_count_usr;

            backwardBranch_count_usr += rhs.backwardBranch_count_usr;
            forwardBranch_count_usr += rhs.forwardBranch_count_usr;

            // sys
            instr_count_sys += rhs.instr_count_sys;
            branch_count_sys += rhs.branch_count_sys;
            b_count_sys += rhs.b_count_sys;
            bcond_count_sys += rhs.bcond_count_sys;
            bl_count_sys += rhs.bl_count_sys;
            blr_count_sys += rhs.blr_count_sys;
            br_count_sys += rhs.br_count_sys;
            cbnz_count_sys += rhs.cbnz_count_sys;
            cbz_count_sys += rhs.cbz_count_sys;
            tbnz_count_sys += rhs.tbnz_count_sys;
            tbz_count_sys += rhs.tbz_count_sys;
            ret_count_sys += rhs.ret_count_sys;

            backwardBranch_count_sys += rhs.backwardBranch_count_sys;
            forwardBranch_count_sys += rhs.forwardBranch_count_sys;

            for (const uint64_t addr : rhs.unique_pc_addrs) {
                unique_pc_addrs.insert(addr);
            }
            return *this;
        }
        memref_tid_t tid = 0;
        int_least64_t instrs = 0;
        int_least64_t instrs_nofetch = 0;
        int_least64_t prefetches = 0;
        int_least64_t instr_count = 0;
        int_least64_t branch_count = 0;
        int_least64_t b_count = 0;
        int_least64_t bcond_count = 0;
        int_least64_t bl_count = 0;
        int_least64_t blr_count = 0;
        int_least64_t br_count = 0;
        int_least64_t cbnz_count = 0;
        int_least64_t cbz_count = 0;
        int_least64_t tbnz_count = 0;
        int_least64_t tbz_count = 0;
        int_least64_t ret_count = 0;
        int_least64_t backwardBranch_count = 0;
        int_least64_t forwardBranch_count = 0;
        // usr
        int_least64_t instr_count_usr = 0;
        int_least64_t branch_count_usr = 0;
        int_least64_t b_count_usr = 0;
        int_least64_t bcond_count_usr = 0;
        int_least64_t bl_count_usr = 0;
        int_least64_t blr_count_usr = 0;
        int_least64_t br_count_usr = 0;
        int_least64_t cbnz_count_usr = 0;
        int_least64_t cbz_count_usr = 0;
        int_least64_t tbnz_count_usr = 0;
        int_least64_t tbz_count_usr = 0;
        int_least64_t ret_count_usr = 0;
        int_least64_t backwardBranch_count_usr = 0;
        int_least64_t forwardBranch_count_usr = 0;
        // sys
        int_least64_t instr_count_sys = 0;
        int_least64_t branch_count_sys = 0;
        int_least64_t b_count_sys = 0;
        int_least64_t bcond_count_sys = 0;
        int_least64_t bl_count_sys = 0;
        int_least64_t blr_count_sys = 0;
        int_least64_t br_count_sys = 0;
        int_least64_t cbnz_count_sys = 0;
        int_least64_t cbz_count_sys = 0;
        int_least64_t tbnz_count_sys = 0;
        int_least64_t tbz_count_sys = 0;
        int_least64_t ret_count_sys = 0;
        int_least64_t backwardBranch_count_sys = 0;
        int_least64_t forwardBranch_count_sys = 0;

        std::unordered_set<uint64_t> unique_pc_addrs;
        std::string error;
    };
    static bool
    cmp_counters(const std::pair<memref_tid_t, counters_t *> &l,
                 const std::pair<memref_tid_t, counters_t *> &r);

    // The keys here are int for parallel, tid for serial.
    std::unordered_map<memref_tid_t, counters_t *> shard_map_;
    // This mutex is only needed in parallel_shard_init.  In all other accesses to
    // shard_map (process_memref, print_results) we are single-threaded.
    std::mutex shard_map_mutex_;
    unsigned int knob_verbose_;
    static const std::string TOOL_NAME;
};

#endif /* _jump_judge_H_ */
