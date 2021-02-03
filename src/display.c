#include "display.h"
#include "config.h"
#include <ncurses.h>

//WINDOW *map;
//WINDOW *status;

/*int setup() {
	return setup_windows(map, status);
}
*/

int setup_windows(WINDOW **map, WINDOW **status) {
	initscr();
	/* potentially this should be replaced with getmaxyx */

	if (BOX_X > COLS || BOX_Y > LINES) {
		endwin();
		fprintf(stderr, "Window size error. %d > %d or %d > %d.", BOX_X, COLS, BOX_Y, LINES);
		return -1;
	}

	/* calculate where the map will go. Dead centre. */

	int startx = (COLS - BOX_X)/2;
	int starty = (LINES - BOX_Y)/2;
	
	*status = newwin(1, BOX_X, starty, startx);
	*map = newwin(BOX_Y, BOX_X, starty+1, startx);

	/* status belongs one row up */

	/* finally, initialise the visual element/borders of them */
	box(*map, 0, 0);
	wprintw(*status, "> ");
	wrefresh(*map);
	wrefresh(*status);
	return 0;
}

int update_status(char *input_str, WINDOW *status) {
	wprintw(status, "> %s", input_str);
	wrefresh(status);
	wgetch(status);
	return 0;
}

/* There are 3 display modes. Main mode (move and mine) Map [explore] mode 
 * (fly about the map to view numbers but not enemies.) Inventory mode 
 * (view dat inventory). We need keypress and viewing opts for both.
 */

int main_mode_keys(WINDOW *win) {
	
	switch(wgetch(win)) {
		//case NORTH:
		//	update_status("north");
	}
	return 0;
}
