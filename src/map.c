#include "map.h"

int init_map(struct map_tile map[MAP_Y][MAP_X], int depth) {
	int i, j;
	for (i = 0; i < MAP_Y; i++) {
		for (j = 0; j < MAP_X; j++) {
			map[i][j].display = ' ';
			map[i][j].explored = false;
		}
	}
	return 0;
}

/*
 * tile types:
 * 
 * empty
 * sand
 * mine (explosive empty)
 *
 */
int update_numbers(struct map_tile map[MAP_Y][MAP_X]) {
	int i, j;
	/* 
	 * for every tile, sum the 8 surrounding tiles (if they exist)
	 * if mine
	 */
	for ( i = 0; i < MAP_Y; i++) {
		for (j = 0; j < MAP_X; j++) {
			;
		}
	}
	return 0;
}


