# Memory Management Library

This project implements a simple memory management library with custom allocation and deallocation functions. The library provides functions to allocate and free memory blocks, manage free lists, and handle memory fragmentation.

## Files

- `heap.h`: Header file containing the definitions and declarations for the memory management functions.
- `heap.c`: Source file containing the implementation for malloc,calloc, realloc and free.
- `HmmAlloc.c` :Source file containing the implementation for HmmAlloc and split_block .
- `HmmFree.c`:Source file containing the implementation for HmmFree and merge_block .



## Functions

### `void *HmmAlloc(size_t size)`

Allocates a block of memory of the specified size.

- **Parameters**: 
  - `size`: The size of the memory block to allocate.
- **Returns**: 
  - A pointer to the allocated memory block, or `NULL` if allocation fails.

### `void HmmFree(void *ptr)`

Frees a previously allocated block of memory.

- **Parameters**: 
  - `ptr`: A pointer to the memory block to free.

### `void* sbrk(size_t size)`

Increases the program's data space by the specified size.

- **Parameters**: 
  - `size`: The size by which to increase the data space.
- **Returns**: 
  - A pointer to the new program break.

### `int split_block(struct Metadata *block, size_t size)`

Splits a memory block into two smaller blocks if possible.

- **Parameters**: 
  - `block`: A pointer to the memory block to split.
  - `size`: The size of the first block after splitting.
- **Returns**: 
  - `0` if the block was successfully split, `-1` otherwise.

### `void merge_blocks(struct Metadata *block1, struct Metadata *block2)`

Merges two adjacent memory blocks into a single block.

- **Parameters**: 
  - `block1`: A pointer to the first memory block.
  - `block2`: A pointer to the second memory block.

## Metadata Structure

The `Metadata` structure is used to manage memory blocks and contains the following fields:

- `size`: The size of the memory block.
- `is_free`: A flag indicating whether the block is free.
- `next`: A pointer to the next memory block in the free list.

## Usage

To use the memory management library, include the `heap.h` header file in your project and link against the compiled `heap.c` source file.

```c
#include "heap.h"

int main() {
    void *ptr = HmmAlloc(100);
    if (ptr != NULL) {
        // Use the allocated memory
    }

    HmmFree(ptr);
    return 0;
}
```
## Build Instructions

1. **Clone the Repository**

   ```sh
   git clone https://github.com/username/repository.git
   ```
- *Navigate to the Project Directory* :     
    ```sh
   cd <project-directory>
    ```    

- *to create shared library* : 

    ```sh    
        gcc -c -fPIC *.c 
     ```

     ```sh
        gcc --shared -o libhmm.c *.o
    ```
- *to replace real malloc , calloc , realloc and free with HmmAlloc and HmmFree* :

    ```sh
        LD_PRELOAD=[realpath dynamic library] [procces]
    ```
    - ex :
    ```sh
        LD_PRELOAD=./libHmm bash
        
        LD_PRELOAD=./libHmm ls

    ```

# testing Video

https://github.com/user-attachments/assets/29ec717c-5e2b-48df-ba46-569463aa63a7


---------------------------------
