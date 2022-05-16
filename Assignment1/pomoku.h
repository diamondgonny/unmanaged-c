#ifndef POMOKU_H
#define POMOKU_H

/* temp *********************
#include <windows.h>
temp ********************* */

#include "color.h" /* learnt using "include guard" */

/* basic funcs */
void init_game(void);

unsigned int get_row_count(void);

unsigned int get_column_count(void);

int get_score(const color_t color);

int get_color(const unsigned int row, const unsigned int col);

int is_placeable(const unsigned int row, const unsigned int col);

/* custom function using into 'place_stone' */
int count_stone_recursive(int color, int y, int x, int dy, int dx);

void obtain_score_algorithm(int color, int y, int x);

int place_stone(const color_t color, const unsigned int row, const unsigned int col);

/* special moves */
int check_score(const color_t color, int score_req);

void consume_score(const color_t color, int score_req);

int insert_row(const color_t color, const unsigned int row);

int insert_column(const color_t color, const unsigned int col);

int remove_row(const color_t color, const unsigned int row);

int remove_column(const color_t color, const unsigned int col);

int swap_rows(const color_t color, const unsigned int row0, const unsigned int row1);

int swap_columns(const color_t color, const unsigned int col0, const unsigned int col1);

int copy_row(const color_t color, const unsigned int src, const unsigned int dst);

int copy_column(const color_t color, const unsigned int src, const unsigned int dst);

#endif /* POMOKU_H */
