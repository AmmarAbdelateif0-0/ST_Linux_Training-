all:output clean

output:heap.o stress_test.o
	@gcc -w heap.o stress_test.o -o output
heap.o:heap.c
	@gcc -c -w heap.c -o heap.o
stress_test.o:stress_test.c
	@gcc -c -w stress_test.c -o stress_test.o
clean:
	@rm -rf *.o
