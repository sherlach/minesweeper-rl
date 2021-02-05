#ifndef H_DISPLAY
#define H_DISPLAY

#include <ncurses.h>
#include "map.h"
//int setup();
int setup_windows(WINDOW**, WINDOW**);
//int test_box();
//int test(WINDOW *win);
int update_status(char *, WINDOW*);

int main_mode_keys(WINDOW*);
int main_mode_display(WINDOW*, struct position); 

#endif
