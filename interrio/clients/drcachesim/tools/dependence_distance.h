#ifndef _DEP_DISTANCE_CREATE_H_
#define _DEP_DISTANCE_CREATE_H_ 1

#include <mutex>
#include <unordered_map>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <iostream>

#include "analysis_tool.h"

class dep_distance_t : public analysis_tool_t {
public:
    dep_distance_t();
    ~dep_distance_t() override;
    bool
    process_memref(const memref_t &memref) override;
    bool
    print_results() override;

protected:
    static const std::string TOOL_NAME;

    uint64_t threshold = 0;

    struct reg_access {
        int distance;
        bool valid;
    };
    typedef struct reg_access reg_access_t;

    struct shard_data_t {
        shard_data_t();
        memref_tid_t tid;
        std::map<int, reg_access_t> regmap;

        uint64_t icount = 0;
        uint64_t TotalNum = 0;
        uint64_t TNumberExceed = 0;
        uint64_t TDistance = 0;
        uint64_t TNumber = 0;
        uint64_t TNumber1 = 0;
        uint64_t TNumber2 = 0;
        uint64_t TNumber4 = 0;
        uint64_t TNumber8 = 0;
        uint64_t TNumber16 = 0;
        uint64_t TNumber32 = 0;
        uint64_t TNumberMore = 0;
    };

    void
    print_shard_results(const shard_data_t *shard);

    // In parallel operation the keys are "shard indices": just ints.
    std::unordered_map<memref_tid_t, shard_data_t *> shard_map_;

private:
    void parse_config() {
        char tools_config_path[128];
        sprintf(tools_config_path,"%s/qr/tools.config",getenv("HOME"));
        FILE *in = fopen(tools_config_path,"r");
        if (in < 0) {
            printf("parameters config file error\n");
        }
        char temp[1000];
        std::string stringtmp1 = "dependence_distance";
        while (fgets(temp, 1000, in) != NULL) {
            std::string stringtmp2 = temp;
            std::vector <char*> token_vector;
            unsigned int head = stringtmp2.find(stringtmp1);
            if (head < stringtmp2.length()) {
                char* token = strtok(temp,"-");
                token_vector.push_back(token);
                while(token != NULL){
                    token = strtok(NULL, "-");
                    token_vector.push_back(token);
                }
                for (unsigned int i = 0; i < token_vector.size(); ++i) {
                    token = token_vector[i];
                    token = strtok(token_vector[i], " ");
                    token = strtok(token, "\n");
                    if (token == NULL) continue;
                    std::string tokentmp = token;
                    unsigned int length = tokentmp.size();
                    unsigned int arg_head = tokentmp.find("distance_threshold=");
                    if (arg_head < length) {
                        threshold = std::strtod(tokentmp.substr(arg_head + 19).data(), NULL);
                        if (threshold < 0) threshold = 0;
                    }
                }
                break;
            }
        }
    }    
};

#endif