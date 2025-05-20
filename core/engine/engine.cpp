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

#include "engine.h"

#include "../../structure/linked_queue/linked_queue.h"
#include "../object/object.h"
#include "../rule/block/block.h"
#include "../runtime/execution/execution_pair.h"

void do_run(fluent::file_code::FileCode &code)
{
    // Define a map to lazily initialize references
    ankerl::unordered_dense::map<ImmutStr *, std::shared_ptr<Object>, ImmutStrHash, ImmutStrEqual> refs;

    // Retrieve the main function
    fluent::util::assert_eq(code.functions.contains("main"), true);
    const auto main_function = code.functions.at(std::string_view("main", 4));

    // Create a new queue for running code as needed
    // Using a vector here wouldn't allow us to pop elements in constant time
    // using a linked list would be a better choice
    LinkedQueue<std::shared_ptr<runtime::ExecutionPair>> queue;
    const auto main_block = std::make_shared<runtime::ExecutionPair>();
    main_block->ast = main_function->body;
    queue.enqueue(main_block);

    // Execute directly
    while (!queue.empty())
    {
        // Get the first element
        const auto &pair = queue.peek();

        // Delete the first element
        queue.release_top();

        // Run the block
        run_block(code, pair, queue, refs);
    }
}
