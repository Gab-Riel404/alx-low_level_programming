#include "lists.h"

/**
 * find_listint_loop - Finds the loop contained in
 *                     a listint_t linked list.
 * @head: A pointer to the head of the listint_t list.
 *
 * Return: If there is no loop - NULL.
 *         Otherwise - the address of the node where the loop starts.
 */
listint_t *find_listint_loop(listint_t *head)
{
	listint_t *th, *ha;

	if (head == NULL || head->next == NULL)
		return (NULL);

	th = head->next;
	ha = (head->next)->next;

	while (ha)
	{
		if (th == ha)
		{
			th = head;

			while (th != ha)
			{
				th = th->next;
				ha = ha->next;
			}

			return (th);
		}

		th = th->next;
		ha = (ha->next)->next;
	}

	return (NULL);
}

