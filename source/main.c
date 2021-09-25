#include "carGameGraphics.h"




void printIntro();

int position[POSITION_POINTS] = {0};
int lives = LIVES;
int victoryCount = 0;
int rows = 0;
int cols = 0;

int main()
{
	char **area = NULL;
	char move = 0;
	int mode = 0;
	int turn = 0;
	int bombCount = 0;
	int difficulty = 25;

	position[CURR_X] = START_X;
	position[CURR_Y] = START_Y;

	
	initscr();

	do
	{	
	printw("What mode would you like?\n[1] - Developer mode (Can cause the game to break)\n[2] - Regular mode\n");
	scanw("%d", &mode);
	}while(mode > 2 || mode < 1);

	if(mode == 1)
	{
		printw("Enter number of rows: ");
		scanw("%d", &rows);

		printw("Enter number of cols: ");
		scanw("%d", &cols);
	}
	else
	{
		rows = 10;
		cols = 25;
	}


	

	noecho();

	bombCount = rows * cols / difficulty;

	area = initArea();
	initObjective(area, OBJECTIVE_COUNT, bombCount);

	printIntro();

	renderPlayer(area);
	renderArea(area);
	do
	{
		move = getch();

		if(move == RIGHT && position[CURR_X] != cols - 2 || move == LEFT && position[CURR_X] != 1 || move == UP && position[CURR_Y] != 1 || move == DOWN && position[CURR_Y] != rows - 2)
		{
			movePlayer(area, move, turn);
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

	freeArea(area);

	return 0;
}

void printIntro()
{
	printw("Welcome to \"CAR GAME\"\nUse the W A S D keys to move! (In CAPS)\nObjects list:\n%c - Regular tile\n%c - Objectives\n%c - Hazards\n%c - Player", TILE, OBJECTIVE, BOMB, PLAYER);
	refresh();
	getch();
}
