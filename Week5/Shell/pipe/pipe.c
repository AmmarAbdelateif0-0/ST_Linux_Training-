#include"../shell/shell.h"

void handle_piping(char *cmd1[], char *cmd2[]) {
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    // Second child process for cmd1
    if(is_internal_command(cmd1)){
    	exexction(cmd1,2);
    }
    else{
    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipefd[0]); 
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]); 

        if (execvp(cmd1[0], cmd1) == -1) {
            perror("Error executing first command");
            exit(EXIT_FAILURE);
        }
    }
  }	
    // Second child process for cmd2
    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipefd[1]); 
        dup2(pipefd[0], STDIN_FILENO); 
        close(pipefd[0]); 

        if (execvp(cmd2[0], cmd2) == -1) {
            perror("Error executing second command");
            exit(EXIT_FAILURE);
        }
    }

    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both child processes
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
