#include "shell.h"

/**
  * main - shell main program
  * @var: variable for error
  * @i: unused variable
  * Return: status
  */

char main(char **var)
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
		else
			st = shell_exe(var, cmd, index);
	}
	return (0);
}
