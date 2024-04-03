#!/bin/bash

docker exec -it qrio /bin/bash -c \
    "cd /root && rm -rf assets && mkdir assets && \
    wget -O assets/kernel.img http://10.176.34.8:9090/kernel.img && \
    wget -O assets/disk.img http://10.176.34.8:9090/disk.img"
