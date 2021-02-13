#include "player.h"
#include "config.h"
#include <stdbool.h>

int init_player(struct player *player) {
  player->hp = 10;
  return 0;
}

int move_player(struct player *player, struct position newpos,
                struct map_tile map[MAP_Y][MAP_X]) {
  struct map_tile *cur_tile = &map[newpos.y][newpos.x];
  if (newpos.x > 0 && newpos.x < MAP_X && newpos.y > 0 && newpos.y < MAP_Y) {
    if (cur_tile->exploding) {
      player->hp = 0;
    }
    if (cur_tile->explored) {
      player->position = newpos;
    } else {
      cur_tile->explored = true;
    }
  }
  return 0;
}

bool check_player_descent(struct position pos,
                          struct map_tile map[MAP_Y][MAP_X]) {
  return map[pos.y][pos.x].sand;
}
