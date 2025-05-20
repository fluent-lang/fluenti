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
// Created by rodrigo on 5/19/25.
//

#include <functional>

#include "../../runtime/print/print.h"
#include "../../runtime/panic/panic.h"
#include "../object/object.h"
#include "../runtime/execution/execution_pair.h"

// A map that maps all stdlib functions
// to their C++ implementations
ankerl::unordered_dense::segmented_map<
    ImmutStr,
    std::function<void(const std::vector<Object> &)>,
    ImmutStrHash,
    ImmutStrEqual
> stdlib_map = {
    { ImmutStr("println", 7, false), runtime::println },
    { ImmutStr("print", 5, false), runtime::print },
    { ImmutStr("panic", 5, false), runtime::panic },
};

namespace fluent_std
{
    std::function<void(const std::vector<Object> &)> find_stdlib_function(const ImmutStr *const &name)
    {
        // Check if the function exists
        if (const auto it = stdlib_map.find(*name); it != stdlib_map.end())
        {
            // Return the function
            return it->second;
        }

        // Panic
        throw std::runtime_error("Function not found");
    }
}
