#include "carGameGraphics.h"




void printIntro();

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

void printIntro()
{
	printw("Welcome to \"CAR GAME\"\nUse the W A S D keys to move! (In CAPS)\nObjects list:\n%c - Regular tile\n%c - Objectives\n%c - Hazards\n%c - Player", TILE, OBJECTIVE, BOMB, PLAYER);
	refresh();
	getch();
}