#include <ncurses.h>
#include "config.h"
#include "display.h"

enum errortypes{none, winsize};

int init();
int close();

int main(int argc, char* argv[]) {
	if (init() == winsize) { 
		return winsize;
	}
	close();
	return 0;
}

int init() {
	if (setup() != 0) {
		return winsize;
	}
	return 0;
}

int close() {
	endwin();
	return 0;
}
