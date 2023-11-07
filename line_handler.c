#include "shell.h"

char **line_handler(char *l)
{
	char *handler = NULL, *mem = NULL, **cmd = NULL, sep[] = " \t\n";
	int i = 0, c = 0;

	if (!l)
		return (NULL);
	mem = _strdup(l);
	handler = strtok(mem, sep);
	while (handler)
	{
		c++;
		handler = strtok (NULL, sep);
	}
	free(mem), mem = NULL;
	cmd = malloc (sizeof(char *) * (c + 1));
	if (!cmd)
	{
		free(l);
		return (NULL);
	}
	handler = strtok(l, sep);
	while (handler)
	{
		cmd[i] = handler;
		handler = strtok(NULL, sep);
		i++;
	}
	free(l), l = NULL;
	cmd[i] = NULL;
	return (cmd);
}
