#include <limits.h>
#include "color.h"
#include "pomoku.h"

/* temp ********************* */
#define TRUE (1)
#define FALSE (0)
/* temp ********************* */

#define BOARD_MAX (20)
#define BOARD_MIN (10)

int g_pomoku_board[BOARD_MAX][BOARD_MAX] = {
    { INT_MIN, }
};
int g_row_count = 15;
int g_col_count = 15;
int g_black_score = 0;
int g_white_score = 0;


void init_game(void)
{
    int i = 0;
    int j = 0;

    g_row_count = 15;
    g_col_count = 15;
    g_black_score = 0;
    g_white_score = 0;

    for (i = 0; i < BOARD_MAX; ++i) {
        for (j = 0; j < BOARD_MAX; ++j) {
            g_pomoku_board[i][j] = INT_MIN;
        }
    }
}

unsigned int get_row_count(void)
{
    return g_row_count;
}

unsigned int get_column_count(void)
{
    return g_col_count;
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
    if (g_row_count <= row || g_col_count <= col) { /* what if... < 0? */
        return FALSE;
    } else if (get_color(row, col) == 0 || get_color(row, col) == 1) {
        return FALSE;
    } else {
        return TRUE;
    }
}

int count_stone_recursive(int color, const unsigned int y, const unsigned int x, int dy, int dx)
{
    if (y >= g_row_count || x >= g_col_count) { /* what if... < 0? */
        return 0;
    }

    if (get_color(y, x) == color) {
        return 1 + count_stone_recursive(color, y + dy, x + dx, dy, dx);
    }
    return 0;
}

void obtain_score_algorithm(int color, int y, int x)
{
    int i = 0;

    /* hori, verti, left-diag, right-diag */
    int direction_indicator[4][2] = {
        {0, 1}, {1, 0}, {-1, 1}, {1, 1}
    };

    for (i = 0; i < 4; ++i) {
        int dy = direction_indicator[i][0];
        int dx = direction_indicator[0][i];
        int stone_counter = count_stone_recursive(color, y + dy, x + dx, dy, dx);
        stone_counter += count_stone_recursive(color, y - dy, x - dx, -dy, -dx);
        stone_counter++; /* also should count the placed stone itself */

        if (stone_counter > 4) {
            switch (color) {
            case 0:
                g_black_score += stone_counter - 4;
                break;
            case 1:
                g_white_score += stone_counter - 4;
                break;
            default:
                break;
            }
        }
    }
}

int place_stone(const color_t color, const unsigned int row, const unsigned int col)
{
    int stone_placeable = FALSE;
    int stone_color = -1;

    /* is_placeable 판정 */
    stone_placeable = is_placeable(row, col);

    /* 들어올 color 판정 */
    switch (color) {
    case COLOR_BLACK:
        stone_color = 0;
        break;
    case COLOR_WHITE:
        stone_color = 1;
        break;
    default:
        break;
    }

    if (stone_placeable == FALSE || stone_color == -1) {
        return FALSE;
    }

    /* 돌 놓기 */
    g_pomoku_board[row][col] = stone_color;

    /* 점수 판정 */
    obtain_score_algorithm(stone_color, row, col);

    return TRUE;
}


/* special moves */
/* 타입(signed/unsigned) 손보기 */
int check_score(const color_t color, int score_req)
{
    if (color == COLOR_BLACK) {
        if (g_black_score >= score_req) {
            return TRUE;
        }
    } else if (color == COLOR_WHITE) {
        if (g_white_score >= score_req) {
            return TRUE;
        }
    }
    return FALSE;
}

void consume_score(const color_t color, int score_req)
{
    if (color == COLOR_BLACK) {
        g_black_score -= score_req;
    } else if (color == COLOR_WHITE) {
        g_white_score -= score_req;
    }
}

int insert_row(const color_t color, const unsigned int row)
{
    int i = 0;
    int j = 0;
    int score_required = 3;

    if (BOARD_MAX <= g_row_count) {
        return FALSE;
    } else if (g_row_count < row) {
        return FALSE;
    }

    if (check_score(color, score_required) == TRUE) {
        consume_score(color, score_required);
        for (i = g_row_count; i >= 0; --i) {
            for (j = 0; j < g_col_count; ++j) {
                if (i > row) {
                    g_pomoku_board[i][j] = g_pomoku_board[i - 1][j];
                } else if (i == row) {
                    g_pomoku_board[i][j] = INT_MIN;
                } else {
                    break;
                }
            }
        }
        g_row_count++;
    }
    return FALSE;
}

int insert_column(const color_t color, const unsigned int col)
{
    int i = 0;
    int j = 0;
    int score_required = 3;

    if (BOARD_MAX <= g_col_count) {
        return FALSE;
    } else if (g_col_count < col) {
        return FALSE;
    }

    if (check_score(color, score_required) == TRUE) {
        consume_score(color, score_required);
        for (i = g_col_count; i >= 0; --i) {
            for (j = 0; j < g_row_count; ++j) {
                if (i > col) {
                    g_pomoku_board[j][i] = g_pomoku_board[j][i - 1];
                } else if (i == col) {
                    g_pomoku_board[j][i] = INT_MIN;
                } else {
                    break;
                }
            }
        }
        g_col_count++;
    }
    return FALSE;
}

int remove_row(const color_t color, const unsigned int row)
{
    int i = 0;
    int j = 0;
    int score_required = 3;

    if (g_row_count <= BOARD_MIN) {
        return FALSE;
    } else if (g_row_count <= row) {
        return FALSE;
    }

    if (check_score(color, score_required) == TRUE) {
        consume_score(color, score_required);
        for (i = 0; i < g_row_count - 1; ++i) {
            for (j = 0; j < g_col_count; ++j) {
                if (i >= row) {
                    g_pomoku_board[i][j] = g_pomoku_board[i + 1][j];
                }
            }
        }
        for (j = 0; j < g_col_count; ++j) {
            g_pomoku_board[g_row_count - 1][j] = INT_MIN;
        }
        g_row_count--;
    }
    return FALSE;
}

int remove_column(const color_t color, const unsigned int col)
{
    int i = 0;
    int j = 0;
    int score_required = 3;

    if (g_col_count <= BOARD_MIN) {
        return FALSE;
    } else if (g_col_count <= col) {
        return FALSE;
    }

    if (check_score(color, score_required) == TRUE) {
        consume_score(color, score_required);
        for (i = 0; i < g_col_count - 1; ++i) {
            for (j = 0; j < g_row_count; ++j) {
                if (i >= col) {
                    g_pomoku_board[j][i] = g_pomoku_board[j][i + 1];
                }
            }
        }
        for (j = 0; j < g_row_count; ++j) {
            g_pomoku_board[j][g_col_count - 1] = INT_MIN;
        }
        g_col_count--;
    }
    return FALSE;
}

int swap_rows(const color_t color, const unsigned int row0, const unsigned int row1)
{
    int i = 0;
    int score_required = 2;
    int temp[BOARD_MAX] = { INT_MIN, };

    if (g_row_count <= row0 || g_row_count <= row1) {
        return FALSE;
    }

    if (check_score(color, score_required) == TRUE) {
        consume_score(color, score_required);
        for (i = 0; i < g_col_count; ++i) {
            temp[i] = g_pomoku_board[row0][i];
        }

        for (i = 0; i < g_col_count; ++i) {
            g_pomoku_board[row0][i] = g_pomoku_board[row1][i];
        }

        for (i = 0; i < g_col_count; ++i) {
            g_pomoku_board[row1][i] = temp[i];
        }
    }
    return FALSE;
}

int swap_columns(const color_t color, const unsigned int col0, const unsigned int col1)
{
    int i = 0;
    int score_required = 2;
    int temp[BOARD_MAX] = { INT_MIN, };

    if (g_col_count <= col0 || g_col_count <= col1) {
        return FALSE;
    }

    if (check_score(color, score_required) == TRUE) {
        consume_score(color, score_required);
        for (i = 0; i < g_row_count; ++i) {
            temp[i] = g_pomoku_board[i][col0];
        }

        for (i = 0; i < g_row_count; ++i) {
            g_pomoku_board[i][col0] = g_pomoku_board[i][col1];
        }

        for (i = 0; i < g_row_count; ++i) {
            g_pomoku_board[i][col1] = temp[i];
        }
    }
    return FALSE;
}

int copy_row(const color_t color, const unsigned int src, const unsigned int dst)
{
    int i = 0;
    int score_required = 4;

    if (g_row_count <= src || g_row_count <= dst) {
        return FALSE;
    }

    if (check_score(color, score_required) == TRUE) {
        consume_score(color, score_required);
        for (i = 0; i < g_col_count; ++i) {
            g_pomoku_board[dst][i] = g_pomoku_board[src][i];
        }
    }
    return FALSE;
}

int copy_column(const color_t color, const unsigned int src, const unsigned int dst)
{
    int i = 0;
    int score_required = 4;

    if (g_col_count <= src || g_col_count <= dst) {
        return FALSE;
    }

    if (check_score(color, score_required) == TRUE) {
        consume_score(color, score_required);
        for (i = 0; i < g_row_count; ++i) {
            g_pomoku_board[i][dst] = g_pomoku_board[i][src];
        }
    }
    return FALSE;
}
