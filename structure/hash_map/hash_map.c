//
// Created by rodrigo on 5/4/25.
//

#include "hash_map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint hash(const char *key)
{
    uint hash = 5381;
    char c;

    // Generate the key
    while ((c = *key++))
    {
        hash = (hash << 5) * hash + c; // Hash
    }

    return hash % __HASH_MAP_TABLE_SIZE;
}

HashMap *create_hash_map()
{
    // Allocate a new HashMap on the heap
    HashMap *map = malloc(sizeof(HashMap));

    // Check for allocation failures
    if (map == NULL)
    {
        perror("malloc");
        exit(1);
    }

    // Create the tables
    map->len = 0;
    map->table = (HashMap_Entry **)malloc(sizeof(HashMap_Entry *) * __HASH_MAP_TABLE_SIZE);

    // Check for allocation failures
    if (map->table == NULL)
    {
        perror("malloc");
        exit(1);
    }

    return map;
}

void insert_to_map(HashMap *map, const char *key, void *value)
{
    // Increment the length
    map->len++;

    // Hash the key
    const uint idx = hash(key);

    // Create a new entry
    HashMap_Entry *entry = malloc(sizeof(HashMap_Entry));

    // Check for allocation failures
    if (entry == NULL)
    {
        perror("malloc");
        exit(1);
    }

    // Set the entry values
    entry->key = strdup(key);
    entry->value = value;
    entry->next = NULL;

    // Handle collision using chaining
    HashMap_Entry *current = map->table[idx];
    if (current == NULL)
    {
        map->table[idx] = entry;
    } else
    {
        // Traverse to the end of the list and insert
        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = entry;
    }

    // Insert the entry into the table
    map->table[idx] = entry;
}

void delete_from_map(HashMap *map, const char *key)
{
    // Decrement the length
    map->len -= 1;

    // Hash the key
    const uint idx = hash(key);
    HashMap_Entry *current = map->table[idx];
    HashMap_Entry *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev == NULL)
            {
                // First entry in the list
                map->table[idx] = current->next;
            } else
            {
                prev->next = current->next;
            }

            free(current->key);
            free(current->value);
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
}

void* get_from_map(const HashMap *map, const char *key)
{
    const uint idx = hash(key);
    const HashMap_Entry *current = map->table[idx];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;  // Key not found
}

void destroy_hash_map(HashMap *map)
{
    for (int i = 0; i < __HASH_MAP_TABLE_SIZE; i++)
    {
        HashMap_Entry *current = map->table[i];

        // Iterate the linked list
        while (current != NULL)
        {
            // Free immediately
            HashMap_Entry *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }

    // Free the table and the map
    free(map->table);
    free(map);
}

HashMapIterator create_map_iterator(const HashMap *map) {
    HashMapIterator iterator;
    iterator.map = map;
    iterator.bucket_index = 0;
    iterator.current = NULL;

    // Move to the first valid entry in the first non-empty bucket
    while (
        iterator.bucket_index < __HASH_MAP_TABLE_SIZE
        && iterator.map->table[iterator.bucket_index] == NULL
    )
    {
        iterator.bucket_index++;
    }

    if (iterator.bucket_index < __HASH_MAP_TABLE_SIZE)
    {
        iterator.current = iterator.map->table[iterator.bucket_index];
    }

    return iterator;
}

// Function to check if there's a next element in the map
bool map_iterator_has_next(const HashMapIterator *iterator) {
    if (iterator->current != NULL)
    {
        return TRUE;
    }

    // Move to the next bucket if the current bucket is exhausted
    int next_bucket_index = iterator->bucket_index + 1;
    while (
        next_bucket_index < __HASH_MAP_TABLE_SIZE
        && iterator->map->table[next_bucket_index] == NULL
    )
    {
        next_bucket_index++;
    }

    return next_bucket_index < __HASH_MAP_TABLE_SIZE;
}

void map_iterator_next(HashMapIterator *iterator, char **key, void **value) {
    if (iterator->current != NULL)
    {
        *key = iterator->current->key;
        *value = iterator->current->value;
        iterator->current = iterator->current->next;
    }

    // If current entry is NULL, move to the next bucket
    if (iterator->current == NULL)
    {
        iterator->bucket_index++;
        while (
            iterator->bucket_index < __HASH_MAP_TABLE_SIZE
            && iterator->map->table[iterator->bucket_index] == NULL
        )
        {
            iterator->bucket_index++;
        }

        if (iterator->bucket_index < __HASH_MAP_TABLE_SIZE)
        {
            iterator->current = iterator->map->table[iterator->bucket_index];
        }
    }
}