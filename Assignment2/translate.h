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


void trim_argv(char* set1, char* set2);

void decapitalize(char* set1);

void substitute(char* ptr_tr, char* set1, char* set2);

void substitute_cap(char* ptr_tr, char* set1, char* set2);

void escape_sequence(char* set1);

void set_range(char* set1);

int translate(int argc, const char** argv);

#endif /* TRANSLATE_H */
