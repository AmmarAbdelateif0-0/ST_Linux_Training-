#include"../shell/shell.h"


void print_argument(const char *arg) {
    if (arg[0] == '"' && arg[strlen(arg) - 1] == '"') {
        printf("%.*s", (int)(strlen(arg) - 2), arg + 1);     
    }
    else {
        printf("%s", arg);
    }
}

void echo_exec(char *cmd[], int size) {
	
    for (int i = 1; i < size; i++) {
  
       if (i > 1) {
            printf(" ");
        }

        print_argument(cmd[i]);
    }


    printf("\n");
}
