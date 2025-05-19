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
// Created by rodrigo on 5/18/25.
//

#ifndef FILE_CODE_H
#define FILE_CODE_H
#include <memory>
#include <ankerl/unordered_dense.h>

#include "../structure/immut_str/immut_str.h"
#include "structure/function/function.h"
#include "structure/mod/mod.h"
#include "structure/ref/ref.h"

namespace file_code
{
    typedef struct
    {
        ankerl::unordered_dense::map<ImmutStr *, std::shared_ptr<Reference>, ImmutStrHash, ImmutStrEqual> refs;
        ankerl::unordered_dense::map<ImmutStr *, std::shared_ptr<Function>, ImmutStrHash, ImmutStrEqual> functions;
        ankerl::unordered_dense::map<ImmutStr *, std::shared_ptr<Mod>, ImmutStrHash, ImmutStrEqual> mods;
    } FileCode;

    FileCode convert_code(const std::shared_ptr<parser::AST>& root);
}

#endif //FILE_CODE_H
