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

#ifndef HEAP_GUARD_H
#define HEAP_GUARD_H

#include <cstddef>
#include <stdexcept>
#include <cstdlib>
#include <atomic>

/**
 * @brief The Fluent Runtime Memory Allocator.
 *
 * HeapGuard is a reference-counted heap memory manager for C/C++,
 * supporting both concurrent (atomic) and non-concurrent (non-atomic) reference counting.
 * It is only compatible with memory allocated via malloc/free.
 * For C++ objects, prefer std::shared_ptr.
 *
 * @tparam T Type of the managed object.
 */
template <typename T>
class HeapGuard
{
    T *ptr = nullptr /* NULL */; ///< Pointer to the managed memory.
    std::atomic<size_t> *ref_count = nullptr; ///< Atomic reference count for concurrent use.
    size_t *non_atomic_ref_count = nullptr; ///< Non-atomic reference count for single-threaded use.
    bool is_concurrent; ///< Whether to use atomic reference counting.
    bool freed = false; ///< Whether the memory has been freed.

    /**
     * @brief Decrement the reference count.
     *
     * Frees the memory if the reference count reaches zero.
     */
    void lower_guard() const
    {
        if (is_concurrent)
        {
            ref_count->fetch_sub(1);
        }
        else
        {
            (*non_atomic_ref_count)--;
        }
    }

    /**
     * @brief Increment the reference count.
     */
    void raise_guard() const
    {
        if (is_concurrent)
        {
            ref_count->fetch_add(1);
        }
        else
        {
            (*non_atomic_ref_count)++;
        }
    }

    /**
     * @brief Get the current reference count.
     * @return The current reference count.
     */
    [[nodiscard]] size_t get_ref_count() const
    {
        if (is_concurrent)
        {
            return ref_count->load();
        }

        return *non_atomic_ref_count;
    }

public:
    /**
     * @brief Allocate and guard a new heap block.
     *
     * @param size Number of elements to allocate.
     * @param is_concurrent Whether to use atomic reference counting.
     * @throws std::runtime_error if allocation fails.
     */
    explicit HeapGuard(const size_t size, const bool is_concurrent)
    : is_concurrent(is_concurrent)
    {
        // Try to malloc the memory
        ptr = static_cast<T *>(malloc(size * sizeof(T)));

        // Check if we got NULL
        if (ptr == nullptr)
        {
            throw std::runtime_error("HeapGuard: Pointer is null");
        }

        // Handle concurrency accordingly
        if (is_concurrent)
        {
            ref_count = new std::atomic<size_t>(1);
        }
        else
        {
            non_atomic_ref_count = new size_t(1);
        }
    }

    /**
     * @brief Guard an existing pointer.
     *
     * @param ptr Pointer to manage (must be malloc'd).
     * @param is_concurrent Whether to use atomic reference counting.
     * @throws std::runtime_error if ptr is null.
     */
    explicit HeapGuard(T *ptr, const bool is_concurrent)
    : ptr(ptr), is_concurrent(is_concurrent)
    {
        {
            // Make sure the pointer is not null
            if (ptr == nullptr)
            {
                throw std::runtime_error("HeapGuard: Pointer is null");
            }

            // Handle concurrency accordingly
            if (is_concurrent)
            {
                ref_count = new std::atomic<size_t>(1);
            }
            else
            {
                non_atomic_ref_count = new size_t(1);
            }
        }
    }

    /**
         * @brief Destroys the managed memory and reference counter.
         *
         * Frees the memory pointed to by @ptr (must be malloc'd), and deletes the reference
         * counter (atomic or non-atomic) depending on the concurrency mode. Sets all internal
         * pointers to nullptr after cleanup. Only use for memory allocated with malloc.
         */
        void destroy()
        {
            if (ptr == nullptr || freed) return;

            // Warning: HeapGuard is only compatible with malloc'd memory
            // for C++ objects, use std::shared_ptr
            free(ptr);

            if (is_concurrent)
            {
                delete ref_count;
            } else
            {
                delete non_atomic_ref_count;
            }

            ptr = nullptr;
            ref_count = nullptr;
            non_atomic_ref_count = nullptr;
            freed = true;
        }

    /**
     * @brief Decrement reference count and free memory if needed.
     *
     * Frees the managed memory and reference counter if the count reaches zero.
     */
    void drop()
    {
        if (ref_count != nullptr && ptr != nullptr)
        {
            lower_guard();

            if (get_ref_count() > 0)
            {
                return; // still have references
            }

            destroy();
        }
    }

    /**
     * @brief Copy constructor.
     *
     * Increments the reference count.
     * @param other The HeapGuard to copy.
     */
    HeapGuard(const HeapGuard& other) noexcept
    : ptr(other.ptr),
      is_concurrent(other.is_concurrent),
      freed(other.freed)
    {
        if (is_concurrent)
        {
            ref_count = other.ref_count;
        }
        else
        {
            non_atomic_ref_count = other.non_atomic_ref_count;
        }

        raise_guard();
    }

    /**
     * @brief Copy assignment operator.
     *
     * Releases current ownership and increments the reference count of the new resource.
     * @param other The HeapGuard to assign from.
     * @return Reference to this.
     */
    HeapGuard& operator=(const HeapGuard& other) {
        if (this != &other) {
            drop(); // release current ownership

            ptr = other.ptr;
            is_concurrent = other.is_concurrent;
            freed = other.freed;

            if (is_concurrent)
            {
                ref_count = other.ref_count;
            }
            else
            {
                non_atomic_ref_count = other.non_atomic_ref_count;
            }

            raise_guard();
        }

        return *this;
    }

    /**
     * @brief Get the raw pointer.
     * @return Pointer to the managed memory.
     */
    T* get() const {
        return ptr;
    }

    /**
     * @brief Dereference operator.
     * @return Reference to the managed object.
     */
    T& operator*() const {
        return *ptr;
    }

    /**
     * @brief Member access operator.
     * @return Pointer to the managed object.
     */
    T* operator->() const {
        return ptr;
    }

    /**
     * @brief Destructor.
     *
     * Decrements the reference count and frees memory if needed.
     */
    ~HeapGuard()
    {
        drop();
    }
};

#endif //HEAP_GUARD_H
