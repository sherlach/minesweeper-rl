#ifndef H_MAP
#define H_MAP

#include "config.h"
#include <stdbool.h>

struct map_tile {
	char display; //how does it appear on the display	
	bool explored; //has it been explored yet
	bool exploding; //is the tile explosive? (a mine)
	bool sand; //is this soft sand to drill down through?
};

struct position {
	int x;
	int y;
};

int init_map(struct map_tile[MAP_Y][MAP_X]);
int update_numbers(struct map_tile map[MAP_Y][MAP_X]);
#endif
