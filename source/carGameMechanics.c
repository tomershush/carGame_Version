#include "carGameGraphics.h"




/*
A function to initalize the game area.
Input: 2D Array that represents the game area.
Output: None.
*/
void initArea(char area[ROWS][COLS])
{
	int i = 0;
	int j = 0;

	for(i = 0; i < ROWS; i++)
	{
		for(j = 0; j < COLS; j++)
		{
			area[i][j] = TILE;
		}
	}
	initObjective(area, OBJECTIVE_COUNT, BOMB_COUNT);	
}



/*
A function to move the player to a new position.
Input: 2D array that represents the game area, move char that represents the direction of the player movement.
Output: None.
*/
void movePlayer(char area[ROWS][COLS], char move)
{
	
	position[PREV_X] = position[CURR_X];
	position[PREV_Y] = position[CURR_Y];

	switch(move)
	{
		case LEFT:
			deletePlayer(area, RUN_OVER_HORIZONTAL);
			position[CURR_X]--;	
			break;

		case RIGHT:
			deletePlayer(area, RUN_OVER_HORIZONTAL);
			position[CURR_X]++;
			break;

		case UP:
			deletePlayer(area, RUN_OVER_VERTICAL);
			position[CURR_Y]--;
			break;

		case DOWN:
			deletePlayer(area, RUN_OVER_VERTICAL);
			position[CURR_Y]++;
			break;
			
	}
	victoryCount += checkObjective(area, OBJECTIVE);
	lives -= checkObjective(area, BOMB);

	renderPlayer(area);
}






void initObjective(char area[ROWS][COLS], int amount, int bombAmount)
{
	int count = 0;
	int tempX = 0;
	int tempY = 0;
	srand(time(0));
	
	while(count < amount)
	{
		tempX = rand() % COLS;
		tempY = rand() % ROWS;

		if(area[tempY][tempX] == TILE)
		{
			count++;
			area[tempY][tempX] = OBJECTIVE;
		}
	}
	count = 0;

	while(count < bombAmount)
	{
		tempX = rand() % COLS;
		tempY = rand() % ROWS;

		if(area[tempY][tempX] == TILE)
		{
			count++;
			area[tempY][tempX] = BOMB;
		}
	}

}

int checkObjective(char area[ROWS][COLS], char type)
{
	int gotObjective = 0;

	if(area[position[CURR_Y] - 1][position[CURR_X] - 1] == type)
	{
		gotObjective++;
	}
	if(area[position[CURR_Y] + 1][position[CURR_X] - 1] == type)
	{
		gotObjective++;
	}
	if(area[position[CURR_Y] - 1][position[CURR_X] + 1] == type)
	{
		gotObjective++;
	}
	if(area[position[CURR_Y] + 1][position[CURR_X] + 1] == type)
	{
		gotObjective++;
	}
	if(area[position[CURR_Y]][position[CURR_X]] == type)
	{
		gotObjective++;
	}
	

	return gotObjective;	
}