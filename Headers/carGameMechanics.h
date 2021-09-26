#ifndef _CARGAME_MECHANICS_H_
#define _CARGAME_MECHANICS_H_
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DEFAULT_ROWS 10
#define DEFAULT_COLS 50
#define OBJECTIVE_COUNT 5
#define PLAYER_SIZE 5
#define POSITION_POINTS 4
#define LIVES 3
#define TURN_CYCLE 3
#define CURR_X 0
#define PREV_X 1
#define CURR_Y 2
#define PREV_Y 3
#define HOSTILE_COORDINATES 2
#define HOSTILE_X 0
#define HOSTILE_Y 1


#define DEFAULT_DIFFICULTY 25
#define BOMB_COUNT (DEFAULT_ROWS * DEFAULT_COLS) / DEFAULT_DIFFICULTY


#define LEFT 'A'
#define RIGHT 'D'
#define UP 'W'
#define DOWN 'S'
#define QUIT 'Q'

void movePlayer(char **area, char move);
void moveHostile(char **area, int hostilePos[], int hostileStat);
void initObjective(char **area, int amount, int bombAmount);
void initHostile(char **area, int hostilePos[]);
void freeArea(char **area);
char **initArea();
int checkObjective(char **area, char type);



#endif