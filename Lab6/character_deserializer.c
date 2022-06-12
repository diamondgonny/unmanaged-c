#include "character_deserializer.h"

uint_t get_atoi(const char* str)
{
    /* TIL) 초기화 안해서 애먹었었음... */
    uint_t res = 0;

    while ('0' <= *str && *str <= '9') {
        res = (res * 10) + (*str - '0');
        str++;
    }
    return res;
}

int find_file_ver(const char* str, const char* word)
{
    /* str에서 word 찾기 */
    int i = 0;

    while (*str != '\0') {
        while (*(word + i) == *(str + i) && *(str + i) != '\0') {
            ++i;
            if (*(word + i) == '\0') {
                return TRUE;
            }
        }
        ++str;
    }
    return FALSE;
}

int get_character(const char* filename, character_v3_t* out_character)
{
    FILE* stream;
    void (*ver_func)(FILE*, char*, character_v3_t*);
    char buffer[LENGTH_BUF] = { 0, };
    int version = 0;

    stream = fopen(filename, "r");
    if (stream == NULL) {
        printf("File not opened...\n");
        return FALSE;
    }

    /* 파일의 첫 줄을 buffer로 가져옴 */
    fgets(buffer, LENGTH_BUF, stream);

    /* 파일검사 -> v1형식? v2형식? v3형식? (cf. 함수포인터 활용해봄) */
    if (find_file_ver(buffer, "|") == TRUE) {
        version = 3;
        ver_func = version3;
    } else if (find_file_ver(buffer, ":") == TRUE) {
        version = 1;
        ver_func = version1;
    } else if (find_file_ver(buffer, "name") == TRUE) {
        version = 2;
        ver_func = version2;
    } else {
        return FALSE;
    }
    ver_func(stream, buffer, out_character);

    fclose(stream);
    return version;
}

void version1(FILE* stream, char* buf, character_v3_t* character)
{
    char* key;
    char* value_c;

    fseek(stream, 0, SEEK_SET);
    fgets(buf, LENGTH_BUF, stream);

    /* key와 value쌍을 맞춰보면서 역직렬화 (e.g. lvl:10,) */
    key = strtok(buf, ":");
    value_c = strtok(NULL, ",");
    operate_version1(key, value_c, character);

    while (1) {
        /* TIL) strtok 함수는 '구분자'를 '\0'으로 바꿔줌 */
        key = strtok(NULL, ":");
        value_c = strtok(NULL, ",");
        /* TIL) 아래와 같은 제약조건 달지 않으면, 세그멘테이션 오류 (선넘네...) */
        if (key != NULL && value_c != NULL) {
            operate_version1(key, value_c, character);
        } else {
            break;
        }
    }
}

void operate_version1(const char* key, const char* value_c, character_v3_t* character)
{
    uint_t value_i = get_atoi(value_c);

    if (strcmp(key, "id") == 0) {
        strcpy(character->name, "player_");
        strncat(character->name, value_c, LENGTH_NAME - 7);
        character->name[LENGTH_NAME] = '\0';
        character->minion_count = 0;
    } else if (strcmp(key, "lvl") == 0) {
        character->level = value_i;
        character->leadership = value_i / 10;
    } else if (strcmp(key, "hp") == 0) {
        character->health = value_i;
    } else if (strcmp(key, "mp") == 0) {
        character->mana = value_i;
    } else if (strcmp(key, "str") == 0) {
        character->strength = value_i;
    } else if (strcmp(key, "dex") == 0) {
        character->dexterity = value_i;
        character->evasion = value_i / 2;
    } else if (strcmp(key, "intel") == 0) {
        character->intelligence = value_i;
    } else if (strcmp(key, "def") == 0) {
        character->armour = value_i;
        character->elemental_resistance.fire = (value_i / 4) / 3;
        character->elemental_resistance.cold = (value_i / 4) / 3;
        character->elemental_resistance.lightning = (value_i / 4) / 3;
    }
}

void version2(FILE* stream, char* buf, character_v3_t* character)
{
    char* token;
    uint_t stat_order = 0;

    fgets(buf, LENGTH_BUF, stream);

    /* 순차적, name부터 시작함 (e.g. Batman_v2,) */
    token = strtok(buf, ",");
    strncpy(character->name, token, LENGTH_NAME);
    character->name[LENGTH_NAME] = '\0';
    character->minion_count = 0;
    ++stat_order;

    /* ver2의 규격을 준수하고, 빠짐없이 채웠다고 가정 */
    while (stat_order < 10) {
        token = strtok(NULL, ",");
        operate_num_version2(token, character, stat_order);
        ++stat_order;
    }
}

void operate_num_version2(const char* token, character_v3_t* character, uint_t stat_order)
{
    uint_t value_i = get_atoi(token);

    switch (stat_order) {
    case 1:
        character->level = value_i;
        character->leadership = value_i / 10;
        break;
    case 2:
        character->strength = value_i;
        break;
    case 3:
        character->dexterity = value_i;
        break;
    case 4:
        character->intelligence = value_i;
        break;
    case 5:
        character->armour = value_i;
        break;
    case 6:
        character->evasion = value_i;
        break;
    case 7:
        character->elemental_resistance.fire = value_i / 3;
        character->elemental_resistance.cold = value_i / 3;
        character->elemental_resistance.lightning = value_i / 3;
        break;
    case 8:
        character->health = value_i;
        break;
    case 9:
        character->mana = value_i;
        break;
    default:
        assert(0);
        break;
    }
}

void version3(FILE* stream, char* buf, character_v3_t* character)
{
    char* token;
    uint_t stat_order = 0;
    uint_t i;
    uint_t j;

    fgets(buf, LENGTH_BUF, stream);

    /* 순차적, name부터 시작함 (e.g. Wonderwoman_v3 | ) */
    token = strtok(buf, " |");
    strncpy(character->name, token, LENGTH_NAME);
    character->name[LENGTH_NAME] = '\0';
    ++stat_order;

    /* ver3의 규격을 준수하고, 빠짐없이 채웠다고 가정 */
    while (stat_order < 14) {
        token = strtok(NULL, " |");
        operate_num_version3(token, character, stat_order);
        ++stat_order;
    }

    /* 미니언 없으면 여기서 끝내고, 있으면 (속성 나열된) 한 줄 건너뛰고 keep going */
    if (character->minion_count == 0) {
        return;
    } else {
        fgets(buf, LENGTH_BUF, stream);
    }

    /* 미니언 개체수만큼 ㄱㄱ */
    for (i = 0; i < character->minion_count; ++i) {
        fgets(buf, LENGTH_BUF, stream);

        token = strtok(buf, " |");
        strncpy(character->minions[i].name, token, LENGTH_NAME);
        character->minions[i].name[LENGTH_NAME] = '\0';

        /* case 구분을 위해 1부터 지정함 (0은 위에서 처리한 name) */
        for (j = 1; j < 4; ++j) {
            token = strtok(NULL, " |\n");
            operate_minion_version3(token, character, i, j);
        }
    }
}

void operate_num_version3(const char* token, character_v3_t* character, uint_t stat_order)
{
    uint_t value_i = get_atoi(token);

    switch (stat_order) {
    case 1:
        character->level = value_i;
        break;
    case 2:
        character->health = value_i;
        break;
    case 3:
        character->mana = value_i;
        break;
    case 4:
        character->strength = value_i;
        break;
    case 5:
        character->dexterity = value_i;
        break;
    case 6:
        character->intelligence = value_i;
        break;
    case 7:
        character->armour = value_i;
        break;
    case 8:
        character->evasion = value_i;
        break;
    case 9:
        character->elemental_resistance.fire = value_i;
        break;
    case 10:
        character->elemental_resistance.cold = value_i;
        break;
    case 11:
        character->elemental_resistance.lightning = value_i;
        break;
    case 12:
        character->leadership = value_i;
        break;
    case 13:
        character->minion_count = value_i;
        break;
    default:
        assert(0);
        break;
    }
}

void operate_minion_version3(const char* token, character_v3_t* character, uint_t minion_num, uint_t stat_order)
{
    uint_t value_i = get_atoi(token);

    switch (stat_order) {
    case 1:
        character->minions[minion_num].health = value_i;
        break;
    case 2:
        character->minions[minion_num].strength = value_i;
        break;
    case 3:
        character->minions[minion_num].defence = value_i;
        break;
    default:
        assert(0);
        break;
    }
}
