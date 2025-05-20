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
// Created by rodrigo on 5/19/25.
//

#ifndef RUNTIME_EXECUTION_PAIR_H
#define RUNTIME_EXECUTION_PAIR_H
#include <ankerl/unordered_dense.h>

#include <fluent/parser/parser.h>
#include "../../../structure/immut_str/immut_str.h"
#include "../../object/object.h"

namespace runtime
{
    typedef struct
    {
        std::shared_ptr<ankerl::unordered_dense::map<ImmutStr *, std::shared_ptr<Object>, ImmutStrHash, ImmutStrEqual>> variables
            = std::make_shared<ankerl::unordered_dense::map<ImmutStr *, std::shared_ptr<Object>, ImmutStrHash, ImmutStrEqual>>();
        std::shared_ptr<parser::AST> ast;
        size_t start_at = 0;
    } ExecutionPair;
}

#endif //RUNTIME_EXECUTION_PAIR_H
