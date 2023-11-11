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

/**
  * struct list_directory - directory linked list
  * @d: directory
  * @next: next node pointer
  */

typedef struct list_directory
{
	char *d;
	struct list_directory *next;
} list_directory;

char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *s);
int _strlen(char *s);
char **line_handler(char *l);
char *line_interpreter(void);
void array_clearer(char **a);
int shell_exe(char **var, char **cmd, int index);
void error_index(char *user, int index, char *cmd);
char *_itoa(int n);
int _atoi(char *str);
char *path_summoner(char *cmd);
char *env_summoner(char *envstr);
void reverse_string(char *str, int len);
int main(int i, char **var);
list_directory *add_node_end(list_directory **head, const char *str);
void free_list(list_directory *head);
list_directory *dir_builder(void);
int builtin_1(char *cmd);
void builtinner(char **bicmd, char **var, int *exit_v, int index);
void env_func(char **cmd, int *exit_v);
void exit_func(char **cmd, int *exit_v);


#endif

