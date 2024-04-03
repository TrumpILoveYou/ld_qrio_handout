#!/bin/sh
export LD_LIBRARY_PATH=${HOME}/qr:$LD_LIBRARY_PATH

loop=1

if [ -n "$1" ];then
	loop=$1
	echo "$1"
fi
index=0

while [ $index -lt $loop ];
do
	echo "Do loop[$index]..."
	./build/bin64/drrun -t drcachesim -ins 1000 -channel 1 -indir drmemtrace.a.out.48252.0183.dir/ -config_file cache16.config

	index=`expr $index + 1`
done
