#include <limits.h>
#include "pomoku.h"
#include "color.h"

#define TRUE (1)
#define FALSE (0)
#define BOARD_MAX (20)
#define BOARD_MIN (10)

int g_pomoku_board[BOARD_MAX][BOARD_MAX];
int g_row_count;
int g_column_count;
int g_black_score;
int g_white_score;


void init_game(void)
{
    int x = 0;
    int y = 0;

    g_row_count = 15;
    g_column_count = 15;
    g_black_score = 0;
    g_white_score = 0;

    for (y = 0; y < BOARD_MAX; ++y) {
        for (x = 0; x < BOARD_MAX; ++x) {
            g_pomoku_board[y][x] = INT_MIN;
        }
    }
}

unsigned int get_row_count(void)
{
    return g_row_count;
}

unsigned int get_column_count(void)
{
    return g_column_count;
}

int get_score(const color_t color)
{
    switch (color) {
    case COLOR_BLACK:
        return g_black_score;
        break;
    case COLOR_WHITE:
        return g_white_score;
        break;
    default:
        return -1;
        break;
    }
}

int get_color(const unsigned int row, const unsigned int col)
{
    switch (g_pomoku_board[row][col]) {
    case 0:
        return 0;
        break;
    case 1:
        return 1;
        break;
    default:
        return -1;
        break;
    }
}

int is_placeable(const unsigned int row, const unsigned int col)
{
    /* should consider "out of range" as well */
    if (g_row_count <= row || g_column_count <= col) {
        return FALSE;
    }
    if (g_pomoku_board[row][col] == INT_MIN) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int place_stone(const color_t color, const unsigned int row, const unsigned int col)
{
        switch (color) {
    case COLOR_BLACK:
        g_pomoku_board[row][col] = 0;
        return TRUE;
        break;
    case COLOR_WHITE:  
        g_pomoku_board[row][col] = 1;
        return TRUE;
        break;
    default:
        return FALSE;
        break;
    }
}
