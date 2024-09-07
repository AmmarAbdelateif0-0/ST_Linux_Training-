#ifndef SHELL_H
#define SHELL_H

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

#define STDIN  0
#define STDOUT 1
#define STDERR 2

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

//  redirection
void execution_for_redirection(char *argv[], int size);
int  handle_redirection(char *argv[], int size);
//piping
void handle_piping(char *cmd1[], char *cmd2[]);
//execution for external command
void external_execution(char *cmd[]);

//Built-in command
void cp_exec(char *cmd[], int size);

void mv_exec(char *cmd[], int size);

void echo_exec(char *cmd[], int size);
char* getenv_value( char *var);
void print_argument(const char *arg);

void pwd_exec();

void error_exec();

void cd_exec(char *cmd[], int size);

int  is_internal_command(const char *cmd);

void type_exec(char *cmd[], int size);

void envir_exec(char *cmd[], int size);
void print_envir();

void free_exec();

void uptime_exec();

void help_exec();



#endif
