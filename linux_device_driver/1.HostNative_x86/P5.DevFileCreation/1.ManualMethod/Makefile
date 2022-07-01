obj-m := mndfc.o

ifdef ARCH

KERNELDIR = /lib/modules/5.15.45Darky@Sanky-v7l/build

default :
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERNELDIR) M=$(shell pwd) modules

clean :
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERNELDIR) M=$(shell pwd) clean

else

KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

endif
