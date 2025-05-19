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

#include <ankerl/unordered_dense.h>
#include <memory>
#include "expr.h"
#include "../../../util/unwrap.h"
#include "../call/call.h"

void run_expr(
    const file_code::FileCode &root,
    const std::shared_ptr<parser::AST> &expr,
    const runtime::ExecutionPair &pair,
    std::vector<runtime::ExecutionPair> &queue,
    ankerl::unordered_dense::map<ImmutStr *, std::shared_ptr<Object>, ImmutStrHash, ImmutStrEqual> &refs
)
{
    // Get the expression's children
    const auto children = try_unwrap(expr->children);

    // Get the first child

    // Determine what we have torun
    switch (
        const auto& first_child = children[0];
        first_child->rule
    )
    {
        case parser::Call:
        {
            run_call(
                root,
                first_child,
                pair,
                queue,
                refs
            );

            break;
        }

        default:
            throw std::runtime_error("Invalid expression type");
    }
}
