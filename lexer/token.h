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

#ifndef TOKEN_H
#define TOKEN_H

#include <optional>
#include <cstddef>
#include <vector>
#include "../structure/immut_str/immut_str.h"

namespace token
{
    typedef enum
    {
        Decimal = 0, // 0
        Number, // 1
        Nothing, // 2
        String, // 3
        Alloca, // 4
        Ret, // 5
        RetVoid, // 6
        Function, // 7
        EndParams, // 8
        EndModule, // 9
        EndCall, // 10
        EndCo, // 11
        EndArray, // 12
        Module, // 13
        Take, // 14
        Address, // 15
        Reference, // 16
        Call, // 17
        Construct, // 18
        Array, // 19
        If, // 20
        Jump, // 21
        Store, // 22
        Mov, // 23
        Property, // 24
        Pick, // 25
        Or, // 26
        And, // 27
        Add, // 28
        Sub, // 29
        Mul, // 30
        Div, // 31
        Gt, // 32
        Lt, // 33
        Ge, // 34
        Le, // 35
        Ne, // 36
        Eq, // 37
        Not, // 38
        Block, // 39
        Ampersand, // 40
        Link, // 41
        End, // 42
        StringLiteral, // 43
        NumLiteral, // 44
        DecLiteral, // 45
        Identifier, // 46
        ArrayType, // 47
        Boolean, // 48
        Unknown, // 49
    } TokenType;

    typedef struct
    {
        TokenType type = Unknown;
        std::optional<ImmutStr *> value;
        size_t line = 0;
        size_t col = 0;
    } Token;

    class TokenStream
    {
        std::vector<Token> tokens;
        size_t current = 0;
        size_t _max = 0;

    public:
        explicit TokenStream(std::vector<Token> tokens)
        {
            _max = tokens.size();
            this->tokens = std::move(tokens);
        }

        std::optional<Token> nth(size_t index);
        std::optional<Token> next();
        std::optional<Token> peek();
        std::optional<Token> backtrack();
        std::optional<Token> curr();
        [[nodiscard]] size_t max() const;
        void reset()
        {
            current = 0;
        }

        ~TokenStream()
        {
            // Free all allocated memory
            reset(); // Position the stream at index 0
            std::optional<Token> current = nth(0); // (Does not consume index 0, just returns the token at index 0)
            while (current.has_value())
            {
                // Get the value
                if (
                    const auto value = current.value().value;
                    value.has_value()
                )
                {
                    // Get the ImmutStr
                    const auto str = value.value();

                    // Destroy the str
                    delete str;
                }

                // Get the next token
                current = next();
            }
        }
    };
}

#endif //TOKEN_H
