#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
void exexction(char argv[], int size);

#define STDIN  0
#define STDOUT 1
#define STDERR 2


int main(void){

        char * cmd = NULL,*cpy_cmd = NULL ,* token= NULL;
        char *delim=" \n";
        size_t n =0 ;
        int argc=0,count=0;
        char **argv=NULL;
        const char *exit="exit";
        const char *prompet="o2mor>$";
       do{
                write(STDOUT,prompet,strlen(prompet));

                if(getline(&cmd,&n,stdin)==-1)
                {
                        perror("Failure");
                }
                cpy_cmd=strdup(cmd);

                token=strtok(cmd,delim);
                while(token){
                        token=strtok(NULL,delim);
                        argc++;
                }
                argv=malloc(sizeof(char ) * argc);

                token = strtok(cpy_cmd,delim);
                while(token){
                        argv[count]=token;
                        token=strtok(NULL,delim);
                        count++;
                }
                argv[count]=NULL;
                count=0;
                while(argv[count]){
                        printf("%s ",argv[count++]);
                        
                }
                printf("\n");
                argc=0;
                count=0;
               // free(cmd),
               

                if(!strcmp(exit,argv[0])){
                    printf("Good Bye :(\n");
                    break;
                }
                 free(cpy_cmd),free(argv);

             //   int exittx=strcmp(token,exit);


        }while(1);
        return 0;
}


void exexction(char argv[], int size){

}
  