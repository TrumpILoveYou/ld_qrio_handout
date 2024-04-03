#include "dependence_distance.h"
#include "qr_head.h"

const std::string dep_distance_t::TOOL_NAME = "Dependence distance tool";

analysis_tool_t *
dep_distance_tool_create()
{
    return new dep_distance_t();
}

dep_distance_t::dep_distance_t()
{
    // Read config from tools.config
    parse_config();
}

dep_distance_t::shard_data_t::shard_data_t()
{
}

dep_distance_t::~dep_distance_t()
{
    for (auto &shard : shard_map_) {
        delete shard.second;
    }
}

void
parse_reg_info(reg_info_t reg_info, std::vector<int> &regs)
{
    for (int i = 0; i < 4; i++) {
        int rw = (reg_info & 0x60) >> 5; // 0B1100000
        if (rw != REG_NONE) {
            int reg = reg_info & 0x1f; // 0B0011111
            regs.push_back(reg);
            regs.push_back(rw);
            reg_info = reg_info >> 7;
        }
    }
}

bool
dep_distance_t::process_memref(const memref_t &memref)
{
    if (memref.data.type != TRACE_TYPE_MARKER && memref.data.size != TRACE_TYPE_REG) {
        // Only process register trace
        return true;
    }

    // For serial operation we index using the tid.
    shard_data_t *shard;
    const auto &lookup = shard_map_.find(memref.data.tid);
    if (lookup == shard_map_.end()) {
        shard = new shard_data_t();
        shard->tid = memref.data.tid;
        shard_map_[memref.data.tid] = shard;
    } else
        shard = lookup->second;

    // Parse register access information from reg_info_t
    std::vector<int> regs;
    reg_info_t reg_info = memref.data.addr;
    parse_reg_info(reg_info, regs);

    // If this is a new instruction, then icount plus 1
    int old = (reg_info & 0xf0000000);
    if (!old)
        shard->icount++;

    int reg_num = regs.size() / 2;
    for (int i = 0; i < reg_num; i++) {
        int rw = regs.at(2 * i + 1);
        reg_access_t &access = shard->regmap[regs.at(2 * i)];
        if (rw == REG_READ) {
            if (access.valid) {
                int distance = shard->icount - access.distance;
                shard->TotalNum++;
                if (threshold > 0 && distance > threshold) {
                    shard->TNumberExceed++;
                    break;
                }
                shard->TDistance += distance;
                shard->TNumber++;
                if (distance == 1)
                    shard->TNumber1++;
                if (distance <= 2)
                    shard->TNumber2++;
                if (distance <= 4)
                    shard->TNumber4++;
                if (distance <= 8)
                    shard->TNumber8++;
                if (distance <= 16)
                    shard->TNumber16++;
                if (distance <= 32)
                    shard->TNumber32++;
                if (distance > 32)
                    shard->TNumberMore++;
                access.valid = false;
            }
        } else if (rw == REG_WRITE) {
            access.distance = shard->icount;
            access.valid = true;
        }
    }

    regs.clear();

    return true;
}

bool
dep_distance_t::print_results()
{
    std::cerr << TOOL_NAME << " results:" << std::endl;
    std::cerr << "Threshold config: " << threshold << std::endl;

    shard_data_t *Tshard = new shard_data_t();
    for (const auto &shard : shard_map_) {
        auto shard_data = shard.second;
        Tshard->icount += shard_data->icount;
        Tshard->TotalNum += shard_data->TotalNum;
        Tshard->TNumberExceed += shard_data->TNumberExceed;
        Tshard->TDistance += shard_data->TDistance;
        Tshard->TNumber += shard_data->TNumber;
        Tshard->TNumber1 += shard_data->TNumber1;
        Tshard->TNumber2 += shard_data->TNumber2;
        Tshard->TNumber4 += shard_data->TNumber4;
        Tshard->TNumber8 += shard_data->TNumber8;
        Tshard->TNumber16 += shard_data->TNumber16;
        Tshard->TNumber32 += shard_data->TNumber32;
        Tshard->TNumberMore += shard_data->TNumberMore;
    }
    print_shard_results(Tshard);

    // for (const auto &shard : shard_map_) {
    //     std::cerr << "\n==================================================\n"
    //                   << TOOL_NAME << " results for shard " << shard.first << " (core "
    //                   << shard.second->tid << "):" << std::endl;
    //     print_shard_results(shard.second);
    // }

    return true;
}

void
dep_distance_t::print_shard_results(const shard_data_t *shard)
{
    // std::cerr << "Total instruction: " << shard->icount << std::endl;
    // std::cerr << "Total number: " << shard->TotalNum << std::endl;

    // std::cerr.setf(std::ios::fixed);

    // std::cerr << "Total number exceeded: " << shard->TNumberExceed << std::endl;
    // std::cerr << "Ratio for distance exceeded: "
    //           << (100.0 * shard->TNumberExceed) / shard->TotalNum << "%" << std::endl;
    // std::cerr << "\nFor distance<=threshold: " << std::endl;
    // std::cerr << "Total distance: " << shard->TDistance << std::endl;
    // std::cerr << "Total number: " << shard->TNumber << std::endl;
    std::cerr.precision(2);
    std::cerr << "Total number for distance == 1:  " << std::setw(12) << shard->TNumber1;
    std::cerr << " (" << (100.0 * shard->TNumber1) / shard->TNumber << "%)" << std::endl;
    std::cerr << "Total number for distance <= 2:  " << std::setw(12) << shard->TNumber2;
    std::cerr << " (" << (100.0 * shard->TNumber2) / shard->TNumber << "%)" << std::endl;
    std::cerr << "Total number for distance <= 4:  " << std::setw(12) << shard->TNumber4;
    std::cerr << " (" << (100.0 * shard->TNumber4) / shard->TNumber << "%)" << std::endl;
    std::cerr << "Total number for distance <= 8:  " << std::setw(12) << shard->TNumber8;
    std::cerr << " (" << (100.0 * shard->TNumber8) / shard->TNumber << "%)" << std::endl;
    std::cerr << "Total number for distance <= 16: " << std::setw(12) << shard->TNumber16;
    std::cerr << " (" << (100.0 * shard->TNumber16) / shard->TNumber << "%)" << std::endl;
    std::cerr << "Total number for distance <= 32: " << std::setw(12) << shard->TNumber32;
    std::cerr << " (" << (100.0 * shard->TNumber32) / shard->TNumber << "%)" << std::endl;
    std::cerr << "Total number for distance > 32:  " << std::setw(12)
              << shard->TNumberMore;
    std::cerr << " (" << (100.0 * shard->TNumberMore) / shard->TNumber << "%)"
              << std::endl;
}
