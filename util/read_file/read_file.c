/*
    The Fluent Programming Language
*/

#include "read_file.h"
#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *path)
{
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("fopen");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    if (buffer == NULL) {
        perror("malloc");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}
