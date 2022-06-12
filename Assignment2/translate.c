#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "translate.h"

#define MAX_LENGTH (512)

int translate(int argc, const char** argv)
{
    int i = 0;
    int j = 0;
    int format = 0;
    int range = 0;
    char set1[MAX_LENGTH] = { '\0', };
    char set2[MAX_LENGTH] = { '\0', };
    char temp[1024];
    char* ptr_tr;
    error_code_t err;

    /* 조건식) '플래그' 검증 */
    /* 1. argv[1]는 유효한가? 2. *argv[1]는 -로 시작하는가? (3. 단일플래그?) */
    /* cf. 복합플래그는 어떻게? strncmp? */
    if (argc > 1 && *argv[1] == '-' && strlen(argv[1]) == 2) {
        /* e.g. "-i" */
        switch (*(argv[1] + 1)) {
        case 'i':
            break;
        default:
            err = ERROR_CODE_INVALID_FLAG;
            print_error_code(err);
            return err;
        }
        /*플래그가 살아있을땐 인자 수를 +1로 고려하라 */
        ++i;
    }

    /* 조건식) 전달하는 '인자 수' 규격 검증 */
    if (argc != 3 + i) {
        err = ERROR_CODE_WRONG_ARGUMENTS_NUMBER;
        print_error_code(err);
        return err;
    }

    /* 조건식) 각 인자들의 '인자 길이' 규격 검증 */
    for (j = 1; j < argc; ++j) {
        if (strlen(argv[j]) > MAX_LENGTH - 1) {
            err = ERROR_CODE_ARGUMENT_TOO_LONG;
            print_error_code(err);
            return err;
        }
    }

    /* (const char형의) 문자 집합이 들어있는 인자를 set1, set2로 복사 */
    strncpy(set1, argv[1 + i], MAX_LENGTH - 1);
    strncpy(set2, argv[2 + i], MAX_LENGTH - 1);
    /* fprintf(stderr, "%s %s\n", set1, set2); */

    /* 대소문자 무시 플래그 (1단계) */
    if (strncmp(argv[1], "-i", 2) == 0) {
        decapitalize(set1);
    }

    /* 조건식) '이스케이프 코드' 규격 검증 */
    /* cf. format이 TRUE이려면, set1, set2 모두 검증 이상무여야함 */
    format = check_escape_seq(set1) & check_escape_seq(set2);
    if (format != TRUE) {
        err = ERROR_CODE_INVALID_FORMAT;
        print_error_code(err);
        return err;
    }

    /* 조건식) '범위' 유효성 검증 */
    range = check_range(set1) & check_range(set2);
    if (range != TRUE) {
        err = ERROR_CODE_INVALID_RANGE;
        print_error_code(err);
        return err;
    }

    /* '기초 동작' : 컴퓨터가 처리 가능하도록 인자들을 다듬음 */
    trim_argv(set1, set2);
    /*
    fprintf(stderr, "%s %s\n", set1, set2);
    fprintf(stderr, "%zd %zd\n", strlen(set1), strlen(set2));
    */

    while (1) {
        ptr_tr = fgets(temp, sizeof(temp), stdin);
        if (ptr_tr == NULL) {
            clearerr(stdin);
            break;
        }

        /* 실질적인 변환 알고리즘, 한 줄씩 받고 출력함 (convert, convert_cap) */
        /* else : 대소문자 무시 플래그 (2단계) */
        /* e.g. abc fgh (a->f, A->f, b->g, B->g, c->h, C->h) */
        if (strncmp(argv[1], "-i", 2) != 0) {
            convert(ptr_tr, set1, set2);
        } else {
            convert_cap(ptr_tr, set1, set2);
        }

        fputs(temp, stdout);
    }

    return 0;
}

void print_error_code(error_code_t err)
{
    switch (err) {
    case 1:
        fprintf(stderr, "ERROR_CODE_WRONG_ARGUMENTS_NUMBER\n");
        break;
    case 2:
        fprintf(stderr, "ERROR_CODE_INVALID_FLAG\n");
        break;
    case 3:
        fprintf(stderr, "ERROR_CODE_INVALID_FORMAT\n");
        break;
    case 4:
        fprintf(stderr, "ERROR_CODE_ARGUMENT_TOO_LONG\n");
        break;
    case 5:
        fprintf(stderr, "ERROR_CODE_INVALID_RANGE\n");
        break;
    default:
        assert(0);
        break;
    }
}

void decapitalize(char* set1)
{
    char* ptr = set1;
    while (*ptr != '\0') {
        if (65 <= *ptr && *ptr <= 90) {
            *ptr += 32;
        }
        ++ptr;
    }
}

int check_escape_seq(char* set)
{
    /* ptr를 활용한 이스케이프 문자 검사 */
    char* ptr = set;

    while (*ptr != '\0') {
        if (*ptr == 92) {
            /* '\' 발견한 자리에 checkpoint_ptr를 심어두는 이유? */
            /* 아래의 while문 처리 이후 (원래 그 자리로) ptr를 다시 복귀시키고자 함 */
            char* checkpoint_ptr = ptr;
            switch (*(ptr + 1)) {
            case 92: /* backslash(\) */
                *ptr = '\x5c';
                break;
            case 'a':
                *ptr = '\x07';
                break;
            case 'b':
                *ptr = '\x08';
                break;
            case 'f':
                *ptr = '\x0c';
                break;
            case 'n':
                *ptr = '\x0a';
                break;
            case 'r':
                *ptr = '\x0d';
                break;
            case 't':
                *ptr = '\x09';
                break;
            case 'v':
                *ptr = '\x0b';
                break;
            case 39: /* quote(') */
                *ptr = '\x27';
                break;
            case 34: /* dubquotes(") */
                *ptr = '\x22';
                break;
            default: /* 유효하지 않은 이스케이프 문자 */
                return FALSE;
            }
            ++ptr;

            /* 이스케이프 문자 기준, 이후의 'set'문자열 전부 좌측 한 칸씩 이동 */
            while (*ptr != '\0' && ptr - set < MAX_LENGTH - 1) {
                *ptr = *(ptr + 1);
                ++ptr;
            }
            *ptr = '\0';
            ptr = checkpoint_ptr;
        }
        ++ptr;
    }
    return TRUE;
}

int check_range(char* set)
{
    /* 참고로, 이미 '인자 길이' 검증이 끝난 상태이므로, strcpy 사용함 */
    char* ptr = set;
    char temp[MAX_LENGTH];

    /* 첫 번째 붙임표는 범위 지정자가 아니므로 pass */
    ++ptr;
    while (*ptr != '\0') {
        if (*ptr == '-') {
            if (*(ptr + 1) == '\0') {
                /* 마지막 붙임표도 범위 지정자가 아니므로 pass */
                break;
            } else if (*(ptr - 1) == *(ptr + 1)) {
                /* e.g. y-y를 y로 바꿔도 결국은 같음 */
                strcpy(temp, ptr + 2);
                strcpy(ptr, temp);
            } else if (*(ptr - 1) < *(ptr + 1)) {
                /* e.g. a-e는 abcde와 같음 */
                size_t letters_count = *(ptr + 1) - *(ptr - 1);
                strcpy(temp, ptr + 2);
                while (letters_count > 0) {
                    *ptr = *(ptr - 1) + 1;
                    ++ptr;
                    --letters_count;
                }
                strcpy(ptr, temp);
            } else if (*(ptr - 1) > *(ptr + 1)) {
                /* e.g. z-a는 유효하지 않은 범위임 */
                return FALSE;
            }
        }
        ++ptr;
    }
    return TRUE;
}

void trim_argv(char* set1, char* set2)
{
    char* target_ptr1 = NULL;
    char* trim_ptr1 = set1;
    char* trim_ptr2 = set2;
    size_t overlap_count = 0u;

    /* 문자 집합 갯수 맞춰주기 (기초 동작) */
    while(trim_ptr1 != '\0' && trim_ptr2 != '\0'){
        ++trim_ptr1;
        ++trim_ptr2;
    }

    if (trim_ptr1 == '\0') {
        /* e.g. abc\0 fghijk\0 -> abc\0 fgh\0... */
        *trim_ptr2 = '\0';
    } else {
        while (*trim_ptr1 != '\0') {
            /* '\0'을 뒤로 한 칸 미루고, 마지막 문자를 집어넣을 것 */
            /* e.g. abcde\0 fgh\0 -> abcde\0 fghhh\0 */
            *(trim_ptr2 + 1) = *trim_ptr2;
            *trim_ptr2 = *(trim_ptr2 - 1);
            ++trim_ptr1;
            ++trim_ptr2;
        }
        *trim_ptr2 = '\0';
    }

    /* '\0' 위치로부터 왼쪽 한 칸, 즉 문자열의 마지막 글자의 위치로 이동 */
    target_ptr1 = --trim_ptr1;

    while (target_ptr1 - set1 > 0) {
        /* target_ptr가 a를 가리킨다면, 중복되는 a는 싹 소거될 것 (오른쪽에서 왼쪽 순) */
        /* 여기서 trim_ptr1은 소거될 a를 색출하는 역할을 함 */
         /* e.g. abada\0 ijkbc\0 -> bda\0 jbc\0 */
        trim_ptr1 = target_ptr1 - 1;
        while (trim_ptr1 - set1 >= 0) {
            /* 스캔해서 중첩되는 문자 발견? 일단 제거하고, 한 칸씩 우측으로 밀어붙인다 */
            if (*trim_ptr1 == *target_ptr1 && *target_ptr1 != '\0') {
                char* checkpoint_ptr = trim_ptr1;
                while (trim_ptr1 - set1 > 0) { /* 첫 글자의 위치까지 가면 치환 대상이 없다 */
                    *trim_ptr1 = *(trim_ptr1 - 1);
                    *(set2 + (trim_ptr1 - set1)) = *(set2 + (trim_ptr1 - set1) - 1);
                    --trim_ptr1;
                }
                trim_ptr1 = checkpoint_ptr;
                set1[overlap_count] = '\0';
                set2[overlap_count] = '\0';
                ++overlap_count;
            } else {
                --trim_ptr1;
            }
        }
        --target_ptr1;
    }
    /* fprintf(stderr, "%zd\n", overlap_count); */

    /* 이제 중첩된 칸 수 만큼을 정리해 줄 시간이다 */
    trim_ptr1 = set1;
    trim_ptr2 = set2;

    if (overlap_count > 0) {
        while (*(trim_ptr1 + overlap_count) != '\0') {
            *trim_ptr1 = *(trim_ptr1 + overlap_count);
            *trim_ptr2 = *(trim_ptr2 + overlap_count);
            ++trim_ptr1;
            ++trim_ptr2;
        }
        *trim_ptr1 = '\0';
        *trim_ptr2 = '\0';
    }
}

void convert(char* ptr_tr, char* set1, char* set2)
{
    char* ptr1 = set1;
    char* ptr2 = set2;

    /* (한 줄을 놓고) 하나 하나 한 글자씩 검사 그리고 변환 */
    while (*ptr_tr != '\0') {
        while (*ptr1 != '\0') {
            if (*ptr_tr == *ptr1) {
                *ptr_tr = *ptr2;
                break;
            }
            ++ptr1;
            ++ptr2;
        }
        ptr1 = set1;
        ptr2 = set2;
        ++ptr_tr;
        /* fprintf(stderr,"%c\n", *ptr_tr); */
    }
}

void convert_cap(char* ptr_tr, char* set1, char* set2)
{
    char* ptr1 = set1;
    char* ptr2 = set2;

    /* 대소문자 관련 내용을 제외하면, 위와 동일 */
    while (*ptr_tr != '\0') {
        while (*ptr1 != '\0') {
            if (*ptr_tr == *ptr1 || *ptr_tr == *ptr1 - 32) {
                *ptr_tr = *ptr2;
                break;
            }
            ++ptr1;
            ++ptr2;
        }
        ptr1 = set1;
        ptr2 = set2;
        ++ptr_tr;
        /* fprintf(stderr,"%c\n", *ptr_tr); */
    }
}
