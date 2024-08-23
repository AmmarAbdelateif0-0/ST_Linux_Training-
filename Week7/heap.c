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
	size_t raw_size = ( current->size - sizeof(metadata) );

	if (raw_size < size)
	{
		moved_size = raw_size;
	}
	else
	{
		moved_size = size;
	}

	memcpy(new_ptr, ptr, moved_size);
	HmmFree(ptr);
	return new_ptr;
}


void *HmmAlloc(size_t size ){
    size = ALIGN(size);
    int total_size=size+ sizeof(metadata);


    struct Metadata* current=list_free,*prev=list_free;
    while(current!=NULL){
        if(current->is_free && current->size > size + sizeof(metadata)){
            if(current->size > size+sizeof(metadata)){
            
            	split_block(current,size);

            }
            
            return (void*) ( current + sizeof(metadata) );
        }
        prev=current;
        current=current->next;
    }
    total_size+=PAGE_SIZE;	
    current =sbrk(total_size);

    if (current == (void*)-1){
        	sprintf(stderr,"sbrk failed");
		return NULL;
	}
    
    current->size=total_size;
    current->is_free=0;
    current->next=NULL;


        split_block(current, size);


    if (prev != NULL)
    {
        prev->next = current;
    }
    else
    {
        list_free = current;
    }

    return (char*) current + sizeof(metadata);

}
void HmmFree(void *ptr){

        if(ptr==NULL){
            return;
        }
        ptr-=sizeof(metadata);
        struct Metadata* current=list_free,*prev=NULL;
        while(current!=NULL){
            if(ptr == current) {
                current->is_free = 1;

                bool before_is_free = 0, after_is_free = 0;
                if (current->next->is_free && current->next != NULL) {
                    after_is_free = 1;
                }
                if (prev != NULL && prev->is_free) {
                    before_is_free = 1;
                }

                if (after_is_free && before_is_free) {
                    merge_blocks(prev, current);
                    merge_blocks(prev, current->next);
                }else if (!after_is_free && before_is_free)
                    merge_blocks(prev, current);
                else if (after_is_free && !before_is_free)
                    merge_blocks(current, current->next);

                return;
            }

            prev=current;
            current=current->next;
        }

}


// return 0 if successed | return -1 if failed
int split_block(struct Metadata * block , size_t size){


    if( ( block->size - (sizeof(metadata)+size) ) > ( sizeof(metadata) ) ){
        size = ALIGN(size);
        struct Metadata *new= (metadata*) (block+size+ sizeof(metadata) );
        new->size=block->size-(sizeof(metadata)+size);
        new->is_free=1;
        new->next=NULL;

        block->is_free=0;
        block->size=size+ sizeof(metadata);
        block->next=new;
        if(new->size < sizeof(metadata) ){
            sbrk(PAGE_SIZE);
            new->size+=PAGE_SIZE;
        }

        return 0;
    }

    return -1;

}


void merge_blocks(struct Metadata *block1,struct Metadata *block2){
    block1->next=block2->next;
    block1->size+=block2->size;

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
