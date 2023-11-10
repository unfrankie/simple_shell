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
		write(STDOUT_FILENO, INITIATOR, 2);
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
	char *handler = NULL, *mem = NULL, **cmd = NULL;
	int i = 0, c = 0;

	if (!l)
		return (NULL);
	mem = _strdup(l);
	handler = strtok(mem, SEPARATOR);
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
		handler = strtok(NULL, SEPARATOR);
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
	handler = strtok(l, SEPARATOR);
	while (handler)
	{
		cmd[i] = _strdup(handler);
		handler = strtok(NULL, SEPARATOR);
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
  * @index: shell line index
  * Return: status 0 || 127
  */

int shell_exe(char **var, char **cmd, int index)
{
	int stat;
	char *c;
	pid_t child;

	c = path_summoner(cmd[0]);
	if (!c)
	{
		error_index(var[0], index, cmd[0]);
		array_clearer(cmd);
		return (127);
	}
	child = fork();
	if (child == 0)
	{
		if (execve(c, cmd, environ) == -1)
		{
			array_clearer(cmd);
			free(c);
			c = NULL;
		}
	}
	else
	{
		waitpid(child, &stat, 0);
		array_clearer(cmd);
		free(c);
		c = NULL;
	}
	return (WEXITSTATUS(stat));
}

/**
  * path_summoner - handle path of a command line
  * @cmd: command line to be handled
  * Return: the full path of the command
  */

char *path_summoner(char *cmd)
{
	int i;
	struct stat status;
	char *trail, *cmd_0, *folder;

	for (i = 0; cmd[i]; i++)
	{
		if (cmd[i] == '/')
		{
			if (stat(cmd, &status) == 0)
				return (_strdup(cmd));
			return (NULL);
		}
	}
	trail = env_summoner("PATH");
	if (!trail)
		return (NULL);
	folder = strtok(trail, ":");
	while (folder)
	{
		cmd_0 = malloc(_strlen(folder) + _strlen(cmd) + 2);
		if (cmd_0)
		{
			_strcpy(cmd_0, folder);
			_strcat(cmd_0, "/");
			_strcat(cmd_0, cmd);
			if (stat(cmd_0, &status) == 0)
			{
				free(trail);
				return (cmd_0);
			}
			free(cmd_0);
			cmd_0 = NULL;
			folder = (":");
		}
	}
	free(trail);
	return (NULL);
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
	int st = 0, index = 0;
	(void) i;

	while (1)
	{
		l = line_interpreter();
		if (l == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (st);
		}
		cmd = line_handler(l);
		if (!cmd)
			continue;
		st = shell_exe(var, cmd, index);
	}
}