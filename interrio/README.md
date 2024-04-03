# QEMURIO

##How to build(default is for aarch64)
- change clients/drcachesim/analyzer_multi.cpp 's tools.config path 
- change clients/drcachesim/reader/ipc_reader.h 's path of qr_header.h 
- change clients/drcachesim/reader/ipc_reader.cpp 's path of ftok.key of shm 
- create a build dir named build1 
- cd build1
- cmake ..
- make -j

## How to run 
- in rio home dir:
- vim tools.config to select tools to be run (basic_counts, cache, reuse_time, reuse_distance) default is opcode_mix
- ./run.sh to launch rio 
