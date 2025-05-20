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
// Created by rodrigo on 5/18/25.
//

#include "mod.h"

#include <fluent/util/unwrap.h>
#include "../type/type.h"

void process_mod(file_code::FileCode &result, const std::shared_ptr<parser::AST> &ast)
{
    // Create a new module
    const auto mod = std::make_shared<file_code::Mod>();

    // Unwrap the children
    const auto children = util::try_unwrap(ast->children);

    // Get the mod name
    const auto name = util::try_unwrap(children[0]->value);

    // Get the mod name
    for (size_t i = 1; i < children.size(); i++)
    {
        // Parse the type
        const auto type = process_type(children[i]);

        // Add the type to the module
        mod->types.push_back(type);
    }

    // Push the module to the result
    result.mods[name] = mod;
}
