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

#include "block.h"

#include "../../../util/unwrap.h"
#include "../expr/expr.h"

void run_block(
    const file_code::FileCode &root,
    const runtime::ExecutionPair &pair,
    std::vector<runtime::ExecutionPair> &queue,
    ankerl::unordered_dense::map<ImmutStr *, std::shared_ptr<Object>, ImmutStrHash, ImmutStrEqual> &refs
)
{
    // Get the block
    const auto block = pair.ast;

    // Iterate over all children
    for (
        const auto children = try_unwrap(block->children);
        const auto &child : children
    )
    {
        switch (child->rule)
        {
            case parser::Expression:
            {
                run_expr(root, child, pair, queue, refs);
                break;
            }

            default:
                break;
        }
    }
}
