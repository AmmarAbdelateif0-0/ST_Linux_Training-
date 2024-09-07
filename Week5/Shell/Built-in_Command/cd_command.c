#include"../shell/shell.h"


void cd_exec(char *cmd[], int size) {
    if (size < 2) {
        fprintf(stderr, "Usage: cd <directory>\n");
        return;
    }

    if (chdir(cmd[1]) != 0) {
        perror("cd");
    }
}
