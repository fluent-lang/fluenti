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

typedef struct HashMap_Entry
{
    char *key;
    void *value;
    struct HashMap_Entry *next;
} HashMap_Entry;

typedef struct
{
    HashMap_Entry **table;
} HashMap;

uint __HashMap_hash(const char *key);
void insert_to_map(const HashMap *map, const char *key, void *value);
void delete_from_map(const HashMap *map, const char *key);
void* get_from_map(const HashMap *map, const char *key);
void destroy_hash_map(HashMap *map);
HashMap *create_hash_map();

#endif //HASH_MAP_H
