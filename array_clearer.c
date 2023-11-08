#include "shell.h"

/**
  * array_clearer - free the array
  * @a: two dimentionnel array
  */

void array_clearer(char **a)
{
	int i;
	if (!a)
		return;
	for (i = 0; a[i]; i++)
	{
		free(a[i]);
		a[i] = NULL;
	}
	free(a);
	a = NULL;
}
