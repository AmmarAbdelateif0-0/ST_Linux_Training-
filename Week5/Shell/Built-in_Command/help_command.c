#include"../shell/shell.h"


void help_exec() {
    printf("Built-in command :\n");
    printf("  mypwd   | pwd      - Print current working directory\n");
    printf("  myecho  | echo     - Print arguments to standard output\n");
    printf("  mycp    | cp       - Copy files\n");
    printf("  mymv    | mv       - Move files\n");
    printf("  myenvir | envir    - Print environment variables\n");
    printf("  mycd    | cd       - Change directory\n");
    printf("  exit               - Exit the shell\n");
    printf("  help               - Display this help message\n");
    printf("  type               - Display type of command\n");
}
