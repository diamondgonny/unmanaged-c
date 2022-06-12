#ifndef CHARACTER_DESERIALIZER_H
#define CHARACTER_DESERIALIZER_H

#include <stdio.h>
#include <assert.h>
#include <string.h>

#define TRUE (1)
#define FALSE (0)

/* #define보다 이게 더 나은가...? 명시적 타입 때문인가? */
enum length {
    LENGTH_NAME = 50,
    LENGTH_BUF = 1024
};

typedef unsigned int uint_t;

typedef struct {
    char name[LENGTH_NAME + 1];
    uint_t health;
    uint_t strength;
    uint_t defence;
} minion_t;

typedef struct {
    uint_t fire;
    uint_t cold;
    uint_t lightning;
} elemental_resistance_t;

typedef struct {
    char name[LENGTH_NAME + 1];
    uint_t level;
    uint_t health;
    uint_t mana;
    uint_t strength;
    uint_t dexterity;
    uint_t intelligence;
    uint_t armour;
    uint_t evasion;
    uint_t leadership;
    uint_t minion_count;
    elemental_resistance_t elemental_resistance;
    minion_t minions[3];
} character_v3_t;

uint_t get_atoi(const char* str);

int find_file_ver(const char* str, const char* word);

int get_character(const char* filename, character_v3_t* out_character);

void version1(char* buf, character_v3_t* character);

void operate_version1(const char* key, const char* value_c, character_v3_t* character);

void version2(FILE* stream, char* buf, character_v3_t* character);

void operate_num_version2(const char* token, character_v3_t* character, uint_t stat_order);

void version3(FILE* stream, char* buf, character_v3_t* character);

void operate_num_version3(const char* token, character_v3_t* character, uint_t stat_order);

void operate_minion_version3(const char* token, character_v3_t* character, uint_t minion_num, uint_t stat_order);

#endif /* CHARACTER_DESERIALIZER_H */
