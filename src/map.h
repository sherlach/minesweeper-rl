#ifndef H_MAP
#define H_MAP

// map_tile struct?
// map_slice struct?


struct map_tile {
	int display; //how does it appear on the display	
	char explored; //has it been explored yet
	char exploding; //is the tile explosive? (a mine)
	char sand; //is this soft sand to drill down through?
};

struct position {
	int x;
	int y;
};

#endif
