#include "shell.h"

/**
  * add_node_end - add a new node at the end
  * @head: head pointer
  * @str: string
  * Return: the address of the new element || NULL
  */

directory *add_node_end(directory **head, const char *str)
{
	directory *l;
	int i = 0;
	directory *l1 = *head;

	while (str[i])
		i++;
	l = malloc(sizeof(list_t));
	if (!l)
	{
		return (NULL);
	}
	l->str = strdup(str);
	l->len = i;
	l->next = NULL;
	if (*head == NULL)
	{
		*head = l;
		return (l);
	}
	while (l1->next)
		l1 = l1->next;

	l1->next = l;

	return (l);
}

/**
  * free_list - free list
  * @head: head pointer
  */

void free_list(directory *head)
{
	directory *l;

	while (head)
	{
		l = head->next;
		free(head->str);
		free(head);
		head = l;
	}
}

/**
  * main - shell main program
  * @var: variable
  * Return: status
  */

char main(char **var)
{
	char **cmd = NULL, *l = NULL, *trail = NULL;
	int st = 0, index = 0;
	(void) i;

	while (1)
	{
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
		else
			st = shell_exe(var, cmd, index);
	}
	return (0);
}
