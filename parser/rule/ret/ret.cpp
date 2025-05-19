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

#include "ret.h"

#include "../../../util/assert.h"
#include "../expr/expr.h"

void parse_ret(
    const std::vector<std::shared_ptr<parser::AST>> &blocks,
    token::TokenStream *tokens,
    const std::shared_ptr<parser::AST> &ast
)
{
    // Make sure we have at least one block
    assert(blocks.empty(), false);

    // Create a new ret node
    const auto ret = std::make_shared<parser::AST>();
    ret->rule = parser::Ret;
    ret->value = std::nullopt;
    ret->children = std::make_optional(std::vector<std::shared_ptr<parser::AST>>());

    // Check if we have a ret_void token
    if (tokens->curr()->type == token::RetVoid)
    {
        // Add the tree directly to the AST
        ast->children->push_back(ret);
        return;
    }

    // Parse the expression
    parse_expr(tokens, ret, "ret");

    // Add the ret node to the AST
    ast->children->push_back(ret);
}
