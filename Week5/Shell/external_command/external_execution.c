#include"../shell/shell.h"


void external_execution(char *cmd[]) {
    pid_t pid = fork();
    if (pid > 0) {
        int status;
        wait(&status);
    } else if (pid == 0) {
        execvp(cmd[0], cmd);
        perror("Execution failed");
        exit(EXIT_FAILURE);
    } else {
        perror("Fork failed");
    }
}
