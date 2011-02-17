#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void initrand() {
    srand((unsigned int)(time(NULL)));
}

// Returns 1 if the grid is full.
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
	if (grid[0] == 1 && grid[1] == 1 && grid[2] == 1)
		return 1;
	else if (grid[3] == 1 && grid[4] == 1 && grid[5] == 1)
		return 1;
	else if (grid[6] == 1 && grid[7] == 1 && grid[8] == 1)
		return 1;
	else if (grid[0] == 1 && grid[3] == 1 && grid[6] == 1)
		return 1;
	else if (grid[1] == 1 && grid[4] == 1 && grid[7] == 1)
		return 1;
	else if (grid[2] == 1 && grid[5] == 1 && grid[8] == 1)
		return 1;
	else if (grid[0] == 1 && grid[4] == 1 && grid[8] == 1)
		return 1;
	else if (grid[2] == 1 && grid[4] == 1 && grid[6] == 1)
		return 1;
	else if (grid_full(grid))
		return 10;
}

void cpu_turn(int grid[]) {
	while(1) {
		int n = rand() % 9;
		if (grid[n] == 0) {
			grid[n] = 2;
			break;
		}
	}
}

main() {
	int number;
	int grid[9];
	int i;
	for (i = 0; i < 9; i++) {
		grid[i] = 0;
	}
	
	while (1) {
		initrand();
		
		print_grid(grid);
		
		printf("It's your turn, pick a number.\n0 will quit the game.\n");
		scanf("%d", &number);
	
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
		
		cpu_turn(grid);
		}
		
		return 0;
}