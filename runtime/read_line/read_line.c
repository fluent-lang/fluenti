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

#include "../../types/int.h"
#ifndef _WIN32
#include <fluent_libc/stdi/library.h>
#else
#include "win_read_line.h"
#endif
#include "read_line.h"

#include "../print/print.h"

#ifndef EOF
#define EOF (-1)
#endif

#ifndef FLUENT_RUNTIME_READ_LINE_BUF_SIZE
#define FLUENT_RUNTIME_READ_LINE_BUF_SIZE 250
#endif

String runtime_read_line()
{
    // Flush the print buffer
    flush_print_buffer();

    String str = create_string();

#ifdef _WIN32
    // Use the windows-compatible fluent_libc read_line impl
    const char *line = win_read_line();
#else
    // Use fluent_libc read_lime impl
    const char *line = read_line();
#endif

    // Write the string
    write_string(&str, line);

    return str;
}