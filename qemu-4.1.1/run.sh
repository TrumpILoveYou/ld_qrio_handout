export LD_LIBRARY_PATH=${HOME}/qr:$LD_LIBRARY_PATH

./aarch64-softmmu/qemu-system-aarch64  \
	-qrtag \
	-machine virt,virtualization=true,gic-version=3 \
	-nographic \
	-m size=1024M \
	-cpu cortex-a57  \
	-smp cpus=16 \
	-kernel /root/assets/kernel.img  \
	-hda /root/assets/disk.img \
	-channel 1 \
	-clockRate 1 \
	-append "root=/dev/vda rw console=ttyAMA0 rdinit=/linuxrc"  \
