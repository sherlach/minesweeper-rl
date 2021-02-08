#ifndef H_PLAYER
#define H_PLAYER

#include "map.h"
#include "config.h"

struct player {
	struct position position;
	int hp;
};

int init_player(struct player*);
int move_player(struct player*, struct position, struct map_tile[MAP_Y][MAP_X]);
#endif

