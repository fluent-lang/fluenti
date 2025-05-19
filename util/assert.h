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

#ifndef ASSERT_H
#define ASSERT_H

template <typename T>
void assert(T a, T b)
{
    if (a != b)
    {
        // Print the error
        throw std::runtime_error("Assertion failed, a != b. Most likely cause: Invalid IR structure");
    }
}

#endif //ASSERT_H
