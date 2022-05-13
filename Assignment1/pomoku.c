#include <limits.h>
#include "color.h"
#include "pomoku.h"

/* temp ********************* */
#define TRUE (1)
#define FALSE (0)
/* temp ********************* */

#define BOARD_MAX (20)
#define BOARD_MIN (10)

/* how to initialize array anyways? */
int g_pomoku_board[BOARD_MAX][BOARD_MAX];
int g_row_count = 15;
int g_col_count = 15;
int g_black_score = 0;
int g_white_score = 0;


int calc_score(int color, int cnt)
{
    if (cnt > 4) {
        switch (color) {
        case 0:
            g_black_score += cnt - 4;
            break;
        case 1:
            g_white_score += cnt - 4;
            break;
        default:
            break;
        }
    }
    return 0;
}

void count_stone(int color, const unsigned int row, const unsigned int col)
{
    int i = 0;
    int stone_counter = 0;
    /* the value that calculates left(right) diag */
    int left_diag_indicator = (int)row - (int)col;
    int right_diag_indicator = (int)row + (int)col;
    /* to know which one is abolutely longer to calculate right diag */
    int longer_line_index = 0;
    int shorter_line_index = 0;

    if (g_row_count < g_col_count) {
        longer_line_index = g_col_count - 1;
        shorter_line_index = g_row_count - 1;
    } else {
        longer_line_index = g_row_count - 1;
        shorter_line_index = g_col_count - 1;
    }

    /* hori */
    for (i = col; i < g_col_count; ++i) {
        if (g_pomoku_board[row][i] == color) {
            stone_counter++;
        } else {
            break;
        }
    }
    for (i = col; i >= 0; --i) {
        if (g_pomoku_board[row][i] == color) {
            stone_counter++;
        } else {
            break;
        }
    }
    stone_counter -= 1;
    stone_counter = calc_score(color, stone_counter);

    /* verti */
    for (i = row; i < g_row_count; ++i) {
        if (g_pomoku_board[i][col] == color) {
            stone_counter++;
        } else {
            break;
        }
    }
    for (i = row; i >= 0; --i) {
        if (g_pomoku_board[i][col] == color) {
            stone_counter++;
        } else {
            break;
        }
    }
    stone_counter -= 1;
    stone_counter = calc_score(color, stone_counter);

    /* left-diag (bottom, top, middle) */
    if (left_diag_indicator > 10) {
        for (i = col; i >= 0; --i) {
            if (g_pomoku_board[i + left_diag_indicator][i] == color) {
                stone_counter++;
            } else {
                break;
            }
        }
        for (i = row; i < g_row_count; ++i) {
            if (g_pomoku_board[i][i - left_diag_indicator] == color) {
                stone_counter++;
            } else {
                break;
            }
        }
    } else if (left_diag_indicator < -10) {
        for (i = row; i >= 0; --i) {
            if (g_pomoku_board[i][i - left_diag_indicator] == color) {
                stone_counter++;
            } else {
                break;
            }
        }
        for (i = col; i < g_col_count; ++i) {
            if (g_pomoku_board[i + left_diag_indicator][i] == color) {
                stone_counter++;
            } else {
                break;
            }
        }
    } else {
        if (g_col_count < g_row_count) {
            if (g_row_count - g_col_count > left_diag_indicator) {
                for (i = col; i >= 0; --i) {
                    if (g_pomoku_board[i + left_diag_indicator][i] == color) {
                        stone_counter++;
                    } else {
                        break;
                    }
                }
                for (i = col; i < g_col_count; ++i) {
                    if (g_pomoku_board[i + left_diag_indicator][i] == color) {
                        stone_counter++;
                    } else {
                        break;
                    }
                }
            } else {
                for (i = col; i >= 0; --i) {
                    if (g_pomoku_board[i + left_diag_indicator][i] == color) {
                        stone_counter++;
                    } else {
                        break;
                    }
                }
                for (i = row; i < g_row_count; ++i) {
                    if (g_pomoku_board[i][i - left_diag_indicator] == color) {
                        stone_counter++;
                    } else {
                        break;
                    }
                }
            }
        } else {
            if (g_col_count - g_row_count > 0 - left_diag_indicator) {
                for (i = row; i >= 0; --i) {
                    if (g_pomoku_board[i][i - left_diag_indicator] == color) {
                        stone_counter++;
                    } else {
                        break;
                    }
                }
                for (i = row; i < g_row_count; ++i) {
                    if (g_pomoku_board[i][i - left_diag_indicator] == color) {
                        stone_counter++;
                    } else {
                        break;
                    }
                }
            } else {
                for (i = row; i >= 0; --i) {
                    if (g_pomoku_board[i][i - left_diag_indicator] == color) {
                        stone_counter++;
                    } else {
                        break;
                    }
                }
                for (i = col; i < g_col_count; ++i) {
                    if (g_pomoku_board[i + left_diag_indicator][i] == color) {
                        stone_counter++;
                    } else {
                        break;
                    }
                }
            }
        }
    }
    stone_counter -= 1;
    stone_counter = calc_score(color, stone_counter);

    /* right-diag (0 < s < l < M) */
    if (right_diag_indicator < shorter_line_index) {
        for (i = col; i >= 0; --i) {
            if (g_pomoku_board[right_diag_indicator - i][i] == color) {
                stone_counter++;
            } else {
                break;
            }
        }
        for (i = row; i >= 0; --i) {
            if (g_pomoku_board[i][right_diag_indicator - i] == color) {
                stone_counter++;
            } else {
                break;
            }
        }
    } else if (right_diag_indicator > longer_line_index) {
        for (i = col; i < g_col_count; ++i) {
            if (g_pomoku_board[right_diag_indicator - i][i] == color) {
                stone_counter++;
            } else {
                break;
            }
        }
        for (i = row; i < g_row_count; ++i) {
            if (g_pomoku_board[i][right_diag_indicator - i] == color) {
                stone_counter++;
            } else {
                break;
            }
        }
    } else {
        if (g_col_count < g_row_count) {
            for (i = col; i >= 0; --i) {
                if (g_pomoku_board[right_diag_indicator - i][i] == color) {
                    stone_counter++;
                } else {
                    break;
                }
            }
            for (i = col; i < g_col_count; ++i) {
                if (g_pomoku_board[right_diag_indicator - i][i] == color) {
                    stone_counter++;
                } else {
                    break;
                }
            }
        } else {
            for (i = row; i >= 0; --i) {
                if (g_pomoku_board[i][right_diag_indicator - i] == color) {
                    stone_counter++;
                } else {
                    break;
                }
            }
            for (i = row; i < g_row_count; ++i) {
                if (g_pomoku_board[i][right_diag_indicator - i] == color) {
                    stone_counter++;
                } else {
                    break;
                }
            }
        }
    }
    stone_counter -= 1;
    stone_counter = calc_score(color, stone_counter);
}

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
    if (g_row_count <= row || g_col_count <= col) {
        /* should consider "out of range" as well */
        return FALSE;
    } else if (g_pomoku_board[row][col] == 0 || g_pomoku_board[row][col] == 1) {
        return FALSE;
    } else {
        return TRUE;
    }
}

int place_stone(const color_t color, const unsigned int row, const unsigned int col)
{
    int stone_color = -1;

    if (g_row_count <= row || g_col_count <= col) {
        /* should consider "out of range" as well */
        return FALSE;
    } else if (g_pomoku_board[row][col] == 0 || g_pomoku_board[row][col] == 1) {
        return FALSE;
    }

    switch (color) {
    case COLOR_BLACK:
        stone_color = 0;
        break;
    case COLOR_WHITE:  
        stone_color = 1;
        break;
    default:
        return FALSE; /* invalid color */
        break;
    }

    /* score algorithm activates with counting after placement */
    g_pomoku_board[row][col] = stone_color;
    count_stone(stone_color, row, col);

    return TRUE;
}

/* special moves */
/* add function, add score_req-- */
int score_checker(const color_t color, int score_req)
{
    if (!(color == COLOR_BLACK || color == COLOR_WHITE)) {
        return FALSE; /* invalid color */
    } else if (color == COLOR_BLACK) {
        if (g_black_score < score_req) {
            return FALSE;
        }
    } else if (color == COLOR_WHITE) {
        if (g_white_score < score_req) {
            return FALSE;
        }
    }
    return TRUE;
}

void score_activator(const color_t color, int score_req)
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

    if (score_checker(color, score_required) == FALSE) {
        return FALSE;
    }

    score_activator(color, score_required);

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
    
    return TRUE;
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

    if (score_checker(color, score_required) == FALSE) {
        return FALSE;
    }

    score_activator(color, score_required);


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
    
    return TRUE;
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

    if (score_checker(color, score_required) == FALSE) {
        return FALSE;
    }

    score_activator(color, score_required);


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

    return TRUE;
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

    if (score_checker(color, score_required) == FALSE) {
        return FALSE;
    }

    score_activator(color, score_required);


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

    return TRUE;
}

int swap_rows(const color_t color, const unsigned int row0, const unsigned int row1)
{
    int i = 0;
    int score_required = 2;
    int temp[BOARD_MAX] = { INT_MIN, };

    if (g_row_count <= row0 || g_row_count <= row1) {
        return FALSE;
    }

    if (score_checker(color, score_required) == FALSE) {
        return FALSE;
    }

    score_activator(color, score_required);


    for (i = 0; i < g_col_count; ++i) {
        temp[i] = g_pomoku_board[row0][i];
    }

    for (i = 0; i < g_col_count; ++i) {
        g_pomoku_board[row0][i] = g_pomoku_board[row1][i];
    }

    for (i = 0; i < g_col_count; ++i) {
        g_pomoku_board[row1][i] = temp[i];
    }

    return TRUE;
}

int swap_columns(const color_t color, const unsigned int col0, const unsigned int col1)
{
    int i = 0;
    int score_required = 2;
    int temp[BOARD_MAX] = { INT_MIN, };

    if (g_col_count <= col0 || g_col_count <= col1) {
        return FALSE;
    }

    if (score_checker(color, score_required) == FALSE) {
        return FALSE;
    }

    score_activator(color, score_required);


    for (i = 0; i < g_row_count; ++i) {
        temp[i] = g_pomoku_board[i][col0];
    }

    for (i = 0; i < g_row_count; ++i) {
        g_pomoku_board[i][col0] = g_pomoku_board[i][col1];
    }

    for (i = 0; i < g_row_count; ++i) {
        g_pomoku_board[i][col1] = temp[i];
    }

    return TRUE;
}

int copy_row(const color_t color, const unsigned int src, const unsigned int dst)
{
    int i = 0;
    int score_required = 4;

    if (g_row_count <= src || g_row_count <= dst) {
        return FALSE;
    }

    if (score_checker(color, score_required) == FALSE) {
        return FALSE;
    }

    score_activator(color, score_required);


    for (i = 0; i < g_col_count; ++i) {
        g_pomoku_board[dst][i] = g_pomoku_board[src][i];
    }

    return TRUE;
}

int copy_column(const color_t color, const unsigned int src, const unsigned int dst)
{
    int i = 0;
    int score_required = 4;

    if (g_col_count <= src || g_col_count <= dst) {
        return FALSE;
    }

    if (score_checker(color, score_required) == FALSE) {
        return FALSE;
    }

    score_activator(color, score_required);


    for (i = 0; i < g_row_count; ++i) {
        g_pomoku_board[i][dst] = g_pomoku_board[i][src];
    }

    return TRUE;
}
