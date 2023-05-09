#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void exit_with_error(int error_code, char *file_name, int fd);

/**
 * exit_with_error - Prints error messages and exits with the given error code.
 * @error_code: Either the exit code or file descriptor.
 * @file_name: Name of either file_from or file_to.
 * @fd: File descriptor.
 *
 * Return: None.
 */
void exit_with_error(int error_code, char *file_name, int fd)
{
	switch (error_code)
	{
		case 97:
			dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
			break;
		case 98:
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_name);
			break;
		case 99:
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_name);
			break;
		case 100:
			dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
			break;
		default:
			break;
	}

	exit(error_code);
}

/**
 * main - Copies the contents of a file to another file.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: If the argument count is incorrect - exit code 97.
 * If file_from does not exist or cannot be read - exit code 98.
 * If file_to cannot be created or written to - exit code 99.
 * If file_to or file_from cannot be closed - exit code 100.
 */
int main(int argc, char *argv[])
{
	if (argc != 3)
		exit_with_error(97, NULL, 0);

	char buffer[BUFFER_SIZE];
	int file_from, file_to;
	ssize_t bytes_read, bytes_written;

	file_from = open(argv[1], O_RDONLY);
	if (file_from == -1)
		exit_with_error(98, argv[1], 0);

	file_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (file_to == -1)
		exit_with_error(99, argv[2], 0);

	bytes_read = read(file_from, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		bytes_written = write(file_to, buffer, bytes_read);
		if (bytes_written == -1)
			exit_with_error(99, argv[2], 0);

		bytes_read = read(file_from, buffer, BUFFER_SIZE);
	}

	if (bytes_read == -1)
		exit_with_error(98, argv[1], 0);

	if (close(file_from) == -1)
		exit_with_error(100, NULL, file_from);

	if (close(file_to) == -1)
		exit_with_error(100, NULL, file_to);

	return (0);
}

