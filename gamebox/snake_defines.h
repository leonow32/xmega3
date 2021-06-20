#if COMPONENT_GAMEBOX
#ifndef SNAKE_DEFINES_H_
#define SNAKE_DEFINES_H_

// Enum to select one of possible color modes
enum Snake_BlockColor_t {
	GB_SnakeColorBody,
	GB_SnakeColorFood,
	GB_SnakeColorBackground,
};

// Struct to store foot position and each block of snake's body
struct Snake_Point {
	uint8_t x;
	uint8_t y;
};

// Sturture of all global variables used by the game
struct Snake_Control {
	Snake_Point Head;
	Snake_Point Food;
	uint16_t Score;
};

#endif /* SNAKE_DEFINES_H_ */
#endif
