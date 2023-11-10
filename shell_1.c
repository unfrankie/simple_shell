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
  * main - shell main program
  * @var: variable
  * @i: unused integer
  * Return: status
  */

int main(int i, char **var)
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
