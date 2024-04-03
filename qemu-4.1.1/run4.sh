#/home/qemu-arm64-system/bin/qemu-system-aarch64  -m size=1024M  -smp cpus=1 -smp threads=1 -kernel /home/tools/linux/arch/arm64/boot/Image -machine virt,virtualization=true,gic-version=3 -nographic -cpu cortex-a57 -initrd /home/tools/busybox-1.31.0/_install/rootfs.cpio.gz  -append "rdinit=/linuxrc rw console=ttyAMA0" 
#/home/qemu-arm64-system/bin/qemu-system-aarch64 -machine virt,virtualization=true,gic-version=3 -nographic -m size=1024M -cpu cortex-a57  -smp 1 -kernel /home/tools/linux/arch/arm64/boot/Image  -append "console=ttyAMA0 rw rdinit=/linuxrc" -initrd /home/tools/busybox-1.31.0/_install/rootfs.cpio.gz 
#/root/duan/qemu-arm64-system/bin/qemu-system-aarch64 -machine virt,virtualization=true,gic-version=3 -nographic -m size=1024M -cpu cortex-a57  -smp 1 -kernel /root/duan/tools/linux/arch/arm64/boot/Image  -append "console=ttyAMA0 rw rdinit=/linuxrc" -initrd /root/duan/tools/busybox-1.31.0/_install/rootfs.cpio.gz 

export LD_LIBRARY_PATH=${HOME}/qr:$LD_LIBRARY_PATH

./aarch64-softmmu/qemu-system-aarch64  \
	-machine virt,virtualization=true,gic-version=3 \
	-nographic \
	-m size=1024M \
	-cpu cortex-a72  \
	-smp cpus=1 \
	-kernel ~/qr/vmlinuz-4.4.0-116-generic  \
	-hda ~/qr/ppi.img \
	-append "root=/dev/vda rw console=ttyAMA0 rdinit=/linuxrc"  \
	-channel 1 
#	-clockRate 0.8 -tagRate 0.5 -sendRate 0.002
#	-kernel ~/qr/vmlinuz-4.4.0-116-generic  \
#	-kernel ~/qr/ubuntu4.4.image  \
