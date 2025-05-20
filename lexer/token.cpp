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

#include "token.h"

using namespace std;
using namespace token;

size_t TokenStream::max() const
{
    return _max;
}

std::optional<Token> TokenStream::nth(const size_t index)
{
    // Check if the index is valid
    if (index >= _max)
    {
        return nullopt;
    }

    // Return the token at the specified index
    return tokens[index];
}

std::optional<Token> TokenStream::curr()
{
    return nth(current);
}

std::optional<Token> TokenStream::next()
{
    // Check if we are at the last element
    if (current == _max)
    {
        return nullopt;
    }

    // Increment the current index
    current++;
    return curr();
}

std::optional<Token> TokenStream::peek()
{
    // Check if we are at the last element
    if (current == _max)
    {
        return nullopt;
    }

    return nth(current + 1);
}

std::optional<Token> TokenStream::backtrack()
{
    // Make sure we aren't at index 0
    if (current == 0)
    {
        return nullopt;
    }

    // Decrement the current index
    current--;
    return curr();
}
