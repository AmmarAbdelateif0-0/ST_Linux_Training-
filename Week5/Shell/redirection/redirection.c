#include"../shell/shell.h"

void execution_for_redirection(char *argv[], int size) {
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
    } else if (strcmp(argv[0], "envir") == 0 ||  strcmp(argv[0], "myenvir") == 0) {
        envir_exec(argv, size);
    } else if (strcmp(argv[0], "free") == 0) {
        free_exec();
    } else if (strcmp(argv[0], "uptime") == 0) {
        uptime_exec();
    } else {
        if (execvp(argv[0], argv) == -1) {
            perror("Error executing command");
        }
    }
}

int handle_redirection(char *argv[], int size) {
    int fd;
    pid_t pid;
    int redirection_found = 0;
    int counter=0;   // to calc size of command before redirection sympol
    for (int i = 0; i < size; i++) {
        if (strcmp(argv[i], ">") == 0 || strcmp(argv[i], ">>") == 0 ||
            strcmp(argv[i], "<") == 0 || strcmp(argv[i], "2>") == 0) {
            redirection_found++;
            pid = fork();
            if (pid < 0) {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            }

            // Child process
            if (pid == 0) {
                if (strcmp(argv[i], ">") == 0) {
                    // Output redirection
                    fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd == -1) {
                        perror("Failed to open output file");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    argv[i] = NULL;
                    if(counter==0){
                    	counter=i;
                    }
                } else if (strcmp(argv[i], ">>") == 0) {
                    // Append redirection
                    fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                    if (fd == -1) {
                        perror("Failed to open output file");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    argv[i] = NULL;
                    if(counter==0){
                    	counter=i;
                    }
                } else if (strcmp(argv[i], "<") == 0) {
                    // Input redirection
                    fd = open(argv[i + 1], O_RDONLY);
                    if (fd == -1) {
                        perror("Failed to open input file");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                    argv[i] = NULL;
                    if(counter==0){
                    	counter=i;
                    }
                } else if (strcmp(argv[i], "2>") == 0) {
                    // Error redirection
                    fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd == -1) {
                        perror("Failed to open error file");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd, STDERR_FILENO);
                    close(fd);
                    argv[i] = NULL;
                    if(counter==0){
                    	counter=i;
                    }
                }
                execution_for_redirection(argv, counter);
                exit(EXIT_SUCCESS);
            }


            else {
                int status;
                waitpid(pid, &status, 0);
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                    fprintf(stderr, "Command failed with exit status %d\n", WEXITSTATUS(status));
                }
            }
        }
    }
    return redirection_found;
}
