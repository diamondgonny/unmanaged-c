#include "character_deserializer.h"

/*
반환값: int(version)
캐릭터 파일명: const char* filename
character_v3_t 구조체의 포인터: character_v3_t* out_character
ㅡ
filename 파일에 저장되어 있는 캐릭터 정보를 out_character로 역직렬화할 것
*/

int find_word(char* str, const char* word)
{
    char* p = str;
    int i = 0;

    while (*p != '\0') {
        while (*(word + i) == *(p + i) && *(p + i) != '\0') {
            ++i;
            if (*(word + i) == '\0') {
                return TRUE;
            }
        }
        ++p;
    }
    return FALSE;
}

int get_character(const char* filename, character_v3_t* out_character)
{
    FILE* stream;
    char character_buf[BUF_LEN] = { 0, };
    char* p_buf = character_buf;
    int version = 0;

    /* 오류 처리 */
    stream = fopen(filename, "r");
    if (stream == NULL) {
        printf("File not opened...\n");
        return FALSE;
    }

    /* 버퍼에 대입 : p_buf - character_buf < BUF_LEN - 1 ? */
    /* 파일에서 문자들 싹 가져옴 */
    do {
        *p_buf = fgetc(stream);
    } while (*p_buf++ != EOF && p_buf - character_buf < BUF_LEN - 1);
    *--p_buf = '\0';

    /* 내용 : v1형식? v2형식? v3형식? 함수포인터! */
    /* read_num = fread(names, sizeof(names[0]), NUM_NAMES, stream); */
    if (find_word(character_buf, "|") == TRUE) {
        version = 3;
        version3(character_buf, out_character);
    } else if (find_word(character_buf, "id") == TRUE) {
        version = 1;
        version1(character_buf, out_character);
    } else if (find_word(character_buf, "name") == TRUE) {
        version = 2;
        version2(character_buf, out_character);
    } else {
        return FALSE;
    }

    fclose(stream);
    return version;
}

uint_t get_atoi(const char* str)
{
    /* 초기화 안해서 애먹었었음;; */
    uint_t res = 0;

    while ('0' <= *str && *str <= '9') {
        res = (res * 10) + (*str - '0');
        str++;
    }
    return res;
}

int operate_version1(const char* key, const char* value_c, character_v3_t* character)
{
    /* token(lvl:10)
    char key[NAME_LEN];
    char value_c[NAME_LEN];
    char* p; */
    uint_t value_i = 0;
    value_i = get_atoi(value_c);

    /* key(lvl)
    p = key;
    while (*token != ':') {
        *p = *token;
        ++p;
        ++token;
    }
    *p = '\0';
    ++token; */

    /* value_i(10)
    p = value_c;
    while (*token != '\0') {
        *p = *token;
        ++p;
        ++token;
    }
    *p = '\0';
    value_i = get_atoi(value_c); */

    /* value에 0은 없고, 규격을 준수했다고 가정 */
    if (value_i == 0) {
        return FALSE;
    }

    if (strcmp(key, "id") == 0) {
        strcpy(character->name, "player_");
        strncat(character->name, value_c, NAME_LEN - 7);
        character->name[NAME_LEN] = '\0';
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
    } else {
        return FALSE;
    }
    return TRUE;
}

void version1(char* buf, character_v3_t* character)
{
    char* key = strtok(buf, ":"); /* e.g. lvl:10 */
    char* value_c = strtok(NULL, ",");
    operate_version1(key, value_c, character);

    while (1) {
        key = strtok(NULL, ":"); /* 바로 뒤에 조건 달지 않으면, seg err */
        value_c = strtok(NULL, ",");
        if (key != NULL && value_c != NULL) {
            operate_version1(key, value_c, character);
        } else {
            break;
        }
    }
}

int operate_num_version2(const char* token, character_v3_t* character, uint_t stat)
{
    uint_t value_i = get_atoi(token);

    switch (stat) {
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
    return TRUE;
}

void version2(char* buf, character_v3_t* character)
{
    char* token;
    uint_t stat_order = 0;

    while (*buf++ != '\n') {
    }

    token = strtok(buf, ","); /* e.g. Batman_v2 */
    strncpy(character->name, token, NAME_LEN + 1);
    character->name[NAME_LEN] = '\0';
    character->minion_count = 0;
    ++stat_order;

    while (stat_order < 10) {
        token = strtok(NULL, ","); /* Ver2의 규격을 준수하고, 빠짐없이 채웠다고 가정 */
        operate_num_version2(token, character, stat_order);
        ++stat_order;
    }
}

int operate_num_version3(const char* token, character_v3_t* character, uint_t stat)
{
    uint_t value_i = get_atoi(token);

    switch (stat) {
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
    return TRUE;
}

int operate_minion_version3(const char* token, character_v3_t* character, uint_t minion_num, uint_t stat_order)
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
    return TRUE;
}

void version3(char* buf, character_v3_t* character)
{
    char* token;
    uint_t stat_order = 0;
    uint_t i;
    uint_t j;

    while (*buf++ != '\n') {
    }

    token = strtok(buf, " |"); /* e.g. Wonderwoman_v3 */
    /* name이 영문자 혹은 _이 아닌 경우? */
    strncpy(character->name, token, NAME_LEN);
    character->name[NAME_LEN] = '\0';
    ++stat_order;

    while (stat_order < 14) {
        token = strtok(NULL, " |"); /* Ver3의 규격을 준수하고, 빠짐없이 채웠다고 가정 */
        operate_num_version3(token, character, stat_order);
        ++stat_order;
    }

    if (character->minion_count == 0) {
        return;
    } else {
        while (*buf++ != '\n') {
        }
        while (*buf++ != '\n') {
        }
    }

    for (i = 0; i < character->minion_count; ++i) {
        /* strtok의 '\0' 치환으로 개행 못하는 문제, q포인터로 해결 */
        char* q = buf;
        while (*q != '\n' && *q != '\0') {
            ++q;
        }
        token = strtok(buf, " |");
        strncpy(character->minions[i].name, token, NAME_LEN);
        character->minions[i].name[NAME_LEN] = '\0';

        for (j = 1; j < 4; ++j) {
            token = strtok(NULL, " |\n");
            operate_minion_version3(token, character, i, j);
        }

        if (*(q + 1) != '\0') {
            buf = q + 1;
        }
    }
}
