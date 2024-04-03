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

/* ipc_reader: obtains memory streams from DR clients running in
 * application processes and presents them via an interator interface
 * to the cache simulator.
 */

#ifndef _IPC_READER_H_
#define _IPC_READER_H_ 1

#include "reader.h"
#include "../common/memref.h"
#include "../common/named_pipe.h"
#include "../common/trace_entry.h"
#include "qr_head.h"
#include "ring_buf.h"

#ifdef FUN_SPECIFY
#include <stack>
#include <unordered_map>
#endif

typedef struct trace_info1{
    unsigned long pc;
    unsigned char instr[4];
    unsigned long hva;
}trace_info1_t;

class ipc_reader_t : public reader_t {
public:
    int ipc_ins_print;
    int ipc_channel_d;
    bool ipc_only_usr;
    ipc_reader_t();
    ipc_reader_t(const char *ipc_name, int verbosity, int ins_print ,int channel_d,bool only_usr);
    virtual ~ipc_reader_t();
    bool operator!() override;
    // This potentially blocks.
    bool
    init() override;
    std::string
    get_pipe_name() const;

protected:
#ifdef FUN_SPECIFY
    std::unordered_map<int,std::stack<unsigned long>> tid2stack;
    //std::stack<unsigned long> call_stack;
    unsigned long target_function_pc;
    FILE* target_file = fopen("target_function_pc.txt", "r");
    //int start_counts = 0, end_counts = 0;
    //int call_counts = 0, ret1_counts = 0, ret2_counts = 0;
    bool
    ppi_instr_is_call_arch(unsigned int start)   // bl 94 97��ͷ   blr d63f0  ��ͷ  
    {
        unsigned int tmp1 = (start >> 24);
        if (tmp1 == 0x94 || tmp1 == 0x97)
            return true;
        tmp1 = (start >> 12);
        if (tmp1 == 0xd63f0)
            return true;
        return false;
    }

    bool
    ppi_instr_is_return(unsigned int start)    // ret d65f03c0
    {
        unsigned int tmp1 = (start >> 12);
        if (tmp1 == 0xd65f0) {
            return true;
        }
        return false;
    }
#endif
    ringbuf_t *ringbuf;
    trace_entry_t * read_next_entry() override;
    bool read_next_tb();
    bool pre_tb = false;
    bool read_next_thread_entry(size_t, trace_entry_t *, bool *) override
    {
        // Only an interleaved stream is supported.
        return false;
    }

    uint32_t cacheline_size = 512;
    int pr = 0;
    int pw = 0;
    int ct = 0;
    int tb_num = 0;
    unsigned long ins_total = 0;
    volatile  int cpu_id=0;
    volatile  int dpid=0;
    volatile  int dtid=0;
    int start_sig = 0;
    int header = 0;
    int core_header = 0;
    int el_type_header=0;
    int tid_cg_header=0;
    int r_idx = 0;
    int mem_r_idx = 0;
    int reg_r_idx = 0;
    std::unordered_map<addr_t, int> core_map_;
    std::unordered_map<addr_t, int> core_tb_map_;
    std::unordered_map<addr_t, int> pid_usr_map_;
    std::unordered_map<addr_t, int> pid_sys_map_;
    unsigned long dcount=1;
private:
    named_pipe_t pipe_;
    bool creation_success_;

    // For efficiency we want to read large chunks at a time.
    // The atomic write size for a pipe on Linux is 4096 bytes but
    // we want to go ahead and read as much data as we can at one
    // time.
    static const int BUF_SIZE = 16 * 1024;
    trace_entry_t buf_[BUF_SIZE];
    trace_entry_t *cur_buf_;
    trace_entry_t *end_buf_;
    trace_entry_t *buf_temp = (trace_entry_t *)malloc(sizeof(trace_entry_t));
//    interbuf buf;
    //struct tb_trace tt;
};

#endif /* _IPC_READER_H_ */
