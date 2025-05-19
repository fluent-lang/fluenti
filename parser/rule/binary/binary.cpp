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
// Created by rodrigo on 5/17/25.
//

#include "binary.h"

#include "../identifier/identifier.h"

inline std::shared_ptr<parser::AST> create_node(const parser::Rule rule)
{
    // Create a new AST node
    const auto node = std::make_shared<parser::AST>();
    node->rule = rule;
    node->value = std::nullopt;
    node->children = std::make_optional(std::vector<std::shared_ptr<parser::AST>>());

    return node;
}

void parse_singly_opt(
    token::TokenStream *tokens,
    const std::shared_ptr<parser::AST> &ast,
    const parser::Rule rule
)
{
    // Create a new AST node
    const std::shared_ptr<parser::AST> node = create_node(rule);

    // Parse two identifiers for the operands
    node->children->push_back(parse_identifier(tokens));

    // Add the binary node to the AST
    ast->children->push_back(node);
}

void parse_binary_opt(
    token::TokenStream *tokens,
    const std::shared_ptr<parser::AST> &ast,
    const parser::Rule rule
)
{
    // Create a new AST node
    const std::shared_ptr<parser::AST> node = create_node(rule);

    // Parse two identifiers for the operands
    node->children->push_back(parse_identifier(tokens));
    node->children->push_back(parse_identifier(tokens));

    // Add the binary node to the AST
    ast->children->push_back(node);
}
