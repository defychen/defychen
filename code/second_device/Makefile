ifneq ($(KERNELRELEASE), )

obj-m := second_device.o

else

EXTRA_CFLAGS += DDEBUG
KDIR := /home/defychen/repository_software/linux-4.4.189
all:
	make CROSS_COMPILE=arm-linux-gnueabi- ARCH=arm -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.ko *.o *.mod.o *.mod.c *.symvers *.order .*.ko .tmp_versions
endif

.PYONY:all clean
