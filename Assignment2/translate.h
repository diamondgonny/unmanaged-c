#ifndef TRANSLATE_H
#define TRANSLATE_H

#define TRUE (1)
#define FALSE (0)

typedef enum error_code {
    ERROR_CODE_WRONG_ARGUMENTS_NUMBER = 1,
    ERROR_CODE_INVALID_FLAG,
    ERROR_CODE_INVALID_FORMAT,
    ERROR_CODE_ARGUMENT_TOO_LONG,
    ERROR_CODE_INVALID_RANGE
} error_code_t;

/*
    ERROR_CODE_WRONG_ARGUMENTS_NUMBER: translate 프로그램을 호출할 때 전달 된 인자 수가 틀림
    ERROR_CODE_INVALID_FLAG: 지원하지 않는 플래그가 지정됨
    ERROR_CODE_INVALID_FORMAT: 인자들의 포맷이 틀림
    ERROR_CODE_ARGUMENT_TOO_LONG: 너무 긴 인자가 존재
    ERROR_CODE_INVALID_RANGE: 올바르지 않은 문자열 범위를 사용함
*/

int translate(int argc, const char** argv);

void print_error_code(error_code_t err);

void decapitalize(char* set1);

int check_escape_seq(char* set);

int check_range(char* set);

void trim_set(char* set1, char* set2);

void convert(char* ptr_tr, char* set1, char* set2);

void convert_cap(char* ptr_tr, char* set1, char* set2);

#endif /* TRANSLATE_H */
