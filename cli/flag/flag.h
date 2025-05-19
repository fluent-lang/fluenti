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

#ifndef FLAG_H
#define FLAG_H

#ifndef FLAG_TYPE_H
#include "flag_type.h"
#endif

#include <string>

typedef struct
{
    FlagType type;
    std::string original_name;
    std::string desc;
    std::string shortcut;
    bool required;
} Flag;

#endif //FLAG_H
