#include "carGameGraphics.h"


/*
A function to refresh the screen and render the game.
Input: 2D Array that represents the game area.
Output: None.
*/
void renderArea(char area[ROWS][COLS])
{
	int i = 0;
	int j = 0;
	
	clear();
	printw("Score: %d| Lives: %d\n", victoryCount, lives);
	for(i = 0; i < ROWS; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			printw("%c", area[i][j]);	
		}
		printw("\n");

	}
	refresh();
}

void renderPlayer(char area[ROWS][COLS])
{
	area[position[CURR_Y]][position[CURR_X]] = PLAYER;
	area[position[CURR_Y] - 1][position[CURR_X] - 1] = PLAYER;
	area[position[CURR_Y] + 1][position[CURR_X] + 1] = PLAYER;
	area[position[CURR_Y] - 1][position[CURR_X] + 1] = PLAYER;
	area[position[CURR_Y] + 1][position[CURR_X] - 1] = PLAYER;

}

void deletePlayer(char area[ROWS][COLS], char moveType)
{
	area[position[CURR_Y]][position[CURR_X]] = TILE;
	area[position[CURR_Y] - 1][position[CURR_X] - 1] = moveType;
	area[position[CURR_Y] + 1][position[CURR_X] + 1] = moveType;
	area[position[CURR_Y] - 1][position[CURR_X] + 1] = moveType;
	area[position[CURR_Y] + 1][position[CURR_X] - 1] = moveType;

}

/*
A function to clear all road marks on the game area.
Input: 2D Array that represents the game area.
Output: None.
*/
void deleteRoad(char area[ROWS][COLS])
{
	int i = 0;
	int j = 0;

	for(i = 0; i < ROWS; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			if(area[i][j] == RUN_OVER_HORIZONTAL || area[i][j] == RUN_OVER_VERTICAL)
			{
				area[i][j] = TILE;
			}
		}
	}
}