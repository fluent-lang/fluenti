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

#include "../../../structure/linked_queue/linked_queue.h"
#include <fluent/util/unwrap.h>
#include "../expr/expr.h"

void run_block(
    const file_code::FileCode &root,
    const std::shared_ptr<runtime::ExecutionPair> &pair,
    LinkedQueue<std::shared_ptr<runtime::ExecutionPair>> &queue,
    ankerl::unordered_dense::map<ImmutStr *, std::shared_ptr<Object>, ImmutStrHash, ImmutStrEqual> &refs
)
{
    // Get the block
    const auto block = pair->ast;

    // Get the children
    const auto children = util::try_unwrap(block->children);
    const auto max_children = std::max(children.size(), static_cast<size_t>(1)) - 1;

    // Iterate over all children
    for (size_t i = pair->start_at; i <= max_children; i++)
    {
        // Get the child
        switch (const auto &child = children[i]; child->rule)
        {
            case parser::Expression:
            {
                if (
                    run_expr(
                        root,
                        child,
                        pair,
                        queue,
                        refs, i,
                        i == max_children
                    )
                )
                {
                    return;
                }

                break;
            }

            default:
                break;
        }
    }
}
