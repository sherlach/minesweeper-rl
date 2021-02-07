#include "player.h"
#include "config.h"

int init_player(struct player* player) {
	player->hp = 10;
	return 0;
}
int movep(struct position* player_pos, struct position newpos, struct map_tile map[MAP_Y][MAP_X]) {
	if (newpos.x > 0 && newpos.x < MAP_X && newpos.y > 0 && newpos.y < MAP_Y) {
	if (map[newpos.y][newpos.x].explored) {
		player_pos->x = newpos.x;
		player_pos->y = newpos.y;
	} else {
		map[newpos.y][newpos.x].explored = 1;
	}
	}
	return 0;
}
