include(FetchContent)
cmake_minimum_required(VERSION 3.30)
project(fluenti)

set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(
        unordered_dense
        GIT_REPOSITORY https://github.com/martinus/unordered_dense.git
        GIT_TAG        main
)

FetchContent_Declare(
        fluent_libc
        GIT_REPOSITORY https://github.com/rodrigoo-r/fluent_libc
        GIT_TAG        master
)

FetchContent_MakeAvailable(unordered_dense)
FetchContent_MakeAvailable(fluent_libc)

add_executable(fluenti main.cpp
        cli/argv_impl.cpp
        cli/argv_impl.h
        cli/flag/flag.h
        cli/flag/flag_type.h
        cli/default/get_flags.h
        cli/default/get_flags.cpp
        std_c/print/print.c
        std_c/print/print.h
        std_c/runtime.c
        std_c/runtime.h
        std/std.cpp
        std/std.h
        algorithm/padding/padding.cpp
        algorithm/padding/padding.h
        structure/string_builder/string_builder.c
        structure/string_builder/string_builder.h
        algorithm/help_generator/help_generator.cpp
        algorithm/help_generator/help_generator.h
        core/core.cpp
        core/core.h
        lexer/lexer.cpp
        lexer/lexer.h
        lexer/token.h
        heap/heap_guard.h
        lexer/token.cpp
        heap/heap_guard.cpp
        parser/parser.cpp
        parser/parser.h
        parser/rule/link/link.cpp
        parser/rule/link/link.h
        util/assert.h
        util/unwrap.h
        parser/rule/function/function.cpp
        parser/rule/function/function.h
        parser/rule/identifier/identifier.cpp
        parser/rule/identifier/identifier.h
        parser/rule/type/type.cpp
        parser/rule/type/type.h
        parser/rule/reference/reference.cpp
        parser/rule/reference/reference.h
        parser/rule/module/module.cpp
        parser/rule/module/module.h
        parser/rule/ret/ret.cpp
        parser/rule/ret/ret.h
        parser/rule/expr/expr.cpp
        parser/rule/expr/expr.h
        parser/rule/ranged/ranged.cpp
        parser/rule/ranged/ranged.h
        parser/rule/prop/prop.cpp
        parser/rule/prop/prop.h
        parser/rule/binary/binary.cpp
        parser/rule/binary/binary.h
        parser/rule/var/var.cpp
        parser/rule/var/var.h
        parser/rule/if/if.cpp
        parser/rule/if/if.h
        parser/rule/block/block.cpp
        parser/rule/block/block.h
        file_code/file_code.cpp
        file_code/file_code.h
        file_code/type/type_wrapper.h
        file_code/structure/mod/mod.h
        file_code/rule/ref/ref.cpp
        file_code/rule/ref/ref.h
        file_code/rule/type/type.cpp
        file_code/rule/type/type.h
        structure/immut_str/immut_str.cpp
        structure/immut_str/immut_str.h
        file_code/structure/ref/ref.h
        file_code/structure/function/function.h
        file_code/rule/function/function.cpp
        file_code/rule/function/function.h
        parser/rule/pick/pick.cpp
        parser/rule/pick/pick.h
        parser/rule/arithmetic/arithmetic.cpp
        parser/rule/arithmetic/arithmetic.h
        file_code/rule/mod/mod.cpp
        file_code/rule/mod/mod.h
        core/rule/function/function.cpp
        core/rule/function/function.h
        core/object/object.h
        core/engine/engine.cpp
        core/engine/engine.h
        core/runtime/execution/execution_pair.h
        core/runtime/scope/scope.h
        core/rule/block/block.cpp
        core/rule/block/block.h
        core/rule/expr/expr.cpp
        core/rule/expr/expr.h
        core/rule/call/call.cpp
        core/rule/call/call.h
        core/object/object.cpp
        core/lazy/ref.cpp
        core/lazy/ref.h
        runtime/print/print.h
        core/std/stdlib_map.h
        core/std/stdlib_map.cpp
)

target_include_directories(fluenti PRIVATE ${CMAKE_BINARY_DIR}/_deps/unordered_dense-src/include)
target_include_directories(fluenti PRIVATE ${CMAKE_BINARY_DIR}/_deps/fluent_libc-src/include)
target_link_libraries(fluenti PRIVATE unordered_dense)
target_link_libraries(fluenti PRIVATE fluent_libc)

# Add aggressive optimization flags for C++ and C compilers
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -funroll-loops -flto")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -march=native -funroll-loops -flto")