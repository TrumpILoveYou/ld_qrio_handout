#/home/qemu-arm64-system/bin/qemu-system-aarch64  -m size=1024M  -smp cpus=1 -smp threads=1 -kernel /home/tools/linux/arch/arm64/boot/Image -machine virt,virtualization=true,gic-version=3 -nographic -cpu cortex-a57 -initrd /home/tools/busybox-1.31.0/_install/rootfs.cpio.gz  -append "rdinit=/linuxrc rw console=ttyAMA0" 
#/home/qemu-arm64-system/bin/qemu-system-aarch64 -machine virt,virtualization=true,gic-version=3 -nographic -m size=1024M -cpu cortex-a57  -smp 1 -kernel /home/tools/linux/arch/arm64/boot/Image  -append "console=ttyAMA0 rw rdinit=/linuxrc" -initrd /home/tools/busybox-1.31.0/_install/rootfs.cpio.gz 
#/root/duan/qemu-arm64-system/bin/qemu-system-aarch64 -machine virt,virtualization=true,gic-version=3 -nographic -m size=1024M -cpu cortex-a57  -smp 1 -kernel /root/duan/tools/linux/arch/arm64/boot/Image  -append "console=ttyAMA0 rw rdinit=/linuxrc" -initrd /root/duan/tools/busybox-1.31.0/_install/rootfs.cpio.gz 
/root/duan/qemu-arm64-system/bin/qemu-system-aarch64 \
	-qrtag \
	-machine virt,virtualization=true,gic-version=3 \
	-nographic \
	-m size=1024M \
	-cpu cortex-a57  \
	-smp cpus=8  \
	-kernel /root/duan/Image  \
	-append "console=ttyAMA0 rw rdinit=/linuxrc"  \
	 -initrd /root/duan/tools/busybox-1.31.0/qemufs/rootfs.cpio.gz
