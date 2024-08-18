all:main clean

Visualize_Heap:Visualize_Heap.o heap.o
	@gcc -w  Visualize_Heap.o heap.o -o Visualize_Heap
Visualize_Heap.o:Visualize_Heap.c
	@gcc -w -c Visualize_Heap.c -o  Visualize_Heap.o
heap.o:heap.c
	@gcc -w -c heap.c -o heap.o
clean:
	@rm -rf *.o
