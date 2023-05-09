#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define MAX_FILE_NAME_LENGTH 1024

void check_if_elf(unsigned char *e_ident);
void print_magic(unsigned char *e_ident);
void print_class(unsigned char *e_ident);
void print_data(unsigned char *e_ident);
void print_version(unsigned char *e_ident);
void print_osabi(unsigned char *e_ident);
void print_abi(unsigned char *e_ident);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <ELF-file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *file_name = argv[1];
    FILE *file = fopen(file_name, "rb");

    if (file == NULL)
    {
        fprintf(stderr, "Error: Cannot open file %s\n", file_name);
        return EXIT_FAILURE;
    }

    unsigned char e_ident[EI_NIDENT];
    size_t n_read = fread(e_ident, 1, EI_NIDENT, file);
    fclose(file);

    if (n_read != EI_NIDENT)
    {
        fprintf(stderr, "Error: Cannot read ELF identification from file %s\n", file_name);
        return EXIT_FAILURE;
    }

    check_if_elf(e_ident);
    printf("ELF Header:\n");
    print_magic(e_ident);
    print_class(e_ident);
    print_data(e_ident);
    print_version(e_ident);
    print_osabi(e_ident);
    print_abi(e_ident);

    return EXIT_SUCCESS;
}

void check_if_elf(unsigned char *e_ident)
{
    if (e_ident[EI_MAG0] != 0x7F || e_ident[EI_MAG1] != 'E' ||
        e_ident[EI_MAG2] != 'L' || e_ident[EI_MAG3] != 'F')
    {
        fprintf(stderr, "Error: Not an ELF file\n");
        exit(EXIT_FAILURE);
    }
}

void print_magic(unsigned char *e_ident)
{
    printf("  Magic:   ");

    for (int i = 0; i < EI_NIDENT; i++)
    {
        printf("%02x ", e_ident[i]);
    }

    printf("\n");
}

void print_class(unsigned char *e_ident)
{
    printf("  Class:   ");

    switch (e_ident[EI_CLASS])
    {
        case ELFCLASSNONE:
            printf("none\n");
            break;
        case ELFCLASS32:
            printf("ELF32\n");
            break;
        case ELFCLASS64:
            printf("ELF64\n");
            break;
        default:
            printf("<unknown: %x>\n", e_ident[EI_CLASS]);
    }
}

void print_data(unsigned char *e_ident)
{
    printf("  Data:    ");

    switch (e_ident[EI_DATA])
    {
        case ELFDATANONE:
            printf("none\n");
            break;
        case ELFDATA2LSB:
            printf("2's complement, little endian\n");
            break;
        case ELFDATA2MSB:
            printf("2's complement, big endian\n");
            break;
        default:
            printf("<unknown: %x>\n", e_ident[EI_DATA]);
    }
}

void print_version(unsigned char *e_ident)
{
    printf("  Version: %d", e_ident[EI_VERSION]);

    if (e_ident[EI_VERSION] == EV_CURRENT)
    {
        printf(" (current)\n");
    }
    else
    {
        printf("\n");
    }
}

void print_os

