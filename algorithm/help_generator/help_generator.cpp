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
// Created by rodrigo on 5/16/25.
//

#include "help_generator.h"
#include "../../std_c/print/print.h"
#include "../padding/padding.h"

void generate_help(
    const char *name,
    const char *desc,
    const ankerl::unordered_dense::map<std::string, std::shared_ptr<Flag>>& flags
)
{
    // We can use the C print implementation directly, no need to use the mutexed
    // version here, as this is supposed to happen on startup
    r_print(name);
    r_print(" - ");
    r_println(desc);
    r_println("");
    r_println("AVAILABLE FLAGS:");

    // Iterate over the flags and print them all
    for (auto &[key, value] : flags)
    {
        // Ignore shortcuts
        if (key == value->shortcut)
        {
            continue;
        }

        // Print the flag info
        print_padding(key.c_str(), 15);
        r_print(value->desc.c_str());

        // Print the flag metadata
        if (value->type == STRING)
        {
            r_print(" (STRING)");
        }

        if (value->required)
        {
            r_print(" (REQUIRED)");
        }
        r_println("");
    }
}