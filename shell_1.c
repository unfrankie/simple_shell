#include "shell.h"

/**
  * builtin_1 - builtin checker
  * @cmd: command to be checked
  * Return: 1 true || 0 false
  */

int builtin_1(char *cmd)
{
	int i;
	char *bi[] = {"exit", "env", NULL};

	for (i = 0; bi[i]; i++)
	{
		if (_strcmp(cmd, bi[i]) == 0)
			return (1);
	}
	return (0);
}

/**
  * builtinner - builtin handler
  * @bicmd: builtin command
  * @var: void cast
  * @index: void cast
  * @exit_v: exit value
  */

void builtinner(char **bicmd, char **var, int *exit_v, int index)
{
	(void) index;
	(void) var;

	if (_strcmp(bicmd[0], "exit") == 0)
		exit_func(bicmd, exit_v);
	else if (_strcmp(bicmd[0], "env") == 0)
		env_func(bicmd, exit_v);
}

/**
  * exit_func - exit shell function
  * @cmd: command
  * @exit_v: exit value
  */

void exit_func(char **cmd, int *exit_v)
{
	array_clearer(cmd);
	exit(*exit_v);
}

/**
  * env_func - display environement
  * @cmd: command
  * @exit_v: exit value
  */

void env_func(char **cmd, int *exit_v)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	(*exit_v) = 0;
	array_clearer(cmd);
}

/**
  * main - shell main program
  * @var: variable
  * @i: unused integer
  * Return: status
  */

int main(int i, char **var)
{
	char **cmd = NULL, *l = NULL, *trail = NULL;
	int st = 0, index = 0;
	(void) i;

	while (1)
	{
		l = line_interpreter();
		if (l == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(trail);
			return (st);
		}
		cmd = line_handler(l);
		if (!cmd)
			continue;
		if (builtin_1(cmd[0]))
			builtinner(cmd, var, &st, index);
		else
			st = shell_exe(var, cmd, index);
	}
	return (0);
}
