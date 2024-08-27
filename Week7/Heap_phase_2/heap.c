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


