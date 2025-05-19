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

#ifndef STDLIB_MAP_H
#define STDLIB_MAP_H
#include <ankerl/unordered_dense.h>

#include "../../runtime/print/print.h"
#include "../../structure/immut_str/immut_str.h"
#include "../object/object.h"

namespace fluent_std
{
    std::function<void(const std::vector<Object> &)> find_stdlib_function(const ImmutStr *const &name);
}

#endif //STDLIB_MAP_H
