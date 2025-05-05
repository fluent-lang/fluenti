//
// Created by rodrigo on 5/4/25.
//

#include "hash_map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint __HashMap_hash(const char *key)
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
    map->table = (HashMap_Entry **)malloc(sizeof(HashMap_Entry *) * __HASH_MAP_TABLE_SIZE);

    // Check for allocation failures
    if (map->table == NULL)
    {
        perror("malloc");
        exit(1);
    }

    return map;
}

void insert_to_map(const HashMap *map, const char *key, void *value)
{
    // Hash the key
    const uint hash = __HashMap_hash(key);

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
    HashMap_Entry *current = map->table[hash];
    if (current == NULL)
    {
        map->table[hash] = entry;
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
    map->table[hash] = entry;
}

void delete_from_map(const HashMap *map, const char *key)
{
    // Hash the key
    const uint hash = __HashMap_hash(key);
    HashMap_Entry *current = map->table[hash];
    HashMap_Entry *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev == NULL)
            {
                // First entry in the list
                map->table[hash] = current->next;
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
    const uint hash = __HashMap_hash(key);
    const HashMap_Entry *current = map->table[hash];

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