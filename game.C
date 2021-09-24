#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 25
#define COLS 50
#define PLAYER_SIZE 5
#define START_Y ROWS / 2
#define START_X COLS / 2
#define OBJECTIVE_COUNT 5
#define BOMB_COUNT (ROWS * COLS) / 30
#define POSITION_POINTS 4
#define LIVES 3
#define TURN_CYCLE 3
#define CURR_X 0
#define PREV_X 1
#define CURR_Y 2
#define PREV_Y 3

#define PLAYER '*'
#define TILE '_'
#define OBJECTIVE '&'
#define BOMB '#'
#define RUN_OVER_HORIZONTAL '='
#define RUN_OVER_VERTICAL '|'
#define LEFT 'A'
#define RIGHT 'D'
#define UP 'W'
#define DOWN 'S'
#define QUIT 'Q'

void printIntro();
void initArea(char area[ROWS][COLS]);
void renderArea(char area[ROWS][COLS]);
void movePlayer(char area[ROWS][COLS], char move);
void renderPlayer(char area[ROWS][COLS]);
void deletePlayer(char area[ROWS][COLS], char moveType);
void initObjective(char area[ROWS][COLS], int amount, int bombAmount);
void deleteRoad(char area[ROWS][COLS]);
int checkObjective(char area[ROWS][COLS], char type);

int position[POSITION_POINTS] = {0};
int lives = LIVES;
int victoryCount = 0;

int main()
{
	char area[ROWS][COLS] = {0};
	char move = 0;
	int turn = 0;

	position[CURR_X] = START_X;
	position[CURR_Y] = START_Y;
	
	initscr();
	noecho();

	initArea(area);

	printIntro();

	renderPlayer(area);
	renderArea(area);
	do
	{
		move = getch();

		if(move == RIGHT && position[CURR_X] != COLS - 2 || move == LEFT && position[CURR_X] != 1 || move == UP && position[CURR_Y] != 1 || move == DOWN && position[CURR_Y] != ROWS - 2)
		{
			movePlayer(area, move);
			renderArea(area);
			turn++;

			if(victoryCount == OBJECTIVE_COUNT)
			{
				clear();
				printw("VICTORY ROYAL");
				refresh();
				getch();

				move = QUIT;
			}
			else if(lives <= 0)
			{
				clear();
				printw("YOU LOST!):");
				refresh();
				getch();

				move = QUIT;
			}
			else if(turn == TURN_CYCLE)
			{
				deleteRoad(area);
				turn = 0;
			}
		}	
	}while(move != QUIT);
	
	endwin();

	return 0;
}

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


void printIntro()
{
	printw("Welcome to \"CAR GAME\"\nUse the W A S D keys to move! (In CAPS)\nObjects list:\n%c - Regular tile\n%c - Objectives\n%c - Hazards\n%c - Player", TILE, OBJECTIVE, BOMB, PLAYER);
	refresh();
	getch();
}