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

#ifndef FILE_CODE_TYPE_WRAPPER_H
#define FILE_CODE_TYPE_WRAPPER_H

#include <cstddef>

namespace file_code
{
    typedef enum
    {
        Nothing,
        Num,
        Dec,
        String,
    } PrimitiveType;

    typedef struct
    {
        size_t pointers = 0;
        size_t arrays = 0;
        std::optional<ImmutStr *> base_type = std::nullopt;
        std::optional<PrimitiveType> primitive = std::make_optional(Nothing);
    } Type;
}

#endif //FILE_CODE_TYPE_WRAPPER_H
