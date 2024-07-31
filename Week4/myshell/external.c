#include"/home/ammar/Desktop/myshell/shell.h"

void external_exec(char *cmd[]) {
    pid_t pid = fork();
    if (pid > 0) {
        int status;
        wait(&status);
    } else if (pid == 0) {
        if (execvp(cmd[0], cmd) == -1) {
            perror("Error executing command");
            
        }
    } 
}
