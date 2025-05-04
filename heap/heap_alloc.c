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

#include "../object/fluent_object.h"
#include <stdlib.h>
#include "heap_alloc.h"

#include <stdio.h>

struct Heap
{
    HeapGuard* guard;
    struct Heap* next;
};
typedef struct Heap Heap;
Heap* heap = NULL;

HeapGuard *create_with_prealloc(void **ptr)
{
    // Allocate a new guard on the heap
    HeapGuard *guard = malloc(sizeof(HeapGuard));

    // Check for allocation failure
    if (guard == NULL)
    {
        perror("malloc");
        exit(1);
    }

    // Create a new mutex on the heap
    Mutex *mutex = malloc(sizeof(Mutex));

    // Check for allocation failure
    if (mutex == NULL)
    {
        free(guard);
        perror("malloc");
        exit(1);
    }

    // Allocate a new object
    FluentObject* object = malloc(sizeof(FluentObject));

    // Check for allocation failure
    if (object == NULL)
    {
        destroy_mutex(mutex);
        free(guard);
        free(mutex);

        perror("malloc");
        exit(1);
    }

    // Initialize the objects
    object->element = *ptr;
    guard->on_destroy = NULL;
    guard->size = sizeof(ptr);
    guard->value = object;
    guard->mutex = mutex;
    guard->ref_count = 1;

    // Create a new heap node
    Heap* node = malloc(sizeof(Heap));

    // Check for allocation failure
    if (node == NULL)
    {
        destroy_mutex(mutex);
        free(guard);
        free(mutex);
        free(object);
        perror("malloc");
        exit(1);
    }

    node->guard = guard;
    if (heap == NULL)
    {
        heap = node;
    } else
    {
        // Relocate the heap
        node->next = heap;
        heap = node;
    }

    return guard;
}

HeapGuard* alloc(const size_t size)
{
    // Malloc the value
    void *ptr = malloc(size);

    // Check for allocation failure
    if (ptr == NULL)
    {
        perror("malloc");
        exit(1);
    }

    // Create with prealloc
    HeapGuard *guard = create_with_prealloc(&ptr);
    guard->size = size;

    return guard;
}

void ensure_guard(const HeapGuard *guard)
{
    // Check if the guard has been freed
    if (guard->mutex == NULL || guard->value == NULL)
    {
        puts("Memory failure: Attempted to raise/lower an already-freed guard");
        exit(1);
    }
}

void expand_guard(HeapGuard *guard, const size_t size)
{
    ensure_guard(guard);

    // Update the size
    guard->size += size;

    // Reallocate the value
    void *new_ptr = realloc(guard->value->element, guard->size);

    // Check for allocation failure
    if (new_ptr == NULL)
    {
        perror("realloc");
        exit(1);
    }

    // Update the ptr
    guard->value->element = new_ptr;
}

void destroy_guard(HeapGuard *guard)
{
    // See if we have an on_destroy function
    if (guard->on_destroy != NULL)
    {
        guard->on_destroy(guard);
    }

    // Destroy the mutex
    destroy_mutex(guard->mutex);

    // Free the mutex
    free(guard->mutex);

    // Make sure the listener function has not set the element to NULL
    if (guard->value->element != NULL)
    {
        free(guard->value->element);
    }

    // Free the guard's object
    free(guard->value);

    // Set the elements to NULL
    guard->value = NULL;
    guard->mutex = NULL;
}

void raise_guard(HeapGuard *guard)
{
    ensure_guard(guard);

    // Lock the guard's mutex
    lock_mutex(guard->mutex);

    // Increment the reference count
    guard->ref_count++;

    // Unlock the guard's mutex
    unlock_mutex(guard->mutex);
}

void drop_guard(HeapGuard *guard)
{
    // Lock the guard's mutex
    lock_mutex(guard->mutex);

    // Decrement the reference count
    guard->ref_count--;

    // Check if we can free the guard
    if (guard->ref_count == 0)
    {
        // Unlock the guard's mutex
        unlock_mutex(guard->mutex);
        destroy_guard(guard);

        // Remove the guard from the heap
        Heap *current = heap;
        Heap *prev = NULL;

        while (current != NULL)
        {
            if (current->guard == guard)
            {
                // Handle the case where the guard is the first element
                if (prev == NULL)
                {
                    heap = heap->next;
                    break;
                }

                // Relocate the heap
                prev->next = current->next;
                break;
            }

            prev = current;
            current = current->next;
        }

        free(guard);
        return;
    }

    // Unlock the guard's mutex
    unlock_mutex(guard->mutex);
}

void cleanup_heap()
{
    // Clean the heap
    Heap* current = heap;

    // Iterate the list
    while (current != NULL)
    {
        Heap* next = current->next;

        // Destroy the guard
        destroy_guard(current->guard);

        // Free the guard
        free(current->guard);

        // Free the element
        free(current);

        current = next;
    }
}