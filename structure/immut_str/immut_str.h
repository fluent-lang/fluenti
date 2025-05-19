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
// Created by rodrigo on 5/18/25.
//

#ifndef IMMUT_STR_H
#define IMMUT_STR_H

#include <cstring>
#include <string>
#include <string_view>

class ImmutStr {
public:
    char* buffer = nullptr;
    size_t size = 0;
    const bool is_heap;

    explicit ImmutStr(char *buffer, const size_t size, const bool is_heap = true)
        : buffer(buffer), size(size), is_heap(is_heap)
    {}

    ~ImmutStr()
    {
        if (is_heap)
        {
            free(buffer);
        }
    }

    bool operator==(const ImmutStr &other) const
    {
        return strcmp(buffer, other.buffer) == 0;
    }

    bool operator==(const char *other) const
    {
        return strcmp(buffer, other) == 0;
    }

    bool operator==(const std::string &other) const
    {
        return strcmp(buffer, other.c_str()) == 0;
    }
};

struct ImmutStrHash {
    using is_transparent = void;

    size_t operator()(const ImmutStr* s) const noexcept
    {
        return std::hash<std::string_view>()(std::string_view(s->buffer, s->size));
    }

    size_t operator()(const ImmutStr &s) const noexcept
    {
        return std::hash<std::string_view>()(std::string_view(s.buffer, s.size));
    }

    size_t operator()(const char* s) const noexcept
    {
        return std::hash<std::string_view>()(std::string_view(s, strlen(s)));
    }

    size_t operator()(const std::string_view& s) const noexcept
    {
        return std::hash<std::string_view>()(s);
    }
};

struct ImmutStrEqual {
    using is_transparent = void;

    bool operator()(const ImmutStr* lhs, const ImmutStr* rhs) const noexcept
    {
        if (lhs->size != rhs->size) return false;
        return memcmp(lhs->buffer, rhs->buffer, lhs->size) == 0;
    }

    bool operator()(const ImmutStr &lhs, const ImmutStr* rhs) const noexcept
    {
        if (lhs.size != rhs->size) return false;
        return memcmp(lhs.buffer, rhs->buffer, lhs.size) == 0;
    }

    bool operator()(const ImmutStr &lhs, const ImmutStr &rhs) const noexcept
    {
        if (lhs.size != rhs.size) return false;
        return memcmp(lhs.buffer, rhs.buffer, lhs.size) == 0;
    }

    bool operator()(const ImmutStr* lhs, const char* rhs) const noexcept
    {
        // Can't avoid strlen here, but you can accept string_view with size if you want no strlen
        if (const size_t rhs_len = strlen(rhs); lhs->size != rhs_len) return false;
        return memcmp(lhs->buffer, rhs, lhs->size) == 0;
    }

    bool operator()(const char* lhs, const ImmutStr* rhs) const noexcept
    {
        if (const size_t lhs_len = strlen(lhs); lhs_len != rhs->size) return false;
        return memcmp(lhs, rhs->buffer, rhs->size) == 0;
    }

    bool operator()(const ImmutStr* lhs, const std::string_view& rhs) const noexcept
    {
        if (lhs->size != rhs.size()) return false;
        return memcmp(lhs->buffer, rhs.data(), lhs->size) == 0;
    }

    bool operator()(const std::string_view& lhs, const ImmutStr* rhs) const noexcept
    {
        if (lhs.size() != rhs->size) return false;
        return memcmp(lhs.data(), rhs->buffer, rhs->size) == 0;
    }
};

template<>
struct std::hash<ImmutStr> {
    size_t operator()(const ImmutStr& str) const noexcept {
        return std::hash<std::string_view>()(std::string_view(str.buffer, str.size));
    }
};

#endif //IMMUT_STR_H
