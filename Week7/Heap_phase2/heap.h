#ifndef HEAP_H
#define HEAP_H

#include<stdio.h>
#include<string.h>
#include <stdbool.h>
#include <unistd.h>

#define ALIGN(size) (((size) + (sizeof(void*) - 1)) & ~(sizeof(void*) - 1))

#define HEAP_SIZE (40*1024*1024)
#define PAGE_SIZE (1024*1024)

typedef struct Metadata{
    struct Metadata* next;
    int size;
    bool is_free;
}metadata;

char heap[HEAP_SIZE];
struct Metadata* list_free =NULL;
char* program_break=heap;

void *HmmAlloc(size_t size );

int split_block(struct Metadata * block , size_t size);

void HmmFree(void *ptr);

void merge_blocks(struct Metadata *block1,struct Metadata *block2);

void   traverse_heap();

#endif // HEAP_H
