all:myfdisk clean

myfdisk:myfdisk.o
	@gcc myfdisk.o -o myfdisk
myfdisk.o:myfdisk.c
	@gcc -c myfdisk.c -o myfdisk.o
clean:
	@rm -rf *.o
