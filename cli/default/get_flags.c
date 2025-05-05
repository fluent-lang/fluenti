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

#include "../../structure/hash_map/hash_map.h"
#include "../../shared/on_hash_map_destroy.h"
#include "../flag/flag.h"
#include "get_flags.h"

void handle_flag_destroy(FluentObject *object)
{
    // Get the map
    const HashMap *map = object->element;

    // Get the path guard
    HeapGuard *path_guard = get_from_map(map, "path");

    // Drop the path guard
    drop_guard(path_guard);

    // Get the help guard
    HeapGuard *help_guard = get_from_map(map, "help");

    // Drop the help guard
    drop_guard(help_guard);

    // Destroy the map directly
    on_hash_map_destroy(object);
}

HeapGuard *get_default_flags()
{
    // Create a new HashMap
    HashMap *flags = create_hash_map();

    // Create an out path flag
    HeapGuard *path_guard = alloc(sizeof(Flag));
    Flag *path_flag = path_guard->value->element;
    path_flag->original_name = "";
    path_flag->desc = "Path to the program to be executed";
    path_flag->shortcut = "p";
    path_flag->type = STRING;
    path_flag->required = TRUE;

    // Create a help flag
    HeapGuard *help_guard = alloc(sizeof(Flag));
    Flag *help_flag = help_guard->value->element;
    help_flag->original_name = "";
    help_flag->desc = "Displays this menu";
    help_flag->shortcut = "h";
    help_flag->type = STATIC;
    help_flag->required = FALSE;

    // Set the default flags
    insert_to_map(flags, "path", path_guard);
    insert_to_map(flags, "help", help_guard);

    // Create a new HeapGuard with the HashMap
    HeapGuard *guard = create_with_prealloc((void **) &flags);

    // Set the on_destroy hook
    guard->on_destroy = handle_flag_destroy;

    return guard;
}
