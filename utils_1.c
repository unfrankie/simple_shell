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

/**
  * _itoa - convert an integer to string
  * @n: the integer
  * Return: string
  */

char *_itoa(int n)
{
	char max[20];
	int i = 0;

	if (n == 0)
		max[i++] = '0';
	else
	{
		while (n > 0)
		{
			max[i++] = (n % 10) + '0';
			n /= 10;
		}
	}
	max[i] = '\0';
	reverse_string(max, i);
	return (_strdup(max));
}

/**
  * _atoi - convert a string to an integer
  * @str: the string
  * Return: numerical value of the string
  */

int _atoi(char *str)
{
	int i, num = 0;

	for (i = 0; str[i] ; i++)
	{
		num *= 10;
		num += (str[i] - '0');
	}
	return (num);
}

/**
  * reverse_string - reverse string
  * @str: string to be reversed
  * @len: the length of the string
  * Return: (void).
  */

void reverse_string(char *str, int len)
{
	char temp;
	int s = 0;
	int e = len - 1;

	while (s < e)
	{
		temp = str[s];
		str[s] = str[e];
		str[e] = temp;
		s++;
		e--;
	}
}

/**
  * error_index - display error command not found
  * @user: user
  * @index: shell line index
  * @cmd: command to be tested
  */

void error_index(char *user, int index, char *cmd)
{
	char *i;
	char output[] = ": not found\n";

	i = _itoa(index);

	write(STDERR_FILENO, user, _strlen(user));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, i, _strlen(i));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, output, _strlen(output));
	free(i);
}
