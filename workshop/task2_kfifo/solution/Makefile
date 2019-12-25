obj-m := hook.o
hook-y := module.o logger.o


KVERSION = $(shell uname -r)
KDIR := /lib/modules/$(KVERSION)/build

CFLAGS_$(obj-m) := -g -DDEBUG

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
