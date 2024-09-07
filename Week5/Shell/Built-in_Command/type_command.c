#include"../shell/shell.h"

int is_internal_command(const char *cmd) {
    for (int i = 0; internal_commands[i] != NULL; i++) {
        if (strcmp(cmd, internal_commands[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void type_exec(char *cmd[], int size) {
    if (size < 2) {
        fprintf(stderr, "Usage: type <command>\n");
        return;
    }

    if (is_internal_command(cmd[1])) {
        printf("%s is a shell built-in command\n", cmd[1]);
    } else {
        printf("%s is an external command\n", cmd[1]);
    }
}
