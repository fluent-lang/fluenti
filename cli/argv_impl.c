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

#include "flag/flag.h"
#include <fluent_libc/str_len/library.h>
#include "argv_impl.h"
#include <stdio.h>
#include <stdlib.h>
#include <fluent_libc/str_copy/library.h>

void on_destroy_hook(bool _, FluentObject *object)
{
    const Argv *element = object->element;
    if (element->static_flags != NULL)
    {
        destroy_hash_map(element->static_flags);
    }

    if (element->string_flags != NULL)
    {
        destroy_hash_map(element->string_flags);
    }
}

HeapGuard *parse_argv(const int argc, const char **argv, HashMap *flags)
{
    // Create a HeapGuard
    HeapGuard *guard = alloc(sizeof(Argv));
    guard->on_destroy = on_destroy_hook;

    // Create a result
    Argv *result = guard->value->element;
    result->success = TRUE;

    // Check if argc is empty
    if (argc == 1)
    {
        result->success = FALSE;
        return guard;
    }

    // Insert all flags by shortcut
    HashMapIterator iterator = create_map_iterator(flags);
    while (map_iterator_has_next(&iterator))
    {
        char *key;
        Flag *value;
        map_iterator_next(&iterator, &key, (void **) &value);

        // Set the original name
        value->original_name = key;

        // Insert into the flags
        insert_to_map(flags, value->shortcut, value);
    }

    // Create a HashMap for the static & string flags
    HashMap *static_flags = create_hash_map();
    HashMap *string_flags = create_hash_map();

    // Set the static & string flags
    result->static_flags = static_flags;
    result->string_flags = string_flags;

    // Flags
    bool parsing_flag = FALSE;
    char *last_flag_name = NULL;

    // Iterate over argv
    argv++;
    while (*argv)
    {
        // Get the current argument
        const char *arg = *argv;

        // Check if we are parsing a flag
        if (parsing_flag)
        {
            // Move onto the next element
            argv++;

            // Set the value in the map
            insert_to_map(result->string_flags, last_flag_name, (void *) arg);

            // Free the ptr immediately and set it to NULL
            free(last_flag_name);
            last_flag_name = NULL;
            parsing_flag = FALSE;
            continue;
        }

        // Determine if we have a flag
        if (arg[0] == '-')
        {
            // Move onto the next element
            argv++;

            // Check if we have a short or long flag
            if (arg[1] == '-')
            {
                // Make sure the string does not end at index 2
                if (arg[2] == '\0')
                {
                    if (last_flag_name != NULL)
                    {
                        free(last_flag_name);
                    }

                    result->success = FALSE;
                    return guard;
                }

                // Get the arg length
                const size_t arg_len = str_len(arg);

                // Allocate the flag's name on the heap
                char *name = malloc(sizeof(char) * (arg_len + 1));

                // Copy the string
                str_copy(arg + 2, name);

                last_flag_name = name;
            } else if (arg[1] != '\0')
            {
                // Make sure the string ends at index 2
                if (arg[2] != '\0')
                {
                    if (last_flag_name != NULL)
                    {
                        free(last_flag_name);
                    }

                    result->success = FALSE;
                    return guard;
                }

                // Allocate the flag's name on the heap
                char *name = malloc(sizeof(char) * 2);
                name[1] = '\0';
                name[0] = arg[1];

                // Set the last flag's name
                last_flag_name = name;
            } else
            {
                // Unexpected EOF
                result->success = FALSE;
                return guard;
            }

            // Get the flag by name
            const Flag *flag = get_from_map(flags, last_flag_name);

            // Check if it is NULL
            if (flag == NULL)
            {
                free(last_flag_name);
                result->success = FALSE;
                return guard;
            }

            // Insert to the parsed flags if needed
            if (flag->type == STATIC)
            {
                parsing_flag = FALSE;
                insert_to_map(result->static_flags, last_flag_name, NULL);

                // Free the pointer immediately and set it to NULL
                free(last_flag_name);
                last_flag_name = NULL;
            } else
            {
                parsing_flag = TRUE;
            }

            continue;
        }

        // Unexpected value, terminate immediately
        result->success = FALSE;
        return guard;
    }

    // Make sure we properly free memory
    if (last_flag_name != NULL)
    {
        free(last_flag_name);
    }

    // Make sure we have flags
    if (parsing_flag || (static_flags->len == 0 && string_flags->len == 0))
    {
        result->success = FALSE;
    }

    return guard;
}
