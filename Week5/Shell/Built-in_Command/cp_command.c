#include"../shell/shell.h"

void cp_exec(char *cmd[], int size) {
    if (size < 3) {
        fprintf(stderr, "Usage: cp <source> <destination>\n");
        return;
    }

    if (rename(cmd[1], cmd[2]) != 0) {
        perror("cp");
    }
}
