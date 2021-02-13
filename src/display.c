#include "display.h"
#include "config.h"
#include "map.h"
#include "player.h"
#include "stdbool.h"
#include <ncurses.h>

#define DEF_COLOUR 9

int setup_windows(WINDOW **map, WINDOW **status) {
  initscr();
  /* potentially this should be replaced with getmaxyx */

  if (BOX_X > COLS || BOX_Y > LINES) {
    endwin();
    fprintf(stderr, "Window size error. %d > %d or %d > %d.", BOX_X, COLS,
            BOX_Y, LINES);
    return -1;
  }

  /* calculate where the map will go. Dead centre. */

  int startx = (COLS - BOX_X) / 2;
  int starty = (LINES - BOX_Y) / 2;

  *status = newwin(1, BOX_X, starty, startx);
  *map = newwin(BOX_Y, BOX_X, starty + 1, startx);

  /* status belongs one row up */

  /* finally, initialise the visual element/borders of them */
  box(*map, 0, 0);
  wprintw(*status, "> ");
  wrefresh(*map);
  wrefresh(*status);
  return 0;
}

int update_status(char *input_str, WINDOW *status) {
  int x;
  // if (*input_str < getmaxx(status)-1) {
  wmove(status, 0, 0);
  for (x = 0; x < getmaxx(status); x++) {
    wprintw(status, " ");
  }
  wmove(status, 0, 0);
  wprintw(status, "> %s", input_str);
  wrefresh(status);
  //}

  return 1;
}

/* There are 3 display modes. Main mode (move and mine) Map [explore] mode
 * (fly about the map to view numbers but not enemies.) Inventory mode
 * (view dat inventory). We need keypress and viewing opts for both.
 */

int main_mode_keys(WINDOW *win, struct player *player,
                   struct map_tile map[MAP_Y][MAP_X], int depth,
                   bool status_toggle) {
  struct position newpos = {player->position.x, player->position.y};
  int j;
  char status_string[BOX_X - 3];
  switch (wgetch(win)) {
  case NORTH:
    j = sprintf(status_string, "north");
    newpos.y -= 1;
    move_player(player, newpos, map);
    break;
  case SOUTH:
    j = sprintf(status_string, "south");
    newpos.y += 1;
    move_player(player, newpos, map);
    break;
  case WEST:
    j = sprintf(status_string, "west");
    newpos.x -= 1;
    move_player(player, newpos, map);
    break;
  case EAST:
    j = sprintf(status_string, "east");
    newpos.x += 1;
    move_player(player, newpos, map);
    break;
  case NORTH_WEST:
    j = sprintf(status_string, "northwest");
    newpos.x -= 1;
    newpos.y -= 1;
    move_player(player, newpos, map);
    break;
  case SOUTH_WEST:
    j = sprintf(status_string, "southwest");
    newpos.x -= 1;
    newpos.y += 1;
    move_player(player, newpos, map);
    break;
  case NORTH_EAST:
    j = sprintf(status_string, "northeast");
    newpos.x += 1;
    newpos.y -= 1;
    move_player(player, newpos, map);
    break;
  case SOUTH_EAST:
    j = sprintf(status_string, "southeast");
    newpos.x += 1;
    newpos.y += 1;
    move_player(player, newpos, map);
    break;
  case DOWN:
    if (check_player_descent(player->position, map)) {
      update_status("Drilling down...", win);
      return 3;
    }

    j = sprintf(status_string, "attempting to drill down... failure!");
    break;

  case STATUS:
    j = sprintf(status_string, "HP: %d, Depth: %dm, GPS: (%d, %d)", player->hp,
                depth, player->position.x, player->position.y);
    break;
  case STATUS_TOGGLE:
    // HACK to display status immediately
    if (status_toggle) {
      j = sprintf(status_string, "Status bar toggled off.");
    } else {
      j = sprintf(status_string, "HP: %d, Depth: %dm, GPS: (%d, %d)",
                  player->hp, depth, player->position.x, player->position.y);
    }

    update_status(status_string, win);
    return 2;
  case QUIT:
    update_status("Player exited.", win);
    return 10;
#ifdef DEBUG
  case 'z':
    player->hp = 0;
    return 0;
#endif
  default:
    j = sprintf(status_string, "invalid input");
    break;
  }
  if (status_toggle) {
    j = sprintf(status_string, "HP: %d, Depth: %dm, GPS: (%d, %d)", player->hp,
                depth, player->position.x, player->position.y);
  }

  update_status(status_string, win);
  return 1;
}

int main_mode_display(WINDOW *win, struct map_tile map[MAP_Y][MAP_X],
                      struct position player_pos, bool alive) {
  /* so the map window is a subsection of the overall map. We draw that
   * in, as much as will fit in the display port. Then we draw the @ in
   * the middle
   */
  // BOX_X and BOX_Y is the viewport size
  // MAP_X and MAP_Y is the overall map size

  int vp_height = BOX_Y - 2;
  int vp_width = BOX_X - 2;

  int vp_h = vp_height / 2;
  int vp_w = vp_width / 2;

  // struct position player_disp_pos = {vp_w, vp_h}; //where to draw the player
  // relative to display

  struct position vp_o = {0,
                          0}; // the map co-ords that correspond to what 0,0 in
                              // the viewport is depicting (viewport_origin)

  // We need to
  // 1. find the correct portion of the map array
  //    (if the array would stretch past legal bounds, ignore)
  // 2. find the symbols they use and print them
  //

  if (player_pos.x + vp_w >= MAP_X) {
    vp_o.x = (MAP_X - BOX_X + 1);
  } else if (player_pos.x - vp_w < 0) {
    vp_o.x = 0;
  } else {
    vp_o.x = player_pos.x - vp_w;
  }

  if (player_pos.y + vp_h >= MAP_Y) {
    vp_o.y = (MAP_Y - BOX_Y + 1);
  } else if (player_pos.y - vp_h < 0) {
    vp_o.y = 0;
  } else {
    vp_o.y = player_pos.y - vp_h;
  }

  int i, j;
  for (i = 1; i < vp_height + 1; i++) {
    wmove(win, i, 1);
    for (j = 1; j < vp_width + 1; j++) {
      if (map[vp_o.y + i][vp_o.x + j].explored || !alive) {
#ifdef COLOUR
        if (map[vp_o.y + i][vp_o.x + j].display > '0' &&
            map[vp_o.y + i][vp_o.x + j].display < '9') {
          wattron(win, COLOR_PAIR(map[vp_o.y + i][vp_o.x + j].display - '0'));
          waddch(win, map[vp_o.y + i][vp_o.x + j].display);
          wattroff(win, COLOR_PAIR(map[vp_o.y + i][vp_o.x + j].display - '0'));
        } else {
          wattron(win, DEF_COLOUR);
#endif

          waddch(win, map[vp_o.y + i][vp_o.x + j].display);
#ifdef COLOUR
          wattroff(win, DEF_COLOUR);
        }
#endif
      } else {
#ifdef COLOUR
        wattron(win, DEF_COLOUR);
        waddch(win, UNEXPLORED);
        wattroff(win, DEF_COLOUR);
#else
        waddch(win, UNEXPLORED);
#endif
      }
    }
  }

  // mvwaddch the player pos, '@'
  if (alive)
    mvwaddch(win, player_pos.y - vp_o.y, player_pos.x - vp_o.x, ICON_PLAYER);
  wrefresh(win);
  return 0;
}

int dead_mode_keys(WINDOW *win) {
  switch (wgetch(win)) {
  case QUIT:
    return 11;
  }

  return 1;
}
