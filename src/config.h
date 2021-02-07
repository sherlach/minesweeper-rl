#ifndef H_CONFIG
#define H_CONFIG


#define DEBUG

/* Keymap definitions */

#define NORTH 'k'
#define EAST 'l'
#define SOUTH 'j'
#define WEST 'h'
#define NORTH_WEST 'y'
#define SOUTH_WEST 'b'
#define NORTH_EAST 'u'
#define SOUTH_EAST 'n'

#define DOWN '>'

#define STATUS 's'
#define STATUS_TOGGLE 'S'
#define INVENTORY 'i'
#define MAP_VIEW 'm'

#define QUIT 'q'
/* Map icon definitions */

#define ICON_PLAYER '@'
#define UNEXPLORED '#'
// etc.

/* Game definitions */

// Unless you know what you are doing, don't edit these values!
/* box x and box y are the size the game box will appear. Adjust to fit your screen.
 * Too small is very bad. 
 */

#define BOX_X 70
#define BOX_Y 20

/* eventually the map size will be different per floor, currently it's set as a 
 * blanket quantity. To avoid undefined behaviour, please try to keep this 
 * larger than the box size. Also please note that indices 0 and MAX aren't 
 * traversable.
 *
 */
#define MAP_X 100
#define MAP_Y 100


#endif
