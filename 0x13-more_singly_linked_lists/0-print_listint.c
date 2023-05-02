#include "lists.h"
#include <stdio.h>

/**
 * print_listint - Prints all the elements of a listint_t list.
 * @d: A pointer to the head of the list_t list.
 *
 * Return: The number of nodes in the list_t list.
 */
size_t print_listint(const listint_t *d)
{
	size_t nodes = 0;

	while (d)
	{
		nodes++;
		printf("%d\n", d->n);
		d = d->next;
	}

	return (nodes);
}

