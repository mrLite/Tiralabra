#include <stdio.h>

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

main() {
	int luku;
	int grid[9];
	int i;
	for (i = 0; i < 9; i++) {
		grid[i] = 0;
	}
	
	print_grid(grid);
	printf("It's your turn, pick a number.\n");
	scanf("%d", &luku);
	
	if (luku < 1)
		return 0;
	else if (luku > 9)
		return 0;
	else
		grid[luku-1] = 1;
		
	print_grid(grid);
	
	return 0;
}