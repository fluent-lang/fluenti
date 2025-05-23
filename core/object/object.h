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

#ifndef FLUENT_OBJECT_H
#define FLUENT_OBJECT_H

#include <memory>

#include "fluent/file_code/file_code.h"

typedef struct
{
    fluent::file_code::Type type;
    void * value = nullptr;
    std::optional<fluent::file_code::Mod> mod;
} Object;

Object convert_to_object(const std::shared_ptr<fluent::parser::AST> &ast);

#endif //FLUENT_OBJECT_H
