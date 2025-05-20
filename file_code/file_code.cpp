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

#include "file_code.h"

#include "rule/function/function.h"
#include "rule/mod/mod.h"
#include "rule/ref/ref.h"

file_code::FileCode file_code::convert_code(const std::shared_ptr<fluent::parser::AST>& root)
{
    // Define a result
    FileCode result;

    for (
        // Unwrap the children
        const auto children = fluent::util::try_unwrap(root->children);
        // Iterate over all children
        const auto& child : children
    )
    {
        switch (child->rule)
        {
            case fluent::parser::Ref:
            {
                process_ref(result, child);
                break;
            }

            case fluent::parser::Function:
            {
                process_function(result, child);
                break;
            }

            case fluent::parser::Mod:
            {
                process_mod(result, child);
                break;
            }

            case fluent::parser::Link:
            {
                // Skip links directly, as they're not
                // relevant for interpretation
                break;
            }

            default:
                throw std::runtime_error(
                    "Unknown rule in file code conversion: " + std::to_string(child->rule)
                );
        }
    }

    return result;
}
