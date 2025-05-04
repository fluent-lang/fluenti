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

#ifndef FLUENT_OBJECT_H
#define FLUENT_OBJECT_H

#ifndef FLUENT_STRUCT
#include "fluent_struct.h"
#endif

#ifndef OBJECT_TYPE_H
#include "object_type.h"
#endif

typedef struct
{
    void *element;
    ObjectType type;
    FluentStruct *struct_ptr;
} FluentObject;

#endif //FLUENT_OBJECT_H
