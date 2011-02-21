#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "helpers.h"
#include "negamax.h"

int max;
int current_move;
int best_move;

// player X is 1 and O is 2.
int negamax(int game_grid[], int player) {
	// To start with, we have to check if the game is still on.
	int situation = check_situation(game_grid);
	max = -1;
	
	// check_situation() returns 0 if the game hasn't ended yet.
	if (situation == 0) {
		// Copy the game grid to a temporary grid.
		int temp_grid[9];
		int n;
		for (n = 0; n < 9; n++) {
			temp_grid[n] = game_grid[n];
		}
		
		// For each legal move on the board, find the one which maximizes the minimum gain.
		int i;
		for(i = 0; i < 9; i++) {
			if (temp_grid[i] == 0) {
				current_move = i;
				temp_grid[i] = player;
				
				int x = negamax(temp_grid, ((player%2)+1));
				temp_grid[x] = ((player%2)+1);
			}
		}
	// Now, if the game has indeed ended, check_situation() returns:
	// 1 if X has won
	// -1 if O has won
	// 10 if the end result was a tie.
	}
	else if (situation == 1) {
		if (player == 1) {
			max = 1;
			best_move = current_move;
		}
		else 
			max = -1;
	}
	else if (situation == -1) {
		if (player == 2) {
			max = 1;
			best_move = current_move;
		}
		else
			max = -1;
	}
	else if (situation == 10) {
		if (max < 0)
			best_move = current_move;
		max = 0;
	}
	else {
		printf("An unknown error has occured.\n");
		exit(EXIT_FAILURE);
	}
	
	// The return value is the index of the slot in grid[9], which has the best end result for player.
	return best_move;
}

/*
const int sign[2]={1,-1}   //0 is blue, 1 is red

int NegaMax(Board b, int depth, int color) {
    if (GameOver(b) or depth>MaxDepth)
        return sign[color]*Analysis(b)
    int max = -infinity
    for each legal move m in board b {
        copy b to c
        make move m in board c
        int x= - NegaMax(c, depth+1, 1-color)  //Note the "-" before "NegaMax"
        if (x>max) max = x
    }
    return max
}
*/