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
#include <memory>
#include "argv_impl.h"

std::shared_ptr<Argv> parse_argv(const int argc, const char **argv, ankerl::unordered_dense::map<std::string, std::shared_ptr<Flag>> &flags)
{
    // Create a result
    const auto result = std::make_shared<Argv>();
    result->success = true;

    // Check if argc is empty
    if (argc == 1)
    {
        result->success = false;
        return result;
    }

    // Insert all flags by shortcut
    ankerl::unordered_dense::map<std::string, std::shared_ptr<Flag>> new_flags;
    for (auto &[key, value] : flags)
    {
        value->original_name = key;
        // Insert the flag into the map
        new_flags[value->shortcut] = value;
    }

    // Insert the new flags
    for (auto &[key, value] : new_flags)
    {
        // Insert the flag into the map
        flags[key] = value;
    }

    // Create a HashMap for the static & string flags
    ankerl::unordered_dense::map<std::string, bool> static_flags;
    ankerl::unordered_dense::map<std::string, const char *> string_flags;

    // Flags
    bool parsing_flag = false;
    std::string last_flag_name;

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
            string_flags[last_flag_name] = arg;

            // Reset the flag
            last_flag_name.clear();
            parsing_flag = false;
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
                    result->success = false;
                    return result;
                }

                last_flag_name = std::string(arg + 2);
            } else if (arg[1] != '\0')
            {
                // Make sure the string ends at index 2
                if (arg[2] != '\0')
                {
                    result->success = false;
                    return result;
                }

                // Set the last flag's name
                last_flag_name = std::string(arg + 1);
            } else
            {
                // Unexpected EOF
                result->success = false;
                return result;
            }

            // Get the flag by name
            if (!flags.contains(last_flag_name))
            {
                result->success = false;
                return result;
            }

            const std::shared_ptr<Flag> flag = flags[last_flag_name];

            // Insert to the parsed flags if needed
            if (flag->type == STATIC)
            {
                parsing_flag = false;
                static_flags[last_flag_name] = true;
            } else
            {
                parsing_flag = true;
            }

            last_flag_name = flag->original_name;
            continue;
        }

        // Unexpected value, terminate immediately
        result->success = false;
        return result;
    }

    // Make sure we have flags
    if (parsing_flag || (static_flags.empty() && string_flags.empty()))
    {
        result->success = false;
        return result;
    }

    // Make sure we have all required flags
    if (!static_flags.contains("help"))
    {
        for (auto &[key, value] : flags)
        {
            // Skip the flag if it's a shortcut
            if (key == value->shortcut)
            {
                continue;
            }

            // Check if the flag is required
            if (value->required)
            {
                // Check if the flag is in the map
                if (
                    (value->type == STATIC && !static_flags.contains(key))
                    || (value->type == STRING && !string_flags.contains(key))
                )
                {
                    result->success = false;
                    return result;
                }
            }
        }
    }

    // Set the static & string flags
    result->static_flags = static_flags;
    result->string_flags = string_flags;

    return result;
}
