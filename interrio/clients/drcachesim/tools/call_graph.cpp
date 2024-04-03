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


#include <stack>
#include <map>
#include <string>
#include <iostream>
#include "call_graph.h"
#include "../common/utils.h"

const std::string call_graph_t::TOOL_NAME = "Call graph tool";

analysis_tool_t *
call_graph_tool_create(unsigned int verbose)
{
    return new call_graph_t(verbose);
}

call_graph_t::call_graph_t(unsigned int verbose)
    : knob_verbose_(verbose)
{
    // Empty.
    
    std::string tmp = getenv("HOME");
    std::string config_path = tmp + "/qr/tools.config";
    
    FILE* in = fopen(config_path.c_str(), "r");
    if (in < 0) {
        printf("parameters config file error\n");
    }
    
    char temp[1000];

    std::string stringtmp1 = "call_graph";
    std::string stringtmp2 = "-trace";

    while (fgets(temp, 1000, in) != NULL) {
        std::string stringtmp3 = temp;
        if (stringtmp3[0]!='/' && stringtmp3.find(stringtmp1) != stringtmp3.npos) {
            if (stringtmp3.find(stringtmp2) != stringtmp3.npos) {
                trace_flag = true;
            }
        }
    }
}
call_graph_t::~call_graph_t()
{
    
}

bool
call_graph_t::process_memref(const memref_t &memref)
{
    if (memref.instr.type == TRACE_TYPE_INSTR   && memref.instr.el_type==0) {
        int cur_bb_flag = memref.instr.is_bb_end;
        if (cur_bb_flag == bb_start) {//memref是bb开头
            bb_insn_count=1;
            call_graph_t::call_graph_process(memref, bb_start);
        }
        else if (cur_bb_flag == bb_end) {//memref是bb结尾
            bb_insn_count++;
            call_graph_t::call_graph_process(memref, bb_end);
            bb_insn_count = 0;
        }
        else if (cur_bb_flag == bb_start_end) {//memref是bb开头&结尾(只有一条)
            bb_insn_count=1;
            call_graph_t::call_graph_process(memref, bb_start_end);
            bb_insn_count = 0;
        }
        else {//memref是bb中间
            bb_insn_count++;
        }
        //call_graph_insn_flow_dump(memref, memref.instr.is_bb_end);  //用于打印callgraph收到的指令流的函数，不需要打印时注释即可
    }
    return true;
}

void
call_graph_t::call_graph_insn_flow_dump(const memref_t& memref,int is_bb_end)
{
    if (is_bb_end == bb_start || is_bb_end == bb_start_end) {
        countbb++;
        fprintf(f4, "\n%d pid %d tid %d\n", countbb,(int)memref.instr.pid, (int)memref.instr.tid_cg);
    }
    fprintf(f4, "pc %016lx inst %08x\n", memref.instr.pc, *(unsigned int*)memref.instr.addr);
    return;
}

void
call_graph_t::call_graph_process(const memref_t& memref,int start_end_flag)
{
    call_graph_t::id_info tt_id_info;
    tt_id_info.pid = memref.instr.pid;
    tt_id_info.tid = memref.instr.tid_cg;

    if ((start_end_flag == bb_start || start_end_flag == bb_start_end) && (call_graph_t::tid2preinfo.count(tt_id_info) == 0)) {  //在start检测，是不是是新出现的线程
        pre_info tt_pre_info;
        tt_pre_info.prejump = 0;
        tt_pre_info.flag = 0;
        tt_pre_info.count_inst = 0;
        call_graph_t::tid2preinfo[tt_id_info] = tt_pre_info;

        funccount cur_funccount;//仅对0函数做初始化，它既需要统计又不会出现在call中
        cur_funccount.time = 0;
        cur_funccount.min = 0;
        cur_funccount.max = 0;
        cur_funccount.count_total = 0;
        tid2funcmap[tt_id_info][0] = cur_funccount;
        tid2funcmap[tt_id_info][0].once_count.push(0);

        edge_info cur_edge;
        cur_edge.pc = 0, cur_edge.father_pc = 0;
        tid2curedge[tt_id_info] = cur_edge;
    }

    //在新的bb开始时，如果上一个bb结尾指令是call/ret，进入call_and_return_process函数
    if (start_end_flag == bb_start || start_end_flag == bb_start_end) {//start
        if (call_graph_t::tid2preinfo[tt_id_info].flag == 1) {  //上一个bb最后是call
            call_and_return_process(1, tt_id_info, memref);
            call_graph_t::tid2preinfo[tt_id_info].flag = 0;
        }
        else if (call_graph_t::tid2preinfo[tt_id_info].flag == 2) {  //上一个bb最后是return
            call_and_return_process(0, tt_id_info, memref);
            call_graph_t::tid2preinfo[tt_id_info].flag = 0;
        }
    }

    //在一个bb结束时，判断最后一条指令是不是call/ret，并更新一系列计数器
    if (start_end_flag == bb_end || start_end_flag == bb_start_end) {//end
        if (ppi_instr_is_call_arch(*(unsigned int*)memref.instr.addr)) {
            tid2preinfo[tt_id_info].flag = 1;
        }
        else if (ppi_instr_is_return(*(unsigned int*)memref.instr.addr)) {
            tid2preinfo[tt_id_info].flag = 2;
        }
        call_graph_t::tid2preinfo[tt_id_info].prejump = memref.instr.pc;
        call_graph_t::tid2preinfo[tt_id_info].count_inst += bb_insn_count;


        //每个bb结束时更新当前函数的单次self计数，当前边的总self计数
        unsigned long long cur_func = tid2stack[tt_id_info].empty() ? 0 : tid2stack[tt_id_info].top().pc;
        tid2funcmap[tt_id_info][cur_func].once_count.top() += bb_insn_count;

        if (tid2curedge[tt_id_info].pc != 0) {
            tid2edgemap[tt_id_info] [ tid2curedge[tt_id_info] ].count_total+= bb_insn_count;
        }
        //调用时更新调用栈，更新当前边，更新边和函数的调用次数
        //返回时更新调用栈，更新当前边，更新边和函数的单次最大最小值,更新函数的total
        //每个bb结束时，更新当前边的total，更新当前函数的单次self
    }
    return;
}

void
call_graph_t::call_and_return_process(bool flag, call_graph_t::id_info tt_id_info , const memref_t& memref) {  //flag ：  1 call   0 return

    if (flag == 1) {
        callstack_element call_ele;
        call_ele.pc = memref.instr.pc;
        call_ele.call_pc = tid2preinfo[tt_id_info].prejump;
        
        //有新调用时更新当前函数和边的信息
        edge_info cur_edge;
        cur_edge.pc = call_ele.pc;
        cur_edge.father_pc = tid2stack[tt_id_info].empty() ? 0 : tid2stack[tt_id_info].top().pc;
        tid2curedge[tt_id_info]= cur_edge;

        if (tid2funcmap[tt_id_info].count(call_ele.pc) == 0) {//新函数
            funccount cur_funccount;
            cur_funccount.time = 1;
            cur_funccount.min = 100000000;//初始最小值设为一亿，极特殊情况可能不对
            cur_funccount.max = 0;
            cur_funccount.count_total = 0;
            tid2funcmap[tt_id_info][call_ele.pc] = cur_funccount;
        }
        else {
            tid2funcmap[tt_id_info][call_ele.pc].time++;
        }
        tid2funcmap[tt_id_info][call_ele.pc].once_count.push(0);

        if (tid2edgemap[tt_id_info].count(cur_edge) == 0) {//新边
            edgecount cur_edgecount;
            cur_edgecount.time = 1;
            cur_edgecount.min = 100000000;
            cur_edgecount.max = 0;
            cur_edgecount.count_total = 0;
            tid2edgemap[tt_id_info][cur_edge] = cur_edgecount;
        }
        else {
            tid2edgemap[tt_id_info][cur_edge].time++;
        }
        tid2stack[tt_id_info].push(call_ele);
        if(trace_flag)
            fprintf(f5, "%d|c:%llx;%lld\n",(int)memref.instr.tid_cg,call_ele.pc, tid2preinfo[tt_id_info].count_inst);
    }
    else {
        if (tid2stack[tt_id_info].empty()) {
            fprintf(f2, "This should never happen! 1 in pid %d tid %d \nret %016llx -> %016llx\n", tt_id_info.pid, tt_id_info.tid, tid2preinfo[tt_id_info].prejump, memref.instr.pc);
            return;
        }

        callstack_element  tmp_ele = tid2stack[tt_id_info].top();
        tid2stack[tt_id_info].pop();

        //检查ret到的地址是否符合预期
        if (memref.instr.pc != tmp_ele.call_pc + 4) {
            fprintf(f2, "This should never happen! 2\n	%016llx != %016llx + 4 in pid %d tid %d\n", memref.instr.pc, tmp_ele.call_pc, tt_id_info.pid, tt_id_info.tid);
            if(trace_flag)
                fprintf(f5, "%d|w:%llx-%llx!=%llx+4;%lld\n",(int)memref.instr.tid_cg, tid2preinfo[tt_id_info].prejump,memref.instr.pc,tmp_ele.call_pc, tid2preinfo[tt_id_info].count_inst);
            return;
        }
        else {
            if(trace_flag)
                fprintf(f5, "%d|r;%lld\n", (int)memref.instr.tid_cg, tid2preinfo[tt_id_info].count_inst);
        }

        edge_info cur_edge;
        cur_edge.pc = tmp_ele.pc;
        cur_edge.father_pc = tid2stack[tt_id_info].empty() ? 0 : tid2stack[tt_id_info].top().pc;

        int self_once_count = tid2funcmap[tt_id_info][tmp_ele.pc].once_count.top();
        tid2funcmap[tt_id_info][tmp_ele.pc].once_count.pop();
        tid2funcmap[tt_id_info][tmp_ele.pc].count_total += self_once_count;
        tid2funcmap[tt_id_info][tmp_ele.pc].min = tid2funcmap[tt_id_info][tmp_ele.pc].min < self_once_count ? tid2funcmap[tt_id_info][tmp_ele.pc].min : self_once_count;
        tid2funcmap[tt_id_info][tmp_ele.pc].max = tid2funcmap[tt_id_info][tmp_ele.pc].max > self_once_count ? tid2funcmap[tt_id_info][tmp_ele.pc].max : self_once_count;

        tid2edgemap[tt_id_info][cur_edge].min = tid2edgemap[tt_id_info][cur_edge].min < self_once_count ? tid2edgemap[tt_id_info][cur_edge].min : self_once_count;
        tid2edgemap[tt_id_info][cur_edge].max = tid2edgemap[tt_id_info][cur_edge].max > self_once_count ? tid2edgemap[tt_id_info][cur_edge].max : self_once_count;

        //更新当前edge
        edge_info new_edge;
        new_edge.pc = cur_edge.father_pc;
        if (tid2stack[tt_id_info].empty()) {
            new_edge.father_pc = 0;
        }
        else {
            callstack_element tmp = tid2stack[tt_id_info].top();
            tid2stack[tt_id_info].pop();
            if (tid2stack[tt_id_info].empty()) {
                new_edge.father_pc = 0;
            }
            else {
                new_edge.father_pc = tid2stack[tt_id_info].top().pc;
            }
            tid2stack[tt_id_info].push(tmp);
        }
        tid2curedge[tt_id_info] = new_edge;
    }
    return;
}


bool
call_graph_t::ppi_instr_is_call_arch(unsigned int start)   // bl 94 97开头   blr d63f0  开头  
{
    unsigned int tmp1 = (start >> 24);
    if (tmp1==0x94 || tmp1==0x97) return true;
    tmp1 = (start >> 12);
    if (tmp1==0xd63f0) return true;
    return false;
}

bool 
call_graph_t::ppi_instr_is_return(unsigned int start)    // ret d65f03c0
{
    unsigned int tmp1 = (start >> 12);
    if (tmp1 == 0xd65f0){
	    return true;
	}
    return false;
}

bool
call_graph_t::print_results()
{
    //输出函数
    for (auto it1 = tid2funcmap.begin(); it1 != tid2funcmap.end(); ++it1) {
        if (it1->first.tid == 0) continue;
        for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2) {
            if (it2->second.max == 0) {
                it2->second.min = 0;
                it2->second.count_total = it2->second.once_count.top();
            }
            fprintf(f1, "%016llx time=%d min=%llu max=%llu self=%llu tid=%u;\n", it2->first, it2->second.time, it2->second.min, it2->second.max, it2->second.count_total, it1->first.tid);
        }
    }
    //输出边
    for (auto it1 = tid2edgemap.begin(); it1 != tid2edgemap.end(); ++it1) {
        for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2) {
            fprintf(f1, "%016llx -> %016llx time=%d min=%llu max=%llu self=%llu tid=%u;\n", it2->first.father_pc, it2->first.pc, it2->second.time, it2->second.min, it2->second.max, it2->second.count_total, it1->first.tid);
        }
    }
    //输出调用栈中的剩余元素
    for (auto it1 = tid2stack.begin(); it1 != tid2stack.end(); ++it1) {
        if (it1->second.empty() == false) {
            fprintf(f3, "pid=%u_tid=%u  callstack remain element:\n", it1->first.pid, it1->first.tid);
            int element_count = 1;
            do {
                fprintf(f3, "top%d  pc:%016llx\n", element_count, it1->second.top().pc);
                it1->second.pop();
                element_count++;
            } while (it1->second.empty() == false);
        }
    }
    //输出每个线程的总指令数
    fprintf(f6, "callgraph_total_insn_num:\n");
    for (auto it = tid2preinfo.begin(); it != tid2preinfo.end(); ++it) {
        fprintf(f6, "pid=%u_tid=%u total=%llu\n", it->first.pid, it->first.tid, it->second.count_inst);
    }
    
    return true;
}
