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
// Created by rodrigo on 5/15/25.
//

#ifndef RUNTIME_CPP_H
#define RUNTIME_CPP_H

namespace fluent_std
{
    class Runtime {
    public:
        static void print_char(char str);
        static void print(const char *str);
        static void println(const char *str);
    };
} //runtime

#endif //RUNTIME_CPP_H
