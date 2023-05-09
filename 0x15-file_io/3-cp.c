#include <main.h>

#define MAXSIZE 1024

/**
 * __exit - prints error messages and exits with exit number
 *
 * @error: the exit number or file descriptor
 * @str: the name of the file that caused the error
 * @fd: the file descriptor that caused the error
 *
 * Return: void
 */
void __exit(int error, const char *str, int fd)
{
	switch (error)
	{
		case 97:
			dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
			break;
		case 98:
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", str);
			break;
		case 99:
			dprintf(STDERR_FILENO, "Error: Can't write to file %s\n", str);
			break;
		case 100:
			dprintf(STDERR_FILENO, "Error: Can't close file descriptor %d\n", fd);
			break;
		default:
			return;
	}

	exit(error);
}

/**
 * main - create a copy of a file
 *
 * @argc: the number of arguments
 * @argv: the array of arguments
 *
 * Return: 0 on success, non-zero on failure
 */
int main(int argc, char *argv[])
{
	int file_in, file_out;
	ssize_t read_stat, write_stat;
	int close_in, close_out;
	char buffer[MAXSIZE];

	if (argc != 3)
	{
		__exit(97, NULL, 0);
	}

	file_in = open(argv[1], O_RDONLY);
	if (file_in < 0)
	{
		__exit(98, argv[1], 0);
	}

	file_out = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0664);
	if (file_out < 0)
	{
		__exit(99, argv[2], 0);
	}

	while ((read_stat = read(file_in, buffer, MAXSIZE)) > 0)
	{
		write_stat = write(file_out, buffer, read_stat);
		if (write_stat < 0 || write_stat != read_stat)
		{
			__exit(99, argv[2], 0);
		}
	}

	if (read_stat < 0)
	{
		__exit(98, argv[1], 0);
	}

	close_in = close(file_in);
	if (close_in < 0)
	{
		__exit(100, NULL, file_in);
	}

	close_out = close(file_out);
	if (close_out < 0)
	{
		__exit(100, NULL, file_out);
	}

	return 0;
}
