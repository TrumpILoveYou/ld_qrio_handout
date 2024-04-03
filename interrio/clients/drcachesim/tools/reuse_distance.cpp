/* **********************************************************
 * Copyright (c) 2016-2020 Google, Inc.  All rights reserved.
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

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include "reuse_distance.h"
#include "../common/utils.h"

const std::string reuse_distance_t::TOOL_NAME = "Reuse distance tool";

unsigned int reuse_distance_t::knob_verbose;

analysis_tool_t *
reuse_distance_tool_create(const reuse_distance_knobs_t &knobs)
{
    return new reuse_distance_t(knobs);
}

reuse_distance_t::reuse_distance_t(const reuse_distance_knobs_t &knobs)
    : knobs_(knobs)
    , line_size_bits_(compute_log2((int)knobs_.line_size))
{
    if (DEBUG_VERBOSE(2)) {
        std::cerr << "cache line size " << knobs_.line_size << ", "
                  << "reuse distance threshold " << knobs_.distance_threshold
                  << std::endl;
    }
}

reuse_distance_t::~reuse_distance_t()
{
    for (auto &shard : shard_map_) {
        delete shard.second;
    }
}

reuse_distance_t::shard_data_t::shard_data_t(uint64_t reuse_threshold, uint64_t skip_dist,
                                             bool verify)
{
    ref_list_data_16 = std::unique_ptr<line_ref_list_t>(
        new line_ref_list_t(reuse_threshold, skip_dist, verify));
    ref_list_data_64 = std::unique_ptr<line_ref_list_t>(
        new line_ref_list_t(reuse_threshold, skip_dist, verify));
    ref_list_data_256 = std::unique_ptr<line_ref_list_t>(
        new line_ref_list_t(reuse_threshold, skip_dist, verify));
    ref_list_data_4096 = std::unique_ptr<line_ref_list_t>(
        new line_ref_list_t(reuse_threshold, skip_dist, verify));
    ref_list_inst_16 = std::unique_ptr<line_ref_list_t>(
        new line_ref_list_t(reuse_threshold, skip_dist, verify));
    ref_list_inst_64 = std::unique_ptr<line_ref_list_t>(
        new line_ref_list_t(reuse_threshold, skip_dist, verify));
    ref_list_inst_256 = std::unique_ptr<line_ref_list_t>(
        new line_ref_list_t(reuse_threshold, skip_dist, verify));
    ref_list_inst_4096 = std::unique_ptr<line_ref_list_t>(
        new line_ref_list_t(reuse_threshold, skip_dist, verify));
}

bool
reuse_distance_t::parallel_shard_supported()
{
    return true;
}

void *
reuse_distance_t::parallel_shard_init(int shard_index, void *worker_data)
{
    auto shard = new shard_data_t(knobs_.distance_threshold, knobs_.skip_list_distance,
                                  knobs_.verify_skip);
    std::lock_guard<std::mutex> guard(shard_map_mutex_);
    shard_map_[shard_index] = shard;
    return reinterpret_cast<void *>(shard);
}

bool
reuse_distance_t::parallel_shard_exit(void *shard_data)
{
    // Nothing (we read the shard data in print_results).
    return true;
}

std::string
reuse_distance_t::parallel_shard_error(void *shard_data)
{
    shard_data_t *shard = reinterpret_cast<shard_data_t *>(shard_data);
    return shard->error;
}

bool
reuse_distance_t::parallel_shard_memref(void *shard_data, const memref_t &memref)
{
    // Data cache
    if (memref.data.type == TRACE_TYPE_READ || memref.data.type == TRACE_TYPE_WRITE) {
        shard_data_t *shard = reinterpret_cast<shard_data_t *>(shard_data);
        if (DEBUG_VERBOSE(3)) {
            std::cerr << " ::" << memref.data.pid << "." << memref.data.tid
                      << ":: " << trace_type_names[memref.data.type];
            if (memref.data.type != TRACE_TYPE_THREAD_EXIT) {
                std::cerr << " @ ";
                if (!type_is_instr(memref.data.type))
                    std::cerr << (void *)memref.data.pc << " ";
                std::cerr << (void *)memref.data.addr << " x" << memref.data.size;
            }
            std::cerr << std::endl;
        }

        addr_t tag = memref.data.addr >> 4;
        std::unordered_map<addr_t, line_ref_t *>::iterator it =
            shard->cache_map_data_16.find(tag);
        if (it == shard->cache_map_data_16.end()) {
            line_ref_t *ref = new line_ref_t(tag);
            // insert into the map
            shard->cache_map_data_16.insert(std::pair<addr_t, line_ref_t *>(tag, ref));
            // insert into the list
            shard->ref_list_data_16->add_to_front(ref);
        } else {
            int_least64_t dist = shard->ref_list_data_16->move_to_front(it->second);
            std::unordered_map<int_least64_t, int_least64_t>::iterator dist_it =
                shard->dist_map_data_16.find(dist);
            if (dist_it == shard->dist_map_data_16.end())
                shard->dist_map_data_16.insert(
                    std::pair<int_least64_t, int_least64_t>(dist, 1));
            else
                ++dist_it->second;
            if (DEBUG_VERBOSE(3)) {
                std::cerr << "Distance is " << dist << "\n";
            }
        }

        tag = memref.data.addr >> 6;
        it = shard->cache_map_data_64.find(tag);
        if (it == shard->cache_map_data_64.end()) {
            line_ref_t *ref = new line_ref_t(tag);
            // insert into the map
            shard->cache_map_data_64.insert(std::pair<addr_t, line_ref_t *>(tag, ref));
            // insert into the list
            shard->ref_list_data_64->add_to_front(ref);
        } else {
            int_least64_t dist = shard->ref_list_data_64->move_to_front(it->second);
            std::unordered_map<int_least64_t, int_least64_t>::iterator dist_it =
                shard->dist_map_data_64.find(dist);
            if (dist_it == shard->dist_map_data_64.end())
                shard->dist_map_data_64.insert(
                    std::pair<int_least64_t, int_least64_t>(dist, 1));
            else
                ++dist_it->second;
            if (DEBUG_VERBOSE(3)) {
                std::cerr << "Distance is " << dist << "\n";
            }
        }

        tag = memref.data.addr >> 8;
        it = shard->cache_map_data_256.find(tag);
        if (it == shard->cache_map_data_256.end()) {
            line_ref_t *ref = new line_ref_t(tag);
            // insert into the map
            shard->cache_map_data_256.insert(std::pair<addr_t, line_ref_t *>(tag, ref));
            // insert into the list
            shard->ref_list_data_256->add_to_front(ref);
        } else {
            int_least64_t dist = shard->ref_list_data_256->move_to_front(it->second);
            std::unordered_map<int_least64_t, int_least64_t>::iterator dist_it =
                shard->dist_map_data_256.find(dist);
            if (dist_it == shard->dist_map_data_256.end())
                shard->dist_map_data_256.insert(
                    std::pair<int_least64_t, int_least64_t>(dist, 1));
            else
                ++dist_it->second;
            if (DEBUG_VERBOSE(3)) {
                std::cerr << "Distance is " << dist << "\n";
            }
        }

        tag = memref.data.addr >> 12;
        it = shard->cache_map_data_4096.find(tag);
        if (it == shard->cache_map_data_4096.end()) {
            line_ref_t *ref = new line_ref_t(tag);
            // insert into the map
            shard->cache_map_data_4096.insert(std::pair<addr_t, line_ref_t *>(tag, ref));
            // insert into the list
            shard->ref_list_data_4096->add_to_front(ref);
        } else {
            int_least64_t dist = shard->ref_list_data_4096->move_to_front(it->second);
            std::unordered_map<int_least64_t, int_least64_t>::iterator dist_it =
                shard->dist_map_data_4096.find(dist);
            if (dist_it == shard->dist_map_data_4096.end())
                shard->dist_map_data_4096.insert(
                    std::pair<int_least64_t, int_least64_t>(dist, 1));
            else
                ++dist_it->second;
            if (DEBUG_VERBOSE(3)) {
                std::cerr << "Distance is " << dist << "\n";
            }
        }
    }

    // Instruction cache
    if (type_is_instr(memref.instr.type)) {
        shard_data_t *shard = reinterpret_cast<shard_data_t *>(shard_data);
        addr_t tag = memref.instr.addr >> 4;
        std::unordered_map<addr_t, line_ref_t *>::iterator it =
            shard->cache_map_inst_16.find(tag);
        if (it == shard->cache_map_inst_16.end()) {
            line_ref_t *ref = new line_ref_t(tag);
            // insert into the map
            shard->cache_map_inst_16.insert(std::pair<addr_t, line_ref_t *>(tag, ref));
            // insert into the list
            shard->ref_list_inst_16->add_to_front(ref);
        } else {
            int_least64_t dist = shard->ref_list_inst_16->move_to_front(it->second);
            std::unordered_map<int_least64_t, int_least64_t>::iterator dist_it =
                shard->dist_map_inst_16.find(dist);
            if (dist_it == shard->dist_map_inst_16.end())
                shard->dist_map_inst_16.insert(
                    std::pair<int_least64_t, int_least64_t>(dist, 1));
            else
                ++dist_it->second;
            if (DEBUG_VERBOSE(3)) {
                std::cerr << "Distance is " << dist << "\n";
            }
        }

        tag = memref.instr.addr >> 6;
        it = shard->cache_map_inst_64.find(tag);
        if (it == shard->cache_map_inst_64.end()) {
            line_ref_t *ref = new line_ref_t(tag);
            // insert into the map
            shard->cache_map_inst_64.insert(std::pair<addr_t, line_ref_t *>(tag, ref));
            // insert into the list
            shard->ref_list_inst_64->add_to_front(ref);
        } else {
            int_least64_t dist = shard->ref_list_inst_64->move_to_front(it->second);
            std::unordered_map<int_least64_t, int_least64_t>::iterator dist_it =
                shard->dist_map_inst_64.find(dist);
            if (dist_it == shard->dist_map_inst_64.end())
                shard->dist_map_inst_64.insert(
                    std::pair<int_least64_t, int_least64_t>(dist, 1));
            else
                ++dist_it->second;
            if (DEBUG_VERBOSE(3)) {
                std::cerr << "Distance is " << dist << "\n";
            }
        }

        tag = memref.instr.addr >> 8;
        it = shard->cache_map_inst_256.find(tag);
        if (it == shard->cache_map_inst_256.end()) {
            line_ref_t *ref = new line_ref_t(tag);
            // insert into the map
            shard->cache_map_inst_256.insert(std::pair<addr_t, line_ref_t *>(tag, ref));
            // insert into the list
            shard->ref_list_inst_256->add_to_front(ref);
        } else {
            int_least64_t dist = shard->ref_list_inst_256->move_to_front(it->second);
            std::unordered_map<int_least64_t, int_least64_t>::iterator dist_it =
                shard->dist_map_inst_256.find(dist);
            if (dist_it == shard->dist_map_inst_256.end())
                shard->dist_map_inst_256.insert(
                    std::pair<int_least64_t, int_least64_t>(dist, 1));
            else
                ++dist_it->second;
            if (DEBUG_VERBOSE(3)) {
                std::cerr << "Distance is " << dist << "\n";
            }
        }

        tag = memref.instr.addr >> 12;
        it = shard->cache_map_inst_4096.find(tag);
        if (it == shard->cache_map_inst_4096.end()) {
            line_ref_t *ref = new line_ref_t(tag);
            // insert into the map
            shard->cache_map_inst_4096.insert(std::pair<addr_t, line_ref_t *>(tag, ref));
            // insert into the list
            shard->ref_list_inst_4096->add_to_front(ref);
        } else {
            int_least64_t dist = shard->ref_list_inst_4096->move_to_front(it->second);
            std::unordered_map<int_least64_t, int_least64_t>::iterator dist_it =
                shard->dist_map_inst_4096.find(dist);
            if (dist_it == shard->dist_map_inst_4096.end())
                shard->dist_map_inst_4096.insert(
                    std::pair<int_least64_t, int_least64_t>(dist, 1));
            else
                ++dist_it->second;
            if (DEBUG_VERBOSE(3)) {
                std::cerr << "Distance is " << dist << "\n";
            }
        }
    }

    return true;
}

bool
reuse_distance_t::process_memref(const memref_t &memref)
{
    // For serial operation we index using the tid.
    shard_data_t *shard;
    const auto &lookup = shard_map_.find(memref.data.tid);
    if (lookup == shard_map_.end()) {
        shard = new shard_data_t(knobs_.distance_threshold, knobs_.skip_list_distance,
                                 knobs_.verify_skip);
        shard->tid = memref.data.tid;
        shard_map_[memref.data.tid] = shard;
    } else
        shard = lookup->second;
    if (!parallel_shard_memref(reinterpret_cast<void *>(shard), memref)) {
        error_string_ = shard->error;
        return false;
    }
    return true;
}

void
reuse_distance_t::print_shard_results(const shard_data_t *shard)
{
    std::cerr.precision(2);
    std::cerr.setf(std::ios::fixed);
    double sum = 0.0;
    int_least64_t count = 0;
    std::cerr << "Data reuse distance" << std::endl;
    for (const auto &it : shard->dist_map_data_16) {
        sum += it.first * it.second;
        count += it.second;
    }
    double mean_16 = sum / count;
    std::cerr << "  Cache line size =" << std::setw(5) << 16 << ":  " << std::setw(8)
              << mean_16 << std::endl;
    // 64
    sum = 0.0;
    count = 0;
    for (const auto &it : shard->dist_map_data_64) {
        sum += it.first * it.second;
        count += it.second;
    }
    double mean_64 = sum / count;
    std::cerr << "  Cache line size =" << std::setw(5) << 64 << ":  " << std::setw(8)
              << mean_64 << std::endl;
    // 256
    sum = 0.0;
    count = 0;
    for (const auto &it : shard->dist_map_data_256) {
        sum += it.first * it.second;
        count += it.second;
    }
    double mean_256 = sum / count;
    std::cerr << "  Cache line size =" << std::setw(5) << 256 << ":  " << std::setw(8)
              << mean_256 << std::endl;
    // 4096
    sum = 0.0;
    count = 0;
    for (const auto &it : shard->dist_map_data_4096) {
        sum += it.first * it.second;
        count += it.second;
    }
    double mean_4096 = sum / count;
    std::cerr << "  Cache line size =" << std::setw(5) << 4096 << ":  " << std::setw(8)
              << mean_4096 << std::endl;
    std::cerr << "  64 / 16:        " << 1.0 * mean_64 / mean_16 << std::endl;
    std::cerr << "  256 / 64:       " << 1.0 * mean_256 / mean_64 << std::endl;
    std::cerr << "  4096 / 256:     " << 1.0 * mean_4096 / mean_256 << std::endl;

    std::cerr << "Inst reuse distance" << std::endl;
    for (const auto &it : shard->dist_map_inst_16) {
        sum += it.first * it.second;
        count += it.second;
    }
    mean_16 = sum / count;
    std::cerr << "  Cache line size =" << std::setw(5) << 16 << ":  " << std::setw(8)
              << mean_16 << std::endl;
    // 64
    sum = 0.0;
    count = 0;
    for (const auto &it : shard->dist_map_inst_64) {
        sum += it.first * it.second;
        count += it.second;
    }
    mean_64 = sum / count;
    std::cerr << "  Cache line size =" << std::setw(5) << 64 << ":  " << std::setw(8)
              << mean_64 << std::endl;
    // 256
    sum = 0.0;
    count = 0;
    for (const auto &it : shard->dist_map_inst_256) {
        sum += it.first * it.second;
        count += it.second;
    }
    mean_256 = sum / count;
    std::cerr << "  Cache line size =" << std::setw(5) << 256 << ":  " << std::setw(8)
              << mean_256 << std::endl;
    // 4096
    sum = 0.0;
    count = 0;
    for (const auto &it : shard->dist_map_inst_4096) {
        sum += it.first * it.second;
        count += it.second;
    }
    mean_4096 = sum / count;
    std::cerr << "  Cache line size =" << std::setw(5) << 4096 << ":  " << std::setw(8)
              << mean_4096 << std::endl;
    std::cerr << "  64 / 16:        " << 1.0 * mean_64 / mean_16 << std::endl;
    std::cerr << "  256 / 64:       " << 1.0 * mean_256 / mean_64 << std::endl;
    std::cerr << "  4096 / 256:     " << 1.0 * mean_4096 / mean_256 << std::endl;
}

bool
reuse_distance_t::print_results()
{
    // First, aggregate the per-shard data into whole-trace data.
    auto aggregate = std::unique_ptr<shard_data_t>(new shard_data_t(
        knobs_.distance_threshold, knobs_.skip_list_distance, knobs_.verify_skip));

    for (const auto &shard : shard_map_) {
        // We merge the histogram and the cache_map_data_16.
        for (const auto &entry : shard.second->dist_map_data_16) {
            aggregate->dist_map_data_16[entry.first] += entry.second;
        }
        for (const auto &entry : shard.second->dist_map_data_64) {
            aggregate->dist_map_data_64[entry.first] += entry.second;
        }
        for (const auto &entry : shard.second->dist_map_data_256) {
            aggregate->dist_map_data_256[entry.first] += entry.second;
        }
        for (const auto &entry : shard.second->dist_map_data_4096) {
            aggregate->dist_map_data_4096[entry.first] += entry.second;
        }
        for (const auto &entry : shard.second->dist_map_inst_16) {
            aggregate->dist_map_inst_16[entry.first] += entry.second;
        }
        for (const auto &entry : shard.second->dist_map_inst_64) {
            aggregate->dist_map_inst_64[entry.first] += entry.second;
        }
        for (const auto &entry : shard.second->dist_map_inst_256) {
            aggregate->dist_map_inst_256[entry.first] += entry.second;
        }
        for (const auto &entry : shard.second->dist_map_inst_4096) {
            aggregate->dist_map_inst_4096[entry.first] += entry.second;
        }
    }

    // For regular shards the line_ref_t's are deleted in ~line_ref_list_t.
    for (auto &iter : aggregate->cache_map_data_16) {
        delete iter.second;
    }
    for (auto &iter : aggregate->cache_map_data_64) {
        delete iter.second;
    }
    for (auto &iter : aggregate->cache_map_data_256) {
        delete iter.second;
    }
    for (auto &iter : aggregate->cache_map_data_4096) {
        delete iter.second;
    }
    for (auto &iter : aggregate->cache_map_inst_16) {
        delete iter.second;
    }
    for (auto &iter : aggregate->cache_map_inst_64) {
        delete iter.second;
    }
    for (auto &iter : aggregate->cache_map_inst_256) {
        delete iter.second;
    }
    for (auto &iter : aggregate->cache_map_inst_4096) {
        delete iter.second;
    }
    std::cerr << TOOL_NAME << " aggregated results:\n";
    print_shard_results(aggregate.get());
    // Reset the i/o format for subsequent tool invocations.
    std::cerr << std::dec;
    return true;
}
