#include "./heap.h"


static char heap[MAX_SIZE];

static void *program_break=heap;
static int    usage_malloc=0;
static void  *last_node=heap;

metadata Listhead[MAX_SIZE]={ {&heap[0],0,1,NULL} };

void* split_break(size_t number_page){
    program_break+=PAGE_SIZE*number_page;
    return program_break;
}
void *HmmAlloc(size_t bytes){
    if(bytes==0 || last_node+bytes > (void*)&heap[MAX_SIZE-1]){
        sprintf(stderr,"Heap is Full");
        return NULL;
    }
    int count=0;
    int delete=1;
    if(program_break <= ( last_node+bytes+sizeof(metadata) )){
        int num=( ( (int)( (void *)heap - last_node ) )+bytes+sizeof(metadata))/PAGE_SIZE;
        (num)? split_break(num+1):split_break(1);
    }
    while(usage_malloc > count){
        if(Listhead[count].is_free && Listhead[count].size >= bytes)
        {
            break;
        } else{
                count++;
        }
    }

    if(count==0)
        delete=0;
    else
        delete=1;

    Listhead[count].start =Listhead[count-delete].start + Listhead[count-delete].size;
    Listhead[count].size=bytes;
    Listhead[count].is_free=0;
    Listhead[count].next=Listhead[count].start +bytes;
    last_node=Listhead[count].next;
    usage_malloc++;
    return Listhead[count].start;
}

void HmmFree(void *target){
    int count=0;
    if(target==NULL){
        sprintf(stderr,"NULL Pointer can't Free");

        return;
    }
    while(usage_malloc > count){
        if(Listhead[count].start==target)
        {
            Listhead[count].is_free=1;
            break;
        } else{
            count++;
        }
    }
}
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
