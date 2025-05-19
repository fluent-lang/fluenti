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

#ifndef PARSER_BINARY_H
#define PARSER_BINARY_H
#include <memory>

#include "../../parser.h"
#include "../../../lexer/token.h"

void parse_binary_opt(
    token::TokenStream *tokens,
    const std::shared_ptr<parser::AST> &ast,
    parser::Rule rule
);

void parse_singly_opt(
    token::TokenStream *tokens,
    const std::shared_ptr<parser::AST> &ast,
    parser::Rule rule
);

#endif //PARSER_BINARY_H
