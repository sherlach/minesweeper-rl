#include "player.h"

int movep(struct player player, struct position newpos, struct map_tile map[MAP_Y][MAP_X]) {
	player.position.x = newpos.x;
	player.position.y = newpos.y;
}
