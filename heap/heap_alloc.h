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

#ifndef HEAP_ALLOC_H
#define HEAP_ALLOC_H

#ifndef FLUENT_OBJECT_H
#include "../object/fluent_object.h"
#endif

#ifndef FunctionPointer
typedef void (*FunctionPointer)(FluentObject *);
#endif

#ifndef MUTEX_H
#include "../structure/mutex/mutex.h"
#endif

typedef struct
{
    FluentObject *value;
    size_t size;
    size_t ref_count;
    Mutex *mutex;
    FunctionPointer on_destroy;
} HeapGuard;

HeapGuard *alloc(size_t size);
void expand_guard(HeapGuard *guard, size_t size);
void raise_guard(HeapGuard *guard);
void drop_guard(HeapGuard *guard);
void cleanup_heap();

#endif //HEAP_ALLOC_H
