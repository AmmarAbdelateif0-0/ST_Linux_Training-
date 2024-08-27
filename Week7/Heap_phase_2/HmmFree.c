#include"./heap.h"

void HmmFree(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    struct Metadata *block = (struct Metadata *)((char *)ptr - sizeof(struct Metadata));
    block->is_free = 1;

    struct Metadata *current = list_free, *prev = NULL;

    while (current != NULL) {
        if (current == block) {
        
            bool before_is_free = (prev != NULL && prev->is_free);
            bool after_is_free = (current->next != NULL && current->next->is_free);

            if (before_is_free && after_is_free) {
                merge_blocks(prev, current);
                merge_blocks(prev, current->next);
            } else if (!after_is_free && before_is_free) {
                merge_blocks(prev, current);
            } else if (after_is_free && !before_is_free) {
                merge_blocks(current, current->next);
            }
            return;
        }
        prev = current;
        current = current->next;
    }
}

void merge_blocks(struct Metadata *block1,struct Metadata *block2){
    block1->size += block2->size;
    block1->next = block2->next;
}
