#ifndef _HOT_SPOT_H_
#define _HOT_SPOT_H_ 1

#include "analysis_tool.h"

class hot_spot_t : public analysis_tool_t {
public:
    hot_spot_t(unsigned int verbose);
    ~hot_spot_t() override;
    bool
    process_memref(const memref_t &memref) override;
    bool
    print_results() override;

protected:
    struct id_info_t {
        unsigned int pid;
        unsigned int tid;
        bool
        operator<(const id_info_t &o) const
        {
            return tid < o.tid || (tid == o.tid && pid < o.pid);
        }
    };
    struct bb_id_t { // block start pc and end pc
        unsigned long start;
        unsigned long end;
        bool
        operator<(const bb_id_t &o) const
        {
            return start < o.start || (start == o.start && end < o.end);
        }
    };
    struct bb_info_t {
        unsigned long long run_times = 0;
        unsigned long long run_insts = 0;
        uint64_t func_pc = 0;
        bool
        operator>(const bb_info_t &o) const
        {
            return run_insts > o.run_insts;
        }
        bool
        operator!=(const bb_info_t &o) const
        {
            return run_insts != o.run_insts;
        }
    };
    struct func_info_t {
        unsigned long long run_times = 0;
        unsigned long long run_insts = 0;
        bool
        operator>(const func_info_t &o) const
        {
            return run_insts > o.run_insts;
        }
        bool
        operator!=(const func_info_t &o) const
        {
            return run_insts != o.run_insts;
        }
    };
    struct run_info_t {
        unsigned long long run_inst_total = 0;
        unsigned long long bb_run_time_total = 0;
        unsigned long long func_call_time_total = 0;
        std::stack<uint64_t> call_stack; // recode run func stack during running
        std::map<bb_id_t, bb_info_t> bb_run_infos; // a specific block run infos
        std::map<unsigned long, func_info_t> func_run_infos; // a specific func run infos
    };
    struct comp_desc {
        template <typename T>

        // Comparator function
        bool
        operator()(const T &l, const T &r) const
        {
            if (l.second != r.second) {
                return l.second > r.second;
            }
            return l.first < r.first;
        }
    };

    std::map<id_info_t, bb_id_t> current_bb_by_ptid;
    std::map<id_info_t, bool> bb_start_from_call_by_ptid;
    // std::map<id_info_t, uint64_t> current_func_pc_by_ptid;  // need to per tid
    run_info_t all_run_infos;
    std::map<id_info_t, run_info_t> run_infos_by_ptid;
    FILE *f_bb_call_count = fopen("bb_call_count.txt", "w");

    unsigned int knob_verbose_;
    static const std::string TOOL_NAME;

    bool
    ppi_instr_is_call_arch(unsigned int start);
    bool
    ppi_instr_is_return(unsigned int start);};

#endif /* _HOT_SPOT_H_ */
