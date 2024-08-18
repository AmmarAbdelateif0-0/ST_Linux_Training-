#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stddef.h> // For size_t



// Function declarations
void*  split_break(size_t number_page);
void  *HmmAlloc(size_t bytes);
void  HmmFree(void *target);
void  traverse_heap();

#endif // HEAP_H
