#include "carGameGraphics.h"

#define DEV 1
#define REGULAR 2


void printIntro();

// Global variables 
int position[POSITION_POINTS] = {0};
int lives = LIVES;
int victoryCount = 0;
int rows = 0;
int cols = 0;
int hostileStat = 0;


int main()
{
	char **area = NULL;
	char move = 0;
	int mode = 0;
	int turn = 0;
	int bombCount = 0;
	int startX = 0;
	int startY = 0;
	int difficulty = DEFAULT_DIFFICULTY; // Difficulty decides how many bombs will be in the game.
	int hostilePosition[HOSTILE_COORDINATES] = {0};
	/*
		Formula for the number of bombs:
		(rows * cols) / difficulty = bombCount
	*/



	
	initscr(); // Starting the ncurses window.

	do // Loop for choosing game mode.
	{	
		printw("What mode would you like?\n[1] -Developer mode (Can cause the game to break)\n[2] - Regular mode\n");
		scanw("%d", &mode);
	}while(mode > REGULAR || mode < DEV);

	if(mode == DEV) // Enter developer mode.
	{
		printw("Enter number of rows: ");
		scanw("%d", &rows);

		printw("Enter number of cols: ");
		scanw("%d", &cols);
	}
	else // Enter regular mode.
	{
		rows = DEFAULT_ROWS;
		cols = DEFAULT_COLS;
	}
		//Player position will be in the middle of the area.
		startX = cols / 2; // Calculating the start position of the player.
		startY = rows / 2;

		position[CURR_X] = startX; //Setting the start position of the player.
		position[CURR_Y] = startY;


	

	noecho(); // Stop echoing keystrokes to prevent showing user actions on screen.

	bombCount = rows * cols / difficulty;

	area = initArea();
	initObjective(area, OBJECTIVE_COUNT, bombCount);
	initHostile(area, hostilePosition);

	printIntro();

	renderPlayer(area); // Showing the area and the player on the screen.
	renderArea(area);

	do // Game main loop.
	{
		move = getch(); // Get player's move.

		// Check if the move is valid and the player is not at the border.
		if(move == RIGHT && position[CURR_X] != cols - 2 || move == LEFT && position[CURR_X] != 1 || move == UP && position[CURR_Y] != 1 || move == DOWN && position[CURR_Y] != rows - 2)
		{
			movePlayer(area, move, turn);
			renderArea(area);
			turn++; 

			if(victoryCount == OBJECTIVE_COUNT) // Check if the player has won.
			{
				clear();
				printw("VICTORY ROYAL");
				refresh();
				getch();

				move = QUIT;
			}
			else if(lives <= 0) // Check if the player has lost.
			{
				clear();
				printw("YOU LOST!):");
				refresh();
				getch();

				move = QUIT;
			}
			else if(turn == TURN_CYCLE) // Check if the turn cycle has ended.
			{
				deleteRoad(area); // Clearing road marks.
				moveHostile(area, hostilePosition, hostileStat); // Move the hostile.
				turn = 0;
			}
		}	
	}while(move != QUIT);
	
	endwin(); // Close ncurses window.

	freeArea(area); // Free the dynamically allocated area.

	return 0;
}


/*
A function to print the game intro and instructions to the user.
Input: None.
Output: None.
*/
void printIntro()
{
	printw("Welcome to \"CAR GAME\"\nUse the W A S D keys to move! (In CAPS)\nObjects list:\n%c - Regular tile\n%c - Objectives\n%c - Hazards\n%c - Player", TILE, OBJECTIVE, BOMB, PLAYER);
	refresh();
	getch();
}
