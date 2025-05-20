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

#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

template <typename T>
struct LinkedQueueElement
{
    T value;
    LinkedQueueElement *next = nullptr;
};

template <typename T>
class LinkedQueue
{
    LinkedQueueElement<T> *head = nullptr;

public:
    explicit LinkedQueue() = default;

    void enqueue(const T value)
    {
        // Create a new value
        auto *new_element = new LinkedQueueElement<T>();
        new_element->value = value;

        // Relocate the head
        new_element->next = head;
        head = new_element;
    }

    void release_top()
    {
        // Get the head
        const auto *temp = head;
        head = head->next;

        // Delete the head
        delete temp;
    }

    bool empty()
    {
        return head == nullptr;
    }

    T peek()
    {
        // Panic if the head is null
        if (head == nullptr)
        {
            throw std::runtime_error("LinkedQueue: Head is null");
        }

        // Return the head's value
        return head->value;
    }

    ~LinkedQueue()
    {
        while (head != nullptr)
        {
            release_top();
        }
    }
};

#endif //LINKED_QUEUE_H
