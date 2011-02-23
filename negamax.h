#ifndef NEGAMAX
#define NEGAMAX
typedef struct move {
	int slot;
	int max;
} move;
#endif

struct move negamax(int game_grid[], int player);