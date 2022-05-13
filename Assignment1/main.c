/*
본인이 작성한 코드를 테스트할 수 있는 포목 게임입니다.
본인 코드에 문제가 있을 시 게임에서 버그나 툴다운이 발생할 수 있습니다.
pomoku.h에서 #include <windows.h> 추가 후
#define TRUE (1)
#define FALSE (0)
부분 주석처리 해야 컴파일 됩니다.
빌드봇 채점 시 pomoku.h는 원상복귀 시키고
main.c는 게임 구현 관련 코드를 주석:처리 하거나
기존에 쓰던 main.c를 써주세요.
*/
 
/* temp***************

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "pomoku.h"
 
void game_start(void);
void goto_xy(const size_t x, const size_t y);
void goto_row_col(const size_t row, const size_t col);
void draw_board(void);
void draw_stone(const color_t color);
void update_state(const color_t color, const size_t x, const size_t y);
 
int main(void)
{
    game_start();
    return 0;
}
 
void game_start(void)
{
    int x = 0;
    int y = 0;
    char key_input = 0;
    int color = COLOR_BLACK;
    int skill = 0;
    int skill_position1 = -1;
    int skill_position2 = -1;
    int is_skill_successful = FALSE;
 
    init_game();
    system("cls");
    draw_board();
    update_state(COLOR_BLACK, 0, 0);
 
    while (key_input != 27) {
        key_input = _getch();
        is_skill_successful = FALSE;
        switch (key_input) {
        case 32:
            if (skill != 0) {
                if ('Q' == skill || 'W' == skill || 'q' == skill || 'w' == skill) {
                    goto_row_col(y, get_column_count());
                    printf(" ");
                    if ('Q' == skill || 'q' == skill) {
                        is_skill_successful = insert_row(color, y);
                    } else if ('W' == skill || 'w' == skill) {
                        is_skill_successful = remove_row(color, y);
                    }                    
                } else if ('E' == skill || 'R' == skill || 'e' == skill || 'r' == skill) {
                    goto_row_col(get_row_count(), x);
                    printf(" ");
                    if ('E' == skill || 'e' == skill) {
                        is_skill_successful = insert_column(color, x);
                    } else if ('R' == skill || 'r' == skill) {
                        is_skill_successful = remove_column(color, x);
                    }                    
                } else if (-1 == skill_position2) {
                    if ('1' == skill || 'A' == skill || 'a' == skill) {
                        skill_position2 = y;
                        break;
                    } else if ('2' == skill || 'S' == skill || 's' == skill) {
                        skill_position2 = x;
                        break;
                    }
                } else if (skill_position2 != -1) {
                    if ('1' == skill || 'A' == skill || 'a' == skill) {
                        goto_row_col(skill_position1, get_column_count());
                        printf(" ");
                        goto_row_col(y, get_column_count());
                        printf(" ");
                        if ('1' == skill) {
                            is_skill_successful = swap_rows(color, skill_position1, y);
                        } else if ('A' == skill || 'a' == skill) {
                            is_skill_successful = copy_row(color, skill_position1, y);
                        }
                    } else if ('2' == skill || 'S' == skill || 's' == skill) {
                        goto_row_col(get_row_count(), skill_position1);
                        printf(" ");
                        goto_row_col(get_row_count(), x);
                        printf(" ");
                        if ('2' == skill) {
                            is_skill_successful = swap_columns(color, skill_position1, x);
                        } else if ('S' == skill || 's' == skill) {
                            is_skill_successful = copy_column(color, skill_position1, x);
                        }
                    }
                }
 
                skill_position1 = -1;
                skill_position2 = -1;
                skill = 0;                
 
                if (TRUE == is_skill_successful) {
                    if (COLOR_BLACK == color) {
                        color = COLOR_WHITE;
                    } else if (COLOR_WHITE == color) {
                        color = COLOR_BLACK;
                    }
                }
                system("cls");
                draw_board();
                update_state(color, x, y);                
                break;
            } 
            if (TRUE == is_placeable(y, x)) {
                place_stone(color, y, x);
                draw_stone(color);
 
                if (COLOR_BLACK == color) {
                    color = COLOR_WHITE;
                } else if (COLOR_WHITE == color) {
                    color = COLOR_BLACK;
                }
 
                update_state(color, x, y);
            }
            break;
        case 72:
            if (y > 0) {
                y--;
                if ('Q' == skill || 'W' == skill || 'q' == skill || 'w' == skill) {
                    goto_row_col(skill_position1, get_column_count());
                    printf(" ");
                    skill_position1 = y;
                    goto_row_col(y, get_column_count());
                    printf("<");
                } else if('1' == skill || 'A' == skill || 'a' == skill) {
                    if (-1 == skill_position2) {
                        goto_row_col(skill_position1, get_column_count());
                        printf(" ");
                        skill_position1 = y;
                        goto_row_col(y, get_column_count());
                        printf("<");
                    } else if (skill_position2 != -1) {
                        goto_row_col(skill_position2, get_column_count());
                        printf(" ");
                        skill_position2 = y;
                        goto_row_col(y, get_column_count());
                        printf("<");
                        goto_row_col(skill_position1, get_column_count());
                        printf("<");
                    }
                }
            }
            break;
        case 80:
            y++;
            if ('Q' == skill || 'W' == skill || 'q' == skill || 'w' == skill) {
                goto_row_col(skill_position1, get_column_count());
                printf(" ");
                skill_position1 = y;
                goto_row_col(y, get_column_count());           
                printf("<");
            } else if('1' == skill || 'A' == skill || 'a' == skill) {
                if (-1 == skill_position2) {
                    goto_row_col(skill_position1, get_column_count());
                    printf(" ");
                    skill_position1 = y;
                    goto_row_col(y, get_column_count());
                    printf("<");
                } else if (skill_position2 != -1) {
                    goto_row_col(skill_position2, get_column_count());
                    printf(" ");
                    skill_position2 = y;
                    goto_row_col(y, get_column_count());
                    printf("<");
                    goto_row_col(skill_position1, get_column_count());
                    printf("<");
                }
            }
            break;
        case 75:
            if (x > 0) {
                x--;
                if ('E' == skill || 'R' == skill || 'e' == skill || 'r' == skill) {
                    goto_row_col(get_row_count(), skill_position1);
                    printf("  ");
                    skill_position1 = x;
                    goto_row_col(get_row_count(), x);
                    printf("^^");
                } else if('2' == skill || 'S' == skill || 's' == skill) {
                    if (-1 == skill_position2) {
                        goto_row_col(get_row_count(), skill_position1);
                        printf("  ");
                        skill_position1 = x;
                        goto_row_col(get_row_count(), x);
                        printf("^^");
                    } else if (skill_position2 != -1) {
                        goto_row_col(get_row_count(), skill_position2);
                        printf("  ");
                        skill_position2 = x;
                        goto_row_col(get_row_count(), x);
                        printf("^^");
                        goto_row_col(get_row_count(), skill_position1);
                        printf("^^");
                    }
                }
            }
            break;
        case 77:
            x++;
            if ('E' == skill || 'R' == skill || 'e' == skill || 'r' == skill) {
                goto_row_col(get_row_count(), skill_position1);
                printf("  ");
                skill_position1 = x;
                goto_row_col(get_row_count(), x);
                printf("^^");
            } else if('2' == skill || 'S' == skill || 's' == skill) {
                if (-1 == skill_position2) {
                    goto_row_col(get_row_count(), skill_position1);
                    printf("  ");
                    skill_position1 = x;
                    goto_row_col(get_row_count(), x);
                    printf("^^");
                } else if (skill_position2 != -1) {
                    goto_row_col(get_row_count(), skill_position2);
                    printf("  ");
                    skill_position2 = x;
                    goto_row_col(get_row_count(), x);
                    printf("^^");
                    goto_row_col(get_row_count(), skill_position1);
                    printf("^^");
                }
            }
            break;
        case 27:
            break;
        case 'Q':
        case 'q':
        case 'W':
        case 'w':
            if (0 == skill) {
                skill = key_input;
                skill_position1 = y;
                goto_row_col(y, get_column_count());
                printf("<");
            }
            break;
        case 'E':
        case 'e':
        case 'R':
        case 'r':
            if (0 == skill) {
                skill = key_input;
                skill_position1 = x;
                goto_row_col(get_row_count(), x);
                printf("^^");
            }
            break;
        case '1':
        case 'A':
        case 'a':
            if (0 == skill) {
                skill = key_input;
                skill_position1 = y;
                goto_row_col(y, get_column_count());
                printf("<");
            }
            break;
        case '2':
        case 'S':
        case 's':
            if (0 == skill) {
                skill = key_input;
                skill_position1 = x;
                goto_row_col(get_row_count(), x);
                printf("^^");
            }
            break;
        default:
            break;
        }
        goto_xy(x, y);
    }
    system("cls");
}
 
void goto_xy(const size_t x, const size_t y)
{
    COORD XY;
    XY.X = x * 2;
    XY.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}
 
void goto_row_col(const size_t row, size_t col)
{
    COORD XY;
    XY.X = col * 2;
    XY.Y = row;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}
 
void draw_board(void)
{
    size_t row = 0;
    size_t col = 0;
 
    for (row = 0; row < get_row_count(); ++row) {        
        for (col = 0; col < get_column_count(); ++col) {
            goto_row_col(row, col);
            draw_stone(get_color(row, col));
        }
    }
}
 
void draw_stone(const color_t color)
{
    if (COLOR_BLACK == color) {
        printf("()");
    } else if (COLOR_WHITE == color) {
        printf("[]");
    } else {
        printf("--");
    }
}
 
void update_state(const color_t color, const size_t x, const size_t y)
{
    char stone[3] = "()";
 
    goto_xy(21, 2);
    printf("place stone / use skill : spacebar");
    goto_xy(21, 3);
    printf("exit : ESC");
 
    if (COLOR_BLACK == color) {
        strcpy_s(stone, 3, "()");
    }
    else if (COLOR_WHITE == color) {
        strcpy_s(stone, 3, "[]");
    }
 
    goto_xy(21, 5);
    printf("Turn : %s    Score : () %d [] %d", stone, get_score(COLOR_BLACK), get_score(COLOR_WHITE));
 
          goto_xy(21, 8);
    printf("[2 points]  swap rows : 1");  
    goto_xy(21, 9);
    printf("[2 points]  swap columns : 2");
    goto_xy(21, 10);
    printf("[3 points]  insert row : Q");
    goto_xy(21, 11);
    printf("[3 points]  remove row : W");
    goto_xy(21, 12);
    printf("[3 points]  insert column : E");
    goto_xy(21, 13);
    printf("[3 points]  remove column : R");
    goto_xy(21, 14);
    printf("[4 points]  copy row : A");
    goto_xy(21, 15);
    printf("[4 points]  copy column : S");
 
    goto_xy(x, y);
}
*/
