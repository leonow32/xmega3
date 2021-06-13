#if COMPONENT_GAMEBOX

// ========================================
// Includes
// ========================================

#include	"snake.h"

// ========================================
// Global variables
// ========================================



// ========================================
// Functions
// ========================================


// Glabal variables
static uint16_t GB_SnakeScore = 12345;

// Run game
void GB_SnakeCmdRun(uint8_t argc, uint8_t * argv[]) {
	GB_SnakeCanvas();
}

// Print canvas in the background
void GB_SnakeCanvas(void) {
	
	// Title
	SSD1351_CursorSet(0, 0);
	SSD1351_FontSet(&SSD1351_FontSans16B_PL);
	SSD1351_ColorFrontSet(SSD1351_COLOR_YELLOW_RGB565);
	SSD1351_Text("Snake", SSD1351_HALIGN_CENTER);
	
	// Rectangle around game area
	SSD1351_ColorFrontSet(SSD1351_COLOR_WHITE_RGB565);
	SSD1351_DrawRectangle(SNAKE_BORDER_LEFT, SNAKE_BORDER_TOP, SNAKE_BORDER_RIGHT, SNAKE_BORDER_BOTTOM);
	
	// Score
	SSD1351_CursorSet(0, 111);
	SSD1351_FontSet(&SSD1351_FontSans16_PL);
	char Score[6];
	itoa(GB_SnakeScore, Score, 10);
	SSD1351_Text(Score, SSD1351_HALIGN_CENTER);
	
	for(uint8_t i=0; i<24; i++) {
		SSD1351_DrawRectangle(
			SNAKE_BLOCK_START_X + i*SNAKE_BLOCK_SIZE, 
			SNAKE_BLOCK_START_Y, 
			SNAKE_BLOCK_START_X + (SNAKE_BLOCK_SIZE-1) + i*SNAKE_BLOCK_SIZE, 
			SNAKE_BLOCK_START_Y + (SNAKE_BLOCK_SIZE-1)
		);
	}
	
	for(uint8_t i=0; i<17; i++) {
		SSD1351_DrawRectangle(
			SNAKE_BLOCK_START_X, 
			SNAKE_BLOCK_START_Y + i*SNAKE_BLOCK_SIZE, 
			SNAKE_BLOCK_START_X + (SNAKE_BLOCK_SIZE-1), 
			SNAKE_BLOCK_START_Y + (SNAKE_BLOCK_SIZE-1) + i*SNAKE_BLOCK_SIZE
		);
	}
	
	
	
}


#endif
