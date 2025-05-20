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

#include "call.h"

#include "../../../util/unwrap.h"
#include "../../lazy/ref.h"
#include "../../std/stdlib_map.h"

inline std::shared_ptr<Object> get_param(
    ImmutStr * &name,
    const runtime::ExecutionPair &pair,
    const file_code::FileCode &root,
    ankerl::unordered_dense::map<ImmutStr *, std::shared_ptr<Object>, ImmutStrHash, ImmutStrEqual> &refs
)
{
    // Check if the local variables contain the name
    if (pair.variables->contains(name))
    {
        // Return the object
        return pair.variables->at(name);
    }

    // Retrieve the ref
    return load_ref(root, name, refs);
}

void run_call(
    const file_code::FileCode &root,
    const std::shared_ptr<parser::AST> &call,
    const runtime::ExecutionPair &pair,
    LinkedQueue<runtime::ExecutionPair> &queue,
    ankerl::unordered_dense::map<ImmutStr *, std::shared_ptr<Object>, ImmutStrHash, ImmutStrEqual> &refs
)
{
    // Create a new execution pair
    runtime::ExecutionPair new_pair;

    // Get the call's children
    const auto children = try_unwrap(call->children);

    // Check if we have a std function
    if (
        const auto name = try_unwrap(children[0]->value);
        root.functions.contains(name)
    )
    {
        // Get the function from the root
        const auto function = root.functions.at(name);
        new_pair.ast = function->body;

        // Get the signature's params and iterate over them
        size_t i = 1;
        for (const auto &[name, _] : function->params)
        {
            // Get the call param at index i
            const auto &call_param = children[i];

            // Get the param's name
            ImmutStr *param_name = try_unwrap(call_param->value);

            // Add the object to the pair's stack
            (*new_pair.variables)[name] = get_param(
                param_name,
                pair,
                root,
                refs
            );

            i++;
        }
    } else
    {
        // Get the function from the stdlib map
        const auto it = fluent_std::find_stdlib_function(name);

        // Define a vector for all the parameters
        std::vector<Object> params;

        // Collect all parameters
        for (size_t i = 1; i < children.size(); i++)
        {
            // Get the param's name
            ImmutStr *param_name = try_unwrap(children[i]->value);

            // Get the param from the pair
            const auto param = get_param(
                param_name,
                pair,
                root,
                refs
            );

            // Add the param to the vector
            params.push_back(*param);
        }

        // Directly call the stdlib impl
        it(params);

        return;
    }

    // Add the pair to the queue
    queue.append_top(new_pair);
}
