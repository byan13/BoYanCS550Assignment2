obj-m:= process_list.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(shell pwd) modules
	gcc -g -Wall user.c -o user
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(shell pwd) clean
	rm user
