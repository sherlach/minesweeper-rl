#include "display.h"
#include "config.h"
#include "map.h"
#include <ncurses.h>

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
	int x;
	wmove(status, 0, 0);
	for (x = 0; x < getmaxx(status); x++) {
		wprintw(status, " ");
	}
	wmove(status, 0, 0);
	wprintw(status, "> %s", input_str);
	wrefresh(status);
	return 0;
}

/* There are 3 display modes. Main mode (move and mine) Map [explore] mode 
 * (fly about the map to view numbers but not enemies.) Inventory mode 
 * (view dat inventory). We need keypress and viewing opts for both.
 */

int main_mode_keys(WINDOW *win) {
	
	switch(wgetch(win)) {
		case NORTH:
			update_status("north", win);
			return 0;	
		case SOUTH:
			update_status("south", win);
			return 0;	
		case WEST:
			update_status("west ", win); // hack
			return 0;	
		case EAST:
			update_status("east ", win);
			return 0;	
		case NORTH_WEST:
			update_status("northwest", win);
			return 0;
		case SOUTH_WEST:
			update_status("southwest", win);
			return 0;
		case NORTH_EAST:
			update_status("northeast", win);
			return 0;
		case SOUTH_EAST:
			update_status("southeast", win);
			return 0;
		case QUIT:
			return 1;
		default:
			update_status("invalid case", win);
			return 0;
	}
	return 1;
}

int main_mode_display(WINDOW *win, struct map_tile map[MAP_Y][MAP_X], struct position player_pos) {
	/* so the map window is a subsection of the overall map. We draw that
	 * in, as much as will fit in the display port. Then we draw the @ in
	 * the middle
	 */
	int y, x;
	getmaxyx(win, y, x); //viewport size
	// MAP_X and MAP_Y is the overall map size
	//
	// We need to
	// 1. find the correct portion of the map array
	//    (if the array would stretch past legal bounds, ignore)
	// 2. find the symbols they use and print them
	
	return 0;
}
