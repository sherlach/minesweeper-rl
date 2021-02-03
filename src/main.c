#include <ncurses.h>
#include "config.h"
#include "display.h"

enum errortypes{none, winsize};

int init();
int close();
int main_game(WINDOW*, WINDOW*);

int main(int argc, char* argv[]) {
	WINDOW *map = NULL;
	WINDOW *status = NULL;
	
	//if (init(map, status) == winsize) { 
	//	return winsize;
	//}
	
	if (setup_windows(&map, &status) == winsize) {
		return winsize;
	}

	init();
	int excode = main_game(map, status);		
	close();
	return 0;
}

int init() {
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	return 0;
}

int close() {
	endwin();
	return 0;
}

int main_game(WINDOW* map, WINDOW* status) {
	enum gamestate{state_main, state_map, state_invent};
	int returncode = 0; 
	while (!returncode) {
		
	update_status("ol", status);	
	}
}
