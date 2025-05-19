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

#include "std.h"
#include "../std_c/print/print.h"
#include <thread>

namespace fluent_std
{
    // Define all mutexes
    std::mutex print_mutex;

    void Runtime::print(const char *str)
    {
        // Lock the mutex
        std::lock_guard guard(print_mutex);

        // Call the C impl
        r_print(str);
    }

    void Runtime::print_char(const char str)
    {
        // Lock the mutex
        std::lock_guard guard(print_mutex);

        // Call the C impl
        f_print(str);
    }

    void Runtime::println(const char *str)
    {
        // Lock the mutex
        std::lock_guard guard(print_mutex);

        // Call the C impl
        r_println(str);
    }
}// runtime