#include "config.h"
#include "display.h"
#include "player.h"
#include <ncurses.h>

enum errortypes { none, winsize };

int init();
int close();
int main_game(WINDOW *, WINDOW *);

int main(int argc, char *argv[]) {
  WINDOW *map = NULL;
  WINDOW *status = NULL;

  if (setup_windows(&map, &status) == winsize) {
    return winsize;
  }

  init();
  int excode = main_game(map, status);
  close();
  return 0;
}

int init() {
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  return 0;
}

int close() {
  endwin();
  return 0;
}

int main_game(WINDOW *map, WINDOW *status) {
  enum gamestate { state_main, state_map, state_invent };
  int returncode = 0;
  struct map_tile levelmap[MAP_Y][MAP_X];
  struct player player;
  player.player_pos.x = MAP_X / 2;
  player.player_pos.y = MAP_Y / 2;
  while (!returncode) {
    returncode = main_mode_keys(status);
    main_mode_display(map, levelmap, player.player_pos);
  }
}
