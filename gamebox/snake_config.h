#if COMPONENT_GAMEBOX
#ifndef SNAKE_CONFIG_H_
#define SNAKE_CONFIG_H_

// Border around game area
#define SNAKE_BORDER_TOP				18
#define SNAKE_BORDER_BOTTOM				109
#define SNAKE_BORDER_LEFT				0
#define SNAKE_BORDER_RIGHT				127

// Blocks
#define SNAKE_BLOCK_SIZE				5
#define SNAKE_BLOCK_START_X_POSITION	4								// Position in pixels
#define SNAKE_BLOCK_START_Y_POSITION	20								// Position in pixels
#define SNAKE_BLOCK_X_MAX				23
#define SNAKE_BLOCK_Y_MAX				16
#define SNAKE_BLOCK_COLOR_BODY			SSD1351_COLOR_YELLOW_RGB565
#define SNAKE_BLOCK_COLOR_FOOD			SSD1351_COLOR_GREEN_RGB565
#define SNAKE_BLOCK_COLOR_BACKGROUN		SSD1351_COLOR_BLACK_RGB565



#endif /* SNAKE_CONFIG_H_ */
#endif
