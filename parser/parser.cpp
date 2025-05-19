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

#include "parser.h"

#include "../util/assert.h"
#include "rule/binary/binary.h"
#include "rule/block/block.h"
#include "rule/expr/expr.h"
#include "rule/function/function.h"
#include "rule/if/if.h"
#include "rule/link/link.h"
#include "rule/module/module.h"
#include "rule/pick/pick.h"
#include "rule/reference/reference.h"
#include "rule/ret/ret.h"
#include "rule/var/var.h"

namespace parser
{
    std::shared_ptr<AST> parse_code(token::TokenStream *stream)
    {
        // Create a new AST node
        auto ast = std::make_shared<AST>();
        ast->rule = Program;
        ast->children = std::make_optional(std::vector<std::shared_ptr<AST>>());

        // Define a vector of blocks to build the blocks
        std::vector<std::shared_ptr<AST>> blocks;
        std::optional<std::shared_ptr<AST>> pivot = std::nullopt;
        std::optional<std::shared_ptr<AST>> pivot_fn = std::nullopt;

        // Iterate over the tokens
        std::optional<token::Token> current_opt = stream->nth(0);
        while (current_opt.has_value())
        {
            // Get the current token
            switch (
                const auto current = current_opt.value();
                current.type
            )
            {
                case token::Block:
                {
                    assert(pivot_fn.has_value(), true);
                    parse_block(blocks, stream, pivot_fn.value());
                    pivot = blocks[blocks.size() - 1];
                    break;
                }

                case token::Function:
                {
                    pivot_fn = parse_function(blocks, stream, ast);
                    pivot = blocks[blocks.size() - 1];
                    break;
                }

                case token::Module:
                {
                    parse_mod(blocks, stream, ast);
                    break;
                }

                case token::End:
                {
                    // Delete the last block
                    if (!blocks.empty()) {
                        blocks.pop_back();

                        if (!blocks.empty())
                        {
                            pivot = blocks[blocks.size() - 1];
                        } else
                        {
                            pivot = std::nullopt;
                        }
                    } else
                    {
                        pivot = std::nullopt;
                    }

                    break;
                }

                case token::Link:
                {
                    parse_link(blocks, stream);
                    break;
                }

                case token::Reference:
                {
                    // Parse the reference
                    parse_reference(blocks, stream, ast);
                    break;
                }

                case token::RetVoid:
                case token::Ret:
                {
                    assert(pivot.has_value(), true);
                    parse_ret(blocks, stream, pivot.value());
                    break;
                }

                case token::Alloca:
                {
                    assert(pivot.has_value(), true);
                    parse_var(stream, pivot.value(), Alloca, true, false);
                    break;
                }

                case token::Mov:
                {
                    assert(pivot.has_value(), true);
                    parse_var(stream, pivot.value(), Mov, true, true);
                    break;
                }

                case token::Store:
                {
                    assert(pivot.has_value(), true);
                    parse_var(stream, pivot.value(), Store, false, true);
                    break;
                }

                case token::Jump:
                {
                    assert(pivot.has_value(), true);
                    parse_singly_opt(stream, pivot.value(), Jump);
                    break;
                }

                case token::If:
                {
                    assert(pivot.has_value(), true);
                    parse_if(stream, pivot.value());
                    break;
                }

                case token::Pick:
                {
                    assert(pivot.has_value(), true);
                    parse_pick(stream, pivot.value());
                    break;
                }

                default:
                {
                    assert(pivot.has_value(), true);
                    parse_expr(stream, pivot.value(), "default");
                }
            }

            // Move to the next token
            current_opt = stream->next();
        }

        return ast;
    }
}