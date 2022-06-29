#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"

#define INCREMENT (2048)

char** tokenize_malloc(const char* str, const char* delim)
{
    size_t i;
    size_t max_token = INCREMENT;
    char* str_tmp = malloc(strlen(str) + 1);
    char* p_str;
    char** pa_tok = malloc(max_token);
    char** pp;

    strcpy(str_tmp, str);
    p_str = str_tmp;
    pp = pa_tok;

    p_str = strtok(str_tmp, delim);
    if (p_str == NULL) {
        goto first_null;
    }
    *pp = (char*)malloc(strlen(p_str) + 1);
    strcpy(*pp, p_str);
    /* printf("%s\n", *pp); */
    ++pp;
    p_str = strtok(NULL, delim);

    for (i = 1; p_str != NULL; ++i, ++pp) {
        if (i == max_token) {
            char** tmp;
            max_token += INCREMENT;
            tmp = malloc(max_token * sizeof(char*));
            memcpy(tmp, pa_tok, i * sizeof(char*));
            free(pa_tok);
            pa_tok = tmp;
            pp = pa_tok + i;
        }
        *pp = (char*)malloc(strlen(p_str) + 1);
        strcpy(*pp, p_str);
        /* printf("%s\n", *pp); */
        p_str = strtok(NULL, delim);
    }

first_null:
    if (p_str == NULL) {
        *pp = (char*)malloc(1);
        *pp = NULL;
    }

    free(str_tmp);

    return pa_tok;
}
