#ifndef H_PLAYER
#define H_PLAYER

#include "map.h"
#include "config.h"

struct player {
	struct position player_pos;
	int hp;
};

int movep(struct player, struct position newpos, struct map_tile map[MAP_Y][MAP_X]);
#endif

