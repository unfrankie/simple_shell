#include "shell.h"

/**
  * _strcat - concatenates two strings
  * @dest: string to append to
  * @src: string
  * Return: a pointer to the resulting string
  */

char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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

/**
  * *_strcpy - copy the string pointed to by src
  * including the terminating null byte (\0)
  * to the buffer pointed to by dest
  * @dest: pointer to the buffer in which we copy the string
  * @src: string to be copied
  * Return: the pointer to dest
  */

char *_strcpy(char *dest, char *src)
{
	int l, i;

	l = 0;

	while (src[l] != '\0')
	{
		l++;
	}

	for (i = 0; i < l; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return (dest);
}

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
	while (s[length])
		length++;
	p = malloc(sizeof(char) * (length + 1));
	if (p == NULL)
		return (NULL);
	for (i = 0; i <= length; i++)
		p[i] = s[i];
	return (p);
}


/**
  * _strlen - returns the length of a string
  * @s: the string
  * Return: returns the lenght
  */

int _strlen(char *s)
{
	int n, i;

	i = 0;
	for (n = 0; s[n] != '\0'; n++)
	i++;
	return (i);
}
