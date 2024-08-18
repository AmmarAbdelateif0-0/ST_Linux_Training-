# My Memory Allocator

This project is a simple implementation of a custom memory allocator in C. It manages memory allocation and deallocation within a fixed-size heap, allowing for dynamic memory management using a basic metadata structure.

## Features

- Custom memory allocation and deallocation
- Heap management with a fixed-size memory block
- Metadata handling for memory blocks

## Code Overview

## Folder

### [`1-Heap_Version1`]()

The main file that contains the implementation of the custom memory allocator. It includes:

### Constants

- `page_size`: Defines the size of each page in bytes. (512 bytes)
- `MAX_SIZE`: Defines the maximum size of the heap. (2 MB)

### Global Variables

- `heap[MAX_SIZE]`: The static array that represents the heap.
- `program_break`: Pointer to the end of the heap, used to manage the heap's dynamic growth.
- `usage_malloc`: Counter for the number of allocated memory blocks.
- `last_node`: Pointer to the last allocated block.

### Structures

- `Metadata`: Structure used to store metadata about each memory block.
  - `start`: Start address of the memory block.
  - `size`: Size of the memory block.
  - `is_free`: Flag indicating whether the block is free.
  - `next`: Pointer to the next metadata block.

### Functions

- `split_break(size_t number_page)`: Adjusts the program break by increasing the heap size.
- `void *hmmalloc(size_t bytes)`: Allocates a block of memory of the specified size.
- `void hmfree(void *target)`: Frees the allocated memory block pointed to by `target`.
- `void traverse_heap(void *ptr)`: Traverses the heap and prints information about each memory block.
--------------------------------------
### [`2-Visualize_Heap`]()

A utility to visualize the current state of the heap. This file includes functionality to traverse and print details of allocated and free memory blocks, allowing you to see how memory is being used.

#### Overview

- **Purpose**: To print detailed information about the memory blocks in the heap, including their start address, size, allocation status, and next node address.
- **Usage**: Provides a clear view of how memory is allocated and deallocated, helping to verify the functionality of the allocator.

#### Files in `Visualize_Heap` Folder

- **`Visualize_Heap.c`**: Contains the code for visualizing the heap's state.

--------------------------------------------
### [`3-Randomization_test`]()

### Overview

The `Randomization_test` folder contains utilities designed to test the robustness and correctness of the custom memory allocator. It performs a series of randomized memory allocation and deallocation operations to evaluate the allocator's behavior under varying conditions. This test helps in identifying potential issues such as memory leaks, fragmentation, or incorrect memory management.

### Folder Contents

#### `strees_test.c`

This file contains the implementation of the randomization test. It performs a series of memory operations with random sizes and patterns to stress-test the allocator. The file includes logic for:

- **Random Allocation**: Allocating memory blocks of various sizes.
- **Random Deallocation**: Freeing memory blocks at random.
- **Error Reporting**: Providing feedback on allocation failures and reporting issues encountered during testing.
----------------------------


## Build Instructions

1. **Clone the Repository**

   ```sh
   git clone https://github.com/username/repository.git
   ```
- *Navigate to the Project Directory* :     
    ```sh
   cd <project-directory>
    ```    

- *Compile memory_allocator* : Use gcc or another compiler to compile the memory_allocator in Visualize_Heap or Randmization_test file have makefile so just write :


    ```sh    
        make 
     ```

Run the  output file from makefile : 

```   
        ./executable_file 
```

---------------------------------
