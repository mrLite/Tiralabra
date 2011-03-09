#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "main.h"
#include "helpers.h"
#include "negamax.h"
#include "test.h"

///
/// Returns struct move {slot, value}, where slot is the index of the move on the game grid which yields the best value.
///
struct move negamax(int game_grid[], int player) {
	// To start with, we have to check if the game is still on.
	int situation = check_situation(game_grid);
	int max = -1;
	move best_move = {-1, -1};

	// check_situation() returns 0 if the game hasn't ended yet.
	if (situation == 0) {
		// For each legal move on the board, find the one which maximizes the minimum gain.
		int i;
		for(i = 0; i < GRID_SIZE; i++) {
			if (game_grid[i] == 0) {
				int* temp_grid = malloc(sizeof(int)*GRID_SIZE);
				if (temp_grid != NULL) {
					int n;
					for (n = 0; n < GRID_SIZE; n++) {
						temp_grid[n] = game_grid[n];
					}
					int current_slot = i;
					temp_grid[i] = player;

					move x = negamax(temp_grid, ((player%2)+1));
					if (-(x.max) > max) {
						best_move.max = -(x.max);
						best_move.slot = current_slot;
						max = -(x.max);
					}
					free(temp_grid);
				}
				else {
					printf("I CAN HAS NO MEMORY!!1\n");
					exit(EXIT_FAILURE);
				}
			}
		}
	}
	// Now, if the game has indeed ended, check_situation() returns:
	// 1 if X has won
	// -1 if O has won
	// 10 if the end result was a tie.
	else if (situation == 1) {
		if (player == 1) {
			best_move.max = 1;
		}
		else
			best_move.max = -1;
	}
	else if (situation == -1) {
		if (player == 2) {
			best_move.max = 1;
		}
		else
			best_move.max = -1;
	}
	else if (situation == 10) {
		best_move.max = 0;
	}
	else {
		printf("An unknown error has occured.\n");
		exit(EXIT_FAILURE);
	}
		
	return best_move;
}