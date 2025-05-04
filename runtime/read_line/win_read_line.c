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

#ifdef _WIN32
#include "win_read_line.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef STDI_READ_LINE_BUFFER_SIZE
#define STDI_READ_LINE_BUFFER_SIZE 250
#endif

#ifndef EOF
#define EOF (-1)
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/**
 * @brief Reads a specified number of bytes from standard input (stdin) into a buffer.
 *
 * This function uses the Windows API to read data from the standard input.
 *
 * @param buffer A pointer to the buffer where the read data will be stored.
 * @param size The maximum number of bytes to read.
 * @return The number of bytes read, or -1 if an error occurs.
 */
ssize_t win_fread_line(char* buffer, const size_t size)
{
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD bytesRead = 0;

    if (hStdIn == INVALID_HANDLE_VALUE) {
        return -1;  // Error getting the standard input handle
    }

    if (ReadFile(hStdIn, buffer, size, &bytesRead, NULL)) {
        return bytesRead;
    } else {
        return -1;  // ReadFile failed
    }
}

/**
 * @brief Reads a line of input from standard input (stdin) using the Windows API.
 *
 * This function dynamically allocates memory to store the input line. It reads characters
 * one by one until a newline or EOF is encountered. If the buffer size is exceeded, it
 * reallocates memory to accommodate additional characters.
 *
 * @return A pointer to the dynamically allocated string containing the input line, or NULL
 *         if an error occurs (e.g., memory allocation failure or read error).
 *
 * @warning The caller is responsible for freeing the memory allocated for the returned string.
 */
char* win_read_line()
{
    // Allocate a buffer (+1 for null terminator)
    char* buffer = malloc(sizeof(char) * (STDI_READ_LINE_BUFFER_SIZE + 1));

    // Check for allocation failure
    if (buffer == NULL) {
        return NULL;
    }

    // Initialize tracking variables
    size_t written = 0;
    size_t length = 0;

    // Read until we find EOF or a newline character
    while (TRUE) {
        // Check if we have to reallocate the buffer
        if (written == STDI_READ_LINE_BUFFER_SIZE) {
            // Reallocate (+1 for null terminator)
            char* new_buffer = realloc(buffer, sizeof(char) * (STDI_READ_LINE_BUFFER_SIZE + length + 1));
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            written = 0;
            buffer = new_buffer;
        }

        // Read from standard input
        if (written == 0) {
            const ssize_t bytes_read = win_fread_line(buffer + length, STDI_READ_LINE_BUFFER_SIZE - length);

            // Handle errors
            if (bytes_read == -1) {
                free(buffer);
                return NULL;
            }

            // If no bytes were read, return the buffer
            if (bytes_read == 0) {
                buffer[length] = '\0';
                return buffer;
            }

            written += bytes_read;
            length += bytes_read;
        }

        // Check if we have an EOF or newline
        if (length > 0 && (buffer[length - 1] == EOF || buffer[length - 1] == '\n')) {
            // Add a null terminator and return the buffer
            buffer[length - 1] = '\0';
            return buffer;
        }
    }
}
#endif