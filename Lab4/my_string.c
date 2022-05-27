#include <stddef.h>
#include "my_string.h"
#define TRUE (1)
#define FALSE (0)

void swap(char* a, char* b)
{
    char temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

/* str, p를 char*에서 const char*로 변경 (why?) */
size_t get_str_length(const char* str)
{
    const char* p = str;

    while (*p++ != '\0') {
    }
    return p - str - 1;
}

size_t cmp_str(const char* str, const char* word)
{
    while (*word != '\0' && *str == *word) {
        ++str;
        ++word;
    }
    return *word == '\0' ? TRUE : FALSE;
}

void reverse(char* str)
{
    size_t i;
    size_t str_length = get_str_length(str);

    for (i = 0; i < (str_length / 2); ++i) {
        swap(str + i, str + str_length - 1 - i);
    }
}

int index_of(const char* str, const char* word)
{
    size_t i;
    size_t result = 0;
    size_t str_length = get_str_length(str);
    size_t word_length = get_str_length(word);

    for (i = 0; i < str_length - word_length + 1; ++i) {
        result = cmp_str(str, word);
        if (result == TRUE) {
            return i;
        } else {
            ++str;
        }
    }
    return -1;
}

void reverse_by_words(char* str)
{
    size_t i;
    char* p_ongoing = str;

    while (*p_ongoing != '\0') {
        if (*p_ongoing == ' ') {
            for (i = 0; i < (p_ongoing - str) / 2; ++i) {
                swap(str + i, p_ongoing - 1 - i);
            }
            /*
            while (*(p_ongoing + 1) == ' ') {
                ++p_ongoing;
            } */
            str = p_ongoing + 1;
        }
        ++p_ongoing;
    }

    if (*p_ongoing == '\0') {
        --p_ongoing;
        for (i = 0; i < (p_ongoing - str) / 2; ++i) {
            swap(str + i, p_ongoing - i);
        }
    }
}

char* tokenize(char* str_or_null, const char* delims)
{
    static char* s_p_ongoing;
    const char* p_delims = delims;

    /* [반환값] 스타또 포인트 (동기화 : 새로하기 vs 이어하기) */
    str_or_null != NULL ? (s_p_ongoing = str_or_null) : (str_or_null = s_p_ongoing);

    /* 현재위치 NULL 이거나 현재값 '\0'? NULL을 반환 */
    if (s_p_ongoing == NULL || *s_p_ongoing == '\0') {
        return NULL;
    }

    /* 현재값 구분자? 구분자이면 루프돌고(좌항), 비구분자이면 탈출(우항). */
    /* 예시)  ...'g'g..................,,,0  */
    while (*s_p_ongoing != '\0') {
        while (*p_delims != '\0') {
            if (*s_p_ongoing == *p_delims) {
                break;
            } else {
                ++p_delims;
            }
        }
        if (*p_delims != '\0') {
            ++s_p_ongoing;
        } else {
            break;
        }
    }

    /* 유효한 토큰 반환을 위한 구분자 감지 알고리즘 */
    str_or_null = s_p_ongoing;
    for (s_p_ongoing = str_or_null; *s_p_ongoing != '\0'; ++s_p_ongoing) {
        for (p_delims = delims; *p_delims != '\0'; ++p_delims) {
            if (*s_p_ongoing == *p_delims) {
                *s_p_ongoing++ = '\0';
                return str_or_null;
            }
        }
    }
    return str_or_null;
}

char* reverse_tokenize(char* str_or_null, const char* delims)
{
    char* p_reverse_token;
    p_reverse_token = tokenize(str_or_null, delims);
    if(p_reverse_token == NULL) {
        return NULL;
    }
    reverse(p_reverse_token);
    return p_reverse_token;
}
