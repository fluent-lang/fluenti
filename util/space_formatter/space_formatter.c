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

#include "space_formatter.h"

#include <stdio.h>
#include <stdlib.h>
#include <fluent_libc/str_copy/library.h>
#include <fluent_libc/str_len/library.h>

void f_format_spaces(char *buffer, const size_t len, const char* initial_str, const size_t spaces)
{
    // Determine the number of spaces we need
    ssize_t spaces_needed = (ssize_t) spaces - len;
    if (spaces_needed < 0)
    {
        spaces_needed = 1;
    }

    // Copy the string
    str_copy(initial_str, buffer);

    // Add the spaces
    for (size_t i = 0; i < spaces_needed; i++)
    {
        buffer[len + i] = ' ';
    }

    // Add a null terminator
    buffer[len + spaces_needed] = '\0';
}

char *format_spaces(const char* initial_str, const size_t spaces)
{
    // Determine the capacity we are going to need
    size_t capacity = 0;

    // Determine the length of the string
    const size_t len = str_len(initial_str);
    capacity += len;

    // Determine the number of spaces we need
    ssize_t spaces_needed = (ssize_t) spaces - len;
    if (spaces_needed < 0)
    {
        // Add only 1 to the spaces needed
        capacity += 1;
    } else
    {
        capacity += spaces_needed;
    }

    // Directly allocate the string on the heap (+1 for the null terminator)
    char *str = malloc(sizeof(char) * (capacity + 1));

    // Handle allocation errors
    if (str == NULL)
    {
        perror("malloc");
        exit(1);
    }

    f_format_spaces(str, len, initial_str, spaces);

    // Return the string
    return str;
}