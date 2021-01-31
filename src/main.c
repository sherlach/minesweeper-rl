#include <ncurses.h>
#include "config.h"


int init();
int close();

int main(int argc, char* argv[]) {
	if (init() != 0) { 
		close();
		return -1;
	}
	close();
	//printf("%d, %d", COLS, LINES);
	return 0;
}


int init() {
	initscr();
	if (BOX_X > COLS || BOX_Y > LINES) {
		fprintf(stderr, "Window size error. %d > %d or %d > %d.", BOX_X, COLS, BOX_Y, LINES);
		return -1;
	}
	return 0;
}

int close() {
	endwin();
	return 0;
}
