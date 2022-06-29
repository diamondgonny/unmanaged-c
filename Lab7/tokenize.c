#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"

char** tokenize_malloc(const char* str, const char* delim)
{
    char str_tmp[100];
    char* p_str;
    char** pa_tok = malloc(30);
    char** pp;

    strcpy(str_tmp, str);
    p_str = str_tmp;
    pp = pa_tok;

    p_str = strtok(str_tmp, delim);
    *pp = (char*)malloc(strlen(p_str) + 1);
    strcpy(*pp, p_str);
    /* printf("%s\n", *pp++); */
    p_str = strtok(NULL, delim);

    while (p_str != NULL) {
        *pp = (char*)malloc(strlen(p_str) + 1);
        strcpy(*pp, p_str);
        /* printf("%s\n", *pp++); */
        p_str = strtok(NULL, delim);
    }

    return pa_tok;
}

/* 1차 합격 */
