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

#include "expr.h"

#include "../../../util/unwrap.h"
#include "../arithmetic/arithmetic.h"
#include "../binary/binary.h"
#include "../ranged/ranged.h"
#include "../identifier/identifier.h"
#include "../prop/prop.h"

void parse_single_token(
    const token::Token &current,
    const std::shared_ptr<parser::AST> &ast,
    const parser::Rule rule
)
{
    // Create a new node
    const auto node = std::make_shared<parser::AST>();
    node->rule = rule;
    node->value = current.value;
    node->children = std::nullopt;

    // Add the node to the AST
    ast->children->push_back(node);
}

void parse_expr(
    token::TokenStream *tokens,
    const std::shared_ptr<parser::AST> &ast,
    const char *trace
)
{
    // Create a new expression node
    const auto expr = std::make_shared<parser::AST>();
    expr->rule = parser::Expression;
    expr->value = std::nullopt;
    expr->children = std::make_optional(std::vector<std::shared_ptr<parser::AST>>());

    // Get the next token
    switch (
        const token::Token next = try_unwrap(tokens->curr());
        next.type
    )
    {
        case token::StringLiteral:
        {
            parse_single_token(next, ast, parser::StringLiteral);
            break;
        }

        case token::NumLiteral:
        {
            parse_single_token(next, ast, parser::NumLiteral);
            break;
        }

        case token::DecLiteral:
        {
            parse_single_token(next, ast, parser::DecLiteral);
            break;
        }

        case token::Identifier:
        {
            const std::shared_ptr<parser::AST> id = parse_identifier_cur(tokens);

            // Add the identifier to the expression node
            expr->children->push_back(id);
            break;
        }

        case token::Call:
        {
            parse_ranged_op(tokens, expr, false, false);
            break;
        }

        case token::Construct:
        {
            parse_ranged_op(tokens, expr, true, false);
            break;
        }

        case token::Array:
        {
            parse_ranged_op(tokens, expr, false, true);
            break;
        }

        case token::Property:
        {
            parse_prop(tokens, expr);
            break;
        }

        case token::Add:
        {
            parse_arithmetic_op(tokens, expr, parser::Add);
            break;
        }

        case token::Sub:
        {
            parse_arithmetic_op(tokens, expr, parser::Sub);
            break;
        }

        case token::Mul:
        {
            parse_arithmetic_op(tokens, expr, parser::Mul);
            break;
        }

        case token::Div:
        {
            parse_arithmetic_op(tokens, expr, parser::Div);
            break;
        }

        case token::Take:
        {
            parse_singly_opt(tokens, expr, parser::Take);
            break;
        }

        case token::Address:
        {
            parse_singly_opt(tokens, expr, parser::Addr);
            break;
        }

        case token::Eq:
        {
            parse_binary_opt(tokens, expr, parser::Eq);
            break;
        }

        case token::Ne:
        {
            parse_binary_opt(tokens, expr, parser::Ne);
            break;
        }

        case token::Not:
        {
            parse_binary_opt(tokens, expr, parser::Not);
            break;
        }

        case token::Gt:
        {
            parse_binary_opt(tokens, expr, parser::Gt);
            break;
        }

        case token::Lt:
        {
            parse_binary_opt(tokens, expr, parser::Lt);
            break;
        }

        case token::Ge:
        {
            parse_binary_opt(tokens, expr, parser::Ge);
            break;
        }

        case token::Le:
        {
            parse_binary_opt(tokens, expr, parser::Le);
            break;
        }

        default:
        {
            puts(trace);
            throw std::runtime_error("Invalid IR structure (expr)");
        }
    }

    // Add the expression node to the AST
    ast->children->push_back(expr);
}
