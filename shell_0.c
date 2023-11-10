#include "shell.h"

/**
  * line_interpreter - wait for user to enter command and read line
  * Return: line
  */

char *line_interpreter(void)
{
	size_t length = 0;
	char *l = NULL;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, INITIATOR, 2);
	if(getline(&l, &length, stdin) == -1)
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

	if (l == NULL)
		return (NULL);
	mem = _strdup(l);
	handler = strtok(mem, SEPARATOR);
	if (!handler)
	{
		free(l);
		l = NULL;
		free(mem);
		mem = NULL;
		return (NULL);
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
		free(mem);
		mem = NULL;
		return (NULL);
	}
	handler = strtok(l, SEPARATOR);
	while (handler)
	{
		cmd[i++] = _strdup(handler);
		handler = strtok(NULL, SEPARATOR);
	}
	cmd[i] = NULL;
	free(l);
	l = NULL;
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
  * env_summoner - display environment of name path
  * @envstr: environment string
  * Return: environment path
  */

char *env_summoner(char *envstr)
{
	char *name, *mem, *path;
	int i;

	for (i = 0; environ[i]; i++)
	{
		mem = _strdup(environ[i]);
		name = strtok(mem, "=");
		if (_strcmp(name, envstr) == 0)
		{
			path = _strdup(strtok(NULL, "\n"));
			free(mem);
			return (path);
		}
		free(mem);
	}
	return (NULL);
}
