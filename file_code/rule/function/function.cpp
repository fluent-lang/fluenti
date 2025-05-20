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

#include "function.h"

#include <fluent/util/unwrap.h>
#include "../type/type.h"

void process_function(file_code::FileCode &result, const std::shared_ptr<parser::AST> &ast)
{
    // Create a new function
    const auto function = std::make_shared<file_code::Function>();

    // Unwrap the children
    const auto children = util::try_unwrap(ast->children);

    // Get the function's name
    const auto name = util::try_unwrap(children[0]->value);

    // Set the function's return type
    function->return_type = process_type(children[1]);

    // Get the parameters node
    const auto &params_node = children[2];

    // Add all parameters
    for (
        const auto &params_children = util::try_unwrap(params_node->children);
        const auto &param : params_children
    )
    {
        // Get the param's children
        const auto param_children = util::try_unwrap(param->children);

        // Get the param's name
        const auto param_name = util::try_unwrap(param_children[0]->value);

        // Get the param's type
        const auto param_type = process_type(param_children[1]);

        // Add the param
        function->params[param_name] = param_type;
    }

    // Set the function's block
    function->body = children[3];

    // Parse additional nodes
    for (size_t i = 4; i < children.size(); i++)
    {
        // Get the block
        const auto &block = children[i];

        // Get the block's children
        const auto block_children = util::try_unwrap(block->children);

        // Get the block's name
        const auto block_name = util::try_unwrap(block_children[0]->value);

        // Add the block to the function's blocks
        function->blocks[block_name] = block;
    }

    // Set the function into the result
    result.functions[name] = function;
}
