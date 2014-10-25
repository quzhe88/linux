obj-m=test.o
KDIR :=/usr/src/linux-3.11.10-7-obj/i386/default

all:
	make -C $(KDIR) M=$(shell pwd)
clean:
	rm -rf *.o .*cmd *.ko *.mod.c *.symvers *.order *marker .*tmp_versions