#include"../shell/shell.h"

void mv_exec(char *cmd[], int size) {
    if (size < 3) {
        fprintf(stderr, "Usage: mv <source> <destination>\n");
        return;
    }

    if (rename(cmd[1], cmd[2]) != 0) {
        perror("mv");
    }
}
