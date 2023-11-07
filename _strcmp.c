#include "shell.h"

/**
  * _strcmp - compares two strings
  * @s1: 1st string
  * @s2: 2nd string
  * Return: 0 || s1 - s2
  */

int _strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
