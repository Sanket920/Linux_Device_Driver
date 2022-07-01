obj-m := dmmn.o
KERNELDIR = /lib/modules/5.15.45Darky@Sanky-v7l/build
PWD := $(shell pwd)

default :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
