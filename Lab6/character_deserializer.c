#include "character_deserializer.h"

/*
2.1 minion_t 구조체를 구현한다
name: 문자열. 최대 50 글자
health: 부호 없는 int 형
strength: 부호 없는 int 형
defence: 부호 없는 int 형

2.2 elemental_resistance_t 구조체를 구현한다
fire: 부호 없는 int 형
cold: 부호 없는 int 형
lightning: 부호 없는 int 형

2.3 character_v3_t 구조체를 구현한다
name: 문자열. 최대 50 글자
level: 부호 없는 int 형
health: 부호 없는 int 형
mana: 부호 없는 int 형
strength: 부호 없는 int 형
dexterity: 부호 없는 int 형
intelligence: 부호 없는 int 형
armour: 부호 없는 int 형
evasion: 부호 없는 int 형
leadership: 부호 없는 int 형
minion_count: 부호 없는 int 형
elemental_resistance: elemental_resistance_t
minions: minion_t의 배열. 최대 세 마리의 미니언
*/

/*
반환값: int(version)
캐릭터 파일명: const char* filename
character_v3_t 구조체의 포인터: character_v3_t* out_character
ㅡ
filename 파일에 저장되어 있는 캐릭터 정보를 out_character로 역직렬화할 것
*/

int find_word(const char* str, const char* word)
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
    char ch = 0;
    char character_buf[BUF_LEN] = { 0, };
    char* p_buf = character_buf;
    int version = 0;

    /* 오류 처리 */
    stream = fopen(filename, "r");
    if (stream = NULL)
    {
        printf("File not opened...\n");
        return FALSE;
    }

    /* 버퍼에 대입 : p_buf - character_buf < BUF_LEN - 1 ? */
    while (ch = fgetc(stream) != EOF && p_buf - character_buf < BUF_LEN - 1) {
        *p_buf = ch; /* 파일에서 문자들 싹 가져옴 */
        ++p_buf;
    }
    *p_buf = '\0';

    /* 내용 : v1형식? v2형식? v3형식? 함수포인터! */
    /* read_num = fread(names, sizeof(names[0]), NUM_NAMES, stream); */
    if (find_word(character_buf, "|") == TRUE) {
        version = 3;
    } else if (find_word(character_buf, "id") == TRUE) {
        version = 1;
    } else if (find_word(character_buf, "name") == TRUE) {
        version = 2;
    } else {
        return FALSE;
    }






    fclose(stream);
}

uint_t atoi(const char* str) {
    uint_t res;
    while (str != '\0' && *str >= '0' && *str <= '9') {
        res = (res * 10) + (*str - '0');
    }
    return res;
}

int operate_version1(const char* token, character_v3_t* character){
    /* e.g. lvl:10 */
    char key[6];
    char value_c[4];
    char* p = key;
    uint_t value_i = 0;

    while (token != ':') {
        *p = *token;
        ++p;
        ++token;
    }
    *p = '\0';                      /* key(lvl) */

    ++token;
    p = value_c;
    while (token != '\0') {
        *p = *token;
        ++p;
        ++token;
    }
    *p = '\0';
    value_i = atoi(value_c);        /* value_i(10) */

    /*
    if (strcmp(key, "id") == 0) {
        character.name = "player_";
        strcat(character.name, value_c);
    } else if (strcmp(key, "lvl") == 0) {
        character.level = value_i;
    } else if (strcmp(key, "hp") == 0) {
        character.level = value_i;
    } else if (strcmp(key, "mp") == 0) {
        character.level = value_i;
    } else if (strcmp(key, "str") == 0) {
        character.level = value_i;
    } else if (strcmp(key, "dex") == 0) {
        character.level = value_i;
    } else if (strcmp(key, "intel") == 0) {
        character.level = value_i;
    } else if (strcmp(key, "def") == 0) {
        character.level = value_i;
    } else {
        return FALSE;
    }
    */

    return TRUE;
}

int version1(const char* buf, character_v3_t* character) {
    char* token = strtok(buf, ","); /* e.g. lvl:10 */

    while (token != '\0') {
        token = strtok(NULL, ",");
    }

}
