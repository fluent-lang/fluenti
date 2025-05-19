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

#include "../flag/flag.h"
#include "get_flags.h"

ankerl::unordered_dense::map<std::string, std::shared_ptr<Flag>> get_default_flags()
{
    // Create a new HashMap
    ankerl::unordered_dense::map<std::string, std::shared_ptr<Flag>> flags;

    // Create an out path flag
    const auto path_flag = std::make_shared<Flag>();
    path_flag->original_name = "";
    path_flag->desc = "Path to the program to be executed";
    path_flag->shortcut = "p";
    path_flag->type = STRING;
    path_flag->required = true;

    // Create a help flag
    const auto help_flag = std::make_shared<Flag>();
    help_flag->original_name = "";
    help_flag->desc = "Displays this menu";
    help_flag->shortcut = "h";
    help_flag->type = STATIC;
    help_flag->required = false;

    // Set the default flags
    flags["path"] = path_flag;
    flags["help"] = help_flag;

    return flags;
}
