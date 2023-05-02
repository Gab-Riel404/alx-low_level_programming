#include "lists.h"
#include <stdio.h>

/**
 * listint_len - Returns the number of elements
 *               in a linked listint_t list.
 * @d: A pointer to the head of the listint_t list.
 *
 * Return: The number of elements in the listint_t list.
 */
size_t listint_len(const listint_t *d)
{
	size_t node = 0;

	while (d)
	{
		node++;
		d = d->next;
	}

	return (node);
}

