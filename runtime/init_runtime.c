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

#include "init_runtime.h"
#include <stdlib.h>
#include "../heap/heap_alloc.h"
#include "print/print.h"

void handle_exit()
{
    // Cleanup the heap
    cleanup_heap();

    // Flush the print buffer
    flush_print_buffer();

    // Un-initialize the print runtime
    un_init_print_runtime();
}

void init_runtime()
{
    // Add at exit hooks
    atexit(handle_exit);

    // Initialize the print runtime
    init_print_runtime();
}
