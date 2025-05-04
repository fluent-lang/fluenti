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
#include "../../structure/mutex/mutex.h"
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/syscall.h>
#endif

#include "print.h"

#ifndef FLUENT_RUNTIME_PRINT_BUF_SIZE
#define FLUENT_RUNTIME_PRINT_BUF_SIZE 1024
#endif

// Create a buffered print buffer
char print_buffer[FLUENT_RUNTIME_PRINT_BUF_SIZE];
size_t print_buffer_index = 0;

// Create a mutex for concurrent access
Mutex mutex;

/**
 * Initializes the print runtime by setting up the mutex.
 * This function must be called before using any print-related functionality.
 * Exits the program with status 1 if the mutex initialization fails.
 */
void init_print_runtime()
{
    // Initialize the mutex
    if (!init_mutex(&mutex))
    {
        exit(1);
    }
}

/**
 * Cleans up the print runtime by destroying the mutex.
 * This function should be called to release resources when print-related functionality is no longer needed.
 * Exits the program with status 1 if the mutex destruction fails.
 */
void un_init_print_runtime()
{
    // Destroy the mutex
    if (!destroy_mutex(&mutex))
    {
        exit(1);
    }
}

/**
 * Flushes the print buffer to the standard output.
 *
 * On Windows:
 * - Uses the `WriteConsole` function to write the buffer contents to the console.
 *
 * On non-Windows systems:
 * - Uses the `syscall` function with `SYS_write` to write the buffer contents to `STDOUT_FILENO`.
 *
 * After flushing, the buffer index is reset to 0.
 */
void flush_print_buffer()
{
#ifdef _WIN32
    // On Windows, use WriteConsole for console output
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    WriteConsole(hConsole, print_buffer, (DWORD)print_buffer_index, &written, NULL);
#else
    // Make a syscall immediately
    syscall(SYS_write, STDOUT_FILENO, print_buffer, print_buffer_index);

    // Reset the index
    print_buffer_index = 0;
#endif
}

void print(const char *str)
{
    // Lock the mutex
    lock_mutex(&mutex);

    // Write the string to the buffer
    while (*str)
    {
        const char c = *str++;

        // Check if the buffer is full
        if (print_buffer_index == FLUENT_RUNTIME_PRINT_BUF_SIZE)
        {
            flush_print_buffer();
        }

        // Write the character to the buffer
        print_buffer[print_buffer_index] = c;
        print_buffer_index++;
    }

    // Unlock the mutex
    unlock_mutex(&mutex);
}

/**
 * Prints the given string followed by a newline character.
 *
 * This function is thread-safe and ensures that the string and the newline
 * are printed atomically by locking the mutex during the operation.
 *
 * @param str The string to be printed.
 */
void println(const char *str)
{
    // Use the print impl
    print(str);
    print("\n");
}