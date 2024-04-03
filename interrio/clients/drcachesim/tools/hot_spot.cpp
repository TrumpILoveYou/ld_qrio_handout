#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <iostream>
#include "hot_spot.h"
#include "../common/utils.h"

const std::string hot_spot_t::TOOL_NAME = "Hot spot tool";

analysis_tool_t *
hot_spot_tool_create(unsigned int verbose)
{
    return new hot_spot_t(verbose);
}

hot_spot_t::hot_spot_t(unsigned int verbose)
    : knob_verbose_(verbose)
{
    // Empty.
}
hot_spot_t::~hot_spot_t()
{
}

bool
hot_spot_t::process_memref(const memref_t &memref)
{
    if (memref.instr.type == TRACE_TYPE_INSTR && memref.instr.el_type == 0) {
        hot_spot_t::id_info_t id_info;
        id_info.pid = memref.instr.pid;
        id_info.tid = memref.instr.tid_cg;
        if( bb_start_from_call_by_ptid.find(id_info) == bb_start_from_call_by_ptid.end()){
            bb_start_from_call_by_ptid[id_info] = false;
        }
        if (memref.instr.is_bb_end == 2 || memref.instr.is_bb_end == 3) { // start
            if (bb_start_from_call_by_ptid[id_info]) {
                run_infos_by_ptid[id_info].call_stack.push(memref.instr.pc);
                run_infos_by_ptid[id_info].func_run_infos[memref.instr.pc].run_times++;
                all_run_infos.func_run_infos[memref.instr.pc].run_times++;
                run_infos_by_ptid[id_info].func_call_time_total++;
                all_run_infos.func_call_time_total++;
                bb_start_from_call_by_ptid[id_info] = false;
            }
            current_bb_by_ptid[id_info].start = memref.instr.pc;
        }
        if (memref.instr.is_bb_end == 1 || memref.instr.is_bb_end == 3) { // end

            current_bb_by_ptid[id_info].end = memref.instr.pc;
            run_infos_by_ptid[id_info].bb_run_infos[current_bb_by_ptid[id_info]].func_pc = run_infos_by_ptid[id_info].call_stack.empty() ? 0 :run_infos_by_ptid[id_info].call_stack.top();
            all_run_infos.bb_run_infos[current_bb_by_ptid[id_info]].func_pc = run_infos_by_ptid[id_info].call_stack.empty() ? 0 :run_infos_by_ptid[id_info].call_stack.top();
            // count bb info
            int current_bb_length = (current_bb_by_ptid[id_info].end - current_bb_by_ptid[id_info].start)/4 + 1;

            ++run_infos_by_ptid[id_info].bb_run_time_total;
            ++run_infos_by_ptid[id_info].bb_run_infos[current_bb_by_ptid[id_info]].run_times;
            run_infos_by_ptid[id_info].bb_run_infos[current_bb_by_ptid[id_info]].run_insts += current_bb_length;
            run_infos_by_ptid[id_info].run_inst_total += current_bb_length;
            run_infos_by_ptid[id_info].func_run_infos[run_infos_by_ptid[id_info].call_stack.empty() ? 0 :run_infos_by_ptid[id_info].call_stack.top()].run_insts += current_bb_length;

            ++all_run_infos.bb_run_time_total;
            ++all_run_infos.bb_run_infos[current_bb_by_ptid[id_info]].run_times;
            all_run_infos.bb_run_infos[current_bb_by_ptid[id_info]].run_insts += current_bb_length;
            all_run_infos.run_inst_total += current_bb_length;
            all_run_infos.func_run_infos[run_infos_by_ptid[id_info].call_stack.empty() ? 0 :run_infos_by_ptid[id_info].call_stack.top()].run_insts += current_bb_length;

            // change func stack, set bb_start_from_call flag
            if (ppi_instr_is_call_arch(*(unsigned int *)memref.instr.addr)) {
                bb_start_from_call_by_ptid[id_info] = true; // record for next bb
            } else if (ppi_instr_is_return(*(unsigned int*)memref.instr.addr)) {
                if (!run_infos_by_ptid[id_info].call_stack.empty()){
                    run_infos_by_ptid[id_info].call_stack.pop();
                }
            }
        }
    }
    return true;
}

bool
hot_spot_t::ppi_instr_is_call_arch(unsigned int start) // bl 94 97开头   blr d63f0  开头
{
    unsigned int tmp4 = start / 0x1000000; // 256
    if (tmp4 >= 148 && tmp4 <= 151)
        return true;
    unsigned int tmp3 = start % 0x1000000 / 0x10000;
    if (tmp4 == 214 && tmp3 == 63) {
        unsigned int tmp2 = start % 0x10000 / 0x100;
        if (tmp2 >= 0 && tmp2 <= 15)
            return true;
    }
    return false;
}

bool 
hot_spot_t::ppi_instr_is_return(unsigned int start)    // ret d65f03c0
{
    unsigned int tmp1 = (start >> 12);
    if (tmp1 == 0xd65f0){
	return true;
	}
    return false;
}

bool
hot_spot_t::print_results()
{
    // all pid_tid
    fprintf(f_bb_call_count, "all bb info: block total=%lu, block run time total=%llu run inst total=%llu\n",
            all_run_infos.bb_run_infos.size(),
            all_run_infos.bb_run_time_total, 
            all_run_infos.run_inst_total
            );
    std::set<std::pair<bb_id_t, bb_info_t>, hot_spot_t::comp_desc> ordered_bb_run_infos(
        all_run_infos.bb_run_infos.begin(), all_run_infos.bb_run_infos.end());
    fprintf(f_bb_call_count, "\t%-8s\t%-25s\t%-12s\t%-12s\t%-16s\t%8s\t%10s\n",  "index", "bb", "func", "run times", "run insts", "cur perc", "accu perc");
    unsigned long tmp_index = 1;
    unsigned long long accumulated_inst_count = 0;
    for (std::pair<bb_id_t, bb_info_t> e : ordered_bb_run_infos) {
        accumulated_inst_count += e.second.run_insts;
        fprintf(f_bb_call_count, "\t%-8lu\t%12lx-%-12lx\t%-12lx\t%-12llu\t%-16llu\t%8.5f\t%10.5f\n", 
            tmp_index, 
            e.first.start,
            e.first.end, 
            e.second.func_pc, 
            e.second.run_times, 
            e.second.run_insts, 
            (double)e.second.run_insts / all_run_infos.run_inst_total, 
            (double)accumulated_inst_count / all_run_infos.run_inst_total
            );
        tmp_index++;
    }
    // func run info
    fprintf(f_bb_call_count, "all func info: func total=%lu, func run time total=%llu, run inst total=%llu\n", 
            all_run_infos.func_run_infos.size(),
            all_run_infos.func_call_time_total,
            all_run_infos.run_inst_total
            );
    std::set<std::pair<unsigned long, func_info_t>, hot_spot_t::comp_desc> ordered_func_run_infos(
        all_run_infos.func_run_infos.begin(), all_run_infos.func_run_infos.end());
    fprintf(f_bb_call_count, "\t%-8s\t%-12s\t%-12s\t%-16s\t%8s\t%10s\n",  "index", "func", "run times", "run insts", "cur perc", "accu perc");
    tmp_index = 1;
    accumulated_inst_count = 0;
    for (std::pair<unsigned long, func_info_t> e : ordered_func_run_infos) {
        accumulated_inst_count += e.second.run_insts;
        fprintf(f_bb_call_count, "\t%-8lu\t%-12lx\t%-12llu\t%-16llu\t%8.5f\t%10.5f\n", 
            tmp_index, 
            e.first, 
            e.second.run_times, 
            e.second.run_insts, 
            (double)e.second.run_insts / all_run_infos.run_inst_total, 
            (double)accumulated_inst_count / all_run_infos.run_inst_total
            );
        tmp_index++;
    }
    // for each pid_tid
    for (auto it1 = run_infos_by_ptid.begin(); it1 != run_infos_by_ptid.end(); ++it1) {
        if (it1->first.pid == 0)
            continue;
        // bb run info
        fprintf(f_bb_call_count, "bb info: pid=%u, tid=%u, block total=%lu, block run time total=%llu run inst total=%llu\n",
                it1->first.pid, 
                it1->first.tid, 
                it1->second.bb_run_infos.size(),
                it1->second.bb_run_time_total, 
                it1->second.run_inst_total
                );
        std::set<std::pair<bb_id_t, bb_info_t>, hot_spot_t::comp_desc> ordered_bb_run_infos(
            it1->second.bb_run_infos.begin(), it1->second.bb_run_infos.end());
        fprintf(f_bb_call_count, "\t%-8s\t%-25s\t%-12s\t%-12s\t%-16s\t%8s\t%10s\n",  "index", "bb", "func", "run times", "run insts", "cur perc", "accu perc");
        unsigned long tmp_index = 1;
        unsigned long accumulated_inst_count = 0;
        for (std::pair<bb_id_t, bb_info_t> e : ordered_bb_run_infos) {
            accumulated_inst_count += e.second.run_insts;
            fprintf(f_bb_call_count, "\t%-8lu\t%12lx-%-12lx\t%-12lx\t%-12llu\t%-16llu\t%8.5f\t%10.5f\n", 
                tmp_index, 
                e.first.start,
                e.first.end, 
                e.second.func_pc, 
                e.second.run_times, 
                e.second.run_insts, 
                (double)e.second.run_insts / it1->second.run_inst_total, 
                (double)accumulated_inst_count / it1->second.run_inst_total
                );
            tmp_index++;
        }
        // func run info
        fprintf(f_bb_call_count, "func info: pid=%u, tid=%u, func total=%lu, func run time total=%llu, run inst total=%llu\n", 
                it1->first.pid,
                it1->first.tid,
                it1->second.func_run_infos.size(),
                it1->second.func_call_time_total,
                it1->second.run_inst_total
                );
        std::set<std::pair<unsigned long, func_info_t>, hot_spot_t::comp_desc> ordered_func_run_infos(
            it1->second.func_run_infos.begin(), it1->second.func_run_infos.end());
        fprintf(f_bb_call_count, "\t%-8s\t%-12s\t%-12s\t%-16s\t%8s\t%10s\n",  "index", "func", "run times", "run insts", "cur perc", "accu perc");
        tmp_index = 1;
        accumulated_inst_count = 0;
        for (std::pair<unsigned long, func_info_t> e : ordered_func_run_infos) {
            accumulated_inst_count += e.second.run_insts;
            fprintf(f_bb_call_count, "\t%-8lu\t%-12lx\t%-12llu\t%-16llu\t%8.5f\t%10.5f\n", 
                tmp_index, 
                e.first, 
                e.second.run_times, 
                e.second.run_insts, 
                e.second.run_insts / double(it1->second.run_inst_total), 
                accumulated_inst_count / double(it1->second.run_inst_total)
                );
            tmp_index++;
        }
    }
    return true;
}
