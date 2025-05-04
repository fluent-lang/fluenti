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

#include <fluent_libc/str_copy/library.h>

#include "heap/heap_alloc.h"
#include "logger/logger.h"
#include "runtime/init_runtime.h"
#include "runtime/print/print.h"
#include "runtime/read_line/read_line.h"

int main(const int argc, const char **argv) {
    // Initialize the runtime
    init_runtime();

    // Warn about unstable behavior for Windows
#ifdef _WIN32
    warn("fluent_libc has not been fully tested on Windows. Proceed with caution.");
#endif

    return 0;
}
