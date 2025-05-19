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

#include "link.h"

#include "../../../util/assert.h"
#include "../../../util/unwrap.h"

void parse_link(const std::vector<std::shared_ptr<parser::AST>> &blocks, token::TokenStream *tokens)
{
    // Ensure we don't have any blocks
    assert(blocks.empty(), true);

    // Peek to the next token
    const auto token = try_unwrap(tokens->next());
    assert(token.type, token::StringLiteral);

    // Do nothing since link is not relevant for interpretation
}
