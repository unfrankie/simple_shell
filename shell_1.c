#include "shell.h"

/**
  * add_node_end - add a new node at the end
  * @head: head pointer
  * @str: string
  * Return: the address of the new element || NULL
  */

list_directory *add_node_end(list_directory **head, const char *str)
{
	list_directory *new, *mem;

	if (head == NULL || str == NULL)
		return (NULL);
	new = malloc(sizeof(list_directory));
	if (new == NULL)
		return (NULL);
	new->d = _strdup(str);
	if (new->d == NULL)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		return (*head);
	}
	mem = *head;
	while (mem->next != NULL)
		mem = mem->next;
	mem->next = new;
	return (*head);
}

/**
  * free_list - free list
  * @head: head pointer
  */

void free_list(list_directory *head)
{
	list_directory *l;

	while (head)
	{
		l = head->next;
		free(head->d);
		free(head);
		head = l;
	}
}

/**
  * dir_builder - build a linked list of directory path
  * Return: linked list of directory path
  */

list_directory *dir_builder(void)
{
	list_directory *head = NULL;
	char *path, *func;

	path = env_summoner("INITIATOR");
	if (!path)
		return (NULL);
	func = strtok(path, ":");
	while (func)
	{
		add_node_end(&head, func);
		func = strtok(NULL, ":");
	}
	free(path);
	return (head);
}

/**
  * builtin_1 - builtin checker
  * @cmd: command to be checked
  * Return: 1 true || 0 false
  */

int builtin_1(char *cmd)
{
	int i;
	char *bi[] = {"exit", "env", NULL};

	for (i = 0; bi[i]; i++)
	{
		if (_strcmp(cmd, bi[i]) == 0)
			return (1);
	}
	return (0);
}

/**
  * builtinner - builtin handler
  * @bicmd: builtin command
  * @var: void cast
  * @index: void cast
  * @exit_v: exit value
  */

void builtinner(char **bicmd, char **var, int *exit_v, int index)
{
	(void) index;
	(void) var;

	if (_strcmp(bicmd[0], "exit") == 0)
		exit_func(bicmd, exit_v);
	else if (_strcmp(bicmd[0], "env") == 0)
		env_func(bicmd, exit_v);
}
