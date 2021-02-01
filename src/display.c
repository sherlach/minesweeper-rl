#include "display.h"
#include "config.h"
#include <ncurses.h>

WINDOW *map;
WINDOW *status;
int setup() {
	return setup_windows(map, status);
}
int setup_windows(WINDOW *map, WINDOW *status) {
	initscr();
	if (BOX_X > COLS || BOX_Y > LINES) {
		endwin();
		fprintf(stderr, "Window size error. %d > %d or %d > %d.", BOX_X, COLS, BOX_Y, LINES);
		return -1;
	}

	/* calculate where the map will go. Dead centre. */

	int startx = (COLS - BOX_X)/2;
	int starty = (LINES - BOX_Y)/2;
	
	map = newwin(BOX_Y, BOX_X, starty, startx);
	box(map, 0, 0);
	wrefresh(map);

	/* status belongs one row up */

	status = newwin(1, BOX_X, starty-1, startx);

	/* finally, initialise the visual element/borders of them */
	box(map, 0, 0);
	wprintw(status, "> ");
	return 0;
}

