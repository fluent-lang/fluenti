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

#include "help_generator.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../cli/flag/flag.h"
#include "../../heap/heap_alloc.h"
#include "../../runtime/print/print.h"
#include "../../algorithm/space_formatter/space_formatter.h"
#include "../../structure/string_builder/string_builder.h"

void generate_help(const char* name, const char* desc, const HashMap *flags)
{
    // Print information headers
    print(name);
    print(" - ");
    println(desc);
    println("");

    // Print usage
    print("USAGE: ");
    print(name);
    println(" --<flags..> [value]");
    println("");

    // Print available flags
    println("AVAILABLE FLAGS:");

    // Check for empty flags
    if (flags->len == 0)
    {
        println("(EMPTY)");
    } else
    {
        // Iterate over the HashMap
        HashMapIterator iterator = create_map_iterator(flags);
        while (map_iterator_has_next(&iterator))
        {
            // Get the item's name
            char *key;
            HeapGuard *value_guard;
            map_iterator_next(&iterator, &key, (void **) &value_guard);
            const Flag *value = value_guard->value->element;

            // Ignore flags that aren't the original ones
            if (key[0] == '\0' || key != value->original_name)
            {
                continue;
            }

            // Add the flag to the string builder
            print("--");
            StringBuilder builder = create_string_builder(250);
            write_to_string_builder(&builder, key);

            if (value->shortcut != NULL && value->shortcut[0] != '\0')
            {
                write_to_string_builder(&builder, ", -");
                write_to_string_builder(&builder, value->shortcut);
            }

            char *spaces = format_spaces(collect_string_builder(&builder), 16);
            print(spaces);
            free(spaces);
            destroy_string_builder(&builder);
            if (value->desc == NULL)
            {
                print("(NO DESC YET)");
            } else
            {
                print(value->desc);
            }

            // Add flag information
            if (value->type != STATIC)
            {
                print(" (STRING)");
            }

            if (value->required == TRUE)
            {
                print(" (REQUIRED)");
            }

            println("");
        }
    }
}
