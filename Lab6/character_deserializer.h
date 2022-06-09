#ifndef CHARACTER_DESERIALIZER_H
#define CHARACTER_DESERIALIZER_H

#define TRUE (1)
#define FALSE (0)

typedef unsigned int uint_t;

enum {
    NAME_LEN = 50,
    BUF_LEN = 2048
}; /* #define보다 이게 더 나은가? why? */

typedef struct {
    char name[NAME_LEN + 1];
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
    char name[NAME_LEN + 1];
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

int get_character(const char* filename, character_v3_t* out_character);

#endif /* CHARACTER_DESERIALIZER_H */
