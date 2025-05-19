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

#ifdef _WIN32
#include <stdio.h> // Use libc's printf implementation directly
#else
#include <unistd.h>
#include <sys/syscall.h>
#endif

#include "print.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#ifndef _WIN32
// Macros directives
#   ifndef PRINT_BUF_SIZE
#       define PRINT_BUF_SIZE 1024
#   endif

    // Define a buffer
    char buffer[PRINT_BUF_SIZE];
    size_t buffer_len = 0;
#endif

void flush_print()
{
    // Handle printing for POSIX systems
#   ifndef _WIN32
        // Make a syscall directly
        syscall(SYS_write, STDOUT_FILENO, buffer, buffer_len);
        // Reset the buffer length
        buffer_len = 0;
#   endif
}

inline void f_print(const char str)
{
    // Use printf directly on Windows
#   ifdef _WIN32
    printf("%c", str);
    return;
#   endif

    // Check if we have to flush the buffer
    if (buffer_len == PRINT_BUF_SIZE)
    {
        flush_print();
    }

    // Write the character to the buffer
    buffer[buffer_len] = str;
    buffer_len++;
}

inline void r_print(const char *str)
{
    // Use printf for Windows directly
#   ifdef _WIN32
        printf("%s", str); // Let the system's libc handle buffering, we aren't
        return;
#   endif

    // Write the string to the buffer
    while (*str != '\0')
    {
        // Call f_print
        f_print(*str);

        // Move to the next character
        str++;
    }
}

inline void r_println(const char *str)
{
    // Print the string with a newline
    r_print(str);
    r_print("\n");
}

#if defined(__cplusplus)
}
#endif