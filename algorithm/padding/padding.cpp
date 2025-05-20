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

#include "padding.h"
#include <fluent/string_builder/library.h>
#include "../../std/std.h"

void print_padding(const char *str, const size_t spaces)
{
    // Calculate the number of spaces needed
    size_t spaces_needed = 0;

    // Temporarily allocate memory to print in one pass
    // and avoid locking the mutex for every character (which is more expensive)
    StringBuilder builder;
    init_string_builder(&builder, 10);

    // Use the runtime to print the string
    while (*str)
    {
        write_char_string_builder(&builder, *str);

        // Increment the spaces needed to calculate the string's length
        spaces_needed++;

        // Move to the next character
        str++;
    }

    // Determine the actual spaces needed
    if (spaces_needed >= spaces)
    {
        // Print an additional space
        write_char_string_builder(&builder, ' ');

        // Print the string directly
        fluent_std::Runtime::print(collect_string_builder_no_copy(&builder));

        // Free the allocated memory
        destroy_string_builder(&builder);
        return;
    }

    // Print the spaces
    spaces_needed = spaces - spaces_needed;
    for (size_t i = 0; i < spaces_needed; i++)
    {
        write_char_string_builder(&builder, ' ');
    }

    // Print the string directly
    fluent_std::Runtime::print(collect_string_builder_no_copy(&builder));

    // Free the allocated memory
    destroy_string_builder(&builder);
}
