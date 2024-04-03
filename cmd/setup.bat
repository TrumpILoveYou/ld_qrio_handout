set container=qrio
set image=qrio

docker build -t %image% .
cd ..

docker run --privileged --name %container% -idt -v %CD%:/root %image% /bin/bash

docker exec -it %container% /bin/bash -c "cd /root/qemu-4.1.1/conf/conf && ./conf.sh && cd /root/qemu-4.1.1 && ./compile-aarch64-system.sh && make -j && make install"

docker exec -it %container% /bin/bash -c "cd /root/interrio && rm -rf build && mkdir build && cd build && cmake .. && make -j"

cd cmd
