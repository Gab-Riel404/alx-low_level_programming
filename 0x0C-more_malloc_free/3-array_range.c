#include <stdlib.h>
#include "main.h"

/**
 * array_range - creates an array of integers
 * @min: minimum
 * @max: maximum
 * Return:the pointer to the newly created array
 */
int *array_range(int min, int max)
{
	int *a, i = 0, t = min;

	if (min > max)
		return (0);
	a = malloc((max - min + 1) * sizeof(int));

	if (!a)
		return (0);
	while (i <= max - min)
		a[i++] = t++;
	return (a);
}
