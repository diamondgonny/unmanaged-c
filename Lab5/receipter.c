#include "receipter.h"

#define FOODAMOUNT_MAX (10)
#define FOODNAME_LENGTH (25)
#define MESSAGE_LENGTH (75)

static char foodname[FOODAMOUNT_MAX][FOODNAME_LENGTH + 1]; /* '\0' */
static double foodprice[FOODAMOUNT_MAX];
static size_t food_counter = 0;
static double tip_buffer = 0;
static char message_buffer[MESSAGE_LENGTH + 2];  /* '\n', '\0' */

void my_strncpy(char* str, const char* input, int length)
{
    int cnt = 0;

    /* 이거 길이제한 안두면, 버퍼가 선을 넘어버리는 수가 있다... */
    while (*input != '\0' && cnt < length) {
        if (cnt == 50) {
            *str = '\n';
            ++str;
            ++cnt;
        }
        *str = *input;
        ++str;
        ++input;
        ++cnt;
    }
    *str = '\0';
}

int add_item(const char* name, double price)
{
    if (food_counter >= FOODAMOUNT_MAX) {
        printf("maximum food amount\n");
        return FALSE;
    } else if(price > 999.99) {
        printf("invalid price\n");
        return FALSE;
    } else {
        /* 2차원 배열에서의 포인터 : *(foodname + food_counter) */
        /* sscanf로 시도해보니, 구분자(공백문자) 버림... */
        my_strncpy(*(foodname + food_counter), name, FOODNAME_LENGTH + 1);
        foodprice[food_counter] = price;
        ++food_counter;
    }

    return TRUE;
}

void set_tip(double tip)
{
    if(tip > 999.99) {
        printf("invalid tip\n");
    } else {
        tip_buffer = tip;
    }
}

void set_message(const char* message)
{
    /* 문자열을 복사해서 붙여넣고, 끝에 '\0'을 넣어주자. length 넘어가면 짤림) */
    my_strncpy(message_buffer, message, MESSAGE_LENGTH + 2);
}

int print_receipt(const char* filename, time_t timestamp)
{
    FILE* fp;
    static int order_number = 0;
    double subtotal = 0;
    struct tm t;
    size_t i;

    if(food_counter == 0 || order_number > 99999) {
        printf("no food...\n");
        tip_buffer = 0;
        *message_buffer = '\0';
        return FALSE;
    } else {
        fp = fopen(filename, "w"); /* 파일 */
    }

    if (fp == NULL) {
        printf("file not opened...\n");
        return FALSE;
    } else {
        fseek(fp, 0, SEEK_SET);
    }

    /* 서브토탈 */
    for (i = 0; i < food_counter; ++i) {
        subtotal += *(foodprice + i);
    }

    /* 날짜-시간 (다시보기) */
    t = *gmtime(&timestamp);

    fprintf(fp, "Charles' Seafood\n");
    fprintf(fp, "--------------------------------------------------\n");
    fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
    fprintf(fp, "                          ");
    fprintf(fp, "%05d\n", order_number);
    fprintf(fp, "--------------------------------------------------\n");
    for (i = 0; i < food_counter; ++i) {
        /* 배열과 포인터 다시보기 */
        fprintf(fp, "%33s", *(foodname + i));
        fprintf(fp, "%17.2f\n", *(foodprice + i));
    }
    fprintf(fp, "\n");
    fprintf(fp, "%33s", "Subtotal");
    fprintf(fp, "%17.2f\n", subtotal);
    if (tip_buffer > 0) {
            fprintf(fp, "%33s", "Tip");
        fprintf(fp, "%17.2f\n", tip_buffer);
    }
    fprintf(fp, "%33s", "Tax");
    fprintf(fp, "%17.2f\n", subtotal * 0.05);
    fprintf(fp, "%33s", "Total");
    fprintf(fp, "%17.2f\n", subtotal + tip_buffer + subtotal * 0.05);
    fprintf(fp, "\n");
    /* 메시지를 한 줄씩 쓴다는 것(~50칸)? */
    if (*message_buffer != '\0') {
        fprintf(fp, "%.50s\n", message_buffer);
    }
    fprintf(fp, "==================================================\n");
    fprintf(fp, "%50s\n", "Tax#-51234");
    fprintf(fp, "\n");

    order_number += 1;
    food_counter = 0;
    tip_buffer = 0;
    *message_buffer = '\0';

    fclose(fp);

    return TRUE;
}
