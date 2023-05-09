#include "main.h"

/**
 * create_file - creates a new file and writes a string to it
 * @filename: the name of the file to create
 * @text_content: the string to write to the file
 *
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
	int file, write_status, words = 0;

	if (!filename) /* check if filename is present */
		return (-1);

	/* create file with read-write permission only for the owner */
	file = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if (file == -1) /* check if file creation was successful */
		return (-1);

	if (text_content) /* write content to file if it's not NULL */
	{
		/* count the number of words */
		while (text_content[words] != '\0')
			words++;

		/* write to file */
		write_status = write(file, text_content, words);
		if (write_status == -1) /* check if write was successful */
			return (-1);
	}

	close(file); /* close file */
	return (1);
}

