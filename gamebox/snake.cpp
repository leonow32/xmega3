#if COMPONENT_GAMEBOX

// ========================================
// Includes
// ========================================

#include	"snake.h"

// ========================================
// Global variables
// ========================================

uint8_t GB_SnakeHeadX = 5;
uint8_t GB_SnakeHeadY = 5;
uint8_t GB_SnakeFoodX = 10;
uint8_t GB_SnakeFoodY = 10;

// ========================================
// Functions
// ========================================


// Glabal variables
static uint16_t GB_SnakeScore = 12345;

// Run game
void GB_SnakeCmdRun(uint8_t argc, uint8_t * argv[]) {
	//GB_SnakeCanvas();
	
	TaskAddMs(GB_SnakeTask, 10);
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
	
// 	for(uint8_t i=0; i<24; i++) {
// 		SSD1351_DrawRectangle(
// 			SNAKE_BLOCK_START_X_POSITION + i*SNAKE_BLOCK_SIZE,
// 			SNAKE_BLOCK_START_Y_POSITION, 
// 			SNAKE_BLOCK_START_X_POSITION + (SNAKE_BLOCK_SIZE-1) + i*SNAKE_BLOCK_SIZE, 
// 			SNAKE_BLOCK_START_Y_POSITION + (SNAKE_BLOCK_SIZE-1)
// 		);
// 	}
// 	
// 	for(uint8_t i=0; i<17; i++) {
// 		SSD1351_DrawRectangle(
// 			SNAKE_BLOCK_START_X_POSITION, 
// 			SNAKE_BLOCK_START_Y_POSITION + i*SNAKE_BLOCK_SIZE,
// 			SNAKE_BLOCK_START_X_POSITION + (SNAKE_BLOCK_SIZE-1), 
// 			SNAKE_BLOCK_START_Y_POSITION + (SNAKE_BLOCK_SIZE-1) + i*SNAKE_BLOCK_SIZE
// 		);
// 	}
}

// Draw block
void GB_SnakeDrawBlock(uint8_t x, uint8_t y, GB_SnakeBlockColor_t Color) {
	
	switch(Color) {
		case GB_SnakeColorBody:			SSD1351_ColorFrontSet(SSD1351_COLOR_YELLOW_RGB565);		break;
		case GB_SnakeColorFood:			SSD1351_ColorFrontSet(SSD1351_COLOR_GREEN_RGB565);		break;
		case GB_SnakeColorBackground:	SSD1351_ColorFrontSet(SNAKE_BLOCK_COLOR_BACKGROUN);		break;
	}
	
	SSD1351_DrawRectangleFill(
		SNAKE_BLOCK_START_X_POSITION + x * SNAKE_BLOCK_SIZE,
		SNAKE_BLOCK_START_Y_POSITION + y * SNAKE_BLOCK_SIZE,
		SNAKE_BLOCK_START_X_POSITION + (SNAKE_BLOCK_SIZE-1) + x * SNAKE_BLOCK_SIZE,
		SNAKE_BLOCK_START_Y_POSITION + (SNAKE_BLOCK_SIZE-1) + y *SNAKE_BLOCK_SIZE
	);
}

void GB_SnakeCmdDrawBlock(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X
	uint8_t x;
	if(Parse_Dec8(argv[1], &x, SNAKE_BLOCK_X_MAX)) return;
	
	// Argument 2 - coordinate Y
	uint8_t y;
	if(Parse_Dec8(argv[2], &y, SNAKE_BLOCK_Y_MAX)) return;
	
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

void GB_SnakeCmdNewFood(uint8_t argc, uint8_t * argv[]) {
	while(1) {
		// Generate new coordinates
		uint8_t RandomX = rand() % SNAKE_BLOCK_X_MAX+1;
		Print_Dec(RandomX);
		uint8_t RandomY = rand()  % SNAKE_BLOCK_Y_MAX+1;
		Print_Dec(RandomY);
		
		// Check if new coordinated don't match with snake's body
		if((RandomX == GB_SnakeHeadX) && (RandomY == GB_SnakeHeadY)) {
			continue;
		}
		
		// Draw new food and update globals
		GB_SnakeDrawBlock(RandomX, RandomY, GB_SnakeColorFood);
		GB_SnakeHeadX = RandomX;
		GB_SnakeHeadY = RandomY;
		
		// Display result
		Print_Format(ForegroundMagentaBright);
		Print("\r\nNew food ");
		Print_Dec(RandomX);
		Print(" ");
		Print_Dec(RandomY);
		Console_PromptShow();
		return;
	}
}

// ========================================
// Tasks
// ========================================

task_t GB_SnakeTask(runmode_t RunMode) {
	
	// Variables
	bool RefreshRequest = false;
	
	// Normal execution
	if(RunMode == Run) {
		
		switch(GB_KeyboardQueuePop()) {
			
			case GB_KeyUpPress:
				if(GB_SnakeHeadY != 0) {
					GB_SnakeDrawBlock(GB_SnakeHeadX, GB_SnakeHeadY, GB_SnakeColorBackground);
					GB_SnakeHeadY--;
					GB_SnakeDrawBlock(GB_SnakeHeadX, GB_SnakeHeadY, GB_SnakeColorBody);
				}
				RefreshRequest = true;
				break;
			
			case GB_KeyDownPress:
				if(GB_SnakeHeadY < SNAKE_BLOCK_Y_MAX) {
					GB_SnakeDrawBlock(GB_SnakeHeadX, GB_SnakeHeadY, GB_SnakeColorBackground);
					GB_SnakeHeadY++;
					GB_SnakeDrawBlock(GB_SnakeHeadX, GB_SnakeHeadY, GB_SnakeColorBody);
				}
				RefreshRequest = true;
				break;
			
			case GB_KeyLeftPress:
				if(GB_SnakeHeadX != 0) {
					GB_SnakeDrawBlock(GB_SnakeHeadX, GB_SnakeHeadY, GB_SnakeColorBackground);
					GB_SnakeHeadX--;
					GB_SnakeDrawBlock(GB_SnakeHeadX, GB_SnakeHeadY, GB_SnakeColorBody);
				}
				RefreshRequest = true;
				break;
			
			case GB_KeyRightPress:
				if(GB_SnakeHeadX < SNAKE_BLOCK_X_MAX) {
					GB_SnakeDrawBlock(GB_SnakeHeadX, GB_SnakeHeadY, GB_SnakeColorBackground);
					GB_SnakeHeadX++;
					GB_SnakeDrawBlock(GB_SnakeHeadX, GB_SnakeHeadY, GB_SnakeColorBody);
				}
				RefreshRequest = true;
				break;
			
			default:
				break;
		}
		
		if(RefreshRequest) {
			
		}
	}
	
	// Constructor
	else if(RunMode == FirstRun) {
		
		// Print canvas
		GB_SnakeCanvas();
		
		// Print snake's head
		GB_SnakeDrawBlock(GB_SnakeHeadX, GB_SnakeHeadY, GB_SnakeColorBody);
		
		// Print food
		GB_SnakeDrawBlock(GB_SnakeFoodX, GB_SnakeFoodY, GB_SnakeColorFood);
	}
	
	// Destructor
	else if(RunMode == Close) {
		GB_Clear();
	}
	
	// Identification
	#if OS_USE_TASK_IDENTIFY
	else if(RunMode == Identify) {
		Print("Snake");
	}
	#endif
	
	return TaskOK;
}



#endif
