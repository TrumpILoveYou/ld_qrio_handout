/usr/local/bin/qemu-system-aarch64 \
	-machine virt,virtualization=true,gic-version=3 \
	-nographic \
	-m size=1024M \
	-cpu cortex-a57  \
	-smp 1 \
	-hda busybox-1.30.1-rootfs_ext4.img \
	-kernel /home/jjh/linux/arch/arm64/boot/Image  \
	-append "root=/dev/vda rw console=ttyAMA0 rdinit=/linuxrc"  \

#-drive if=none,file=busybox-1.30.1-rootfs_ext4.img,id=hd0 -device virtio-blk-device,drive=hd0 \
