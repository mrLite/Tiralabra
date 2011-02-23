#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "helpers.h"
#include "negamax.h"

main() {
	int GRID_SIZE;
	int number;
	
	printf(" \033[2J");
	//system("clear");
	
	printf("O X O X O X O X O X O X O X O X O X O\n");
	printf("X                                   X\n");
	printf("O  Welcome to noughts and crosses!  O\n");
	printf("X                                   X\n");
	printf("O X O X O X O X O X O X O X O X O X O\n\n");
	
	while(1) {
		printf("Menu:\n");
		printf("1\t3X3 game grid\n");
		printf("0\tExit\n");
		int input;
		scanf("%d", &input);
		if (input == 0)
			exit(EXIT_SUCCESS);
		else if (input == 1) {
			GRID_SIZE = 9;
			break;			
		}
		else {
			printf("Not a valid option!\n");
			continue;
		}
	}
	
	int* grid = malloc(sizeof(int)*GRID_SIZE);
	int i;
	for (i = 0; i < GRID_SIZE; i++) {
		grid[i] = 0;
	}
	
	while(1) {
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
		move cpu = negamax(grid, 2);
		printf("CPU: %d\t%d\n", cpu.slot+1, cpu.max);
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
	
	free(grid);
	return 0;
}