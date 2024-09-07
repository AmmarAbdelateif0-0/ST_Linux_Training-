#include"../shell/shell.h"

void error_exec() {
    perror("Command failed");
}

void exexction(char *argv[], int size) {
    // Check for piping
    
    int pipe_pos = -1;
    for (int i = 0; i < size; i++) {
        if (strcmp(argv[i], "|") == 0) {
            pipe_pos = i;
            break;
        }
    }

    if (pipe_pos != -1) {
            argv[pipe_pos] = NULL;  
             // First command
            char **cmd1 = argv;
            // Second command
            char **cmd2 = &argv[pipe_pos + 1];
            handle_piping(cmd1, cmd2);
    } 
    else {
        // No pipe, handle normally

    if (strcmp(argv[0], "type") == 0) {
        type_exec(argv, size);
    } else if (strcmp(argv[0], "cp") == 0 || strcmp(argv[0], "mycp") == 0) {
        cp_exec(argv, size);
    } else if (strcmp(argv[0], "mv") == 0 || strcmp(argv[0], "mymv") == 0) {
        mv_exec(argv, size);
    } else if (strcmp(argv[0], "cd") == 0 || strcmp(argv[0], "mycd") == 0  ) {
        cd_exec(argv, size);
    } else if (strcmp(argv[0], "pwd") == 0 || strcmp(argv[0], "mypwd") == 0 ) {
        pwd_exec(); printf("\n");
    } else if (strcmp(argv[0], "echo") == 0 ||  strcmp(argv[0], "myecho") == 0) {
        echo_exec(argv, size);
    } else if (strcmp(argv[0], "help") == 0) {
        help_exec();
    } else if (strcmp(argv[0], "envir") == 0 || strcmp(argv[0], "myenvir") == 0) {
        envir_exec(argv, size);
    } else if (strcmp(argv[0], "free") == 0) {
        free_exec();
    } else if (strcmp(argv[0], "uptime") == 0) {
        uptime_exec();
    } else {
                    external_execution(argv);
            }
    }
}
