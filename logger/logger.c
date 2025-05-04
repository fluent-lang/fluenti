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
// Created by rodrigo on 5/4/25.
//

#include "logger.h"
#include "../ansi/ansi.h"
#include "../runtime/print/print.h"

#ifndef LOG_PREFIX
#define LOG_PREFIX "[LOG] "
#endif

#ifndef LOG_PREFIX_COLOR
#define LOG_PREFIX_COLOR ANSI_BoldBrightBlue
#endif

#ifndef WARN_PREFIX
#define WARN_PREFIX "[WARN] "
#endif

#ifndef WARN_PREFIX_COLOR
#define WARN_PREFIX_COLOR ANSI_BoldBrightYellow
#endif

#ifndef ERR_PREFIX
#define ERR_PREFIX "[ERR] "
#endif

#ifndef ERR_PREFIX_COLOR
#define ERR_PREFIX_COLOR ANSI_BoldBrightRed
#endif

void log(const char* message)
{
    print(LOG_PREFIX_COLOR);
    print(LOG_PREFIX);
    print(ANSI_Reset);
    print(ANSI_BrightBlack);
    print(message);
    println(ANSI_Reset);
}

void warn(const char* message)
{
    print(WARN_PREFIX_COLOR);
    print(WARN_PREFIX);
    print(message);
    println(ANSI_Reset);
}

void error(const char* message)
{
    print(ERR_PREFIX_COLOR);
    print(ERR_PREFIX);
    print(message);
    println(ANSI_Reset);
}