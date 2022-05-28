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

/* str, p를 char*에서 const char*로 바꿈 (길이구할땐 값접근X) */
size_t get_str_length(const char* str)
{
    const char* p = str;

    while (*p++ != '\0') {
    }
    return p - str - 1;
}

/* index_of 함수에서 word문자열이 더 길면 안됨을 이미 가정했음 */
size_t cmp_str(const char* str, const char* word)
{
    while (*word != '\0' && *str == *word) {
        ++str;
        ++word;
    }
    return *word == '\0' ? TRUE : FALSE; /* word가 먼저 끝남 */
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

    if (str_length < word_length) {
        return -1;
    }

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
            /* 빈칸이 연속적으로 나열되었다면, p_ongoing은 지나감 (for문 패쓰) */
            /* 아래의 반복문이 돌 때, p_ongoing - str >= 0이게끔 설계됨 */
            for (i = 0; i < (size_t)(p_ongoing - str) / 2; ++i) {
                swap(str + i, p_ongoing - 1 - i);
            }
            str = p_ongoing + 1;
        }
        ++p_ongoing;
    }

    if (*p_ongoing == '\0') {
        for (i = 0; i < (size_t)(p_ongoing - str) / 2; ++i) {
            swap(str + i, p_ongoing - 1 - i);
        }
    }
}

char* tokenize(char* str_or_null, const char* delims)
{
    static char* s_p_ongoing;
    const char* p_delims = delims;

    /* s_p_ongoing이 주소를 가리키는 위치를 '새로쓰거나', '이어하거나'.  */
    str_or_null != NULL ? (s_p_ongoing = str_or_null) : (str_or_null = s_p_ongoing);

    /* s_p_ongoing 포인팅이 NULL(무효)이거나 '\0'(문자열의끝)? NULL을 반환 */
    if (s_p_ongoing == NULL || *s_p_ongoing == '\0') {
        return NULL;
    }

    /* 문자열에 구분 문자가 연속적으로 나열되었다면, s_p_ongoing은 지나감 */
    for (s_p_ongoing = str_or_null; *s_p_ongoing != '\0'; ++s_p_ongoing) {
        for (p_delims = delims; *p_delims != '\0'; ++p_delims) {
            if (*s_p_ongoing == *p_delims) {
                break;
            }
        }
        if (*p_delims == '\0') {
            break;
        }
    }

    /* 시작점 세팅, 실질적인 토큰화 알고리즘 (s_p_ongoing의 행보에 주목) */
    str_or_null = s_p_ongoing;
    for (s_p_ongoing = str_or_null; *s_p_ongoing != '\0'; ++s_p_ongoing) {
        for (p_delims = delims; *p_delims != '\0'; ++p_delims) {
            if (*s_p_ongoing == *p_delims) {
                *s_p_ongoing++ = '\0';
                return str_or_null; /* 구분자를 만난 경우 */
            }
        }
    }
    return str_or_null; /* 구분자가 아닌 '\0'(문자열의끝)을 만난 경우 */
}

char* reverse_tokenize(char* str_or_null, const char* delims)
{
    char* p_reverse_token;
    p_reverse_token = tokenize(str_or_null, delims);
    /* tokenize함수가 NULL값 반환(무효or문자열의끝)? 이함수 역시 NULL값 반환 */
    if (p_reverse_token == NULL) {
        return NULL;
    }
    reverse(p_reverse_token);
    return p_reverse_token;
}
