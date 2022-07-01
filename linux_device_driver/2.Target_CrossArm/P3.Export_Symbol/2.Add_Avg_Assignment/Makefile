obj-y := Avg_module/ Add_module/
KERNELDIR = /lib/modules/5.15.45Darky@Sanky-v7l/build
PWD := $(shell pwd)

default :
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERNELDIR) M=$(PWD) modules

clean :
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERNELDIR) M=$(PWD) clean

install:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERNELDIR) M=$(PWD) modules_install


	depmod -a
