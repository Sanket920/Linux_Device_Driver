obj-m := mod_p.o
KERNELDIR = /lib/modules/5.15.45Darky@Sanky-v7l/build
PWD :=$(shell pwd)

default :
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERNELDIR) M=$(PWD) modules

install :
	make ARCH=arm CROSS_COMPILE=arm-linux-gnnueabihf -C $(KERNELDIR) M=$(PWD) modules_install

clean :
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERNELDIR) M=$(PWD) clean
