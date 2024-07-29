#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


#define STDIN  0
#define STDOUT 1
#define STDERR 2

int exit_val = 1;

void exexction(char *argv[], int size);
void cp_exec(char *cmd[], int size);
void mv_exec(char *cmd[], int size);
void cat_exec(char *cmd[], int size);
void echo_exec(char *cmd[], int size);
void pwd_exec();
void help_exec();
void error_exec();
char *internal_command[]={"pwd : path working directory","echo < string > : print this stirng "
                       ,"cp <source> <destination> : copy content <source> to <source> <destination> "
                       ,"mv <source> <destination> : move <source> to <destination>"
                       ,"exit : to end shell" ,"help : to show all command and description every command",NULL};
int main(void) {
    char *cmd = NULL, *cpy_cmd = NULL, *token = NULL;
    char *delim = " \n";
    size_t n = 0;
    int argc = 0, count = 0;
    char **argv = NULL;

    const char *exit = "exit";
    const char *prompet = "o2mor>$";
    
    do {
        write(STDOUT, prompet, strlen(prompet));

        if (getline(&cmd, &n, stdin) == -1) {
            perror("Failure");
        }

        cpy_cmd = strdup(cmd);
        if (cpy_cmd == NULL) {
            perror("Failed");
        }

        // Tokenize the input to count arguments
        token = strtok(cmd, delim);
        while (token) {
            argc++;
            token = strtok(NULL, delim);
        }

        argv = malloc(sizeof(char*) * (argc + 1));
        if (argv == NULL) {
            perror("Failed");
        }

        count = 0;
        token = strtok(cpy_cmd, delim);
        while (token) {
            argv[count] = strdup(token); 
            if (argv[count] == NULL) {
                perror("Failed");
            }
            count++;
            token = strtok(NULL, delim);
        }
        argv[count] = NULL; 

        if (argv[0] == NULL || strcmp(argv[0], "\n") == 0) {
            continue;
        } else {
            exexction(argv, count);
        }

        // Clean up
        free(cpy_cmd);
        //  free(cmd);
        for (int i = 0; i < count; i++) {
            free(argv[i]);
        }
        free(argv);

        argc = 0;
        count = 0;

    } while (exit_val);

    return 0;
}

void exexction(char *argv[], int size) {
    if (strcmp("cp", argv[0]) == 0) {
        cp_exec(argv, size);
    } else if (strcmp(argv[0], "mv") == 0) {
        mv_exec(argv, size);
    } else if (strcmp(argv[0], "pwd") == 0) {
        pwd_exec();
    } else if (strcmp(argv[0], "echo") == 0) {
        echo_exec(argv, size);
    } else if (strcmp(argv[0], "help") == 0) {
        help_exec();
    } else if (strcmp("exit", argv[0]) == 0) {
        printf("Good Bye :(\n");
        exit_val = 0;
    } else {
        error_exec();
    }
}

void cp_exec(char *cmd[], int size) {

if(size!=3){
    fprintf(stderr,"Usage cp <source>  <destenation>\n");
    return;
}
const char *source=cmd[1];
const char *dest  =cmd[2];

int fd_src =open(source,O_RDONLY);
if(fd_src<0){
        perror("Error opening source file");
        return;
}

// Open the destination file for writing (create it if it does not exist, or truncate it if it does)
int fd_dest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd_dest < 0) {
        perror("Error opening destination file");
        close(fd_src);
        return;
    }
    char buffer[4096];
    ssize_t bytes_read;

    // Copy data from source to destination
    while ((bytes_read = read(fd_src, buffer, sizeof(buffer))) > 0) {
        if (write(fd_dest, buffer, bytes_read) != bytes_read) {
            perror("Error writing to destination file");
            close(fd_src);
            close(fd_dest);
            return;
        }
    }

    if (bytes_read < 0) {
        perror("Error reading from source file");
    }


    close(fd_src);
    close(fd_dest);


}

void mv_exec(char *cmd[], int size) {
    if (size != 3) {
        fprintf(stderr, "Usage: mv <source> <destination>\n");
        return;
    }

    const char *source_path = cmd[1];
    const char *dest_path = cmd[2];

    int src_fd = open(source_path, O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening source file");
        return;
    }

    // Open the destination file for writing (create it if it does not exist, or truncate it if it does)
    int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (dest_fd < 0) {
        perror("Error opening destination file");
        close(src_fd);
        return;
    }

    char buffer[4096];
    ssize_t bytes_read;

    // Copy data from source to destination
    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            return;
        }
    }

    if (bytes_read < 0) {
        perror("Error reading from source file");
    }

    close(src_fd);
    close(dest_fd);

    
    if (unlink(source_path) < 0) {
        perror("Error deleting source file");
        return;
    }
}


void echo_exec(char *cmd[], int size) {
    for (int i = 1; i < size; i++) {
        printf("%s", cmd[i]);
        if (i < size - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

void help_exec() {
    for(int i=0;internal_command[i];i++){
        printf("%s\n",internal_command[i]);
    }
}

void error_exec() {
    fprintf(stderr, "Unknown command\n");
}
void pwd_exec() {
    char *wd = NULL;
    size_t size = 1024; 

    wd = malloc(size);
    if (wd == NULL) {
        perror("Failed");
        exit(1);
    }

    // Get the current working directory
    while (getcwd(wd, size) == NULL) {
        if (errno == ERANGE) { // Buffer too small
            size *= 2; // Double the size
            char *temp = realloc(wd, size);
            if (temp == NULL) {
                perror("Failed");
                free(wd);
                exit(1);
            }
            wd = temp;
        } else {
            perror("getcwd() error");
            free(wd);
            exit(1);
        }
    }
    printf("%s\n", wd);
    free(wd); 
}

/*
void pwd_exec() {
    char wd[100];
    if (getcwd(wd, sizeof(wd)) != NULL) {
        printf("%s\n", wd);
    } else {
        perror("getcwd() error");
    }
}
*/