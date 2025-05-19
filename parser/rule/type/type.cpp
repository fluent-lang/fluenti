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

#include "type.h"

#include "../../../util/unwrap.h"

void parse_type(
    token::TokenStream *tokens,
    const std::shared_ptr<parser::AST> &ast
)
{
    // Create a new AST node
    const auto type = std::make_shared<parser::AST>();
    type->rule = parser::Type;
    type->value = std::nullopt;
    type->children = std::make_optional(std::vector<std::shared_ptr<parser::AST>>());

    // Get the next token
    auto token = try_unwrap(tokens->next());

    // Parse pointers
    while (token.type == token::Ampersand)
    {
        // Create a new pointer node
        auto pointer = std::make_shared<parser::AST>();
        pointer->rule = parser::Pointer;
        pointer->value = std::nullopt;
        pointer->children = std::nullopt;

        // Add the pointer to the type
        type->children->push_back(pointer);

        // Move to the next token
        token = try_unwrap(tokens->next());
    }

    // Create a new AST node for the type
    const auto type_node = std::make_shared<parser::AST>();
    type_node->children = std::nullopt;
    type_node->value = std::nullopt;

    // Parse the raw type
    switch (token.type)
    {
        case token::Nothing:
        {
            type_node->rule = parser::Nothing;
            break;
        }

        case token::String:
        {
            type_node->rule = parser::String;
            break;
        }

        case token::Boolean:
        case token::Number:
        {
            type_node->rule = parser::Number;
            break;
        }

        case token::Decimal:
        {
            type_node->rule = parser::Decimal;
            break;
        }

        case token::Identifier:
        {
            type_node->rule = parser::Identifier;
            type_node->value = token.value;
            break;
        }

        default:
        {
            // Report an error
            throw std::runtime_error("Invalid type");
        }
    }

    // Add the identifier to the type
    type->children->push_back(type_node);

    // Parse array types
    while (tokens->peek()->type == token::ArrayType)
    {
        // Create a new AST node for the array type
        const auto arr = std::make_shared<parser::AST>();
        arr->rule = parser::ArrayType;
        arr->children = std::nullopt;
        arr->value = std::nullopt;
        type->children->push_back(arr);
        tokens->next();
    }

    // Add the type to the result
    ast->children->push_back(type);
}