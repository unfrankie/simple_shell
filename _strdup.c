#include "shell.h"

/**
  * _strdup - duplicate string
  * @s: charcter
  * Return: pointer
  */

char *_strdup(char *s)
{
	char *p;
	int length;
	int i;

	if (s == NULL)
	return (NULL);
	length = _strlen(s);
	p = malloc(sizeof(char) * (length + 1));
	if (!p)
		return (NULL);
	for (i = 0; *s != '\0'; s++, i++)
		p[i] = s[0];
	p[i++] = '\0';
	return (p);
}
