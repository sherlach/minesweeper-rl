#ifndef H_DISPLAY
#define H_DISPLAY

#include <ncurses.h>
#include "map.h"
#include "config.h"
#include "player.h"
int setup_windows(WINDOW**, WINDOW**);
int update_status(char *, WINDOW*);

int main_mode_keys(WINDOW*, struct player*, struct map_tile[MAP_Y][MAP_X]);
int main_mode_display(WINDOW*, struct map_tile[MAP_Y][MAP_X], struct position); 

#endif
