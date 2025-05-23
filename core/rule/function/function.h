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
// Created by rodrigo on 5/18/25.
//

#ifndef FUNCTION_RUNNER_H
#define FUNCTION_RUNNER_H

#include "../../object/object.h"
#include "fluent/file_code/file_code.h"

Object run_function(
    const fluent::file_code::Function &function,
    const fluent::file_code::FileCode &root
);

#endif //FUNCTION_RUNNER_H
