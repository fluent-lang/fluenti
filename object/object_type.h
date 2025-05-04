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
// Created by rodrigo on 5/4/25.
//

#ifndef OBJECT_TYPE_H
#define OBJECT_TYPE_H

#ifndef PRIMITIVE_TYPE_H
#include "primitive_type.h"
#endif

#ifndef BOOL_H
#include "../types/bool.h"
#endif

typedef struct
{
    bool is_primitive;
    size_t pointer_count;
    size_t array_count;
    FluentPrimitiveType primitive;
} ObjectType;

#endif //OBJECT_TYPE_H
