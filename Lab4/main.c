#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "my_string.h"

#define _CRT_SECURE_NO_WARNINGS


void print_address(void* addr1, void* addr2) {
    printf("	Return value: %p", addr1);
    if (addr1 == addr2) {
        printf(" == ");
    } else {
        printf(" != ");
    }
    printf("%p(Expected value)\n\n", addr2);
}
 
int main(void)
{
    char str[] = "Oh happy day! My lovely day!";
    char* token;
    int is_passed = 1;
 
    /* &str[0]을 반환. 토큰은 "hO" */
    token = reverse_tokenize(str, " !");
    printf("\"%s\" == \"%s\"?", token, "hO");
    if (strcmp(token, "hO") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[0]);
    if (token != &str[0]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /* &str[3]을 반환. 토큰은 "yppah" */
    token = reverse_tokenize(NULL, " !");
    printf("\"%s\" == \"%s\"?", token, "yppah");
    if (strcmp(token, "yppah") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[3]);
    if (token != &str[3]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /* &str[9]을 반환. 토큰은 "yad" */
    token = reverse_tokenize(NULL, " !");
    printf("\"%s\" == \"%s\"?", token, "yad");
    if (strcmp(token, "yad") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[9]);
    if (token != &str[9]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /* &str[14]을 반환. 토큰은 "yM" */
    token = reverse_tokenize(NULL, " !");
    printf("\"%s\" == \"%s\"?", token, "yM");
    if (strcmp(token, "yM") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[14]);
    if (token != &str[14]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /* &str[17]을 반환. 토큰은 "lovely" */
    token = tokenize(NULL, " !");
    printf("\"%s\" == \"%s\"?", token, "lovely");
    if (strcmp(token, "lovely") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[17]);
    if (token != &str[17]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /* &str[24]을 반환. 토큰은 "yad" */
    token = reverse_tokenize(NULL, " !");
    printf("\"%s\" == \"%s\"?", token, "yad");
    if (strcmp(token, "yad") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[24]);
    if (token != &str[24]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /* NULL을 반환. "!\0"이어서. Delims 다음으로 넘어가도 끝만 나옴. */
    token = reverse_tokenize(NULL, " !");
    printf("\"%s\" == \"%s\"?", token, NULL);
    if (token == NULL) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, NULL);
    if (token != NULL) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /*
    	토큰화가 모두 끝난 빈 문자열("". 즉, '\0')이면,
    	NULL을 반환
	*/
    /* NULL을 반환. ""('\0')이어서. */
    token = reverse_tokenize(token, " !");
    printf("\"%s\" == \"%s\"?", token, NULL);
    if (token == NULL) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, NULL);
    if (token != NULL) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /*
    	이미 토큰화가 다 된(delims를 만나지 않고, '\0'으로 끝나는 연속된 문자들) 단위라도,
    	시작위치 제대로 반환
	*/
    /* &str[0]을 반환. 토큰은 "hO" */
    token = tokenize(str, " !");
    printf("\"%s\" == \"%s\"?", token, "hO");
    if (strcmp(token, "hO") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[0]);
    if (token != &str[0]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
    /*
    	이미 토큰화가 다 된(delims를 만나지 않고, '\0'으로 끝나는 연속된 문자들) 단위라도,
    	단위를 정상적으로 뒤집고, 시작위치 제대로 반환
	*/
    /* &str[0]을 반환. 토큰은 "Oh" */
    token = reverse_tokenize(str, " !");
    printf("\"%s\" == \"%s\"?", token, "Oh");
    if (strcmp(token, "Oh") == 0) {
        printf(" - OK\n");
    } else {
        printf(" - Wrong!!!\n");
        is_passed = 0;
    }
    print_address(token, &str[0]);
    if (token != &str[0]) {
        is_passed = 0;
    }
    if (is_passed == 0) {
        goto end;
    }
 
end:
    if (is_passed == 1) {
        /* 위 테스트를 모두 성공하면 이 메시지를 출력 */
        printf("~~~ If you see this message, you passed all tokenize test. ~~~\n");
        return 0;
    } else {
        /* 위 테스트 중 하나라도 실패하면, 바로 goto로 여기로 오면서 이 실패 메시지를 출력 */
        printf("!!! You may correct your function. !!!\n");
        return 1;
    }
}
