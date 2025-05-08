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

#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#ifndef INT_H
#include "../../types/int.h"
#endif

typedef struct {
    char *buffer;
    size_t len;
    size_t capacity;
    size_t used_capacity;
} StringBuilder;

StringBuilder create_string_builder(size_t capacity);
void writec_to_string_builder(StringBuilder *builder, char str);
void write_to_string_builder(StringBuilder *builder, const char* str);
void destroy_string_builder(StringBuilder *builder);
char *collect_string_builder(const StringBuilder *builder);
void ensure_capacity_in_string_builder(StringBuilder *builder, size_t capacity);

#endif //STRING_BUILDER_H