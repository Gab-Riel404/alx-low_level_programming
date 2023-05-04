#include "main.h"
#include <stdio.h>

/**
 * binary_to_uint - convert a binary number to an unsigned int
 * @b: char string
 * Return: converted decimal number or 0 if there is an unconvertable char
 */
unsigned int binary_to_uint(const char *b)
{
	unsigned int sum, power;
	int ln;

	if (b == NULL)
		return (0);

	for (ln = 0; b[ln]; ln++)
	{
		if (b[ln] != '0' && b[ln] != '1')
			return (0);
	}

	for (power = 1, sum = 0, ln--; ln >= 0; ln--, power *= 2)
	{
		if (b[ln] == '1')
			sum += power;
	}

	return (sum);
}

