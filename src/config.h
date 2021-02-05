#ifndef H_CONFIG
#define H_CONFIG

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
#define INVENTORY 'i'
#define MAP_VIEW 'm'

#define QUIT 'q'
/* Map icon definitions */

#define ICON_PLAYER '@'
// etc.

/* Game definitions */

/* box x and box y are the size the game box will appear. Adjust to fit your screen.
 * Too small is very bad. 
 */

#define BOX_X 70
#define BOX_Y 20


/* eventually the map size will be different per floor, currently it's set as a 
 * blanket quantity 
 */
#define MAP_X 100
#define MAP_Y 100


#endif
