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

#ifndef CALL_RUNNER_H
#define CALL_RUNNER_H
#include "../../../file_code/file_code.h"
#include "../../../structure/linked_queue/linked_queue.h"
#include "../../runtime/execution/execution_pair.h"

bool run_call(
    const file_code::FileCode &root,
    const std::shared_ptr<parser::AST> &call,
    const std::shared_ptr<runtime::ExecutionPair> &pair,
    LinkedQueue<std::shared_ptr<runtime::ExecutionPair>> &queue,
    ankerl::unordered_dense::map<ImmutStr *, std::shared_ptr<Object>, ImmutStrHash, ImmutStrEqual> &refs,
    size_t idx,
    bool is_last
);

#endif //CALL_RUNNER_H
