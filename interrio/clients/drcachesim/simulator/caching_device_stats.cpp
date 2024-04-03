/* **********************************************************
 * Copyright (c) 2015-2020 Google, Inc.  All rights reserved.
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

#include <assert.h>
#include <iostream>
#include <iomanip>
#include "caching_device_stats.h"

caching_device_stats_t::caching_device_stats_t(const std::string &miss_file,
                                               bool warmup_enabled, bool is_coherent)
    : success_(true)
    , num_hits_(0)
    , num_misses_(0)
    , num_child_hits_(0)
    , num_data_hits_(0)
    , num_data_misses_(0)
    , num_instr_hits_(0)
    , num_instr_misses_(0)
    , num_inclusive_invalidates_(0)
    , num_coherence_invalidates_(0)
    , num_compulsory_miss_(0)
    , num_conflict_miss_(0)
    , num_capacity_miss_(0)
    , num_hits_at_reset_(0)
    , num_misses_at_reset_(0)
    , num_child_hits_at_reset_(0)
    , warmup_enabled_(warmup_enabled)
    , is_coherent_(is_coherent)
    , file_(nullptr)
{
    if (miss_file.empty()) {
        dump_misses_ = false;
    } else {
#ifdef HAS_ZLIB
        file_ = gzopen(miss_file.c_str(), "w");
#else
        file_ = fopen(miss_file.c_str(), "w");
#endif
        if (file_ == nullptr) {
            dump_misses_ = false;
            success_ = false;
        } else
            dump_misses_ = true;
    }
}

caching_device_stats_t::~caching_device_stats_t()
{
    if (file_ != nullptr) {
#ifdef HAS_ZLIB
        gzclose(file_);
#else
        fclose(file_);
#endif
    }
}

void
caching_device_stats_t::access(const memref_t &memref, bool hit,
                               caching_device_block_t *cache_block)
{
// We assume we're single-threaded.
// We're only computing miss rate so we just inc counters here.
    bool isData =
        memref.data.type == TRACE_TYPE_READ || memref.data.type == TRACE_TYPE_WRITE;
    if (hit) {
        num_hits_++;
        if (isData)
            num_data_hits_++;
        else
            num_instr_hits_++;
    } else {
        num_misses_++;
        if (dump_misses_)
            dump_miss(memref);
        if (isData)
            num_data_misses_++;
        else
            num_instr_misses_++;
    }
}

void
caching_device_stats_t::child_access(const memref_t &memref, bool hit,
                                     caching_device_block_t *cache_block)
{
    if (hit)
        num_child_hits_++;
    // else being computed in access()
}

void
caching_device_stats_t::dump_miss(const memref_t &memref)
{
    addr_t pc, addr;
    if (type_is_instr(memref.data.type))
        pc = memref.instr.addr;
    else { // data ref: others shouldn't get here
        assert(type_is_prefetch(memref.data.type) ||
               memref.data.type == TRACE_TYPE_READ ||
               memref.data.type == TRACE_TYPE_WRITE);
        pc = memref.data.pc;
    }
    addr = memref.data.addr;
#ifdef HAS_ZLIB
    gzprintf(file_, "0x%zx,0x%zx\n", pc, addr);
#else
    fprintf(file_, "0x%zx,0x%zx\n", pc, addr);
#endif
}

void
caching_device_stats_t::print_warmup(std::string prefix)
{
#ifdef WARMUP
    std::cerr << prefix << std::setw(18) << std::left << "Warmup hits:" << std::setw(20)
              << std::right << num_hits_at_reset_ << std::endl;
    std::cerr << prefix << std::setw(18) << std::left << "Warmup misses:" << std::setw(20)
              << std::right << num_misses_at_reset_ << std::endl;
#endif
}

void
caching_device_stats_t::print_counts(std::string prefix)
{
    std::cerr << prefix << std::setw(18) << std::left << "Hits:" << std::setw(20)
              << std::right << num_hits_ << std::endl;
    std::cerr << prefix << std::setw(18) << std::left << "Misses:" << std::setw(20)
              << std::right << num_misses_ << std::endl;
    std::cerr << prefix << std::setw(18) << std::left << "Data Hits:" << std::setw(20)
              << std::right << num_data_hits_ << std::endl;
    std::cerr << prefix << std::setw(18) << std::left << "Data Misses:" << std::setw(20)
              << std::right << num_data_misses_ << std::endl;
    std::cerr << prefix << std::setw(18) << std::left << "Instr Hits:" << std::setw(20)
              << std::right << num_instr_hits_ << std::endl;
    std::cerr << prefix << std::setw(18) << std::left << "Instr Misses:" << std::setw(20)
              << std::right << num_instr_misses_ << std::endl;
    std::cerr << prefix << std::setw(18) << std::left
              << "Compulsory Misses:" << std::setw(20) << std::right
              << num_compulsory_miss_ << std::endl;
    std::cerr << prefix << std::setw(18) << std::left
              << "Conflict Misses:" << std::setw(20) << std::right << num_conflict_miss_
              << std::endl;
    std::cerr << prefix << std::setw(18) << std::left << "Capacity Misses:" << std::setw(20)
              << std::right << num_capacity_miss_ << std::endl;
    if (is_coherent_) {
        std::cerr << prefix << std::setw(21) << std::left
                  << "Parent invalidations:" << std::setw(17) << std::right
                  << num_inclusive_invalidates_ << std::endl;
        std::cerr << prefix << std::setw(20) << std::left
                  << "Write invalidations:" << std::setw(18) << std::right
                  << num_coherence_invalidates_ << std::endl;
    } else {
        std::cerr << prefix << std::setw(18) << std::left
                  << "Invalidations:" << std::setw(20) << std::right
                  << num_inclusive_invalidates_ << std::endl;
    }
}

void
caching_device_stats_t::print_rates(std::string prefix)
{
    if (num_hits_ + num_misses_ > 0) {
        std::string miss_label = "Miss rate:";
        if (num_child_hits_ != 0)
            miss_label = "Local miss rate:";
        std::cerr << prefix << std::setw(18) << std::left << miss_label << std::setw(20)
                  << std::fixed << std::setprecision(2) << std::right
                  << ((float)num_misses_ * 100 / (num_hits_ + num_misses_)) << "%"
                  << std::endl;
    }
    if (num_data_hits_ + num_data_misses_ > 0) {
        std::string miss_label = "Data Miss rate:";
        std::cerr << prefix << std::setw(18) << std::left << miss_label << std::setw(20)
                  << std::fixed << std::setprecision(2) << std::right
                  << ((float)num_data_misses_ * 100 / (num_data_hits_ + num_data_misses_))
                  << "%" << std::endl;
    }
    if (num_instr_hits_ + num_instr_misses_ > 0) {
        std::string miss_label = "Instr Miss rate:";
        std::cerr << prefix << std::setw(18) << std::left << miss_label << std::setw(20)
                  << std::fixed << std::setprecision(2) << std::right
                  << ((float)num_instr_misses_ * 100 /
                      (num_instr_hits_ + num_instr_misses_))
                  << "%" << std::endl;
    }
}

void
caching_device_stats_t::print_child_stats(std::string prefix)
{
    if (num_child_hits_ != 0) {
        std::cerr << prefix << std::setw(18) << std::left
                  << "Total miss rate:" << std::setw(20) << std::fixed
                  << std::setprecision(2) << std::right
                  << ((float)num_misses_ * 100 /
                      (num_hits_ + num_child_hits_ + num_misses_))
                  << "%" << std::endl;
    }
}

void
caching_device_stats_t::print_stats(std::string prefix)
{
    std::cerr.imbue(std::locale("")); // Add commas, at least for my locale
    if (warmup_enabled_) {
        print_warmup(prefix);
    }
    print_counts(prefix);
    print_rates(prefix);
    print_child_stats(prefix);
    std::cerr.imbue(std::locale("C")); // Reset to avoid affecting later prints.
}

void
caching_device_stats_t::reset()
{
    num_hits_at_reset_ = num_hits_;
    num_misses_at_reset_ = num_misses_;
    num_child_hits_at_reset_ = num_child_hits_;
    num_hits_ = 0;
    num_misses_ = 0;
    num_child_hits_ = 0;
    num_inclusive_invalidates_ = 0;
    num_coherence_invalidates_ = 0;
}

void
caching_device_stats_t::invalidate(invalidation_type_t invalidation_type)
{
    if (invalidation_type == INVALIDATION_INCLUSIVE) {
        num_inclusive_invalidates_++;
    } else if (invalidation_type == INVALIDATION_COHERENCE) {
        num_coherence_invalidates_++;
    }
}