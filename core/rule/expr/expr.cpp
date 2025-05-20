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

bool run_expr(
    const file_code::FileCode &root,
    const std::shared_ptr<parser::AST> &expr,
    const std::shared_ptr<runtime::ExecutionPair> &pair,
    LinkedQueue<std::shared_ptr<runtime::ExecutionPair>> &queue,
    ankerl::unordered_dense::map<ImmutStr *, std::shared_ptr<Object>, ImmutStrHash, ImmutStrEqual> &refs,
    const size_t idx,
    const bool is_last
)
{
    // Get the expression's children
    const auto children = try_unwrap(expr->children);

    // Determine what we have torun
    switch (
        const auto& first_child = children[0];
        first_child->rule
    )
    {
        case parser::Call:
        {
            return run_call(
                root,
                first_child,
                pair,
                queue,
                refs,
                idx,
                is_last
            );
        }

        case parser::Ret:
        {
            break;
        }

        default:
            throw std::runtime_error("Invalid expression type");
    }

    return false;
}
