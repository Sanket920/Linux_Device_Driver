obj-m := avgex.o addex.o
#module-obj := avgex.o addex.o
KERNELDIR = /lib/modules/$(shell uname -r)/build/
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

install:
	$(MAKE) -c $(KERNELDIR) M=$(PWD) modules_install

	depmod -a
