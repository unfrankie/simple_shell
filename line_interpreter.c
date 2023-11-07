#include "shell.h"

char *line_interpreter(void)
{
	size_t length = 0;
	ssize_t i;
	char *l = NULL;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
	i = getline(&l, &length, stdin);
	if ( n == -1)
	{
		free(l);
		return (NULL);
	}
	return (l);
}
