#!/bin/bash

container=qrio
image=qrio

docker build -t $image .

docker run --privileged --name $container -idt -v $(cd .. && pwd):/root $image /bin/bash

# Build QEMU
docker exec -it $container /bin/bash -c \
    "cd /root/qemu-4.1.1/conf/conf && ./conf.sh && \
    cd /root/qemu-4.1.1 && ./compile-aarch64-system.sh && make -j4 && make install"

# Build RIO
docker exec -it $container /bin/bash -c \
    "cd /root/interrio && rm -rf build && mkdir build && cd build && cmake .. && make -j4"
