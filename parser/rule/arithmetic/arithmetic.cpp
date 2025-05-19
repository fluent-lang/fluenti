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

#include "arithmetic.h"

#include "../../../util/unwrap.h"
#include "../identifier/identifier.h"

void parse_arithmetic_op(
    token::TokenStream *tokens,
    const std::shared_ptr<parser::AST> &ast,
    const parser::Rule rule
)
{
    // Create a new AST node
    const auto node = std::make_shared<parser::AST>();
    node->rule = rule;
    node->value = std::nullopt;
    node->children = std::make_optional(std::vector<std::shared_ptr<parser::AST>>());

    // Parse the identifier
    node->children->push_back(parse_identifier(tokens));

    // Get the next token

    // Parse allowed types
    switch (
        const auto next = try_unwrap(tokens->next());
        next.type
    )
    {
        case token::Identifier:
        {
            // Add the identifier
            node->children->push_back(parse_identifier_cur(tokens));
            break;
        }

        case token::NumLiteral:
        {
            // Create a new literal node
            const auto literal = std::make_shared<parser::AST>();
            literal->rule = parser::NumLiteral;
            literal->value = next.value;
            literal->children = std::nullopt;

            // Add the literal node to the AST
            node->children->push_back(literal);
            break;
        }

        default:
        {
            throw std::runtime_error("Invalid IR structure");
        }
    }

    // Add the node to the AST
    ast->children->push_back(node);
}
