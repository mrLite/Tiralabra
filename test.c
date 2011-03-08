#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "helpers.h"
#include "negamax.h"
#include "test.h"

int grid_9[9];
int tests_run = 0;
int failed_tests = 0;
int GRID_SIZE = 9;
int GRID_SIDE = 3;

// Initialize the game grid with zeros.
void initialize_grid() {
	int i;
	for (i = 0; i < 9; i++) {
		grid_9[i] = 0;
	}
}

// Plays 50 games of noughts and crosses with two computer players competing against each other.
// Should return 50 ties if the algorithm works properly.
void test_negamax() {
	printf("running test test_negamax...\n");
	
	int ties = 0;
	int x_wins = 0;
	int o_wins = 0;
	printf("running 50 games of nougths and crosses.\n");
	
	initialize_grid();
	int i;
	for (i = 0; i < 50; i++) {
		while(1) {
			move cpu1 = negamax(grid_9, 1);
			grid_9[cpu1.slot] = 1;
	
			if (check_situation(grid_9) == 1) {
				x_wins++;
				break;
			}
			else if (check_situation(grid_9) == 10) {
				ties++;
				break;
			}
			move cpu2 = negamax(grid_9, 2);
			grid_9[cpu2.slot] = 2;
	
			if (check_situation(grid_9) == -1) {
				o_wins++;
				break;
			}
			else if (check_situation(grid_9) == 10) {
				ties++;
				break;
			}
		}
	}
	printf("number of X wins: %d\n", x_wins);
	printf("number of O wins: %d\n", o_wins);
	printf("number of ties: %d\n", ties);
	tests_run++;
}

// Tests if the function grid_full() returns a valid value.
void test_grid_full() {
	printf("running test test_grid_full...\n");
	
	initialize_grid();
	grid_9[0] = 1; grid_9[1] = 2; grid_9[2] = 1;
	grid_9[3] = 2; grid_9[4] = 1; grid_9[5] = 1;
	grid_9[6] = 1; grid_9[7] = 2; grid_9[8] = 2;
	if (grid_full(grid_9) != 1) {
		printf("test test_grid_full() failed\n");
		failed_tests++;
	}
	tests_run++;
}

// Tests if the function check_situation() returns valid values in three situations.
// First situation tests an empty grid where the game is still going and should return 0.
// Second situation tests a grid where X has won the game and thus should return 1.
// Third one tests the situation when the game has ended in a tie and should return 10.
void test_check_situation() {
	printf("running test test_check_situation...\n");
	
	initialize_grid();
	if (check_situation(grid_9) != 0) {
		printf("test test_check_situation() failed\n");
		failed_tests++;
	}
	
	initialize_grid();
		grid_9[0] = 1; grid_9[4] = 1; grid_9[8] = 1;
		if (check_situation(grid_9) != 1) {
			printf("test test_check_situation() failed\n");
			failed_tests++;
		}
		
		initialize_grid();
		grid_9[0] = 1; grid_9[1] = 2; grid_9[2] = 1;
		grid_9[3] = 1; grid_9[4] = 2; grid_9[5] = 2;
		grid_9[6] = 2; grid_9[7] = 1; grid_9[8] = 1;
		if (check_situation(grid_9) != 10) {
			printf("test test_check_situation() failed\n");
			failed_tests++;
		}
	
	tests_run++;
}

// Tests the availability of a slot in the game grid.
// First an empty slot should return 1 and a slot which has been used should return 0.
void test_check_availability() {
	printf("running test test_check_availability...\n");
		
	initialize_grid();
	
	grid_9[2] = 1;
	
	if (check_availability(grid_9, 1) != 1) {
		printf("test test_check_availability() failed\n");
		failed_tests++;
	}
	if (check_availability(grid_9, 2) != 0) {
		printf("test test_check_availability() failed\n");
		failed_tests++;
	}
	tests_run++;
}

// Runs the four test functions and prints the results.
int main() {
	test_check_availability();
	test_check_situation();
	test_grid_full();
	test_negamax();
	
	printf("\nTEST OUTCOME:\n");
	printf("number of tests run: %d\n", tests_run);
	printf("number of failed tests: %d\n", failed_tests);
}