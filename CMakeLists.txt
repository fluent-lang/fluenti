cmake_minimum_required(VERSION 3.30)
project(fluenti C)
include(ExternalProject)

ExternalProject_Add(
        fluent_libc
        GIT_REPOSITORY https://github.com/rodrigoo-r/fluent_libc
        GIT_TAG master
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/_install
        INSTALL_COMMAND ""
)

set(CMAKE_C_STANDARD 11)

add_executable(fluenti main.c
        heap/heap_alloc.c
        heap/heap_alloc.h
        types/bool.h
        object/object_type.c
        object/object_type.h
        object/fluent_object.c
        object/fluent_object.h
        "object/fluent_struct.c"
        "object/fluent_struct.h"
        structure/hash_map/hash_map.c
        structure/hash_map/hash_map.h
        types/int.h
        object/primitive_type.h
        structure/mutex/mutex.c
        structure/mutex/mutex.h
        runtime/print/print.c
        runtime/print/print.h
        runtime/init_runtime.c
        runtime/init_runtime.h
        runtime/read_line/read_line.c
        runtime/read_line/read_line.h
        runtime/object/string.h
        runtime/object/string.c
        runtime/read_line/win_read_line.c
        runtime/read_line/win_read_line.h
        cli/argv_impl.c
        cli/argv_impl.h
        logger/logger.c
        logger/logger.h
        ansi/ansi.h
        cli/flag/flag.h
        cli/flag/flag_type.h
        cli/default/get_flags.c
        cli/default/get_flags.h
        shared/on_hash_map_destroy.c
        shared/on_hash_map_destroy.h
        util/read_file/read_file.c
        util/space_formatter/space_formatter.c
        util/space_formatter/space_formatter.h
        util/help_generator/help_generator.c
        util/help_generator/help_generator.h
        structure/string_builder/string_builder.c
        structure/string_builder/string_builder.h
)

# Add fluent_libc as a dependency
add_dependencies(fluenti fluent_libc)

# Include the path to the headers from the external library
target_include_directories(fluenti PRIVATE ${CMAKE_BINARY_DIR}/fluent_libc-prefix/src)

# Link to the static library after the external project has installed it
target_link_libraries(fluenti PRIVATE ${CMAKE_BINARY_DIR}/fluent_libc-prefix/src/fluent_libc-build/libfluent_libc.a)
target_link_libraries(fluenti PRIVATE ${CMAKE_BINARY_DIR}/fluent_libc-prefix/src/fluent_libc-build/stdi/libstdi.a)
target_link_libraries(fluenti PRIVATE ${CMAKE_BINARY_DIR}/fluent_libc-prefix/src/fluent_libc-build/str_copy/libstr_copy.a)
target_link_libraries(fluenti PRIVATE ${CMAKE_BINARY_DIR}/fluent_libc-prefix/src/fluent_libc-build/str_len/libstrlen.a)
