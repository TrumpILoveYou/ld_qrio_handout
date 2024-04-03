#!/bin/bash

docker exec -it qrio /bin/bash -c \
    "cd /root/interrio/build && make -j4"
