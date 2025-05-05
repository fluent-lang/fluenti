//
// Created by rodrigo on 5/4/25.
//

#ifndef HASH_MAP_H
#define HASH_MAP_H

#ifndef __HASH_MAP_TABLE_SIZE
#define __HASH_MAP_TABLE_SIZE 20
#endif

#ifndef INT_H
#include "../../types/int.h"
#endif

#ifndef BOOL_H
#include "../../types/bool.h"
#endif

typedef struct HashMap_Entry
{
    char *key;
    void *value;
    struct HashMap_Entry *next;
} HashMap_Entry;

typedef struct
{
    HashMap_Entry **table;
    size_t len;
} HashMap;

typedef struct {
    const HashMap *map;
    int bucket_index;
    HashMap_Entry *current;
} HashMapIterator;

void insert_to_map(HashMap *map, const char *key, void *value);
void delete_from_map(HashMap *map, const char *key);
void* get_from_map(const HashMap *map, const char *key);
void destroy_hash_map(HashMap *map);
HashMap *create_hash_map();

HashMapIterator create_map_iterator(const HashMap *map);
bool map_iterator_has_next(const HashMapIterator *iterator);
void map_iterator_next(HashMapIterator *iterator, const char **key, void **value);

#endif //HASH_MAP_H
