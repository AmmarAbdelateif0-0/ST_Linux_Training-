#include<stdio.h>
#include"./heap.h"

int main(void){
    printf("           *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n");
    printf("           *              MY_HEAP_VERSION1             *\n");
    printf("           *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n\n\n");

    while (1)
    {   
        printf("*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n");
        printf("* 1-Heap Memory allocated                               *\n");
        printf("* 2-To Free Specific memory                             *\n");
        printf("* 3-To Traves All Heap Memory allocated                 *\n");
        printf("* 4-To exit                                             *\n");
        printf("*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n");
        printf("Enter Number Of Operation You Want = ");
        int num_operation=0;
        scanf("%d",&num_operation);;

        switch (num_operation)
        {
        case 1:
            int Bytes=0;
            printf("Enter your size (Byte) you want allocated =");
            scanf("%d",&Bytes);
            void *return_value=HmmAlloc(Bytes);
            if(NULL==return_value){
                printf("Allocation Failed\n");
            }
            else{
                printf("************************************************************\n");
                printf("*       Allocation Successed at Address = %p               \n",return_value);
                printf("************************************************************\n");
            }
            break;
        case 2:
            void *ptr1;
	    void *ptr2=&ptr1;
            printf("Enter address you want to free if you don't kwon this address use travers to Konw : ");
            scanf("%p",ptr2);
            HmmFree(ptr1);
            break;
        case 3:
                traverse_heap();
            break;
        case 4:
            return 0;
            break;
        default:
        printf("invalid number \n");
            break;
        }
       printf("\n\n"); 
    }
    
}
