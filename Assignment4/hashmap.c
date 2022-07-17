#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

/*
void my_dump(hashmap_t* hashmap)
{
    int i;
	for (i = 0; i < hashmap->length; i++) {
		node_t *p = hashmap->plist[i];
		printf("%02d ", i);

		while (p != NULL) {
			printf("→ %d :(%s) ", p->value, p->key);
			p = p->next;
		}
		putchar('\n');
	}
}
*/

hashmap_t* init_hashmap_malloc(size_t length, size_t (*p_hash_func)(const char* key))
{
    size_t i;
    hashmap_t* hashmap = (hashmap_t*)malloc(sizeof(hashmap_t));

    /* malloc이 NULL을 반환하는 경우도 고려해야 하는가? */
    hashmap->hash_func = p_hash_func;
    hashmap->plist = (node_t**)malloc(length * sizeof(node_t*));
    /* memset(hashmap->plist, 0, length * sizeof(node_t*)); */
    hashmap->length = length;

    for (i = 0; i < length; i++) {
        hashmap->plist[i] = NULL;
    }

    return hashmap;
}

int add_key(hashmap_t* hashmap, const char* key, const int value)
{
    node_t* p = hashmap->plist[hashmap->hash_func(key) % hashmap->length];
    node_t* tmp;

    while (p != NULL) {
        /* 이미 등록된 키면 추가 실패 처리 */
        if (strcmp(p->key, key) == 0) {
            return FALSE;
        }
        p = p->next;
    }

    tmp = (node_t*)malloc(sizeof(node_t));
    tmp->key = (char*)malloc(strlen(key) + 1);
    strcpy(tmp->key, key);
    tmp->value = value;
    tmp->next = hashmap->plist[hashmap->hash_func(key) % hashmap->length];
    hashmap->plist[hashmap->hash_func(key) % hashmap->length] = tmp;

    return TRUE;
}

int get_value(const hashmap_t* hashmap, const char* key)
{
    node_t* p = hashmap->plist[hashmap->hash_func(key) % hashmap->length];

    while (p != NULL) {
        if (strcmp(p->key, key) == 0) {
            return p->value;
        }
        p = p->next;
    }

    return -1;
}

int update_value(hashmap_t* hashmap, const char* key, const int value)
{
    node_t* p = hashmap->plist[hashmap->hash_func(key) % hashmap->length];

    while (p != NULL) {
        if (strcmp(p->key, key) == 0) {
            p->value = value;
            return TRUE;
        }
        p = p->next;
    }
    printf("nodap\n");

    return FALSE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    node_t* p = hashmap->plist[hashmap->hash_func(key) % hashmap->length];
    node_t** pp = &hashmap->plist[hashmap->hash_func(key) % hashmap->length];

    while (p != NULL) {
        if (strcmp(p->key, key) == 0) {
            *pp = p->next;
            free(p);
            return TRUE;
        }
        pp = &p->next;
        p = p->next;
    }

    return FALSE;
}

void destroy(hashmap_t* hashmap)
{
    size_t i;

    for (i = 0; i < hashmap->length; ++i) {
        node_t* p = hashmap->plist[i];

        while (p != NULL) {
            node_t* next = p->next;
            free(p->key);
            free(p);
            p = next;
        }
        hashmap->plist[i] = NULL;
    }
    free(hashmap->plist);
    free(hashmap);
}
