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

#include "type.h"

#include <fluent/util/assert.h>
#include <fluent/util/unwrap.h>

file_code::Type process_type(const std::shared_ptr<fluent::parser::AST>& type)
{
    // Create a new Type object
    file_code::Type result;

    // Get the children
    const auto children = fluent::util::try_unwrap(type->children);
    fluent::util::assert(children.empty(), false);

    // Parse all children
    size_t i = 0;
    std::shared_ptr<fluent::parser::AST> curr = children[i];
    const size_t max = children.size();

    while (curr->rule == fluent::parser::Pointer)
    {
        result.pointers++;
        i++;
        curr = children[i];
    }

    // Parse the base type
    if (curr->rule == fluent::parser::Identifier)
    {
        result.base_type = curr->value;
    }
    else if (curr->rule == fluent::parser::Nothing)
    {
        result.primitive = file_code::Nothing;
    }
    else if (curr->rule == fluent::parser::Number)
    {
        result.primitive = file_code::Num;
    }
    else if (curr->rule == fluent::parser::Decimal)
    {
        result.primitive = file_code::Dec;
    }
    else if (curr->rule == fluent::parser::String)
    {
        result.primitive = file_code::String;
    }

    // Parse array types
    while (i < max && children[i]->rule == fluent::parser::ArrayType)
    {
        result.arrays++;
        i++;
    }

    return result;
}
