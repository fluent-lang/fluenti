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

#include "identifier.h"

#include "../../../util/assert.h"
#include "../../../util/unwrap.h"

std::shared_ptr<parser::AST> parse_identifier_cur(token::TokenStream *tokens)
{
    // Get the current token
    const auto current = try_unwrap(tokens->curr());

    assert(current.type, token::Identifier);

    // Create a new AST node
    auto ast = std::make_shared<parser::AST>();
    ast->rule = parser::Identifier;
    ast->value = current.value;
    ast->children = std::nullopt;

    return ast;
}

std::shared_ptr<parser::AST> parse_identifier(token::TokenStream *tokens)
{
    // Get the next token
    try_unwrap(tokens->next());
    return parse_identifier_cur(tokens);
}
