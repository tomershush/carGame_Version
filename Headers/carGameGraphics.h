#ifndef _CARGAME_GRAPHICS_H_
#define _CARGAME_GRAPHICS_H_
#include "carGameMechanics.h"

#define PLAYER '*'
#define TILE '_'
#define OBJECTIVE '&'
#define BOMB '#'
#define RUN_OVER_HORIZONTAL '='
#define RUN_OVER_VERTICAL '|'

void renderArea(char area[ROWS][COLS]);
void renderPlayer(char area[ROWS][COLS]);
void deletePlayer(char area[ROWS][COLS], char moveType);
void deleteRoad(char area[ROWS][COLS]);

#endif