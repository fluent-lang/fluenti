/*
    The Fluent Programming Language
*/

#include "../../types/int.h"
#include "read_file.h"
#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *path)
{
    // Open the file
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        // Handle errors
        perror("fopen");
        return NULL;
    }

    // Read the file
    fseek(file, 0, SEEK_END);
    const size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Malloc the result and write the file's contents
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
