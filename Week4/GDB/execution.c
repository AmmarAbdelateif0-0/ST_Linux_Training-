#include"/home/ammar/Desktop/myshell/shell.h"

void exexction(char *argv[], int size) {
    if (argv[0] == NULL) {
        return;
    }

       if (strcmp(argv[0], "type") == 0) {
        type_exec(argv, size);
       }else if (strcmp(argv[0], "mycp") == 0) {
            cp_exec(argv, size);
       }else if (strcmp(argv[0], "mymv") == 0) {
            mv_exec(argv, size);
       }else if (strcmp(argv[0], "mycd") == 0) {
            cd_exec(argv, size);
       }else if (strcmp(argv[0], "mypwd") == 0) {
            pwd_exec();
       }else if (strcmp(argv[0], "myecho") == 0) {
            echo_exec(argv, size);
       }else if (strcmp(argv[0], "help") == 0) {
            help_exec();
       }else if (strcmp(argv[0], "myenvir") == 0) {
            envir_exec(argv,size);
       }else {
        external_exec(argv);
    	}
}

