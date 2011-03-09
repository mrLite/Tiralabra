#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "main.h"
#include "helpers.h"
#include "negamax.h"

int main() {
	int number;		// This will be used to hold the player's move in the grid.
	int* grid;		// The game grid array.
	int input;		// User's input from the main menu.
	
	printf(" \033[2J\n"); // clears the screen.
	
	printf("O X O X O X O X O X O X O X O X O X O\n");
	printf("X                                   X\n");
	printf("O  Welcome to noughts and crosses!  O\n");
	printf("X                                   X\n");
	printf("O X O X O X O X O X O X O X O X O X O\n\n");
	
	// This loop is for the main menu.
	while(1) {
		printf("Main menu:\n");
		printf("1\t3X3 game grid\n");
		printf("2\t4X4 game grid\n");
		printf("0\tExit\n");
		
		scanf("%d", &input);
		
		if (input == 0)
			exit(EXIT_SUCCESS);
		else if (input == 1) {
			GRID_SIDE = 3;
			GRID_SIZE = GRID_SIDE*GRID_SIDE;
			break;			
		}
		else if (input == 2) {
			printf("Under construction. Sorry!\n");
			continue;
			// GRID_SIDE = 4;
			// GRID_SIZE = GRID_SIDE*GRID_SIDE;
			// break;
		}
		else {
			printf("Not a valid option!\n");
			continue;
		}
	}
	
	// Allocate the game grid and initialize it with zeros so all the slots are free.
	if ((grid = malloc(sizeof(int)*GRID_SIZE)) != NULL) {
		int i;
		for (i = 0; i < GRID_SIZE; i++) {
			grid[i] = 0;
		}
	}
	else {
		printf("I CAN HAS NO MEMORY!!1\n");
		exit(EXIT_FAILURE);
	}
	
	// This loop is being executed during the game and breaks when the game ends or if the user inputs the number 0.
	while(1) {
		print_grid(grid);
		
		printf("It's your turn, pick a number.\n0 will quit the game.\n");
		scanf("%d", &number);
		
		// Loop starts from the beginning until the user has input a number between 1 and GRID_SIZE.
		// After a valid input we'll check if the slot chosen by the user is free.
		if (number < 0 || number > GRID_SIZE) {
			printf("Please choose a number between 1 and %d\n", GRID_SIZE);
			continue;
		}
		else if (number == 0)
			break;
		else {
			if (check_availability(grid, number-1) == 0) {
				printf("The slot %d is already taken!\n", number);
				continue;
			}
			else if (check_availability(grid, number-1) == 1) {
				grid[number-1] = 1;
			}
		}
		// After the player's turn the game situation must be checked to see if it has ended, either in a win or in a tie.
		if (check_situation(grid) == 1) {
			print_grid(grid);
			printf("X has won the game!\n");
			break;
		}
		else if (check_situation(grid) == 10) {
			print_grid(grid);
			printf("Game ended in a tie.\n");
			break;
		}
		
		// Opponents turn, after which we check if it has won the game or if the game ended in a tie.
		move cpu = negamax(grid, 2);
		grid[cpu.slot] = 2;
		
		if (check_situation(grid) == -1) {
			print_grid(grid);
			printf("O has won the game!\n");
			break;
		}
		else if (check_situation(grid) == 10) {
			print_grid(grid);
			printf("Game ended in a tie.\n");
			break;
		}
	}
	// Free the memory allocated for the grid and set the pointer to NULL.
	free(grid);
	grid = NULL;
	
	return 0;
}