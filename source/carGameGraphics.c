#include "carGameGraphics.h"

/*
A function to refresh the screen and render the game.
Input: 2D Array that represents the game area.
Output: None.
*/
void renderArea(char **area)
{
	int i = 0;
	int j = 0;
	
	clear();
	printw("Score: %d| Lives: %d\n", victoryCount, lives);
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			printw("%c", area[i][j]);	
		}
		printw("\n");

	}
	refresh();
}

void renderPlayer(char **area)
{
	area[position[CURR_Y]][position[CURR_X]] = PLAYER;
	area[position[CURR_Y] - 1][position[CURR_X] - 1] = PLAYER;
	area[position[CURR_Y] + 1][position[CURR_X] + 1] = PLAYER;
	area[position[CURR_Y] - 1][position[CURR_X] + 1] = PLAYER;
	area[position[CURR_Y] + 1][position[CURR_X] - 1] = PLAYER;

}

void deletePlayer(char **area, char moveType)
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
void deleteRoad(char **area)
{
	int i = 0;
	int j = 0;

	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			if(area[i][j] == RUN_OVER_HORIZONTAL || area[i][j] == RUN_OVER_VERTICAL)
			{
				area[i][j] = TILE;
			}
		}
	}
}