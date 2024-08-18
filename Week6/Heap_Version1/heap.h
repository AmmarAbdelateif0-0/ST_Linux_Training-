#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stddef.h> // For size_t

#define PAGE_SIZE 512
#define MAX_SIZE ( 2*1024*1024 ) // 2 MB


typedef struct Metadata {
    void *start;           
    size_t size;           
    int is_free;           
    struct Metadata *next; 
} metadata;



// Function declarations
void*  split_break(size_t number_page);
void*  HmmAlloc(size_t bytes);
void   HmmFree(void *target);
void   traverse_heap();

#endif // HEAP_H
