#include"/home/ammar/Desktop/myshell/shell.h"

extern char** environ;

static const char *internal_commands[] = {
    "pwd",
    "echo",
    "cp",
    "mv",
    "exit",
    "help",
    "envir",
    "cd",
    "type",
    NULL
};


/**************************************************************************************/
/**************************************************************************************/

int is_internal_command(const char *cmd) {
    for (int i = 0; internal_commands[i] != NULL; i++) {
        if (strcmp(cmd, internal_commands[i]) == 0) {
            return 1; // Command is internal
        }
    }
    return 0; // Command is external
}
/**************************************************************************************/
void type_exec(char *cmd[], int size) {
    if (size != 2) {
        fprintf(stderr, "Usage: type <command>\n");
        return;
    }

    const char *command = cmd[1];

    if (is_internal_command(command)) {
        printf("%s is an internal command\n", command);
        return;
    }

    pid_t pid = fork();
    if (pid > 0) {
      int status;
      wait(&status); 
    }else if (pid == 0) {

      char *path = getenv("PATH");
      if (path == NULL) {
            perror("Error getting PATH environment variable");

      }

          const char *full_path="/usr/bin";
    //    snprintf(full_path, sizeof(full_path), "%s/%s", token, command);

            if (access(full_path, X_OK) == 0) {
                	printf("%s is an external command\n", command);

            }
            else{
            		// If the command was not found in any PATH directory
        		printf("%s is an unknown command\n", command);

            }
        }

        
} 



/**************************************************************************************/

void cp_exec(char *cmd[], int size) {
    if (size != 3) {
        fprintf(stderr, "Usage: cp <source> <destination>\n");
        return;
    }
    const char *source = cmd[1];
    const char *dest = cmd[2];

    int fd_src = open(source, O_RDONLY);
    if (fd_src < 0) {
        perror("Error opening source file");
        return;
    }

    int fd_dest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd_dest < 0) {
        perror("Error opening destination file");
        close(fd_src);
        return;
    }
    char buffer[4096];
    ssize_t bytes_read;

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
/**************************************************************************************/

void mv_exec(char *cmd[], int size) {
    if (size == 3) {
        if (rename(cmd[1], cmd[2]) == -1) {
            fprintf(stderr, "Error moving file from %s to %s\n", cmd[1], cmd[2]);
        }
    } else {
        fprintf(stderr, "Usage: mv <source> <destination>\n");
    }
}
/**************************************************************************************/

void echo_exec(char *cmd[], int size) {
    for (int i = 1; i < size; i++) {
        printf("%s", cmd[i]);
        if (i < size - 1) {
            printf(" ");
        }
    }
    printf("\n");
}
/**************************************************************************************/

void help_exec() {
    const char *internal_command[] = {
        "pwd : path working directory",
        "cd <path> : change working directory", 
        "echo <string> : print this <string>",
        "cp <source> <destination> : copy content <source> to <destination>",
        "mv <source> <destination> : move <source> to <destination>",
        "exit : to end shell",
        "help : to show all commands and description for each command",
        "envir : to show environment variables",
        "type <command> : determine if <command> is internal, external, or unknown",
        NULL
    };

    for (int i = 0; internal_command[i]; i++) {
        printf("%s\n", internal_command[i]);
    }
}
/**************************************************************************************/

void pwd_exec() {
    char *wd = NULL;
    size_t size = 1024;

    wd = malloc(size);
    if (wd == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }

    while (getcwd(wd, size) == NULL) {
        if (errno == ERANGE) {
            size *= 2;
            char *temp = realloc(wd, size);
            if (temp == NULL) {
                perror("Failed to reallocate memory");
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
/**************************************************************************************/

void cd_exec(char *cmd[], int size) {
    if (size != 2) {
        fprintf(stderr, "Usage: cd <directory>\n");
        return;
    }
    const char *path = cmd[1];
    if (chdir(path) != 0) {
        perror("Failed to change directory");
    }
}

/**************************************************************************************/

void print_envir(){
    int i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i++]);
    }
}
/**************************************************************************************/
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
/**************************************************************************************/
