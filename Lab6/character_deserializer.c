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
    if (stream == NULL)
    {
        printf("File not opened...\n");
        return FALSE;
    }

    /* 버퍼에 대입 : p_buf - character_buf < BUF_LEN - 1 ? */
    do {
        *p_buf = fgetc(stream);    /* 파일에서 문자들 싹 가져옴 */
    } while (*p_buf++ != EOF && p_buf - character_buf < BUF_LEN - 1);
    *--p_buf = '\0';

    /* 내용 : v1형식? v2형식? v3형식? 함수포인터! */
    /* read_num = fread(names, sizeof(names[0]), NUM_NAMES, stream); */
    if (find_word(character_buf, "|") == TRUE) {
        version = 3;
    } else if (find_word(character_buf, "id") == TRUE) {
        version = 1;
        version1(character_buf, out_character);
    } else if (find_word(character_buf, "name") == TRUE) {
        version = 2;
    } else {
        return FALSE;
    }

    fclose(stream);
    return version;
}

uint_t atoi(const char* str) {
    uint_t res = 0;  /* 초기화 안해서 애먹었었음;; */
    while (str != '\0' && '0' <= *str && *str <= '9') {
        res = (res * 10) + (*str - '0');
        str++;
    }
    return res;
}

int operate_version1(const char* token, character_v3_t* character) {
    char key[6];
    char value_c[4];
    char* p;
    uint_t value_i = 0;

    p = key;
    while (*token != ':') {          /* token(lvl:10) */
        *p = *token;
        ++p;
        ++token;
    }
    *p = '\0';                      /* key(lvl) */
    ++token;

    p = value_c;
    while (*token != '\0') {
        *p = *token;
        ++p;
        ++token;
    }
    *p = '\0';
    value_i = atoi(value_c);        /* value_i(10) */

    if (strcmp(key, "id") == 0) {
        strcpy(character->name, "player_");
        strcat(character->name, value_c);
        /* '\0' */
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

void version1(char* buf, character_v3_t* character) {
    char* token = strtok(buf, ","); /* e.g. lvl:10 */
    operate_version1(token, character);

    while (1) {
        token = strtok(NULL, ","); /* 바로 뒤에 조건 달지 않으면, seg err */
        if (token != NULL) {
            operate_version1(token, character);
        } else {
            break;
        }
    }
}
