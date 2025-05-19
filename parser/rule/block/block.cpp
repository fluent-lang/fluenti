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

#include "block.h"

#include "../../../util/assert.h"
#include "../identifier/identifier.h"

void parse_block(
    std::vector<std::shared_ptr<parser::AST>> &blocks,
    token::TokenStream *tokens,
    const std::shared_ptr<parser::AST> &ast
)
{
    // Make sure we have a block
    assert(blocks.empty(), false);

    // Create a new block node
    const auto block = std::make_shared<parser::AST>();
    block->rule = parser::Block;
    block->value = std::nullopt;
    block->children = std::make_optional(std::vector<std::shared_ptr<parser::AST>>());

    // Parse the block's name
    const auto name = parse_identifier(tokens);
    block->children->push_back(name);

    // Push the block to the blocks vector
    blocks.push_back(block);

    // Push the block to the AST
    ast->children->push_back(block);
}
