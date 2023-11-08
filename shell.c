#include "shell.h"

/**
  * line_interpreter - wait for user to enter command and read line
  * Return: line
  */

char *line_interpreter(void)
{
	size_t length = 0;
	ssize_t i;
	char *l = NULL;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
	i = getline(&l, &length, stdin);
	if (i == -1)
	{
		free(l);
		return (NULL);
	}
	return (l);
}

/**
  * line_handler - handle command by command
  * @l: line to be handled
  * Return: command
  */

char **line_handler(char *l)
{
	char *handler = NULL, *mem = NULL, **cmd = NULL, sep[] = " \t\n";
	int i = 0, c = 0;

	if (!l)
		return (NULL);
	mem = _strdup(l);
	handler = strtok(mem, sep);
	if (handler == NULL)
	{
		free(l);
		l = NULL;
		free(mem);
		mem = NULL;
	}
	while (handler)
	{
		c++;
		handler = strtok(NULL, sep);
	}
	free(mem);
	mem = NULL;
	cmd = malloc(sizeof(char *) * (c + 1));
	if (!cmd)
	{
		free(l);
		l = NULL;
		return (NULL);
	}
	handler = strtok(l, sep);
	while (handler)
	{
		cmd[i] = _strdup(handler);
		handler = strtok(NULL, sep);
		i++;
	}
	free(l);
	l = NULL;
	cmd[i] = NULL;
	return (cmd);
}

/**
  * array_clearer - free the array
  * @a: two dimentionnel array
  */

void array_clearer(char **a)
{
	int i;

	if (!a)
		return;
	for (i = 0; a[i]; i++)
	{
		free(a[i]);
		a[i] = NULL;
	}
	free(a);
	a = NULL;
}

/**
  * shell_exe - exexute command
  * @cmd: command to be executed
  * @var: variable
  * Return: status 0 || 127
  */

int shell_exe(char **var, char **cmd)
{
	int stat;
	pid_t c;

	c = fork();
	if (c == 0)
	{
		if (execve(cmd[0], cmd, environ) == -1)
		{
			perror(var[0]);
			array_clearer(cmd);
			exit(127);
		}
	}
	else
	{
		waitpid(c, &stat, 0);
		array_clearer(cmd);
	}
	return (WEXITSTATUS(stat));
}

/**
  * main - shell main program
  * @var: variable for error
  * @i: unused variable
  * Return: status
  */

int main(int i, char **var)
{
	char **cmd = NULL;
	char *l = NULL;
	int stat = 0;
	(void) i;

	while (1)
	{
		l = line_interpreter();
		if (l == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (stat);
		}
		cmd = line_handler(l);
		if (!cmd)
			continue;
		stat = shell_exe(cmd, var);
	}
}
