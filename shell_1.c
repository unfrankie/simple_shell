#include "shell.h"

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
