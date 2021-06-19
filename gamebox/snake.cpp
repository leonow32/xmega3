#if COMPONENT_GAMEBOX

// ========================================
// Includes
// ========================================

#include	"snake.h"

// ========================================
// Global variables
// ========================================

uint8_t Snake_HeadX = 5;
uint8_t Snake_HeadY = 5;
uint8_t Snake_FoodX = 10;
uint8_t Snake_FoodY = 10;
static uint16_t Snake_Score = 12345;

// ========================================
// Functions
// ========================================

// Run game
void Snake_CmdRun(uint8_t argc, uint8_t * argv[]) {
	TaskAddMs(Snake_MainTask, 10);
}

// Print canvas in the background
void Snake_DrawCanvas(void) {
	
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
	itoa(Snake_Score, Score, 10);
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
void Snake_DrawBlock(uint8_t x, uint8_t y, Snake_BlockColor_t Color) {
	
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

void Snake_CmdDrawBlock(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X
	uint8_t x;
	if(Parse_Dec8(argv[1], &x, SNAKE_BLOCK_X_MAX)) return;
	
	// Argument 2 - coordinate Y
	uint8_t y;
	if(Parse_Dec8(argv[2], &y, SNAKE_BLOCK_Y_MAX)) return;
	
	// Argument 3 - color
	Snake_BlockColor_t Color;
	switch(*argv[3]) {
		case 's':		Color = GB_SnakeColorBody;				break;
		case 'f':		Color = GB_SnakeColorFood;				break;
		case 'b':		Color = GB_SnakeColorBackground;		break;
		default:		Print_ResponseError();					return;
	}
	
	// Execute command
	Snake_DrawBlock(x, y, Color);
}

// Generate new food
void Snake_NewFood(void) {
	while(1) {
		// Generate new coordinates
		uint8_t RandomX = rand() % SNAKE_BLOCK_X_MAX+1;
		uint8_t RandomY = rand()  % SNAKE_BLOCK_Y_MAX+1;
		
		// Check if new coordinated don't match with snake's body
		if((RandomX == Snake_HeadX) && (RandomY == Snake_HeadY)) {
			continue;
		}
		
		// Draw new food and update globals
		Snake_DrawBlock(RandomX, RandomY, GB_SnakeColorFood);
		Snake_HeadX = RandomX;
		Snake_HeadY = RandomY;
		
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

void Snake_CmdNewFood(uint8_t argc, uint8_t * argv[]) {
	Snake_NewFood();
}

// ========================================
// Tasks
// ========================================

task_t Snake_MainTask(runmode_t RunMode) {
	
	// Variables
	bool RefreshRequest = false;
	
	// Normal execution
	if(RunMode == Run) {
		
		switch(GB_KeyboardQueuePop()) {
			
			case GB_KeyUpPress:
				if(Snake_HeadY != 0) {
					Snake_DrawBlock(Snake_HeadX, Snake_HeadY, GB_SnakeColorBackground);
					Snake_HeadY--;
					Snake_DrawBlock(Snake_HeadX, Snake_HeadY, GB_SnakeColorBody);
				}
				RefreshRequest = true;
				break;
			
			case GB_KeyDownPress:
				if(Snake_HeadY < SNAKE_BLOCK_Y_MAX) {
					Snake_DrawBlock(Snake_HeadX, Snake_HeadY, GB_SnakeColorBackground);
					Snake_HeadY++;
					Snake_DrawBlock(Snake_HeadX, Snake_HeadY, GB_SnakeColorBody);
				}
				RefreshRequest = true;
				break;
			
			case GB_KeyLeftPress:
				if(Snake_HeadX != 0) {
					Snake_DrawBlock(Snake_HeadX, Snake_HeadY, GB_SnakeColorBackground);
					Snake_HeadX--;
					Snake_DrawBlock(Snake_HeadX, Snake_HeadY, GB_SnakeColorBody);
				}
				RefreshRequest = true;
				break;
			
			case GB_KeyRightPress:
				if(Snake_HeadX < SNAKE_BLOCK_X_MAX) {
					Snake_DrawBlock(Snake_HeadX, Snake_HeadY, GB_SnakeColorBackground);
					Snake_HeadX++;
					Snake_DrawBlock(Snake_HeadX, Snake_HeadY, GB_SnakeColorBody);
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
		Snake_DrawCanvas();
		
		// Print snake's head
		Snake_DrawBlock(Snake_HeadX, Snake_HeadY, GB_SnakeColorBody);
		
		// Print food
		Snake_DrawBlock(Snake_FoodX, Snake_FoodY, GB_SnakeColorFood);
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
