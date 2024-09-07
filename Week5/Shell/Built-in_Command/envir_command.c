#include"../shell/shell.h"

void print_envir() {
    for (char **env = environ; *env != 0; env++) {
        printf("%s\n", *env);
    }
}

void envir_exec(char *cmd[], int size) {
    if(size==1){
    	print_envir();
    }
    else if (size == 2) {
   	    	 const char *variable = cmd[1];
            	 char *value = getenv(variable);

   	 if (value != NULL) {
   	    	 printf("%s=%s\n", variable, value);
   	 } else {
   	    	 printf("%s is not set\n", variable);
   	 }

    }
    else{
        	fprintf(stderr, "Usage: envir <variable> | envir to shoe environment variable \n");
        	return;
    }


}
