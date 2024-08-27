#ifndef HEAP_H
#define HEAP_H

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>



#define ALIGN(size) (((size) + (sizeof(void*) - 1)) & ~(sizeof(void*) - 1))


#define PAGE_SIZE (1024*1024)

typedef struct Metadata{
    struct Metadata* next;
    int size;
    bool is_free;
}metadata;

static struct Metadata* list_free =NULL;

// Function declarations for heap management

void *malloc(size_t size);

void free(void *ptr);

void *calloc(size_t nmemb, size_t size);

void *realloc(void *ptr, size_t size);

void HmmFree(void *ptr);

void merge_blocks(struct Metadata *block1,struct Metadata *block2);

void *HmmAlloc(size_t size);

int split_block(struct Metadata *block, size_t size);




#endif // HEAP_H
