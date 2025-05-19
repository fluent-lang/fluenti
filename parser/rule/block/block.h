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

#ifndef PARSER_BLOOCK_H
#define PARSER_BLOOCK_H

#include <vector>
#include <memory>

#include "../../parser.h"
#include "../../../lexer/token.h"

void parse_block(
    std::vector<std::shared_ptr<parser::AST>> &blocks,
    token::TokenStream *tokens,
    const std::shared_ptr<parser::AST> &ast
);

#endif //PARSER_BLOOCK_H
