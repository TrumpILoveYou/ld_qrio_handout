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

#ifndef _CALL_GRAPH_CREATE_H_
#define _CALL_GRAPH_CREATE_H_ 1


#include <stack>
#include <map>

#include "analysis_tool.h"

class call_graph_t : public analysis_tool_t {
public:
    call_graph_t(unsigned int verbose);
    ~call_graph_t() override;
protected:
    unsigned int knob_verbose_;
    static const std::string TOOL_NAME;
    int bb_insn_count=0;
    int countbb = 0;
    bool trace_flag = false;//通过tools.config控制是否打印trace

    struct pre_info {
        unsigned long long prejump;
        int flag;//1 call 2 ret
        unsigned long long count_inst;
        bool operator < (const pre_info& o) const
        {
            return prejump < o.prejump || (prejump == o.prejump && count_inst < o.count_inst) || (prejump == o.prejump && count_inst == o.count_inst && flag < o.flag);
        }
    };
    struct id_info {
        unsigned int pid;
        unsigned int tid;
        bool operator < (const id_info& o) const
        {
            return tid < o.tid || (tid == o.tid && pid < o.pid);
        }
    };
    struct edge_info {
        unsigned long long pc;
        unsigned long long father_pc;
        bool operator < (const edge_info& o) const
        {
            return pc < o.pc || (pc == o.pc && father_pc < o.father_pc);
        }
    };
    struct funccount {
        unsigned int time;
        unsigned long long min;
        unsigned long long max;
        unsigned long long count_total;
        std::stack<int> once_count;
    };
    struct edgecount {
        unsigned int time;
        unsigned long long min;
        unsigned long long max;
        unsigned long long count_total;
    };
    struct callstack_element {
        unsigned long long pc;
        unsigned long long call_pc;//发生函数调用的pc，只用来检查返回的地址不等于调用地址+4的情况，这种情况很少见，但华为bench 4核上存在
    };
    enum bb_flag {
        bb_end = 1,
        bb_start = 2,
        bb_start_end = 3
    };
public:
    bool process_memref(const memref_t& memref) override;
    std::map < id_info, pre_info> tid2preinfo;
    std::map < id_info, std::stack< callstack_element> > tid2stack;
    std::map < id_info, std::map < unsigned long long, funccount> > tid2funcmap;
    std::map < id_info, std::map < edge_info, edgecount> > tid2edgemap;
    std::map < id_info, edge_info > tid2curedge;

    FILE* f1 = fopen("callgraph/call_and_inst_result.dot", "w");
    FILE* f2 = fopen("callgraph/callgraph_error.txt", "w");
    FILE* f3 = fopen("callgraph/callstack_remain_element.txt", "w");
    FILE* f4 = fopen("callgraph/callgraph_insn_flow_dump.txt", "w");
    FILE* f5 = fopen("callgraph/call_graph_trace.txt", "w");
    FILE* f6 = fopen("callgraph/callgraph_total_insn_num.txt", "w");
    void
        call_graph_process(const memref_t& memref, int start_end_flag);
    void
        call_graph_insn_flow_dump(const memref_t& memref, int is_bb_end);
    void
        call_and_return_process(bool flag, call_graph_t::id_info tt_id_info, const memref_t& memref);
    bool
        ppi_instr_is_call_arch(unsigned int start);
    bool
        ppi_instr_is_return(unsigned int start);
    bool
        print_results() override;
};

#endif /* _CALL_GRAPH_CREATE_H_ */