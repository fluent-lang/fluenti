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
// Created by rodrigo on 5/16/25.
//

#include "core.h"
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <chrono>

#include "../file_code/file_code.h"
#include "../std/std.h"
#include "engine/engine.h"
#include "fluent/lexer/lexer.h"
#include "object/object.h"

void convert_refs(
    ankerl::unordered_dense::map<ImmutStr *, std::shared_ptr<Object>, ImmutStrHash, ImmutStrEqual> &refs,
    const file_code::FileCode &code
)
{
    // Iterate over all references
    for (const auto &[name, ref] : code.refs)
    {
        // Create a new object
        const auto obj = std::make_shared<Object>();
        obj->type = ref->type;

        // Insert the object into the refs map
        refs[name] = obj;
    }
}

void interpret(const char *path)
{
    // Read the file at the specified path
    std::ifstream file(path);
    if (!file.is_open())
    {
        // Print an error message
        fluent_std::Runtime::println("Error: Could not open file");
        exit(1);
    }

    // Read the file contents
    std::stringstream buffer;
    buffer << file.rdbuf();  // Read the whole file
    std::string contents = buffer.str();  // Convert to string

    // Tokenize the contents
    token::TokenStream tokens = lexer::tokenize(contents);

    // Parse the code
    std::shared_ptr<parser::AST> ast = parser::parse_code(&tokens);
    file_code::FileCode code = file_code::convert_code(ast);

    do_run(code);
}
