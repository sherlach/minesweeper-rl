#include "map.h"
#include <math.h>
#include <stdlib.h>

int init_map(struct map_tile map[MAP_Y][MAP_X], int depth) {
  int threshold;
  /* part one: calculate probability threshold based on depth */

  /* I like this formula but it's way too hard right now. Maybe once
   * powerups are implemented... */

  // threshold = (int)(40*log((double)depth+60)-154);
  threshold = (int)(40 * log((double)depth + 60) - 165);

  /* part two: use the threshold to calculate what's going on */

  enum tile_type { normal, mine, sand };
  int i, j;
  int curr_tile_type;

  for (i = 0; i < MAP_Y; i++) {
    for (j = 0; j < MAP_X; j++) {
      curr_tile_type = normal;

      int r = rand() % 100;

      if (r < threshold)
        curr_tile_type = mine;
      else if (r % 50 == 0)
        curr_tile_type = sand;

      if (curr_tile_type == normal) {
        map[i][j] = (struct map_tile){.display = EMPTY,
                                      .explored = false,
                                      map[i][j].exploding = false,
                                      map[i][j].sand = false};
      } else if (curr_tile_type == mine) {
        map[i][j] = (struct map_tile){.display = MINE,
                                      .explored = false,
                                      .exploding = true,
                                      .sand = false};
      } else if (curr_tile_type == sand) {
        map[i][j] = (struct map_tile){.display = SAND,
                                      .explored = false,
                                      .exploding = false,
                                      .sand = true};
      }
    }
  }

  /* Finally, guarantee that a sand tile will exist */
  i = (rand() % MAP_Y - 1) + 1;
  j = (rand() % MAP_X - 1) + 1;
  map[i][j].display = SAND;
  map[i][j].explored = false;
  map[i][j].exploding = false;
  map[i][j].sand = true;

  return 0;
}
/*
 * tile types:
 *
 * empty
 * sand
 * mine (explosive empty)
 */

int update_numbers(struct map_tile map[MAP_Y][MAP_X]) {
  int i, j, c;
  int a, b;
  /*
          for each thing
             if our thing isn't a sand and isn't explosive
                then iterate through a 3x3 grid around it
                   -> guard condition check not < 1 or > MAP_? -1
  */

  for (i = 1; i < MAP_Y; i++) {
    for (j = 1; j < MAP_X; j++) {
      if (!map[i][j].exploding && !map[i][j].sand) {
        c = 0;
        for (a = -1; a < 2; a++) {
          for (b = -1; b < 2; b++) {
            if ((i + a > 0) && (i + a < MAP_Y) && (j + b > 0) &&
                (j + b < MAP_X)) {
              if (map[i + a][j + b].exploding) {
                c++;
              }
            }

            switch (c) {
            case 0:
              map[i][j].display = ' ';
              break;
            /*
            case 1:
              map[i][j].display = '1';
              break;
            case 2:
              map[i][j].display = '2';
              */
            default:
              map[i][j].display = '0' + c;
              break;
            }
          }
        }
      }
    }
  }

  return 0;
}

int safe_landing(struct map_tile map[MAP_Y][MAP_X],
                 struct position player_pos) {
  // make the squares surrounding player_pos empty and non explosive.
  int i, j;
  for (i = -1; i < 2; i++) {
    for (j = -1; j < 2; j++) {

      if (map[player_pos.y + i][player_pos.x + j].exploding) {
        map[player_pos.y + i][player_pos.x + j].exploding = false;
        map[player_pos.y + i][player_pos.x + j].display = EMPTY;
      }

      map[player_pos.y + i][player_pos.x + j].explored = true;
    }
  }
  return 0;
}
