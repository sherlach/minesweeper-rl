#ifndef H_DISPLAY
#define H_DISPLAY

#include "config.h"
#include "map.h"
#include "player.h"
#include <ncurses.h>
#include <stdbool.h>
int setup_windows(WINDOW **, WINDOW **);
int update_status(char *, WINDOW *);

int main_mode_keys(WINDOW *, struct player *, struct map_tile[MAP_Y][MAP_X],
                   int, bool);

int main_mode_display(WINDOW *, struct map_tile[MAP_Y][MAP_X], struct position,
                      bool);

int dead_mode_keys(WINDOW *);

#endif
