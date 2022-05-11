#include <assert.h>
#include <limits.h>
#include "pomoku.h"
#include "color.h"

void init_game_and_test(void);
void score_test(void);


int main(void)
{
    init_game_and_test();
    score_test();
    return 0;
}

void init_game_and_test(void)
{
    init_game();
 
    assert(15 == get_row_count());
    assert(15 == get_column_count());
 
    assert(0 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));
}
 
void score_test(void)
{
    /* hori */
    init_game_and_test();
    place_stone(COLOR_BLACK, 0, 0);
    place_stone(COLOR_BLACK, 0, 1);
    place_stone(COLOR_BLACK, 0, 2);
    place_stone(COLOR_BLACK, 0, 3);
    place_stone(COLOR_BLACK, 0, 4);
 
    assert(1 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 5);
 
    assert(3 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 6);
 
    assert(6 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 1, 1);
    place_stone(COLOR_BLACK, 2, 2);
    place_stone(COLOR_BLACK, 3, 3);
    place_stone(COLOR_BLACK, 4, 4);
 
    assert(7 == get_score(COLOR_BLACK));
 
    init_game_and_test();
    place_stone(COLOR_BLACK, 0, 14);
    place_stone(COLOR_BLACK, 0, 13);
    place_stone(COLOR_BLACK, 0, 12);
    place_stone(COLOR_BLACK, 0, 11);
    place_stone(COLOR_BLACK, 0, 10);
 
    assert(1 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 9);
 
    assert(3 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 8);
 
    assert(6 == get_score(COLOR_BLACK));
 
    /* verti */
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 0, 0);
    place_stone(COLOR_WHITE, 1, 0);
    place_stone(COLOR_WHITE, 2, 0);
    place_stone(COLOR_WHITE, 3, 0);
    place_stone(COLOR_WHITE, 4, 0);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 5, 0);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 6, 0);
 
    assert(6 == get_score(COLOR_WHITE));
 
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 14, 0);
    place_stone(COLOR_WHITE, 13, 0);
    place_stone(COLOR_WHITE, 12, 0);
    place_stone(COLOR_WHITE, 11, 0);
    place_stone(COLOR_WHITE, 10, 0);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 9, 0);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 8, 0);
 
    assert(6 == get_score(COLOR_WHITE));
 
    /* left-diag */
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 0, 0);
    place_stone(COLOR_WHITE, 1, 1);
    place_stone(COLOR_WHITE, 2, 2);
    place_stone(COLOR_WHITE, 3, 3);
    place_stone(COLOR_WHITE, 4, 4);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 5, 5);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 6, 6);
 
    assert(6 == get_score(COLOR_WHITE));
 
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 14, 14);
    place_stone(COLOR_WHITE, 13, 13);
    place_stone(COLOR_WHITE, 12, 12);
    place_stone(COLOR_WHITE, 11, 11);
    place_stone(COLOR_WHITE, 10, 10);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 9, 9);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 8, 8);
 
    assert(6 == get_score(COLOR_WHITE));
 
    /* right-diag */
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 14, 0);
    place_stone(COLOR_WHITE, 13, 1);
    place_stone(COLOR_WHITE, 12, 2);
    place_stone(COLOR_WHITE, 11, 3);
    place_stone(COLOR_WHITE, 10, 4);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 9, 5);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 8, 6);
 
    assert(6 == get_score(COLOR_WHITE));
 
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 0, 14);
    place_stone(COLOR_WHITE, 1, 13);
    place_stone(COLOR_WHITE, 2, 12);
    place_stone(COLOR_WHITE, 3, 11);
    place_stone(COLOR_WHITE, 4, 10);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 5, 9);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 6, 8);
 
    assert(6 == get_score(COLOR_WHITE));
}
