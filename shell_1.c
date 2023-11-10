#include "shell.h"

/**
  * main - shell main program
  * @var: variable for error
  * @i: unused variable
  * Return: status
  */

int main(int i, char **var)
{
	char **cmd = NULL, *l = NULL, *trail = NULL;
	int st = 0, index = 0, cycle = 1, j = 0;
	file_input in;
	
	if (i == 2)
	{
		in = file_summoner(var);
		cycle = in.len;
	}
	while (cycle)
	{
		if (i == 2)
		{
			cycle--;
			l = in.l[j++];
		}
		else
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
		st = shell_exe(var, cmd, index);
	}
}
