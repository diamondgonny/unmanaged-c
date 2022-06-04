#include <stdio.h>
#include <string.h>
#include "translate.h"

#define MAX_LENGTH (512)

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
    }
}

void trim_argv(char* set1, char* set2)
{
    char* target_ptr1 = NULL;
    char* trim_ptr1 = set1;
    char* trim_ptr2 = set2;
    size_t overlap_count = 0u;

    if (strlen(set1) < strlen(set2)) {
        while (*trim_ptr1 != '\0' && trim_ptr1 - set1 < MAX_LENGTH - 1) { /* '\0' */
            ++trim_ptr1;
            ++trim_ptr2;
        }
        *trim_ptr2 = '\0';
    } else {
        while (*trim_ptr1 != '\0' && trim_ptr1 - set1 < MAX_LENGTH - 1) { /* '\0' */
            if (*trim_ptr2 == '\0') {
                *(trim_ptr2 + 1) = *trim_ptr2;
                *trim_ptr2 = *(trim_ptr2 - 1);
            }
            ++trim_ptr1;
            ++trim_ptr2;
        }
        *trim_ptr2 = '\0';
    }

    /* '\0'으로부터 좌측 한 칸, 즉 문자열의 마지막 글자의 위치로 이동한다 */
    /* 그리고 오른쪽에서 왼쪽 순으로 중첩되는 문자 정리를 한다 */
    target_ptr1 = --trim_ptr1;

    while (target_ptr1 - set1 > 0) { /* 첫 글자의 위치까지 가면 비교 대상이 없다 */
        trim_ptr1 = target_ptr1 - 1;
        while (trim_ptr1 - set1 >= 0) {
            /* 스캔해서 중첩되는 문자 발견? 일단 현 위치 기준, 한 칸씩 우측으로 밀어붙인다 */
            if (*trim_ptr1 == *target_ptr1 && *target_ptr1 != '\0') {
                char* comeback_ptr = trim_ptr1;
                while (trim_ptr1 - set1 > 0) { /* 첫 글자의 위치까지 가면 치환 대상이 없다 */
                    *trim_ptr1 = *(trim_ptr1 - 1);
                    *(set2 + (trim_ptr1 - set1)) = *(set2 + (trim_ptr1 - set1) - 1);
                    --trim_ptr1;
                }
                trim_ptr1 = comeback_ptr;
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

void substitute(char* ptr_tr, char* set1, char* set2)
{
    char* ptr1 = set1;
    char* ptr2 = set2;
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

void substitute_cap(char* ptr_tr, char* set1, char* set2)
{
    char* ptr1 = set1;
    char* ptr2 = set2;
    while (*ptr_tr != '\0') {
        while (*ptr1 != '\0') {
            if (*ptr_tr == *ptr1 || *ptr_tr == *ptr1 - 32) {
                *ptr_tr = *ptr2;
                break;
            }
            ++ptr1;
            ++ptr2;
        }
        ++ptr_tr;
        /* fprintf(stderr,"%c\n", *ptr_tr); */
    }
}

int escape_sequence(char* set)
{
    char* ptr = set;
    while (*ptr != '\0') {
        if (*ptr == 92) {
            char* comeback_ptr = ptr;
            switch (*(ptr + 1)) {
            case 92: /* backslash */
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
            case 39: /* quote */
                *ptr = '\x27';
                break;
            case 34: /* dubquotes */
                *ptr = '\x22';
                break;
            default:
                return FALSE;
            }
            ++ptr;

            while (*ptr != '\0' && ptr - set < MAX_LENGTH - 1) {
                *ptr = *(ptr + 1);
                ++ptr;
            }
            *ptr = '\0';
            ptr = comeback_ptr;
        }
        ++ptr;
    }
    return TRUE;
}

int set_range(char* set)
{
    char* ptr = set;
    char temp[MAX_LENGTH];

    /* 이스케이프 문자 관련 일단 제외 */
    /* 입력 가능한 선에서(33이상), 범위 알고리즘 가동...(길이통제?) */
    ++ptr;
    while (*ptr != '\0') {
        if (*ptr == '-' && *(ptr - 1) > 32 && *(ptr + 1) > 32) {
            if (*(ptr - 1) == *(ptr + 1)) {
                strcpy(temp, ptr + 2);
                strcpy(ptr, temp); /* 처음에 strcat 시도했으나, 덮어쓰는 strcpy가 맞음 */
            } else if (*(ptr - 1) < *(ptr + 1)) {
                size_t letters_count = *(ptr + 1) - *(ptr - 1);
                strcpy(temp, ptr + 2);
                while (letters_count > 0) {
                    *ptr = *(ptr - 1) + 1;
                    ++ptr;
                    --letters_count;
                }
                strcpy(ptr, temp);
            } else {
                return FALSE;
            }
        }
        ++ptr;
    }
    return TRUE;
}

int translate(int argc, const char** argv)
{
    int i = 0;
    int j = 0;
    int format = 0;
    int range = 0;
    char buf[512];
    char set1[MAX_LENGTH] = { '\0', };
    char set2[MAX_LENGTH] = { '\0', };
    char* ptr_tr;
    error_code_t err;

    /* 플래그 판별을 위한 조건식 : if (*argv[1] == '-') 로 첫 시도, seg-err... */
    /* " : if (strncmp(argv[1], "-i", 2) == 0), ok */
    /* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */
    if (argc > 1 && *argv[1] == '-' && strlen(argv[1]) == 2) {
        switch (*(argv[1] + 1)) {
        case 'i':
            break;
        default:
            err = ERROR_CODE_INVALID_FLAG;
            print_error_code(err);
            return err;
        }
        ++i;
    }

    /* 커맨드 라인 매개변수가 불충분할 경우 */
    if (argc < 3 + i) {
        err = ERROR_CODE_WRONG_ARGUMENTS_NUMBER;
        print_error_code(err);
        return err;
    }

    for (j = 1; j < argc; ++j) {
        if (strlen(argv[i]) > MAX_LENGTH) {
            err = ERROR_CODE_ARGUMENT_TOO_LONG;
            print_error_code(err);
            return err;
        }
    }

    /* i/o 문자열 복사 */
    /* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */
    strncpy(set1, argv[1 + i], MAX_LENGTH - 1);
    strncpy(set2, argv[2 + i], MAX_LENGTH - 1);

    /* 대소문자 무시 플래그 (1) */
    if (strncmp(argv[1], "-i", 2) == 0) {
        decapitalize(set1);
    }

    /* 이스케이프 시퀀스 처리 */
    format = escape_sequence(set1) & escape_sequence(set2);
    if (format != TRUE) {
        err = ERROR_CODE_INVALID_FORMAT;
        print_error_code(err);
        return err;
    }

    /* 범위 */
    range = set_range(set1) & set_range(set2);
    if (range != TRUE) {
        err = ERROR_CODE_INVALID_RANGE;
        print_error_code(err);
        return err;
    }

    /* 기초 동작 : argv (source, repl)의 재구성 */
    /* length of i/o string should be restricted */
    trim_argv(set1, set2);
    fprintf(stderr, "%s %s\n", set1, set2);

    while (1) {
        ptr_tr = fgets(buf, sizeof(buf), stdin);
        if (ptr_tr == NULL) {
            clearerr(stdin);
            break;
        }
        /* else : 대소문자 무시 플래그 (2) */
        if (strncmp(argv[1], "-i", 2) != 0) {
            substitute(ptr_tr, set1, set2);
        } else {
            substitute_cap(ptr_tr, set1, set2);
        }

        /* BOF 문제없이 문자열 읽기? */
        fprintf(stdout, "%s", buf);
    }

    return 0;
}
