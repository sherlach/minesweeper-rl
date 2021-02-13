#include "player.h"
#include "config.h"
#include <stdbool.h>

int init_player(struct player *player) {
  player->hp = 10;
  return 0;
}

int move_player(struct player *player, struct position newpos,
                struct map_tile map[MAP_Y][MAP_X]) {
  if (newpos.x > 0 && newpos.x < MAP_X && newpos.y > 0 && newpos.y < MAP_Y) {
    if (map[newpos.y][newpos.x].exploding) {
      player->hp = 0;
    }
    if (map[newpos.y][newpos.x].explored) {
      player->position.x = newpos.x;
      player->position.y = newpos.y;
    } else {
      map[newpos.y][newpos.x].explored = true;
    }
  }
  return 0;
}

bool check_player_descent(struct position pos,
                          struct map_tile map[MAP_Y][MAP_X]) {
  return map[pos.y][pos.x].sand;
}
