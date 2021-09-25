#ifndef _CARGAME_MECHANICS_H_
#define _CARGAME_MECHANICS_H_
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ROWS 10
#define COLS 10
#define OBJECTIVE_COUNT 5
#define PLAYER_SIZE 5
#define POSITION_POINTS 4
#define LIVES 3
#define TURN_CYCLE 3
#define CURR_X 0
#define PREV_X 1
#define CURR_Y 2
#define PREV_Y 3


#define START_Y ROWS / 2
#define START_X COLS / 2
#define BOMB_COUNT (ROWS * COLS) / 30


#define LEFT 'A'
#define RIGHT 'D'
#define UP 'W'
#define DOWN 'S'
#define QUIT 'Q'

void movePlayer(char **area, char move);
void initObjective(char **area, int amount, int bombAmount);
char **initArea();
void freeArea(char **area);
int checkObjective(char **area, char type);



#endif