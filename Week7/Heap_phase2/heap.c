#include "./heap.h"

void* malloc(size_t size){
	return HmmAlloc(size);
}

void free(void *ptr){
	HmmFree(ptr);
}
void *calloc(size_t nmemb,size_t size){
	void *ptr=HmmAlloc(nmemb * size);
	if(ptr==NULL)
		return NULL;
	memset(ptr,0,size * nmemb);
	return ptr;
}

void *realloc(void *ptr, size_t size) {
if (ptr == NULL && size == 0){
		return NULL;
	}
	else if (ptr == NULL){
		return HmmAlloc(size);
	}
	else if (size == 0){
		HmmFree(ptr); return NULL;
	}

	struct Metadata *current = ((char*) ptr - sizeof(metadata));

	void *new_ptr = HmmAlloc(size);

	if (new_ptr == NULL){
		return NULL;
	}

	size_t moved_size;
	size_t data_size = ( current->size - sizeof(metadata) );

	if (data_size < size)
	{
		moved_size = data_size;
	}
	else
	{
		moved_size = size;
	}

	memcpy(new_ptr, ptr, moved_size);

	HmmFree(ptr);
	return new_ptr;
}


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


void merge_blocks(struct Metadata *block1,struct Metadata *block2){
    block1->size += block2->size;
    block1->next = block2->next;


}
/*
void traverse_heap(){
    int count=0;

    printf("\n          **  Allocated blocks  **\n");
    while (Listhead[count].start!=NULL){

        printf("*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n");
        printf("*Start Address of block ( %d ) = %p            *\n",count+1,Listhead[count].start);
        printf("*Size = %d                                    *\n",Listhead[count].size);
        printf("*Is_Free = %s                                 *\n",Listhead[count].is_free?"Yes":"NO");
        printf("*Address Next block = %p                       *\n",Listhead[count].next);
        printf("*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n");
        printf("\n");
        count++;
    }
}
*/
