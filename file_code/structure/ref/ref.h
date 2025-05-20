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

#ifndef FILE_CODE_STRUCTURE_REF_H
#define FILE_CODE_STRUCTURE_REF_H
#include <memory>

#include <fluent/parser/parser.h>
#include "../../type/type_wrapper.h"

namespace file_code
{
    typedef struct
    {
        std::shared_ptr<fluent::parser::AST> value;
        Type type;
    } Reference;
}

#endif //FILE_CODE_STRUCTURE_REF_H
