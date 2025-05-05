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

#include "cli/argv_impl.h"
#include "cli/default/get_flags.h"
#include "runtime/init_runtime.h"

int main(const int argc, const char **argv) {
    // Initialize the runtime
    init_runtime();

    // Warn about unstable behavior for Windows
#ifdef _WIN32
    warn("fluent_libc has not been fully tested on Windows. Proceed with caution.");
#endif

    // Get the default CLI flags
    HeapGuard *flags = get_default_flags();

    // Parse the CLI arguments
    const HeapGuard *cli_guard = parse_argv(argc, argv, flags->value->element);
    const Argv *cli_argv = cli_guard->value->element;

    // Drop the flag guard to free it since we don't need it anymore
    drop_guard(flags);

    return 0;
}
