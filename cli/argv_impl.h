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

#ifndef ARGV_IMPL_H
#define ARGV_IMPL_H

#ifndef HASH_MAP_H
#include "../structure/hash_map/hash_map.h"
#endif

#ifndef HEAP_ALLOC_H
#include "../heap/heap_alloc.h"
#endif

#ifndef INT_H
#include "../types/int.h"
#endif

typedef struct
{
    HashMap *static_flags;
    HashMap *string_flags;
    bool success;
} Argv;

HeapGuard *parse_argv(int argc, const char **argv, HashMap *flags);

#endif //ARGV_IMPL_H
