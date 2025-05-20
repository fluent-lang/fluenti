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

#ifndef HELP_GENERATOR_H
#define HELP_GENERATOR_H

#include <ankerl/unordered_dense.h>
#include <memory>

#include "fluent/cli/flag/flag.h"

void generate_help(
    const char *name,
    const char *desc,
    const ankerl::unordered_dense::map<std::string, std::shared_ptr<fluent::cli::Flag>>& flags
);

#endif //HELP_GENERATOR_H
