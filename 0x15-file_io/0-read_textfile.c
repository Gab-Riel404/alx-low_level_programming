#include "main.h"

/**
 * read_textfile - reads a text file and prints the letters
 * @filename: filename.
 * @max_chars: maximum number of characters to read and print.
 *
 * Return: number of characters printed. If it fails, returns 0.
 */
ssize_t read_textfile(const char *filename, size_t max_chars)
{
    int file_descriptor;
    ssize_t n_read, n_written;
    char *buffer;

    if (!filename)
        return (0);

    file_descriptor = open(filename, O_RDONLY);

    if (file_descriptor == -1)
        return (0);

    buffer = malloc(sizeof(char) * max_chars);
    if (!buffer)
        return (0);

    n_read = read(file_descriptor, buffer, max_chars);
    n_written = write(STDOUT_FILENO, buffer, n_read);

    close(file_descriptor);

    free(buffer);

    return (n_written);
}

