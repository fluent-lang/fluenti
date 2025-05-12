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

#include "string_builder.h"
#include <stdio.h>
#include <stdlib.h>
#include <fluent_libc/str_copy/library.h>

#include "../../runtime/print/print.h"

StringBuilder create_string_builder(const size_t capacity)
{
    StringBuilder builder;
    builder.capacity = capacity;
    builder.buffer = malloc(sizeof(char) * (capacity + 1)); // +1 for the null terminator
    builder.used_capacity = 0;
    builder.len = 0;

    // Check for allocation failure
    if (builder.buffer == NULL)
    {
        perror("malloc");
        exit(1);
    }

    return builder;
}

void ensure_capacity_in_string_builder(StringBuilder *builder, const size_t capacity)
{
    // Make sure we have enough capacity in the buffer
    if (builder->used_capacity + capacity >= builder->capacity)
    {
        // Reallocate immediately (+1 for the null terminator)
        char *new_buffer = realloc(builder->buffer, sizeof(char) * (builder->capacity + builder->len + 1));

        // Check for allocation failure
        if (new_buffer == NULL)
        {
            free(builder->buffer);
            perror("realloc");
            exit(1);
        }

        builder->buffer = new_buffer;
        builder->used_capacity = 0;
    }
}

void writec_to_string_builder(StringBuilder *builder, const char str)
{
    // Check if the buffer has been freed
    if (builder->buffer == NULL)
    {
        println("Memory failure: Attempted to write to a freed string builder");
        exit(1);
    }

    // Check if we have to reallocate the buffer
    ensure_capacity_in_string_builder(builder, 1);

    // Write the buffer
    builder->buffer[builder->len] = str;
    builder->len++;
    builder->used_capacity++;
}

void write_to_string_builder(StringBuilder *builder, const char* str)
{
    while (*str != '\0')
    {
        writec_to_string_builder(builder, *str);
        str++;
    }
}

void destroy_string_builder(StringBuilder *builder)
{
    // Check if the buffer has been freed
    if (builder->buffer == NULL)
    {
        println("Memory failure: Attempted to write to a freed string builder");
        exit(1);
    }

    // Free the buffer
    free(builder->buffer);

    // Set the buffer to NULL
    builder->buffer = NULL;
}

char *collect_string_builder(const StringBuilder *builder)
{
    // Add a null terminator to the buffer
    builder->buffer[builder->len] = '\0';

    // Allocate a new string to hold the contents
    char *result = malloc(sizeof(char) * (builder->len + 1)); // +1 for null terminator

    // Copy the string directly
    str_copy(builder->buffer, result);
    return result;
}

void reset_string_builder(StringBuilder *builder)
{
    // Free the buffer
    free(builder->buffer);

    // Reset the length
    builder->len = 0;
    builder->used_capacity = 0;

    // Allocate a new buffer
    builder->buffer = malloc(sizeof(char) * (builder->capacity + 1)); // +1 for the null terminator
    if (builder->buffer == NULL)
    {
        perror("malloc");
        exit(1);
    }
}