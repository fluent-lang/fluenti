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

#include "lexer.h"

#include <chrono>
#include <ankerl/unordered_dense.h>

#include "../heap/heap_guard.h"
#include "../std/std.h"
#include "../structure/string_builder/string_builder.h"

// Define the token map
ankerl::unordered_dense::map<std::string, token::TokenType> token_map =
{
    {"mov", token::Mov},
    {"dec", token::Decimal},
    {"num", token::Number},
    {"nothing", token::Nothing},
    {"str", token::String},
    {"alloca", token::Alloca},
    {"ref", token::Reference},
    {"c", token::Call},
    {"ret", token::Ret},
    {"ret_void", token::RetVoid},
    {"f", token::Function},
    {"end_params", token::EndParams},
    {"end_mod", token::EndModule},
    {"end_call", token::EndCall},
    {"end_co", token::EndCo},
    {"end_arr", token::EndArray},
    {"mod", token::Module},
    {"take", token::Take},
    {"addr", token::Address},
    {"if", token::If},
    {"jump", token::Jump},
    {"store", token::Store},
    {"prop", token::Property},
    {"pick", token::Pick},
    {"or", token::Or},
    {"and", token::And},
    {"add", token::Add},
    {"sub", token::Sub},
    {"mul", token::Mul},
    {"div", token::Div},
    {"gt", token::Gt},
    {"lt", token::Lt},
    {"le", token::Le},
    {"ge", token::Ge},
    {"ne", token::Ne},
    {"eq", token::Eq},
    {"not", token::Not},
    {"block", token::Block},
    {"arr", token::Array},
    {"&", token::Ampersand},
    {"link", token::Link},
    {"end", token::End},
    {"co", token::Construct},
    {"[]", token::ArrayType},
    {"bool", token::Boolean},
};

ImmutStr *convert_value(const StringBuilder &current)
{
    // Assign the value only when needed
    char *str = collect_string_builder(&current);
    return new ImmutStr(str, current.idx);
}

void push_token(
    std::vector<token::Token> &result,
    StringBuilder &current,
    bool &is_string,
    bool &is_num,
    bool &is_dec,
    bool &is_id,
    bool &is_escape,
    const size_t line,
    size_t &col,
    size_t &token_idx
)
{
    // Ignore empty tokens
    if (current.idx == 0) return;

    // Create a new token
    token::Token token;
    token.col = col;
    token.line = line;

    // Assign directly for string literals
    if (is_string)
    {
        // Move the string builder to a HeapGuard
        token.value = convert_value(current);
        token.type = token::StringLiteral;
    }
    // Check if the token is in the map (Collect without copy)
    else if (const auto it = token_map.find(collect_string_builder_no_copy(&current)); it != token_map.end())
    {
        token.type = it->second;
    }
    // Assign the appropriate token type
    else if (is_dec)
    {
        // Move the strings builder to a HeapGuard
        token.value = convert_value(current);
        token.type = token::DecLiteral;
    } else if (is_num)
    {
        // Move the string builder to a HeapGuard
        token.value = convert_value(current);
        token.type = token::NumLiteral;
    } else if (is_id)
    {
        // Move the string builder to a HeapGuard
        token.value = convert_value(current);
        token.type = token::Identifier;
    } else
    {
        // Cloning the value is not needed here
        // Default to unknown token
        token.type = token::Unknown;
    }

    // Push the token to the result
    result.push_back(token);

    // Reset all flags
    is_string = false;
    is_num = false;
    is_dec = false;
    is_id = true;
    is_escape = false;
    token_idx = 0;

    // Reset the string builder
    reset_string_builder(&current);

    col++;
}

token::TokenStream tokenize(const std::string &input)
{
    // Define a result
    std::vector<token::Token> result;

    // Create a new string builder
    StringBuilder current;
    init_string_builder(&current, 120);

    // Define col/line counters
    size_t line = 1;
    size_t col = 1;
    size_t token_idx = 0;

    // Keep track of the lexer status
    bool is_string = false;
    bool is_num = false;
    bool is_dec = false;
    bool is_id = true;
    bool is_escape = false;
    const size_t max = std::max(input.length(), static_cast<size_t>(1)) - 1;
    size_t skip = 0;

    // Iterate over the input string
    for (size_t i = 0; i <= max; i++)
    {
        if (skip && i <= skip)
        {
            continue;
        }

        const char c = input[i];

        // Handle newlines
        if (c == '\n')
        {
            // Handle strings
            if (is_string)
            {
                // Report the error
                fluent_std::Runtime::println("Lexing error: Invalid IR structure");
                exit(1);
            }

            push_token(
                result,
                current,
                is_string,
                is_num,
                is_dec,
                is_id,
                is_escape,
                line,
                col,
                token_idx
            );

            line++;
            col = 1;
            continue;
        }

        // Handle whitespaces
        if (!is_string && c == ' ')
        {
            push_token(
                result,
                current,
                is_string,
                is_num,
                is_dec,
                is_id,
                is_escape,
                line,
                col,
                token_idx
            );
            col++;
            continue;
        }

        // Infer identifiers
        if (token_idx == 0)
        {
            if (isdigit(c))
            {
                is_id = false;
                is_num = true;
            }
        }

        // Special case: '[]'
        if (
            !is_string && i != 0 &&
            i + 1 <= max && c == '[' &&
            input[i + 1] == ']'
        )
        {
            // Push the current token
            push_token(
                result,
                current,
                is_string,
                is_num,
                is_dec,
                is_id,
                is_escape,
                line,
                col,
                token_idx
            );

            // Write an ampersand
            write_char_string_builder(&current, c);
            write_char_string_builder(&current, ']');

            // Push the token
            push_token(
                result,
                current,
                is_string,
                is_num,
                is_dec,
                is_id,
                is_escape,
                line,
                col,
                token_idx
            );

            // Skip the next character
            skip = i + 1;
            continue;
        }

        // Special case: '&'
        if (!is_string && c == '&')
        {
            // Push the current token
            push_token(
                result,
                current,
                is_string,
                is_num,
                is_dec,
                is_id,
                is_escape,
                line,
                col,
                token_idx
            );

            // Write an ampersand
            write_char_string_builder(&current, c);

            // Push the token
            push_token(
                result,
                current,
                is_string,
                is_num,
                is_dec,
                is_id,
                is_escape,
                line,
                col,
                token_idx
            );

            // Continue to the next character
            continue;
        }

        // Handle identifiers
        if (!is_string && !isalnum(c) && c != '_')
        {
            is_id = false;
            is_num = false;
            is_dec = false;
        }

        if (is_num && c == '.')
        {
            is_dec = true;
        }
        else if (c == '"')
        {
            // Handle strings
            if (is_string)
            {
                // Push the current token
                push_token(
                    result,
                    current,
                    is_string,
                    is_num,
                    is_dec,
                    is_id,
                    is_escape,
                    line,
                    col,
                    token_idx
                );
                is_string = false;
                continue;
            }

            // Check if we are escaping
            if (is_escape)
            {
                is_escape = false;
                write_char_string_builder(&current, '"');
            }

            is_num = false;
            is_dec = false;
            is_string = true;
            continue;
        } else if (c == '\\')
        {
            if (!is_string)
            {
                // Report the error
                fluent_std::Runtime::println("Lexing error: Invalid IR structure");
                exit(1);
            }

            is_num = false;
            is_dec = false;
            is_escape = !is_escape;
            continue;
        } else if (!is_string && isalpha(c))
        {
            is_num = false;
            is_dec = false;
        }

        // Write the current character
        write_char_string_builder(&current, c);
        col++;
        token_idx++;
    }

    // Push any residue
    push_token(
        result,
        current,
        is_string,
        is_num,
        is_dec,
        is_id,
        is_escape,
        line,
        col,
        token_idx
    );

    // Make sure we don't end up in a string
    if (is_string)
    {
        // Report the error
        fluent_std::Runtime::println("Lexing error: Invalid IR structure");
        exit(1);
    }

    return token::TokenStream(result);
}
