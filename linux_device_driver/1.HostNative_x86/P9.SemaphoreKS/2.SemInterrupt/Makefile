obj-m := drSem_I.o

ifdef ARCH

KERNELDIR = /lib/modules/5.15.45Darky@Sanky-v7l/build

default:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERNELDIR) M=$(shell pwd) modules
	arm-linux-gnueabihf-gcc -o write1 write1.c
	arm-linux-gnueabihf-gcc -o write2 write2.c
	arm-linux-gnueabihf-gcc -o read1 read1.c

clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERNELDIR) M=$(shell pwd) clean
	rm write1 write2 read1

else

KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o write1 write1.c
	gcc -o write2 write2.c
	gcc -o read1 read1.c

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm write1 write2 read1

endif
