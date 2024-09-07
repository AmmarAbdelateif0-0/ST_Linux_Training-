#include"./shell.h"


extern char** environ;

int main(void) {
    char *cmd = NULL, *cpy_cmd = NULL, *token = NULL;
    char *delim = " \n";
    size_t n = 0;
    int argc = 0, count = 0;
    char **argv = NULL;

    const char *exit_t = "exit";
    const char *prompet = "8ol_ya_sayed:";

    const char *prompet2= ":>$$ ";
    do {
	    pwd_exec();
        write(STDOUT, prompet, strlen(prompet));
	printf("%s",prompet2);
       	if (getline(&cmd, &n, stdin) == -1) {
            perror("Failure");
            cmd = NULL;
            continue;
        }
        if (strcmp(cmd, "\n") == 0) {
            continue;
        }

        cpy_cmd = strdup(cmd);
        if (cpy_cmd == NULL) {
            perror("Failed to allocate memory");
            continue;
        }

        // Count arguments
        token = strtok(cmd, delim);
        while (token) {
            argc++;
            token = strtok(NULL, delim);
        }

        argv = malloc(sizeof(char*) * (argc + 1));
        if (argv == NULL) {
            perror("Failed to allocate memory");
            free(cpy_cmd);
            continue;
        }

        // Tokenize command
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

        if (strcmp(exit_t, argv[0]) == 0) {
            printf("Good Bye :(\"\"\"\"\"\"\"\"\"\n");
            break;
        } else {
            if (handle_redirection(argv, count)) {
                continue;
            }
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

    free(cmd);
    return 0;
}





