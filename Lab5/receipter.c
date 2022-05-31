#include <stdio.h>
#include <time.h>
#include "receipter.h"

#define FOODAMOUNT_MAX (10)
#define FOODNAME_LENGTH (25)
#define MESSAGE_LENGTH (75)

static size_t order_number = 0;
static char foodname[FOODAMOUNT_MAX][FOODNAME_LENGTH];
static double foodprice[FOODAMOUNT_MAX];
static size_t food_counter = 0;
static double tip_thanks = 0;
static char message_thanks[MESSAGE_LENGTH];

void cpy_string(int length)
{
    /* 문자열을 복사해서 붙여넣고, 끝에 '\0'을 넣어주자. length 넘어가면 짤림) */
}

int add_item(const char* name, double price)
{
    if (food_counter < FOODAMOUNT_MAX) {
        /* 2차원 배열에서의 포인터 : *(foodname + food_counter) */
        /* sscanf로 입력하면, 구분자(공백문자) 버림... */

        foodprice[food_counter] = price;
        ++food_counter;
    }
    else {
        return FALSE;
    }

    return TRUE;
}

void set_tip(double tip)
{
    tip_thanks = tip;
}

void set_message(const char* message)
{
    /* sscanf로 입력하면, 구분자(공백문자) 버림... */
}

int print_receipt(time_t timestamp)
{
    size_t i;
    struct tm t;
    double subtotal = 0;

    t = *gmtime(&timestamp);

    if(food_counter == 0){
        return FALSE;
    }

    for (i = 0; i < food_counter; ++i) {
        subtotal += *(foodprice + i);
    }

    printf("Charles' Seafood\n");
    printf("--------------------------------------------------\n");
    printf("%04d-%02d-%02d %02d:%02d:%02d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
    printf("%05lu\n", order_number);
    printf("--------------------------------------------------\n");
    for (i = 0; i < FOODAMOUNT_MAX; ++i) {
        printf("%s", foodname[i]);
        printf("%.2f\n", foodprice[i]);
    }
    printf("\n");
    printf("%20s", "Subtotal");
    printf("%.2f\n", subtotal);
    printf("%20s", "Tip");
    printf("%.2f\n", tip_thanks);
    printf("%20s", "Tax");
    printf("%.2f\n", subtotal * 0.05);
    printf("%20s", "Total");
    printf("%.2f\n", subtotal + tip_thanks + subtotal * 0.05);
    printf("\n");
    printf("%s\n", message_thanks); /* it might be line unit */
    printf("==================================================\n");
    printf("%20s\n", "Tax#-51234");
    printf("\n");

    ++order_number;
    food_counter = 0;
    tip_thanks = 0;

    return TRUE;
}


/*
int print_receipt(const char* filename, time_t timestamp)
{
    FILE *fp;
    size_t i;

    fp == fopen("filename", "w");
    if (fp == NULL) {
        printf("file not opened...\n");
        return FALSE;
    }





    for (i = 0; i < FOODAMOUNT_MAX; i++) {
        for () {
            fprintf("%s\n")
        }
    }





    fclose(fp);

    return TRUE;
}
*/
