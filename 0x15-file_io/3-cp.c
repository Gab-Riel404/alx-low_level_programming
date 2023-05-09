#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char *create_buffer(char *file);
void close_file(int fd);

int main(int argc, char *argv[])
{
    int from_fd, to_fd, read_count, write_count;
    char buffer[BUFFER_SIZE];

    if (argc != 3)
    {
        fprintf(stderr, "Usage: cp file_from file_to\n");
        exit(97);
    }

    from_fd = open(argv[1], O_RDONLY);
    if (from_fd == -1)
    {
        fprintf(stderr, "Error: Can't read from file %s\n", argv[1]);
        exit(98);
    }

    to_fd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
    if (to_fd == -1)
    {
        fprintf(stderr, "Error: Can't write to %s\n", argv[2]);
        exit(99);
    }

    while ((read_count = read(from_fd, buffer, BUFFER_SIZE)) > 0)
    {
        write_count = write(to_fd, buffer, read_count);
        if (write_count == -1 || write_count != read_count)
        {
            fprintf(stderr, "Error: Can't write to %s\n", argv[2]);
            exit(99);
        }
    }

    if (read_count == -1)
    {
        fprintf(stderr, "Error: Can't read from file %s\n", argv[1]);
        exit(98);
    }

    if (close(from_fd) == -1)
    {
        fprintf(stderr, "Error: Can't close fd %d\n", from_fd);
        exit(100);
    }

    if (close(to_fd) == -1)
    {
        fprintf(stderr, "Error: Can't close fd %d\n", to_fd);
        exit(100);
    }

    return (0);
}


