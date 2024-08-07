#include"/home/ammar/Desktop/myshell/shell.h"

#define STDIN  0
#define STDOUT 1
#define STDERR 2

int main(void) {

    char *cmd = NULL, *cpy_cmd = NULL, *token = NULL;
    char *delim = " \n";
    size_t n = 0;
    int argc = 0, count = 0;
    char **argv = NULL;

    const char *exit_t = "exit";
    const char *prompet = "8ol_ya_sayed:>";

    do {
        write(STDOUT, prompet, strlen(prompet));
        if (getline(&cmd, &n, stdin) == -1) {
            perror("Failure");
        }

        cpy_cmd = strdup(cmd);
        if (cpy_cmd == NULL) {
            perror("Failed to allocate memory");
        }

        token = strtok(cmd, delim);
        while (token) {
            argc++;
            token = strtok(NULL, delim);
        }

        argv = malloc(sizeof(char*) * (argc + 1));
        if (argv == NULL) {
            perror("Failed to allocate memory");
        }

        count = 0;
        token = strtok(cpy_cmd, delim);
        while (token) {
            argv[count] = strdup(token);
            if (argv[count] == NULL) {
                perror("Failed to allocate memory");
            }
            count++;
            token = strtok(NULL, delim);
        }
        argv[count] = NULL;

        if (argv[0] == NULL || strcmp(argv[0], "\n") == 0) {
            continue;
        }
        else if (strcmp(exit_t, argv[0]) == 0) {
                printf("Good Bye :(\"\"\"\"\"\"\"\"\"\n");
		break;
        }
        else {
            exexction(argv, count);
        }

        // Clean up
        free(cpy_cmd);
        for (int i = 0; i < count; i++) {
            free(argv[i]);
        }
        free(argv);

        argc = 0;
        count = 0;

    } while (1);

    return 0;
}

