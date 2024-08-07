#ifndef INTERNAL_H
#define INTERNAL_H

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

#endif // INTERNAL_H

