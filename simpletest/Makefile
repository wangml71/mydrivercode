ifeq ($(KERNELRELEASE),)

# ARCH = arm

ifeq ($(ARCH),arm)
KERNELDIR ?= /home/wangml71/kernels/linux-5.10.186
OBJECTDIR ?= /home/wangml71/kernels/objects/vexpress-v2p-ca9
ROOTFS ?= /sync/rootfs
CROSS_COMPILE ?= arm-linux-gnueabi-
else
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
endif
PWD := $(shell pwd)

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) CROSS_COMPILE=$(CROSS_COMPILE) O=$(OBJECTDIR) modules

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) CROSS_COMPILE=$(CROSS_COMPILE) O=$(OBJECTDIR) modules INSTALL_MOD_PATH=$(ROOTFS) modules_install

clean:
	rm -rf  *.o  *.ko  .*.cmd  *.mod*  modules.order  Module.symvers   .tmp_versions

else
	obj-m += myhello.o
# obj-m += testparam.o
# obj-m += mychar.o
# obj-m += multimychar.o
# obj-m += atomicmychar.o
# obj-m += spinlockmychar.o
# obj-m += semaphoremychar.o
# obj-m += mutexmychar.o
# obj-m += kmallocmychar.o
# obj-m += ledmychar.o
# obj-m += dtledmychar.o
# obj-m += dtkeymychar.o
# obj-m += dttlkeymychar.o
# obj-m += dtwqkeymychar.o
# obj-m += dtkey3mychar.o
# obj-m += dttlkey3mychar.o
# obj-m += secondmychar.o


endif

