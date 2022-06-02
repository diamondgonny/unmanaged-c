#include <stdio.h>
#include <string.h>
#include "translate.h"

/*
void trim_argv(char* source, char* repl)
{
    char* trim_ptr;
}
*/

void substitute(char* ptr, const char* source, const char* repl)
{
    while (*ptr != '\0') {
            if (*ptr == *source) {
                *ptr = *repl;
            }
            /* fprintf(stderr,"%c\n", *ptr); */
            ++ptr;
        }
}





int translate(int argc, const char** argv)
{
    int i = 0;
    char buf[512];
    char set1[512];
    char set2[512];
    char *ptr;

    /* 플래그 판별을 위한 조건식 */
    if (*argv[1] == '-') {
        ++i;
    }

    /* argv (source, repl)의 재구성 */
    if (strlen(argv[1]))







    while (1) {
        ptr = fgets(buf, sizeof(buf), stdin);
        if (ptr == NULL) {
            break;
        }
        substitute(ptr, argv[1], argv[2]);

        fprintf(stdout, "%s", str);
    }

    return 0;
}
