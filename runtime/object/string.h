//
// Created by rodrigo on 5/4/25.
//

#ifndef FLUENT_STRING_H
#define FLUENT_STRING_H

#ifndef INT_H
#include "../../types/int.h"
#endif

#ifndef HEAP_ALLOC_H
#include "../../heap/heap_alloc.h"
#endif

typedef struct
{
    HeapGuard *value;
    size_t length;
    size_t used_capacity;
} String;

String create_string();
void grow_string(String *str);
void write_string(String *str, const char *value);
HeapGuard *get_string(const String *str);

#endif //FLUENT_STRING_H
