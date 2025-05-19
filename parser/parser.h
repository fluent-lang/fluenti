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

#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <optional>
#include <vector>

#include "../heap/heap_guard.h"
#include "../lexer/token.h"
#include "../structure/immut_str/immut_str.h"

namespace parser
{
    typedef enum {
        Program = 0, // 0
        StringLiteral, // 1
        NumLiteral, // 2
        DecLiteral, // 3
        String, // 4
        Number, // 5
        Decimal, // 6
        Nothing, // 7
        Identifier, // 8
        Link, // 9
        Function, // 10
        Mov, // 11
        Call, // 12
        Params, // 13
        Param, // 14
        Alloca, // 15
        Store, // 16
        Take, // 17
        Addr, // 18
        Add, // 19
        Sub, // 20
        Mul, // 21
        Div, // 22
        Eq, // 23
        Ne, // 24
        Gt, // 25
        Lt, // 26
        Ge, // 27
        Le, // 28
        Jump, // 29
        Block, // 30
        Pick, // 31
        PickOpt, // 32
        If, // 33
        Ret, // 34
        Ref, // 35
        Mod, // 36
        ModEl, // 37
        Prop, // 38
        Array, // 39
        Expression, // 40
        Pointer, // 41
        ArrayType, // 42
        Type, // 43
        Parameters, // 44
        Not, // 45
        Construct, // 46
    } Rule;

    typedef struct AST
    {
        Rule rule = Program;
        std::optional<std::vector<std::shared_ptr<AST>>> children;
        std::optional<ImmutStr *> value;
    } AST;

    std::shared_ptr<AST> parse_code(token::TokenStream *stream);
}

#endif //PARSER_H
