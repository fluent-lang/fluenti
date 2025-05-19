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

#include "pick.h"

#include "../binary/binary.h"

void parse_pick(
    token::TokenStream *tokens,
    const std::shared_ptr<parser::AST> &ast
)
{
    // Create a new pick node
    const auto pick = std::make_shared<parser::AST>();
    pick->rule = parser::Pick;
    pick->children = std::make_optional(std::vector<std::shared_ptr<parser::AST>>());
    pick->value = std::nullopt;

    // Parse two binary opts
    parse_binary_opt(tokens, pick, parser::PickOpt);
    parse_binary_opt(tokens, pick, parser::PickOpt);

    // Add the pick node to the AST
    ast->children->push_back(pick);
}
