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

#include "object.h"

Object convert_to_object(const std::shared_ptr<fluent::parser::AST> &ast)
{
    // Create a result
    Object result;

    // Determine the object
    switch (ast->rule)
    {
        case fluent::parser::StringLiteral:
        {
            result.type.primitive = fluent::file_code::String;
            break;
        }

        case fluent::parser::NumLiteral:
        {
            result.type.primitive = fluent::file_code::Num;
            break;
        }

        case fluent::parser::DecLiteral:
        {
            result.type.primitive = fluent::file_code::Dec;
            break;
        }

        default:
            throw std::runtime_error("Invalid object type");
    }

    result.value = fluent::util::try_unwrap(ast->value)->buffer;
    return result;
}
