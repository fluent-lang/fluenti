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

#include "ref.h"

std::shared_ptr<Object>load_ref(
    const file_code::FileCode &root,
    ImmutStr *const &name,
    ankerl::unordered_dense::map<ImmutStr *, std::shared_ptr<Object>, ImmutStrHash, ImmutStrEqual> &refs
)
{
    // Check if the ref exists
    if (!root.refs.contains(name))
    {
        throw std::runtime_error("Reference not found");
    }

    // Check if the ref is loaded
    if (refs.contains(name))
    {
        return refs[name];
    }

    // Get the ref from the root
    const auto ref = root.refs.at(name);

    // Convert the ref's AST to an object
    const auto obj = convert_to_object(ref->value);

    // Insert the object into the refs map
    refs[name] = std::make_shared<Object>(obj);

    // Return the object
    return refs[name];
}