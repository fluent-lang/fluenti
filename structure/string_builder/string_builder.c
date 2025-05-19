/*
    The Fluent Programming Language
    -----------------------------------------------------
    This code is released under the GNU GPL v3 license.
    For more information, please visit:
    https://www.gnu.org/licenses/gpl-3.0.html
    -----------------------------------------------------
    Copyright (c) 2025 Rodrigo R. & All Fluent Contributors
    This program comes with ABSOLUTELY NO WARRANTY.
    For details type `fluent l`. This is free software,
    and you are welcome to redistribute it under certain
    conditions; type `fluent l -f` for details.
*/

//
// Created by rodrigo on 5/15/25.
//

#include "string_builder.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if defined(__cplusplus)
extern "C"
{
#endif

inline void init_string_builder(StringBuilder *builder, const size_t capacity)
{
    builder->capacity = capacity;

    // Allocate a new buffer (+1 for null terminator)
    char *buf = malloc(sizeof(char) * (capacity + 1));

    // Check if we got NULL
    if (buf == NULL)
    {
#       ifndef _WIN32
            perror("malloc");
#       else
            puts("Runtime error: Out of memory");
#       endif
        exit(1);
    }

    builder->buf = buf;
    builder->idx = 0;
}

inline char *collect_string_builder_no_copy(const StringBuilder *builder)
{
    // Add a null terminator
    builder->buf[builder->idx] = '\0';
    return builder->buf;
}

inline char *collect_string_builder(const StringBuilder *builder)
{
    // Copy the string
    return strdup(collect_string_builder_no_copy(builder));
}

inline void write_char_string_builder(StringBuilder *builder, const char c)
{
    // Check if we have to reallocate the buffer
    if (builder->idx == builder->capacity)
    {
        // Double the capacity
        builder->capacity *= 2;

        // Reallocate immediately (+1 for null terminator)
        char *new = realloc(builder->buf, sizeof(char) * (builder->capacity + 1));

        // Check if we got NULL
        if (new == NULL)
        {
#       ifndef _WIN32
            perror("realloc");
#       else
            puts("Runtime error: Out of memory");
#       endif
            exit(1);
        }

        builder->buf = new;
    }

    // Write the character to the buffer
    builder->buf[builder->idx] = c;
    builder->idx++;
}

inline void write_string_builder(StringBuilder *builder, const char *str)
{
    // Iterate over the string
    while (*str != '\0')
    {
        // Write the character
        write_char_string_builder(builder, *str);
        // Move to the next character
        str++;
    }
}

inline void destroy_string_builder(StringBuilder *builder)
{
    // Make sure the buffer is not NULL
    if (builder->buf == NULL) return;

    // Free the buffer and set it to NULL
    free(builder->buf);
    builder->buf = NULL;
}

void reset_string_builder(StringBuilder *builder)
{
    destroy_string_builder(builder);
    init_string_builder(builder, builder->capacity);
}

#if defined(__cplusplus)
}
#endif