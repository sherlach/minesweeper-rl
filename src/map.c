#include "map.h"

int init_map(struct map_tile map[MAP_Y][MAP_X], int depth) {
	int i, j;
	for (i = 0; i < MAP_Y; i++) {
		for (j = 0; j < MAP_X; j++) {
			map[i][j].display = ' ';
			map[i][j].explored = false;
			map[i][j].exploding = false;
		}
	}

	map[48][48].exploding = true; //test the explosion logic
	map[48][48].display = MINE;

	map[42][46].exploding = true;
	map[42][46].exploding = MINE;
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
	int i, j, c;
	/* 
	 * for every tile, sum the 8 surrounding tiles (if they exist)
	 *  
	 *  my approach is to do the first row/column and last row/column 
	 *  respectively on their own rather than check for tile validity
	 *  constantly
	 *
	 *  effectively, there are 9 cases.
	 *                  
	 *                  j  j  j
	 *
	 * i = 1            1--5--2
	 *                  |.....|
	 * i = for(;;)      8..9..6
	 *                  |.....|
	 * i = MAP_Y-1      3--7--4
	 */ 	 

	return 0;
}


