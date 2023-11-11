#include "shell.h"

/**
  * _strcat - concatenates two strings
  * @dest: string to append to
  * @src: string
  * Return: a pointer to the resulting string
  */

char *_strcat(char *dest, char *src)
{
	char *p = dest;

	while (*p)
		p++;
	while (*src)
	{
		*p = *src;
		p++;
		src++;
	}
	*p = '\0';
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
	int i;

	i = (int)*s1 - (int)*s2;
	while (*s1)
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
		i = (int)*s1 - (int)*s2;
	}
	return (i);
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
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
  * _strdup - duplicate string
  * @str: string pointer
  * Return: pointer
  */

char *_strdup(const char *str)
{
	char *p;
	int i, length = 0;

	if (str == NULL)
		return (NULL);
	while (str[length])
		length++;
	p = malloc(sizeof(char) * (length + 1));
	if (p == NULL)
		return (NULL);
	for (i = 0; i <= length; i++)
		p[i] = str[i];
	return (p);
}


/**
  * _strlen - returns the length of a string
  * @s: the string
  * Return: returns the lenght
  */

int _strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}
