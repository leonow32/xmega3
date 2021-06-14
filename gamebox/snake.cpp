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

// Draw block
void GB_SnakeDrawBlock(uint8_t x, uint8_t y, GB_SnakeBlockColor_t Color) {
	
	switch(Color) {
		case GB_SnakeColorBody:			SSD1351_ColorFrontSet(SSD1351_COLOR_YELLOW_RGB565);		break;
		case GB_SnakeColorFood:			SSD1351_ColorFrontSet(SSD1351_COLOR_GREEN_RGB565);		break;
		case GB_SnakeColorBackground:	SSD1351_ColorFrontSet(SNAKE_BLOCK_COLOR_BACKGROUN);		break;
	}
	
	SSD1351_DrawRectangleFill(
		SNAKE_BLOCK_START_X + x * SNAKE_BLOCK_SIZE,
		SNAKE_BLOCK_START_Y + y * SNAKE_BLOCK_SIZE,
		SNAKE_BLOCK_START_X + (SNAKE_BLOCK_SIZE-1) + x * SNAKE_BLOCK_SIZE,
		SNAKE_BLOCK_START_Y + (SNAKE_BLOCK_SIZE-1) + y *SNAKE_BLOCK_SIZE
	);
}

void GB_SnakeCmdDrawBlock(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X
	uint8_t x;
	if(Parse_Dec8(argv[1], &x, SSD1351_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y
	uint8_t y;
	if(Parse_Dec8(argv[2], &y, SSD1351_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 3 - color
	GB_SnakeBlockColor_t Color;
	switch(*argv[3]) {
		case 's':		Color = GB_SnakeColorBody;				break;
		case 'f':		Color = GB_SnakeColorFood;				break;
		case 'b':		Color = GB_SnakeColorBackground;		break;
		default:		Print_ResponseError();					return;
	}
	
	// Execute command
	GB_SnakeDrawBlock(x, y, Color);
}


#endif
