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

#ifndef UNWRAP_H
#define UNWRAP_H

#include <optional>

template <typename T>
T try_unwrap(std::optional<T> opt)
{
    // Check if the optional is empty
    if (opt.has_value())
    {
        return opt.value();
    }

    // Report the error
    throw std::runtime_error("Invalid structure");
}

#endif //UNWRAP_H
