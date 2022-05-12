#include <stdio.h>
#include <limits.h>
#include "pomoku.h"
#include "color.h"

#define TRUE (1)
#define FALSE (0)
#define BOARD_MAX (20)
#define BOARD_MIN (10)

/* how to initialize array anyways? */
int g_pomoku_board[BOARD_MAX][BOARD_MAX];
int g_row_count = 15;
int g_column_count = 15;
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

    if (g_row_count < g_column_count) {
        longer_line_index = g_column_count - 1;
        shorter_line_index = g_row_count - 1;
    } else {
        longer_line_index = g_row_count - 1;
        shorter_line_index = g_column_count - 1;
    }

    /* hori */
    for (i = col; i < g_column_count; ++i) {
        if(g_pomoku_board[row][i] == color) {
            stone_counter++;
        } else {
            break;
        }
    }
    for (i = col; i >= 0; --i) {
        if(g_pomoku_board[row][i] == color) {
            stone_counter++;
        } else {
            break;
        }
    }
    stone_counter -= 1;
    stone_counter = calc_score(color, stone_counter);

    /* verti */
    for (i = row; i < g_row_count; ++i) {
        if(g_pomoku_board[i][col] == color) {
            stone_counter++;
        } else {
            break;
        }
    }
    for (i = row; i >= 0; --i) {
        if(g_pomoku_board[i][col] == color) {
            stone_counter++;
        } else {
            break;
        }
    }
    stone_counter -= 1;
    printf("%d", stone_counter);
    stone_counter = calc_score(color, stone_counter);

    /* left-diag (bottom, top, middle) */
    if (left_diag_indicator > 10) {
        for (i = col; i >= 0; --i) {
            if(g_pomoku_board[i + left_diag_indicator][i] == color) {
                stone_counter++;
            } else {
            break;
            }
        }
        for (i = row; i < g_row_count; ++i) {
            if(g_pomoku_board[i][i - left_diag_indicator] == color) {
                stone_counter++;
            } else {
            break;
            }
        }
    } else if (left_diag_indicator < -10) {
        for (i = row; i >= 0; --i) {
            if(g_pomoku_board[i][i - left_diag_indicator] == color) {
                stone_counter++;
            } else {
            break;
            }
        }
        for (i = col; i < g_column_count; ++i) {
            if(g_pomoku_board[i + left_diag_indicator][i] == color) {
                stone_counter++;
            } else {
            break;
            }
        }
    } else {
        if (g_column_count < g_row_count) {
            if(g_row_count - g_column_count > left_diag_indicator) {
                for (i = col; i >= 0; --i) {
                    if(g_pomoku_board[i + left_diag_indicator][i] == color) {
                        stone_counter++;
                    } else {
                        break;
                    }
                }
                for (i = col; i < g_column_count; ++i) {
                    if(g_pomoku_board[i + left_diag_indicator][i] == color) {
                        stone_counter++;
                    } else {
                        break;
                    }
                }
            } else {
                for (i = col; i >= 0; --i) {
                    if(g_pomoku_board[i + left_diag_indicator][i] == color) {
                        stone_counter++;
                    } else {
                        break;
                    }
                }
                for (i = row; i < g_row_count; ++i) {
                    if(g_pomoku_board[i][i - left_diag_indicator] == color) {
                        stone_counter++;
                    } else {
                        break;
                    }
                }
            }
        } else {
            if(g_column_count - g_row_count > 0 - left_diag_indicator) {
                for (i = row; i >= 0; --i) {
                    if(g_pomoku_board[i][i - left_diag_indicator] == color) {
                        stone_counter++;
                    } else {
                        break;
                    }
                }
                for (i = row; i < g_row_count; ++i) {
                    if(g_pomoku_board[i][i - left_diag_indicator] == color) {
                        stone_counter++;
                    } else {
                        break;
                    }
                }
            } else {
                for (i = row; i >= 0; --i) {
                    if(g_pomoku_board[i][i - left_diag_indicator] == color) {
                        stone_counter++;
                    } else {
                        break;
                    }
                }
                for (i = col; i < g_column_count; ++i) {
                    if(g_pomoku_board[i + left_diag_indicator][i] == color) {
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
            if(g_pomoku_board[right_diag_indicator - i][i] == color) {
                stone_counter++;
            } else {
            break;
            }
        }
        for (i = row; i >= 0; --i) {
            if(g_pomoku_board[i][right_diag_indicator - i] == color) {
                stone_counter++;
            } else {
            break;
            }
        }
    } else if (right_diag_indicator > longer_line_index) {
        for (i = col; i < g_column_count; ++i) {
            if(g_pomoku_board[right_diag_indicator - i][i] == color) {
                stone_counter++;
            } else {
            break;
            }
        }
        for (i = row; i < g_row_count; ++i) {
            if(g_pomoku_board[i][right_diag_indicator - i] == color) {
                stone_counter++;
            } else {
            break;
            }
        }
    } else {
        if (g_column_count < g_row_count) {
            for (i = col; i >= 0; --i) {
                if(g_pomoku_board[right_diag_indicator - i][i] == color) {
                    stone_counter++;
                } else {
                    break;
                }
            }
            for (i = col; i < g_column_count; ++i) {
                if(g_pomoku_board[right_diag_indicator - i][i] == color) {
                    stone_counter++;
                } else {
                    break;
                }
            }
        } else {
            for (i = row; i >= 0; --i) {
                if(g_pomoku_board[i][right_diag_indicator - i] == color) {
                    stone_counter++;
                } else {
                    break;
                }
            }
            for (i = row; i < g_row_count; ++i) {
                if(g_pomoku_board[i][right_diag_indicator - i] == color) {
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
    if (g_row_count <= row || g_column_count <= col) {
        /* should consider "out of range" as well */
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
    int stone_color = -1;

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
