#include "config.h"
#include "display.h"
#include "player.h"
#include <ncurses.h>

enum errortypes { none, winsize };

int init_ncurses();
int close();
int main_game(WINDOW *, WINDOW *);

int main(int argc, char *argv[]) {
  WINDOW *map = NULL;
  WINDOW *status = NULL;

  if (setup_windows(&map, &status) == winsize) {
    return winsize;
  }

  init_ncurses();
  int excode = main_game(map, status);
  close();
  printf("Game exited with code %d\n", excode);
  return 0;
}

int init_ncurses() {
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

  int state = state_main;
  /* initialise player & map */
  init_map(levelmap);
  while (!returncode) {
    if (state == state_main) {
        returncode = main_mode_keys(status);
        main_mode_display(map, levelmap, player.player_pos);
    }
  }
  return returncode;
}
