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

/* This trace analyzer requires access to the modules.log file and the
 * libraries and binary from the traced execution in order to obtain further
 * information about each instruction than was stored in the trace.
 * It does not support online use, only offline.
 */
#define SHARE_MEM

#include "dr_api.h"
#include "opcode_mix.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string.h>
#include <unordered_map>
#include "ipc_reader.h"
#include "decode_opcode.h"
#ifdef SHARE_MEM

#    include "decode_opcode.h"

#endif

#ifndef SHARE_MEM_THIS

#    include <stdio.h>
#    include <stdlib.h>
#    include <ctime>
#endif
#ifdef SHARE_MEM_THIS
#    include <stdio.h>
#    include <stdlib.h>
#    include <unistd.h>
#    include <sys/ipc.h>
#    include <sys/shm.h>
#    include <assert.h>
#    include <thread>
#    include <mutex>
#    include <ctime>
std::mutex mtx;
/** share memory head struct, used for judging the rd_idx of buffer block  */

#endif
const std::string opcode_mix_t::TOOL_NAME = "Opcode mix tool";

analysis_tool_t *
opcode_mix_tool_create(const std::string &module_file_path, unsigned int verbose,
                       const std::string &alt_module_dir)
{
    return new opcode_mix_t(module_file_path, verbose, alt_module_dir);
}

opcode_mix_t::opcode_mix_t(const std::string &module_file_path, unsigned int verbose,
                           const std::string &alt_module_dir)
    : module_file_path_(module_file_path)
    , knob_verbose_(verbose)
    , knob_alt_module_dir_(alt_module_dir)
{
}

std::string
opcode_mix_t::initialize()
{
    serial_shard_.worker = &serial_worker_;
    if (module_file_path_.empty())
        return "Module file path is missing";
    dcontext_.dcontext = dr_standalone_init();
    std::string error = directory_.initialize_module_file(module_file_path_);
    if (!error.empty())
        return "Failed to initialize directory: " + error;
    module_mapper_ =
        module_mapper_t::create(directory_.modfile_bytes_, nullptr, nullptr, nullptr,
                                nullptr, knob_verbose_, knob_alt_module_dir_);
    module_mapper_->get_loaded_modules();
    error = module_mapper_->get_last_error();
    if (!error.empty())
        return "Failed to load binaries: " + error;
    return "";
}

opcode_mix_t::~opcode_mix_t()
{
    for (auto &iter : shard_map_) {
        delete iter.second;
    }
}

bool
opcode_mix_t::parallel_shard_supported()
{
    return true;
}

void *
opcode_mix_t::parallel_worker_init(int worker_index)
{
    auto worker = new worker_data_t;
    return reinterpret_cast<void *>(worker);
}

std::string
opcode_mix_t::parallel_worker_exit(void *worker_data)
{
    worker_data_t *worker = reinterpret_cast<worker_data_t *>(worker_data);
    delete worker;
    return "";
}

void *
opcode_mix_t::parallel_shard_init(int shard_index, void *worker_data)
{
    worker_data_t *worker = reinterpret_cast<worker_data_t *>(worker_data);
    auto shard = new shard_data_t(worker);
    std::lock_guard<std::mutex> guard(shard_map_mutex_);
    shard_map_[shard_index] = shard;
    return reinterpret_cast<void *>(shard);
}

bool
opcode_mix_t::parallel_shard_exit(void *shard_data)
{
    // Nothing (we read the shard data in print_results).
    return true;
}

bool
opcode_mix_t::parallel_shard_memref(void *shard_data, const memref_t &memref)
{
    shard_data_t *shard = reinterpret_cast<shard_data_t *>(shard_data);
    if (!type_is_instr(memref.instr.type) &&
        memref.data.type != TRACE_TYPE_INSTR_NO_FETCH) {
        return true;
    }
    ++shard->instr_count;
    if (memref.instr.el_type == 0)
        ++shard->instr_count_usr;
    else
        ++shard->instr_count_sys;

    app_pc mapped_pc;

    const app_pc trace_pc = reinterpret_cast<app_pc>(memref.instr.addr);

    mapped_pc = trace_pc;
    int opcode;
    int cache_enable = 0;

    /* need to judge EL1, user multi process may same pc*/
    auto cached_opcode = shard->worker->opcode_cache.find(memref.instr.pc);

    if (cache_enable == 1 && cached_opcode != shard->worker->opcode_cache.end()) {
        opcode = cached_opcode->second;
    } else {
        opcode = decode_opcode(*(uint *)mapped_pc);
        if (cache_enable == 1)
            shard->worker->opcode_cache[memref.instr.pc] = opcode;
    }
    ++shard->opcode_counts_by_core[memref.data.tid][opcode];
    if (memref.instr.el_type == 0)
        ++shard->opcode_counts_by_core_usr[memref.data.tid][opcode];
    else
        ++shard->opcode_counts_by_core_sys[memref.data.tid][opcode];
    if (opcode == 0) {
        // printf("cannot decode pc = [%lx] , inst = [%08x] \n",memref.instr.pc,*(unsigned
        // int *)memref.instr.addr);
    }
    return true;
}

std::string
opcode_mix_t::parallel_shard_error(void *shard_data)
{
    shard_data_t *shard = reinterpret_cast<shard_data_t *>(shard_data);
    return shard->error;
}

bool
opcode_mix_t::process_memref(const memref_t &memref)
{
    if (!parallel_shard_memref(reinterpret_cast<void *>(&serial_shard_), memref)) {
        error_string_ = serial_shard_.error;
        return false;
    }
    return true;
}

static bool
cmp_val(const std::pair<int, int_least64_t> &l, const std::pair<int, int_least64_t> &r)
{
    return (l.second > r.second);
}

bool
opcode_mix_t::print_results()
{
    shard_data_t total(0);
    if (shard_map_.empty()) {
        total = serial_shard_;
    } else {
        for (const auto &shard : shard_map_) {
            total.instr_count += shard.second->instr_count;
            for (const auto &mapkey : shard.second->opcode_counts_by_core) {
                for (const auto &keyvals : mapkey.second) {
                    total.opcode_counts_by_core[mapkey.first][keyvals.first] +=
                        keyvals.second;
                }
            }
        }
        for (const auto &shard : shard_map_) {
            total.instr_count_usr += shard.second->instr_count_usr;
            for (const auto &mapkey : shard.second->opcode_counts_by_core_usr) {
                for (const auto &keyvals : mapkey.second) {
                    total.opcode_counts_by_core_usr[mapkey.first][keyvals.first] +=
                        keyvals.second;
                }
            }
        }
        for (const auto &shard : shard_map_) {
            total.instr_count_sys += shard.second->instr_count_sys;
            for (const auto &mapkey : shard.second->opcode_counts_by_core_sys) {
                for (const auto &keyvals : mapkey.second) {
                    total.opcode_counts_by_core_usr[mapkey.first][keyvals.first] +=
                        keyvals.second;
                }
            }
        }
    }

    // Only care about usr instructions
    std::cerr << "====== branch counter results ======\n";
    std::unordered_map<int, int_least64_t> instr_histogram;
    for (const auto &mapkey : total.opcode_counts_by_core) {
        std::vector<std::pair<int, int_least64_t>> sorted(mapkey.second.begin(),
                                                          mapkey.second.end());
        std::sort(sorted.begin(), sorted.end(), cmp_val);
        for (const auto &keyvals : sorted) {
            instr_histogram[keyvals.first] += keyvals.second;
        }
    }

    int_least64_t branch = 0;
    for (const auto &keyvals : instr_histogram) {
        switch (keyvals.first) {
            case OP_b:
                /***************************************************************************/
                /* Lab0 TODO: find out all the branch instructions according to the manual */
                /* Hint: Except OP_b, there are 9 branch instrructions remaining. Add them */
                /* here as "case OP_XX" label and accumulate to the total branch counter.  */
                /***************************************************************************/
                branch += keyvals.second;
                break;
            case OP_bcond:
                branch += keyvals.second;
                break;
            case OP_cbnz:
                branch += keyvals.second;
                break;
            case OP_cbz:
                branch += keyvals.second;
                break;
            case OP_tbnz:
                branch += keyvals.second;
                break;
            case OP_tbz:
                branch += keyvals.second;
                break;
            case OP_bl:
                branch += keyvals.second;
                break;
            case OP_blr:
                branch += keyvals.second;
                break;
            case OP_br:
                branch += keyvals.second;
                break;
            case OP_ret:
                branch += keyvals.second;
                break;
            default:
                break;
        }
    }

    // Count data_process, branch, and memory access
    std::cerr.precision(4);
    std::cerr << total.instr_count
              << " total executed instructions\n";
    std::cerr << branch << " ("
              << (100.0 * branch) / total.instr_count << "%) "
              << "branch instructions\n";
    return true;
}
