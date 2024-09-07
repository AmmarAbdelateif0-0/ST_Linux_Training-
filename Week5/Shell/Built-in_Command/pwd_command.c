#include"../shell/shell.h"


void pwd_exec() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s", cwd);
    } else {
        perror("pwd");
    }
}
