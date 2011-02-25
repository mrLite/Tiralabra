#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "main.h"
#include "helpers.h"
#include "negamax.h"

// Prints the game grid showing available slots as numbers.
void print_grid(int grid[]) {
	int i;
	for (i = 0; i < GRID_SIZE; i++) {
		if (grid[i] == 0)
			printf("%d", i+1);
		else if (grid[i] == 1)
			printf("X");
		else
			printf("O");
			
		if ((i+1)%GRID_SIDE == 0)
			printf("\n");
		else
			printf("|");
		}
}

// Returns 1 if the grid is full and 0 if there's at least one free slot.
int grid_full(int grid[]) {
	int full = 1;
	int i;
	for (i = 0; i < GRID_SIZE; i++) {
		if (grid[i] == 0)
			full = 0;
	}
	return full;
}

// Check to see if the slot in the game grid (1..9) chosen by the user is available.
// Returns 1 if available, 0 if not.
int check_availability(int grid[], int number) {
	int available;
	if (grid[number-1] != 0)
		available = 0;
	else if (grid[number-1] == 0)
		available = 1;
	return available;
}

// Checks the current game situation, returns 1 if X has won, -1 if O has won and 10 if it's a tie.
// Also returns 0 if the game hasn't ended yet.
int check_situation(int grid[]) {
	int situation;
	
	if (grid[0] == 1 && grid[1] == 1 && grid[2] == 1)
		situation = 1;
	else if (grid[3] == 1 && grid[4] == 1 && grid[5] == 1)
		situation = 1;
	else if (grid[6] == 1 && grid[7] == 1 && grid[8] == 1)
		situation = 1;
	else if (grid[0] == 1 && grid[3] == 1 && grid[6] == 1)
		situation = 1;
	else if (grid[1] == 1 && grid[4] == 1 && grid[7] == 1)
		situation = 1;
	else if (grid[2] == 1 && grid[5] == 1 && grid[8] == 1)
		situation = 1;
	else if (grid[0] == 1 && grid[4] == 1 && grid[8] == 1)
		situation = 1;
	else if (grid[2] == 1 && grid[4] == 1 && grid[6] == 1)
		situation = 1;

	else if (grid[0] == 2 && grid[1] == 2 && grid[2] == 2)
		situation = -1;
	else if (grid[3] == 2 && grid[4] == 2 && grid[5] == 2)
		situation = -1;
	else if (grid[6] == 2 && grid[7] == 2 && grid[8] == 2)
		situation = -1;
	else if (grid[0] == 2 && grid[3] == 2 && grid[6] == 2)
		situation = -1;
	else if (grid[1] == 2 && grid[4] == 2 && grid[7] == 2)
		situation = -1;
	else if (grid[2] == 2 && grid[5] == 2 && grid[8] == 2)
		situation = -1;
	else if (grid[0] == 2 && grid[4] == 2 && grid[8] == 2)
		situation = -1;
	else if (grid[2] == 2 && grid[4] == 2 && grid[6] == 2)
		situation = -1;
	
	else if (grid_full(grid))
		situation = 10;
	
	else
		situation = 0;
	
	return situation;
}

int game_over(int grid[]) {
	int rvalue;
	rvalue = check_situation(grid);
	rvalue = (rvalue == 1 || rvalue == -1 || rvalue == 10 ) ? 1 : 0;
	return rvalue;
}