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
void movePlayer(char **area, char move, int turn)
{	
	
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
	
	position[CURR_X + turn] = position[CURR_X];
	position[CURR_Y + turn] = position[CURR_Y];


	victoryCount += checkObjective(area, OBJECTIVE);
	lives -= checkObjective(area, BOMB);
	lives += checkObjective(area, LIVEBOOST);
	if(checkObjective(area, HOSTILE))
	{
		lives -= checkObjective(area, HOSTILE);
		hostileStat = TRUE;
	}

	renderPlayer(area);
}


/*
A function to move the hostile after the player. The hostile follows a simple algorithm:
If the player's X or Y coordinates are greater than his, increment them by 1.
If the player's X or Y coordinates are smaller than his, decrement them by 1.
Input: Area of the game, array of hostile coordinates, hostile status(Whether or not he is active).
Output: None.
*/
void moveHostile(char **area, int hostilePos[], int hostileStat)
{

	if(hostileStat == FALSE)
	{
		if(position[CURR_X] > hostilePos[HOSTILE_X] && hostilePos[HOSTILE_X] != cols - 1)
		{
			area[hostilePos[HOSTILE_Y]][hostilePos[HOSTILE_X]] = TILE;

			hostilePos[HOSTILE_X]++;

			area[hostilePos[HOSTILE_Y]][hostilePos[HOSTILE_X]] = HOSTILE; 
		}
		else if (position[CURR_X] < hostilePos[HOSTILE_X] && hostilePos[HOSTILE_X] != 0)
		{
			area[hostilePos[HOSTILE_Y]][hostilePos[HOSTILE_X]] = TILE;

			hostilePos[HOSTILE_X]--;

			area[hostilePos[HOSTILE_Y]][hostilePos[HOSTILE_X]] = HOSTILE; 
		}

		if(position[CURR_Y] > hostilePos[HOSTILE_Y] && hostilePos[HOSTILE_Y] != rows - 1)
		{
			area[hostilePos[HOSTILE_Y]][hostilePos[HOSTILE_X]] = TILE;

			hostilePos[HOSTILE_Y]++;

			area[hostilePos[HOSTILE_Y]][hostilePos[HOSTILE_X]] = HOSTILE;
		}
		else if(position[CURR_Y] < hostilePos[HOSTILE_Y] && hostilePos[HOSTILE_Y] != 0)
		{
			area[hostilePos[HOSTILE_Y]][hostilePos[HOSTILE_X]] = TILE;

			hostilePos[HOSTILE_Y]--;

			area[hostilePos[HOSTILE_Y]][hostilePos[HOSTILE_X]] = HOSTILE;
		}
	}
}




void initObjective(char **area, int amount, int bombAmount, int lifeCount)
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
	count = 0;
	while(count < lifeCount){
		tempX = rand() % cols;
		tempY = rand() % rows;

		if(area[tempY][tempX] == TILE)
		{
			count++;
			area[tempY][tempX] = LIVEBOOST;
		}
	}

}

/*
A function to initialize the hostile bot.
Input: Area of the game, array of hostile's coordinates.
Output: None.
*/
void initHostile(char **area, int hostilePos[])
{
	int tempX = 0;
	int tempY = 0;
	int status = 0;

	srand(time(0));

	while(status == FALSE)
	{
		tempX = rand() % cols;
		tempY = rand() % rows;

		if(area[tempY][tempX] == TILE)
		{
			status = TRUE;
			area[tempY][tempX] = HOSTILE;

			hostilePos[HOSTILE_X] = tempX;
			hostilePos[HOSTILE_Y] = tempY;
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
