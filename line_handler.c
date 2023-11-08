#include "shell.h"

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
	return(WEXITSTATUS(stat));
}
