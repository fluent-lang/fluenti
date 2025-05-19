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

#ifndef ARGV_IMPL_H
#define ARGV_IMPL_H

#include <ankerl/unordered_dense.h>
#include <string>
#include <memory>
#include "flag/flag.h"

typedef struct
{
    ankerl::unordered_dense::map<std::string, bool> static_flags;
    ankerl::unordered_dense::map<std::string, const char *> string_flags;
    bool success;
} Argv;

std::shared_ptr<Argv> parse_argv(int argc, const char **argv, ankerl::unordered_dense::map<std::string, std::shared_ptr<Flag>> &flags);

#endif //ARGV_IMPL_H
