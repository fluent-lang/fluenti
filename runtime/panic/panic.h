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
// Created by rodrigo on 5/19/25.
//

#ifndef RUNTIME_PANIC_H
#define RUNTIME_PANIC_H
#include <vector>

#include "../../core/object/object.h"
#include "../../std/std.h"
#include <fluent/string_builder/library.h>

namespace runtime
{
    inline void panic(const std::vector<Object> &args)
    {
        // Use a string builder to use mutex'd printin whilst
        // non-blocking the mutex for each argument
        StringBuilder builder;
        init_string_builder(&builder, 1024);

        // Write the panic structure
        write_string_builder(&builder, "Panic: ");

        // Write the string
        write_string_builder(&builder, static_cast<char *>(args[0].value));
        write_string_builder(&builder, "\n");

        // Write trace information
        write_string_builder(&builder, "Program panicked at: ");
        write_string_builder(&builder, static_cast<char *>(args[1].value));
        write_string_builder(&builder, ":");
        write_string_builder(&builder, static_cast<char *>(args[2].value));
        write_string_builder(&builder, ":");
        write_string_builder(&builder, static_cast<char *>(args[3].value));

        write_string_builder(&builder, "\n");
        // Print the string builder once
        fluent_std::Runtime::print(collect_string_builder(&builder));

        // Destroy the string builder
        destroy_string_builder(&builder);

        // Exit the program
        exit(1);
    }
}

#endif //RUNTIME_PANIC_H
