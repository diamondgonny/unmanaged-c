#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"

#define INCREMENT (10)

/* ↓p_str */
/* ㅡㅡㅡㅡ/ㅡㅡㅡㅡㅡㅡ/ㅡㅡㅡ/ㅡ/ㅡㅡㅡ/ㅡㅡ/ㅡㅡㅡㅡ'\0' (str_tmp) */

/*  ↓pp                     */
/* pa_tok[0] -> ㅡㅡㅡㅡ/     */
/* pa_tok[1] -> ㅡㅡㅡㅡㅡㅡ/  */
/* ...                      */
/* pa_tok[끝] -> (null)     */

char** tokenize_malloc(const char* str, const char* delim)
{
    size_t i;
    size_t max_token = INCREMENT;
    char* str_tmp = malloc(strlen(str) + 1);
    char* p_str;
    char** pa_tok = malloc(max_token * sizeof(char*));
    char** pp;

    strcpy(str_tmp, str);
    p_str = str_tmp;
    pp = pa_tok;

    p_str = strtok(str_tmp, delim);
    if (p_str != NULL) {
        *pp = (char*)malloc(strlen(p_str) + 1);
        strcpy(*pp, p_str);
        p_str = strtok(NULL, delim);
        ++pp;
    } else {
        goto mamuri;
    }

    /* i = 1 카운트 세는 조건? strcpy 횟수. 위에서 이미 한 번 수행함 */
    /* i == max_token 되면? 동적메모리 재할당. INCREMENT만큼 확장함 */
    for (i = 1; p_str != NULL; ++i, ++pp) {
        if (i == max_token) {
            char** tmp;
            max_token += INCREMENT;
            tmp = realloc(pa_tok, max_token * sizeof(char*));
            if (tmp != NULL) {
                pa_tok = tmp;
            }
            pp = pa_tok + i;
        }
        *pp = (char*)malloc(strlen(p_str) + 1);
        strcpy(*pp, p_str);
        p_str = strtok(NULL, delim);
    }

mamuri:
    /* 여기까지 왔으면, p_str == NULL이라고 가정 */
    *pp = NULL;
    free(str_tmp);

    return pa_tok;
}
