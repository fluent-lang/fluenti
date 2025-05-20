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

#include "algorithm/help_generator/help_generator.h"
#include "cli/default/get_flags.h"
#include "core/core.h"
#include "fluent/cli/argv_impl.h"
#include "std/std.h"
#include "std_c/runtime.h"

// Program metadata
#ifndef PROGRAM_NAME
#define PROGRAM_NAME "fluenti"
#endif

#ifndef PROGRAM_DESC
#define PROGRAM_DESC "The Fluent Language Interpreter"
#endif

using namespace std;
using namespace fluent_std;

int main(const int argc, const char** argv)
{
    // Init the runtime
    init_runtime();

    // Get the default flags
    auto flags = get_default_flags();
    // Parse the arguments
    const auto result = parse_argv(argc, argv, flags);

    if (!result->success || result->static_flags.contains("help"))
    {
        generate_help(PROGRAM_NAME, PROGRAM_DESC, flags);

        if (result->static_flags.contains("help"))
        {
            return 0;
        }

        return 2;
    }

    interpret(result->string_flags.at("path"));
    return 0;
}