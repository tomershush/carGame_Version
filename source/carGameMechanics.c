#include "carGameGraphics.h"






/*
A function to initialize the game area using a dynamic array.
Input: Pointer to pointer of type char to represent the game area, number of rows, number of cols.
Output: None.
*/
char **initArea()
{
	int i = 0;
	int j = 0;
	char **area = NULL;
	area = (char**)malloc(rows * sizeof(char*));
	

	for(i = 0; i < rows; i++)
	{
		area[i] = (char*)malloc(cols * sizeof(char));
		
		
		for(j = 0; j < cols; j++)
		{
			area[i][j] = TILE;
		}
	}
	return area;
	
}

/*
A function to free a previously allocated 2D array.
Input: 2D array, number of rows, number of cols.
Output: None. 
*/
void freeArea(char **area)
{
	int i = 0;
	
	for(i = 0; i < rows; i++)
	{
		free(area[i]);
	}
	free(area);
}


/*
A function to move the player to a new position.
Input: 2D array that represents the game area, move char that represents the direction of the player movement.
Output: None.
*/
void movePlayer(char **area, char move)
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






void initObjective(char **area, int amount, int bombAmount)
{
	int count = 0;
	int tempX = 0;
	int tempY = 0;
	srand(time(0));
	
	while(count < amount)
	{
		tempX = rand() % cols;
		tempY = rand() % rows;

		if(area[tempY][tempX] == TILE)
		{
			count++;
			area[tempY][tempX] = OBJECTIVE;
		}
	}
	count = 0;

	while(count < bombAmount)
	{
		tempX = rand() % cols;
		tempY = rand() % rows;

		if(area[tempY][tempX] == TILE)
		{
			count++;
			area[tempY][tempX] = BOMB;
		}
	}

}

int checkObjective(char **area, char type)
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