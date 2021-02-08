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

  map[48][48].exploding = true; // test the explosion logic
  map[48][48].display = MINE;

  map[47][46].exploding = true;
  map[47][46].display = MINE;
  
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
              map[i][j].display = '0'+c;
              break;
            }
          }
        }
      }
    }
  }

  return 0;
}
