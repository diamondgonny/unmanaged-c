#include <assert.h>
#include <string.h>
#include "my_string.h"

#define _CRT_SECURE_NO_WARNINGS

int main(void)
{
    const char* str = "We all live in a yellow    submarine ";
    char str_cpy[38];
    const char* token;

    strncpy(str_cpy, str, 37);
    str_cpy[37] = '\0';

/*
    reverse(str_cpy);
    assert(strcmp("enirambus wolley a ni evil lla eW", str_cpy) == 0);

    assert(index_of(str, "all ") == 3);
    assert(index_of(str, "marine") == 27);
    assert(index_of(str, "all good") == -1);
    assert(index_of(str, "marinett") == -1);

    reverse(str_cpy);
*/
    assert(strcmp(str_cpy, str) == 0);

    reverse_by_words(str_cpy);
    printf("'%s'\n", str_cpy);

    /* assert(strcmp("eW lla evil ni a wolley enirambus", str_cpy) == 0); */
    reverse_by_words(str_cpy);
    printf("'%s'\n", str_cpy);

    assert(strcmp(str_cpy, str) == 0);
/*
    assert(tokenize(NULL, " ,.!") == NULL);

    token = tokenize(str_cpy, " ,.!");
    assert(token == str_cpy);
    assert(strcmp(token, "We") == 0);

    token = tokenize(NULL, " ,.!");
    assert(token == str_cpy + 3);
    assert(strcmp(token, "all") == 0);

    token = tokenize(NULL, " ,.!");
    assert(token == str_cpy + 7);
    assert(strcmp(token, "live") == 0);

    token = tokenize(NULL, " ,.!");
    assert(token == str_cpy + 12);
    assert(strcmp(token, "in") == 0);

    token = tokenize(NULL, " ,.!");
    token = tokenize(NULL, " ,.!");
    assert(token == str_cpy + 17);
    assert(strcmp(token, "yellow") == 0);

    token = tokenize(NULL, " ,.!");
    printf("'%s'\n", token);
    assert(token == str_cpy + 26);
    printf("'%s'\n", token);
    assert(strcmp(token, "submarine") == 0);
    printf("'%s'\n", token);
*/
    return 0;
}
