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
// Created by rodrigo on 5/15/25.
//

#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#if defined(__cplusplus)
extern "C"
{
#endif

#include <stddef.h>

typedef struct
{
    char *buf;
    size_t idx;
    size_t capacity;
} StringBuilder;

void init_string_builder(StringBuilder *builder, size_t capacity);
char *collect_string_builder(const StringBuilder *builder);
char *collect_string_builder_no_copy(const StringBuilder *builder);
void write_string_builder(StringBuilder *builder, const char *str);
void write_char_string_builder(StringBuilder *builder, char c);
void destroy_string_builder(StringBuilder *builder);
void reset_string_builder(StringBuilder *builder);

#if defined(__cplusplus)
}
#endif

#endif //STRING_BUILDER_H
