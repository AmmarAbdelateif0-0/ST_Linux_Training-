#include"./heap.h"


void *HmmAlloc(size_t size) {
    size = ALIGN(size);
    size_t total_size = size + sizeof(struct Metadata);

    struct Metadata *current = list_free, *prev = NULL;

    while (current != NULL) {
        if (current->is_free && current->size >= total_size) {
            if (current->size > total_size + sizeof(struct Metadata)) {
                split_block(current, size);
            }
            current->is_free = 0;
            return (char *)current + sizeof(struct Metadata);
        }
        prev = current;
        current = current->next;
    }

    current = (struct Metadata *)sbrk(total_size);
    if (current == (void *)-1) {
        perror("sbrk failed");
        return NULL;
    }

    current->size = total_size;
    current->is_free = 0;
    current->next = NULL;

    if (prev != NULL) {
        prev->next = current;
    } else {
        list_free = current;
    }

    return (char *)current + sizeof(struct Metadata);
}


// return 0 if successed | return -1 if failed
int split_block(struct Metadata *block, size_t size) {
    size = ALIGN(size);
    size_t total_size = sizeof(struct Metadata) + size;

    if ((block->size - total_size) >= sizeof(struct Metadata)) {
        struct Metadata *new_block = (struct Metadata *)((char *)block + total_size);
        new_block->size = block->size - total_size;
        new_block->is_free = 1;
        new_block->next = block->next;

        block->size = total_size;
        block->next = new_block;

        return 0;
    }
    return -1;
}

