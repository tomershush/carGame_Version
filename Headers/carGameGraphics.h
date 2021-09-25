#ifndef _CARGAME_GRAPHICS_H_
#define _CARGAME_GRAPHICS_H_
#include "carGameMechanics.h"

#define PLAYER '*'
#define TILE '_'
#define OBJECTIVE '&'
#define BOMB '#'
#define RUN_OVER_HORIZONTAL '='
#define RUN_OVER_VERTICAL '|'

void renderArea(char **area);
void renderPlayer(char **area);
void deletePlayer(char **area, char moveType);
void deleteRoad(char **area);

extern int rows;
extern int cols;
extern int lives;
extern int victoryCount;
extern int position[POSITION_POINTS];

#endif