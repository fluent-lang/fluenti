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
#include "../std/std.h"
#include "engine/engine.h"
#include "fluent/file_code/converter.h"
#include "fluent/file_code/file_code.h"
#include "fluent/lexer/lexer.h"

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

    // Parse the code
    auto tokens = fluent::lexer::tokenize(contents);
    const auto ast = fluent::parser::parse_code(&tokens);
    auto code = fluent::file_code::convert_code(ast);
    do_run(code);
}
