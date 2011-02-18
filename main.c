#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void initrand() {
    srand((unsigned int)(time(NULL)));
}

// Returns 1 if the grid is full and 0 if there's at least one slot free .
int grid_full(int grid[]) {
	int full = 1;
	int i;
	for (i = 0; i < 9; i++) {
		if (grid[i] == 0)
			full = 0;
	}
	return full;
}

// Prints the game grid showing available slots as numbers.
print_grid(int grid[]) {
	int i;
	for (i = 0; i < 9; i++) {
		if (grid[i] == 0)
			printf("%d", i+1);
		else if (grid[i] == 1)
			printf("X");
		else
			printf("O");
			
		if ((i+1)%3 == 0)
			printf("\n");
		else
			printf("|");
		}
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

// Chooses number from the range 0..9 pseudo-randomly and checks its availability in the grid until it finds a slot that is free.
void cpu_turn(int grid[]) {
	while(1) {
		initrand();
		int n = rand() % 10;
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