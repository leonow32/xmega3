#if COMPONENT_GAMEBOX
#ifndef SNAKE_DEFINES_H_
#define SNAKE_DEFINES_H_

#include <avr/io.h>

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

#endif /* SNAKE_DEFINES_H_ */
#endif
