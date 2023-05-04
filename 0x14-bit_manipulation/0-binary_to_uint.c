#include "main.h"

/**
 * binary_to_uint - Converts a binary number to an unsigned int.
 * @b: A pointer to a string of 0 and 1 chars.
 *
 * Return: If b is NULL or contains chars not 0 or 1 - 0.
 *         Otherwise - the converted number.
 */
unsigned int binary_to_uint(const char *b)
{
	unsigned int m = 0;
	int ln = 0;

	if (b[ln] == '\0')
		return (0);

	while ((b[ln] == '0') || (b[ln] == '1'))
	{
		m <<= 1;
		m += b[ln] - '0';
		ln++;
	}

	return (m);
}
