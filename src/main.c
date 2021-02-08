#include "config.h"
#include "display.h"
#include "player.h"
#include <ncurses.h>
#include <stdbool.h>

enum errortypes { none, winsize };
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

  init_ncurses();
  int excode = main_game(map, status);
  close();
  if (excode > 9) {
	  switch (excode - 10) {
		  case normal:
			  printf("Cause of death: suicide.");
			  break;
		  case death:
			  printf("Cause of death: HP dropped to 0.");
			  break;
	  }
  }
  //printf("Game exited with code %d\n", excode);
  return 0;
}

int init_ncurses() {
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  return 0;
}

int close() {
  endwin();
  return 0;
}

int main_game(WINDOW *map, WINDOW *status) {
  enum gamestate { state_new_level, state_main, state_map, state_invent, state_dead }; //state_dead is relatable
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
  /* RETURNCODES: make this an enum once they're more set in stone
   * 
   * still in loop
   * 0
   * 1 normal, valid input & move
   * 2 statusbar toggled 
   * 3
   * 
   * exit loop
   * 10 player chose to quit
   * 11 player died
   */
  while (returncode < 10) {

    if (state == state_new_level) {
	    init_map(levelmap, depth);
	    state = state_main;
    }

    if (state == state_main) {
        returncode = main_mode_keys(status, &player, levelmap, depth, status_toggle);
	if (returncode == 2) {
		status_toggle = !status_toggle;
	}
        main_mode_display(map, levelmap, player.position, alive);
    }

    if (state == state_dead) {
	   main_mode_display(map, levelmap, player.position, alive); 
	   returncode = dead_mode_keys(status);
    }


    if (player.hp <= 0) {
	   state = state_dead; 
	   alive = false;
    }
  }

  return returncode;
}
