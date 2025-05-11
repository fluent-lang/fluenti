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

#ifndef SPACE_FORMATTER_H
#define SPACE_FORMATTER_H

#ifndef INT_H
#include "../../types/int.h"
#endif

char *format_spaces(const char* initial_str, size_t spaces);
void f_format_spaces(char *buffer, size_t len, const char* initial_str, size_t spaces);

#endif //SPACE_FORMATTER_H