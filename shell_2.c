#include "shell.h"

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
