#include <stdio.h>
#include <string.h>
#include "hashmap.h"

hashmap_t* init_hashmap_malloc(size_t length, size_t (*p_hash_func)(const char* key));

int add_key(hashmap_t* hashmap, const char* key, const int value);

int get_value(const hashmap_t* hashmap, const char* key);

int update_value(hashmap_t* hashmap, const char* key, const int value);

int remove_key(hashmap_t* hashmap, const char* key);

void destroy(hashmap_t* hashmap);
