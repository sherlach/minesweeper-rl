#include "config.h"
#include "display.h"
#include "player.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

enum errortypes { none, winsize, colour };
enum exittypes { normal, death };

int init_ncurses();
int close();
int main_game(WINDOW *, WINDOW *);

int main(int argc, char *argv[]) {
  WINDOW *map = NULL;
  WINDOW *status = NULL;

  if (setup_windows(&map, &status) == winsize) {
    return winsize;
  }

#ifdef COLOUR
  if (init_ncurses() == colour) {
    return colour;
  }
#else
  init_ncurses();
#endif

  int excode = main_game(map, status);
  close();
  if (excode > 9) {
    switch (excode - 10) {
    case normal:
      printf("Cause of death: suicide.\n");
      break;
    case death:
      printf("Cause of death: HP dropped to 0.\n");
      break;
    }
  }
  // printf("Game exited with code %d\n", excode);
  return 0;
}

int init_ncurses() {
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

#ifdef COLOUR
  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal doesn't support colour. Please remove COLOUR from "
           "config.h.\n");
    return colour;
  }
  start_color();
  init_pair(1, ONE_SYM, ONE_BACK);
  init_pair(2, TWO_SYM, TWO_BACK);
  init_pair(3, THREE_SYM, THREE_BACK);
  init_pair(4, FOUR_SYM, FOUR_BACK);
  init_pair(5, FIVE_SYM, FIVE_BACK);
  init_pair(6, SIX_SYM, SIX_BACK);
  init_pair(7, SEVEN_SYM, SEVEN_BACK);
  init_pair(8, EIGHT_SYM, EIGHT_BACK);
  init_pair(0, DEF_SYM, DEF_BACK);
#endif
  return 0;
}

int close() {
  endwin();
  return 0;
}

int main_game(WINDOW *map, WINDOW *status) {
  enum gamestate {
    state_new_level,
    state_main,
    state_map,
    state_invent,
    state_dead
  }; // state_dead is relatable content
  int returncode = 1;
  struct map_tile levelmap[MAP_Y][MAP_X];
  int depth = 10;
  bool status_toggle = false;
  struct player player;
  bool alive = true;
  player.position.x = MAP_X / 2;
  player.position.y = MAP_Y / 2;

  int state = state_new_level;
  /* initialise player */
  init_player(&player);

  // srand(69105);

  srand(time(NULL));
  /* RETURNCODES: make this an enum once they're more set in stone
   *
   * still in loop
   * 0
   * 1 normal, valid input & move
   * 2 statusbar toggled
   * 3 descend to next floor
   *
   * exit loop
   * 10 player chose to quit
   * 11 player died
   */
  while (returncode < 10) {

    if (state == state_new_level) {
      init_map(levelmap, depth);
      safe_landing(levelmap, player.position);
      main_mode_display(map, levelmap, player.position, alive);
      state = state_main;
    }

    if (state == state_main) {
      returncode =
          main_mode_keys(status, &player, levelmap, depth, status_toggle);
      if (returncode == 2) {
        status_toggle = !status_toggle;
      }

      if (returncode == 3) {
        depth += 10;
        state = state_new_level;
      }

      update_numbers(levelmap);
      main_mode_display(map, levelmap, player.position, alive);
    }

    if (state == state_dead) {
      main_mode_display(map, levelmap, player.position, alive);
#ifdef DEBUG
      dead_mode_keys(status);
      alive = true;
      state = state_main;
      returncode = 0;
      update_status("Reviving due to debug mode", status);
      player.hp = 10;
#else
      returncode = dead_mode_keys(status);
#endif
    }

    if (player.hp <= 0) {
      state = state_dead;
      alive = false;
    }
  }

  return returncode;
}
