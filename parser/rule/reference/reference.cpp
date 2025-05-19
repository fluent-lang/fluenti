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

#include "reference.h"

#include "../../../util/assert.h"
#include "../../../util/unwrap.h"
#include "../identifier/identifier.h"
#include "../type/type.h"

void parse_reference(
    const std::vector<std::shared_ptr<parser::AST>> &blocks,
    token::TokenStream *tokens,
    const std::shared_ptr<parser::AST> &ast
)
{
    // Make sure we don't have any blocks
    assert(blocks.empty(), true);

    // Create a new AST node
    const auto reference = std::make_shared<parser::AST>();
    reference->rule = parser::Ref;
    reference->value = std::nullopt;
    reference->children = std::make_optional(std::vector<std::shared_ptr<parser::AST>>());

    // Parse the reference name
    const auto name = parse_identifier(tokens);
    reference->children->push_back(name);

    // Parse the type
    parse_type(tokens, reference);

    // Parse the value
    switch (
        const auto value = try_unwrap(tokens->next());
        value.type
    )
    {
        case token::StringLiteral:
        case token::NumLiteral:
        case token::DecLiteral:
        {
            // Create a new string literal node
            const auto literal = std::make_shared<parser::AST>();
            literal->rule =
                value.type == token::StringLiteral ? parser::StringLiteral
                    : value.type == token::NumLiteral ? parser::NumLiteral
                        : parser::DecLiteral;
            literal->value = value.value;
            literal->children = std::nullopt;
            reference->children->push_back(literal);
            break;
        }

        default:
        {
            throw std::runtime_error("Invalid IR structure (ref)");
        }
    }

    // Add the reference to the result
    ast->children->push_back(reference);
}