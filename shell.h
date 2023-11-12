#ifndef SHELL_HEADER
#define SHELL_HEADER

/*Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
/*Macros*/
#define SEPARATOR " \n\t"
#define INITIATOR "$ "
/*Globale variable*/
extern char **environ;
/*shell_0.c*/
char *line_interpreter(void);
char **line_handler(char *l);
int shell_exe(char **var, char **cmd, int index);
char *path_summoner(char *cmd);
char *env_summoner(char *envstr);
/*shell_1.c*/
int builtin_1(char *cmd);
void builtinner(char **bicmd, char **var, int *exit_v, int index);
void env_func(char **cmd, int *exit_v);
void exit_func(char **cmd, int *exit_v);
int main(int i, char **var);
/*utils_0*/
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *s);
int _strlen(char *s);
/*utils_1*/
void array_clearer(char **a);
char *_itoa(int n);
void error_index(char *user, int index, char *cmd);
void reverse_string(char *str, int len);

#endif

