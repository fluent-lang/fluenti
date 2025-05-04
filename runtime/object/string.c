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
// Created by rodrigo on 5/4/25.
//

#include <fluent_libc/str_copy/library.h>
#include "string.h"

#include <stdlib.h>

#ifndef FLUENT_RUNTIME_STR_CAPACITY
#define FLUENT_RUNTIME_STR_CAPACITY 120
#endif

void set_guard_props(const HeapGuard *guard)
{
    if (guard == NULL)
    {
        exit(1);
    }

    guard->value->type.is_primitive = TRUE;
    guard->value->type.pointer_count = 0;
    guard->value->type.array_count = 0;
    guard->value->type.primitive = STR;
}

String create_string()
{
    // Create a new string
    String str;

    // Create a new HeapGuard
    HeapGuard *guard = alloc(sizeof(char) * FLUENT_RUNTIME_STR_CAPACITY);

    // Initialize the value
    char *value = guard->value->element;
    value[0] = '\0';

    // Set the correct object type
    set_guard_props(guard);

    // Set the string's values
    str.length = 0;
    str.value = guard;
    str.used_capacity = 0;

    return str;
}

void grow_string(String *str)
{
    // Expand the guard
    expand_guard(str->value, FLUENT_RUNTIME_STR_CAPACITY);

    // Reset the used capacity
    str->used_capacity = 0;
}

void write_string(String *str, const char *value)
{
    char* buffer = str->value->value->element;

    // Write all characters
    while (*value)
    {
        // Check if we have to reallocate the string
        if (str->used_capacity == FLUENT_RUNTIME_STR_CAPACITY)
        {
            // Grow the string
            grow_string(str);

            // Get the buffer again (changes after reallocation)
            buffer = str->value->value->element;
        }

        // Get and write the character
        const char c = *value;
        buffer[str->length] = c;

        // Increment the length and used capacity
        str->length++;
        str->used_capacity++;

        // Move to the next character
        value++;
    }
}

HeapGuard *get_string(const String *str)
{
    // Create a new HeapGuard
    HeapGuard *guard = alloc(sizeof(char) * (str->length + 1)); // +1 for null terminator
    set_guard_props(guard);

    // Get the buffer
    char *buffer = guard->value->element;

    // Write all characters
    str_copy(str->value->value->element, buffer);

    // Write a new null terminator
    buffer[str->length] = '\0';

    return guard;
}