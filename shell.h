#ifndef SHELL_HEADER
#define SHELL_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#define SEPARATOR " \n\t"
#define INITIATOR "$ "
extern char **environ;

char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strdup(char *s);
int _strlen(char *s);
char **line_handler(char *l);
char *line_interpreter(void);
void array_clearer(char **a);
int shell_exe(char **var, char **cmd, int index);
void error_index(char *user, int index, char *cmd);
char *_itoa(int n);
int _atoi(char *str);
char *path_summoner(char *cmd);

#endif

