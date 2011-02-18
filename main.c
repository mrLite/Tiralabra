#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "helpers.h"

void initrand() {
    srand((unsigned int)(time(NULL)));
}

// Chooses number from the range 0..9 pseudo-randomly and checks its availability in the grid until it finds a slot that is free.
void cpu_turn(int grid[]) {
	while(1) {
		initrand();
		int n = (int)(rand()) % 10;
		if (check_availability(grid, n+1) == 1) {
			grid[n] = 2;
			break;
		}
		else
			continue;
	}
}

main() {
	int number;
	int grid[9];
	int i;
	for (i = 0; i < 9; i++) {
		grid[i] = 0;
	}
	
	printf("O X O X O X O X O X O X O X O X O X O\n");
	printf("X                                   X\n");
	printf("O  Welcome to noughts and crosses!  O\n");
	printf("X                                   X\n");
	printf("O X O X O X O X O X O X O X O X O X O\n\n");
	
	while (1) {		
		print_grid(grid);
		
		printf("It's your turn, pick a number.\n0 will quit the game.\n");
		scanf("%d", &number);
		
		// Loop starts from the beginning until the user has input a number between 1 and 9.
		// After a decent input we'll check if the slot chosen by the user is free.
		if (number < 0 || number > 9)
			continue;
		else if (number == 0)
			break;
		else {
			if (check_availability(grid, number) == 0) {
				printf("The slot %d is already taken!\n", number);
				continue;
			}
			else if (check_availability(grid, number) == 1) {
				grid[number-1] = 1;
			}
		}
		
		// After the player's turn the game situation must be checked to see if it has ended, either in a win or a tie.
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
		cpu_turn(grid);
		
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
	
	return 0;
}