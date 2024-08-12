#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char** environ;

static const char *internal_commands[] = {
    "mypwd",
    "mymecho",
    "mycp",
    "mymv",
    "exit",
    "help",
    "myenvir",
    "mycd",
    "type",
    "free",
    "uptime",
    NULL
};

void execution_for_redirection(char *argv[], int size);
int handle_redirection(char *argv[], int size);
void handle_piping(char *cmd1[], char *cmd2[]);
void external_execution(char *cmd[]);
void cp_exec(char *cmd[], int size);
void mv_exec(char *cmd[], int size);
void echo_exec(char *cmd[], int size);
void pwd_exec();
void help_exec();
void error_exec();
void cd_exec(char *cmd[], int size);
void print_envir();
int is_internal_command(const char *cmd);
void type_exec(char *cmd[], int size);
void envir_exec(char *cmd[], int size);
void free_exec();
void uptime_exec();

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

void handle_piping(char *cmd1[], char *cmd2[]) {
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipefd[0]); // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]); // Close write end after dup

        if (execvp(cmd1[0], cmd1) == -1) {
            perror("Error executing first command");
            exit(EXIT_FAILURE);
        }
    }

    // Second child process for cmd2
    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipefd[1]); // Close unused write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe
        close(pipefd[0]); // Close read end after dup

        if (execvp(cmd2[0], cmd2) == -1) {
            perror("Error executing second command");
            exit(EXIT_FAILURE);
        }
    }

    // Parent process
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both child processes
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

void execution_for_redirection(char *argv[], int size) {
    if (strcmp(argv[0], "type") == 0) {
        type_exec(argv, size);
    } else if (strcmp(argv[0], "cp") == 0) {
        cp_exec(argv, size);
    } else if (strcmp(argv[0], "mv") == 0) {
        mv_exec(argv, size);
    } else if (strcmp(argv[0], "cd") == 0) {
        cd_exec(argv, size);
    } else if (strcmp(argv[0], "pwd") == 0) {
        pwd_exec();
    } else if (strcmp(argv[0], "echo") == 0) {
        echo_exec(argv, size);
    } else if (strcmp(argv[0], "help") == 0) {
        help_exec();
    } else if (strcmp(argv[0], "envir") == 0) {
        envir_exec(argv, size);
    } else if (strcmp(argv[0], "free") == 0) {
        free_exec();
    } else if (strcmp(argv[0], "uptime") == 0) {
        uptime_exec();
    } else {
        if (execvp(argv[0], argv) == -1) {
            perror("Error executing command");
        }
    }
}

int handle_redirection(char *argv[], int size) {
    int fd;
    pid_t pid;
    int redirection_found = 0;

    for (int i = 0; i < size; i++) {
        if (strcmp(argv[i], ">") == 0 || strcmp(argv[i], ">>") == 0 ||
            strcmp(argv[i], "<") == 0 || strcmp(argv[i], "2>") == 0) {
            redirection_found++;
            pid = fork();
            if (pid < 0) {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            }

            // Child process
            if (pid == 0) {
                if (strcmp(argv[i], ">") == 0) {
                    // Output redirection
                    fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd == -1) {
                        perror("Failed to open output file");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    argv[i] = NULL;
                } else if (strcmp(argv[i], ">>") == 0) {
                    // Append redirection
                    fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                    if (fd == -1) {
                        perror("Failed to open output file");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    argv[i] = NULL;
                } else if (strcmp(argv[i], "<") == 0) {
                    // Input redirection
                    fd = open(argv[i + 1], O_RDONLY);
                    if (fd == -1) {
                        perror("Failed to open input file");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                    argv[i] = NULL;
                } else if (strcmp(argv[i], "2>") == 0) {
                    // Error redirection
                    fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd == -1) {
                        perror("Failed to open error file");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd, STDERR_FILENO);
                    close(fd);
                    argv[i] = NULL;
                }
                // Remove the redirection operator and file from the arguments
                execution_for_redirection(argv, size);
                exit(EXIT_SUCCESS);
            }

            // Parent process
            else {
                int status;
                waitpid(pid, &status, 0);
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                    fprintf(stderr, "Command failed with exit status %d\n", WEXITSTATUS(status));
                }
            }
        }
    }
    return redirection_found;
}

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

void cp_exec(char *cmd[], int size) {
    if (size < 3) {
        fprintf(stderr, "Usage: cp <source> <destination>\n");
        return;
    }

    if (rename(cmd[1], cmd[2]) != 0) {
        perror("cp");
    }
}

void mv_exec(char *cmd[], int size) {
    if (size < 3) {
        fprintf(stderr, "Usage: mv <source> <destination>\n");
        return;
    }

    if (rename(cmd[1], cmd[2]) != 0) {
        perror("mv");
    }
}

void echo_exec(char *cmd[], int size) {
    for (int i = 1; i < size; i++) {
        if (i > 1) {
            printf(" ");
        }
        printf("%s", cmd[i]);
    }
    printf("\n");
}

void pwd_exec() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
}

void help_exec() {
    printf("Available commands:\n");
    printf("  mypwd      - Print current working directory\n");
    printf("  myecho     - Print arguments to standard output\n");
    printf("  mycp       - Copy files\n");
    printf("  mymv       - Move files\n");
    printf("  exit       - Exit the shell\n");
    printf("  help       - Display this help message\n");
    printf("  myenvir    - Print environment variables\n");
    printf("  cd         - Change directory\n");
    printf("  type       - Display type of command\n");
}

void error_exec() {
    perror("Command failed");
}

void cd_exec(char *cmd[], int size) {
    if (size < 2) {
        fprintf(stderr, "Usage: cd <directory>\n");
        return;
    }

    if (chdir(cmd[1]) != 0) {
        perror("cd");
    }
}

void print_envir() {
    for (char **env = environ; *env != 0; env++) {
        printf("%s\n", *env);
    }
}

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
void envir_exec(char *cmd[], int size) {
    if(size==1){
    	print_envir();
    }
    else if (size == 2) {
   	    	 const char *variable = cmd[1];
            	 char *value = getenv(variable);

   	 if (value != NULL) {
   	    	 printf("%s=%s\n", variable, value);
   	 } else {
   	    	 printf("%s is not set\n", variable);
   	 }

    }
    else{
        	fprintf(stderr, "Usage: envir <variable> | envir to shoe environment variable \n");
        	return;
    }


}
void free_exec() {
    FILE *meminfo = fopen("/proc/meminfo", "r");
    if (meminfo == NULL) {
        perror("Failed to open /proc/meminfo");
        return;
    }

    char line[256];
    long total_ram = 0, free_ram = 0, available_ram = 0;
    long total_swap = 0, free_swap = 0;

    while (fgets(line, sizeof(line), meminfo)) {
        sscanf(line, "MemTotal: %ld kB", &total_ram);
        sscanf(line, "MemFree: %ld kB", &free_ram);
        sscanf(line, "MemAvailable: %ld kB", &available_ram);
        sscanf(line, "SwapTotal: %ld kB", &total_swap);
        sscanf(line, "SwapFree: %ld kB", &free_swap);
    }
    fclose(meminfo);

    long used_ram = total_ram - free_ram;
    long used_swap = total_swap - free_swap;

    printf("RAM:\n");
    printf("  Total: %ld MB\n", total_ram / 1024);
    printf("  Used: %ld MB\n", used_ram / 1024);
    printf("  Free: %ld MB\n", free_ram / 1024);

    printf("Swap:\n");
    printf("  Total: %ld MB\n", total_swap / 1024);
    printf("  Used: %ld MB\n", used_swap / 1024);
    printf("  Free: %ld MB\n", free_swap / 1024);
}
void uptime_exec() {
    FILE *uptime_file = fopen("/proc/uptime", "r");
    if (uptime_file == NULL) {
        perror("Failed to open /proc/uptime");
        return;
    }

    double uptime, idle_time;
    if (fscanf(uptime_file, "%lf %lf", &uptime, &idle_time) != 2) {
        perror("Failed to read /proc/uptime");
        fclose(uptime_file);
        return;
    }
    fclose(uptime_file);

    int uptime_hours = (int)(uptime / 3600);
    int uptime_minutes = (int)((uptime - (uptime_hours * 3600)) / 60);

    printf("System Uptime: %d hours, %d minutes\n", uptime_hours, uptime_minutes);
    printf("Idle Time: %.2f seconds\n", idle_time);
}

void exexction(char *argv[], int size) {
    // Check for piping
       int pipe_pos = -1;
    for (int i = 0; i < size; i++) {
        if (strcmp(argv[i], "|") == 0) {
            pipe_pos = i;
            break;
        }
    }

    if (pipe_pos != -1) {
        // Split the command at the pipe position
        argv[pipe_pos] = NULL;  

        // First command
        char **cmd1 = argv;

        // Second command
        char **cmd2 = &argv[pipe_pos + 1];

        handle_piping(cmd1, cmd2);
    } 
    else {
        // No pipe, handle normally

        if (strcmp(argv[0], "type") == 0) {
            type_exec(argv, size);
        } else if (strcmp(argv[0], "mycp") == 0) {
            cp_exec(argv, size);
        } else if (strcmp(argv[0], "mymv") == 0) {
            mv_exec(argv, size);
        } else if (strcmp(argv[0], "mycd") == 0) {
            cd_exec(argv, size);
        } else if (strcmp(argv[0], "mypwd") == 0) {
            pwd_exec();
        } else if (strcmp(argv[0], "myecho") == 0) {
            echo_exec(argv, size);
        } else if (strcmp(argv[0], "help") == 0) {
            help_exec();
        } else if (strcmp(argv[0], "myenvir") == 0) {
            envir_exec(argv, size);
        } else if (strcmp(argv[0], "free") == 0) {
            free_exec();
        } else if (strcmp(argv[0], "uptime") == 0) {
            uptime_exec();
        } else {
            external_exec(argv);
        }
    }
}

//

