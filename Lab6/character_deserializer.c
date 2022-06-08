#include "character_deserializer.h"

typedef struct {
    int make_your_own_var;
} minion_t;

typedef struct {
    int make_your_own_var;
} elemental_resistance_t;

typedef struct {
    int make_your_own_var;
} character_v3_t;

int get_character(const char* filename, character_v3_t* out_character);
