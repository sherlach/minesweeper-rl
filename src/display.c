#include "display.h"
#include "config.h"
#include "map.h"
#include "player.h"
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

int main_mode_keys(WINDOW *win, struct player* player, struct map_tile map[MAP_Y][MAP_X]) {
	struct position newpos = {player->position.x, player->position.y};
	switch(wgetch(win)) {
		case NORTH:
			update_status("north", win);
			newpos.y += 1;
			movep(&player->position, newpos, map);
			return 0;	
		case SOUTH:
			update_status("south", win);
			newpos.y -= 1;
			movep(&player->position, newpos, map);
			return 0;	
		case WEST:
			update_status("west", win); 
			newpos.x -= 1;
			movep(&player->position, newpos, map);
			return 0;	
		case EAST:
			update_status("east", win);
			newpos.x += 1;
			movep(&player->position, newpos, map);
			return 0;	
		case NORTH_WEST:
			update_status("northwest", win);
			newpos.x -= 1;
			newpos.y += 1;
			movep(&player->position, newpos, map);
			return 0;
		case SOUTH_WEST:
			update_status("southwest", win);
			newpos.x -= 1;
			newpos.y -= 1;
			movep(&player->position, newpos, map);
			return 0;
		case NORTH_EAST:
			update_status("northeast", win);
			newpos.x += 1;
			newpos.y += 1;
			movep(&player->position, newpos, map);
			return 0;
		case SOUTH_EAST:
			update_status("southeast", win);
			newpos.x += 1;
			newpos.y -= 1;
			movep(&player->position, newpos, map);
			return 0;
		case QUIT:
			return 1;
		default:
			update_status("invalid case", win);
			printf("(%d, %d)", player->position.x, player->position.y);
			return 0;
	}
	return 1;
}

int main_mode_display(WINDOW *win, struct map_tile map[MAP_Y][MAP_X], struct position player_pos) {
	/* so the map window is a subsection of the overall map. We draw that
	 * in, as much as will fit in the display port. Then we draw the @ in
	 * the middle
	 */
	// BOX_X and BOX_Y is the viewport size
	// MAP_X and MAP_Y is the overall map size

	int vp_height = BOX_Y-2;
	int vp_width = BOX_X-2;

	int vp_h = vp_height/2;
	int vp_w = vp_width/2;

	struct position player_disp_pos = {vp_w, vp_h}; //where to draw the player relative to display

	struct position vp_o = {0, 0}; //the map co-ords that correspond to what 0,0 in the viewport is depicting (viewport_origin)

	// We need to
	// 1. find the correct portion of the map array
	//    (if the array would stretch past legal bounds, ignore)
	// 2. find the symbols they use and print them
	//
	
	if (player_pos.x + vp_w > MAP_X) { 
		vp_o.x = (MAP_X-BOX_X);
		player_disp_pos.x -= (MAP_X-vp_w);
	} else if (player_pos.x - vp_w < 0) {
		vp_o.x = 0;
		player_disp_pos.x += vp_w;
	} else {
		vp_o.x = player_pos.x - vp_w;
	}

	if (player_pos.y + vp_h > MAP_Y) {
		vp_o.x = (MAP_Y-BOX_Y);
		player_disp_pos.y -= (MAP_Y-vp_h);
	} else if (player_pos.y - vp_h < 0) {
		vp_o.y = 0;
		player_disp_pos.y += vp_h;
	} else {
		vp_o.y = player_pos.y - vp_h;
	}

	int i, j;
	for (i = 1; i < vp_height+1; i++) {
		wmove(win, i, 1);
		for (j = 1; j < vp_width+1; j++) {
			if (map[vp_o.y+i][vp_o.x+j].explored) {
				waddch(win, map[vp_o.y+i][vp_o.x+j].display);
			} else {
				waddch(win, UNEXPLORED);
			}
		}
	}

	// mvwaddch the player pos, '@'	
	mvwaddch(win, player_disp_pos.y, player_disp_pos.x, ICON_PLAYER);
	wrefresh(win);
	return 0;
}
