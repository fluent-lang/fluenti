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

#ifndef HELP_GENERATOR_H
#define HELP_GENERATOR_H

#ifndef HASH_MAP_H
#include "../../structure/hash_map/hash_map.h"
#endif\

void generate_help(const char* name, const char* desc, const HashMap *flags);

#endif