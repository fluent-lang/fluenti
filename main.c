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
#include "runtime/init_runtime.h"
#include "runtime/print/print.h"
#include "runtime/read_line/read_line.h"

int main(void) {
    // Initialize the runtime
    init_runtime();

    print("Please enter your name: ");
    const String line = runtime_read_line();
    print("Hello, ");
    println(get_string(&line)->value->element);

    // Create a new guard
    HeapGuard *guard = alloc(sizeof(char) * 14);
    str_copy("Hello, world!", guard->value->element);

    HashMap* my_hash_map = create_hash_map();
    insert_to_map(my_hash_map, "message", guard->value->element);

    println(get_from_map(my_hash_map, "message"));
    destroy_hash_map(my_hash_map);

    // Drop the guard (Not necessary since init_runtime adds an atexit hook
    // (heap_cleanup) that acts as a GC that cleans the heap on exit)
    // ref_count is decremented to 0 at this point, hence it is freed
    drop_guard(guard);

    return 0;
}
