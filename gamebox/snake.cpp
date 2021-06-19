#if COMPONENT_GAMEBOX

// ========================================
// Includes
// ========================================

#include	"snake.h"

// ========================================
// Global variables
// ========================================

Snake_Point Snake_Head = {.x=5, .y=5};
Snake_Point Snake_Food = {.x = 10, .y=10};
static uint16_t Snake_Score = 12345;

// ========================================
// Functions
// ========================================

// Run game
void Snake_CmdRun(uint8_t argc, uint8_t * argv[]) {
	TaskAddMs(Snake_MainTask, 10);
}

// Get radnom coordinates
void Snake_GenerateRandomPoint(Snake_Point * Point) {
	Point->x = rand() % SNAKE_BLOCK_X_MAX+1;
	Point->y = rand() % SNAKE_BLOCK_Y_MAX+1;
}

// Compare two points, return true if equal
bool Snake_ComparePoints(Snake_Point * Point1, Snake_Point * Point2) {
	return (Point1->x == Point2->x) && (Point1->y == Point2->y);
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
}

// Draw block
void Snake_DrawBlock(Snake_Point * Point, Snake_BlockColor_t Color) {
	
	switch(Color) {
		case GB_SnakeColorBody:			SSD1351_ColorFrontSet(SSD1351_COLOR_YELLOW_RGB565);		break;
		case GB_SnakeColorFood:			SSD1351_ColorFrontSet(SSD1351_COLOR_GREEN_RGB565);		break;
		case GB_SnakeColorBackground:	SSD1351_ColorFrontSet(SNAKE_BLOCK_COLOR_BACKGROUN);		break;
	}
	
	SSD1351_DrawRectangleFill(
	SNAKE_BLOCK_START_X_POSITION + Point->x * SNAKE_BLOCK_SIZE,
	SNAKE_BLOCK_START_Y_POSITION + Point->y * SNAKE_BLOCK_SIZE,
	SNAKE_BLOCK_START_X_POSITION + (SNAKE_BLOCK_SIZE-1) + Point->x * SNAKE_BLOCK_SIZE,
	SNAKE_BLOCK_START_Y_POSITION + (SNAKE_BLOCK_SIZE-1) + Point->y *SNAKE_BLOCK_SIZE
	);
}

void Snake_CmdDrawBlock(uint8_t argc, uint8_t * argv[]) {
	
	Snake_Point Point;
	
	// Argument 1 - coordinate X
	if(Parse_Dec8(argv[1], &Point.x, SNAKE_BLOCK_X_MAX)) return;
	
	// Argument 2 - coordinate Y
	if(Parse_Dec8(argv[2], &Point.y, SNAKE_BLOCK_Y_MAX)) return;
	
	// Argument 3 - color
	Snake_BlockColor_t Color;
	switch(*argv[3]) {
		case 's':		Color = GB_SnakeColorBody;				break;
		case 'f':		Color = GB_SnakeColorFood;				break;
		case 'b':		Color = GB_SnakeColorBackground;		break;
		default:		Print_ResponseError();					return;
	}
	
	// Execute command
	Snake_DrawBlock(&Point, Color);
}

// Generate new food
void Snake_NewFood(void) {
	while(1) {
		// Generate new coordinates
		Snake_Point Point;
		Snake_GenerateRandomPoint(&Point);
		
		// Check if new coordinated don't match with snake's body
		//if((Point.x == Snake_Head.x) && (Point.y == Snake_Head.y)) {
		if(Snake_ComparePoints(&Point, &Snake_Head)) {
			continue;
		}
		
		// Draw new food and update globals
		Snake_DrawBlock(&Point, GB_SnakeColorFood);
		Snake_Head.x = Point.x;
		Snake_Head.y = Point.y;
		
		// Display result
		Print_Format(ForegroundMagentaBright);
		Print("\r\nNew food ");
		Print_Dec(Point.x);
		Print(" ");
		Print_Dec(Point.y);
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
				if(Snake_Head.y != 0) {
					Snake_DrawBlock(&Snake_Head, GB_SnakeColorBackground);
					Snake_Head.y--;
					Snake_DrawBlock(&Snake_Head, GB_SnakeColorBody);
				}
				RefreshRequest = true;
				break;
			
			case GB_KeyDownPress:
				if(Snake_Head.y < SNAKE_BLOCK_Y_MAX) {
					Snake_DrawBlock(&Snake_Head, GB_SnakeColorBackground);
					Snake_Head.y++;
					Snake_DrawBlock(&Snake_Head, GB_SnakeColorBody);
				}
				RefreshRequest = true;
				break;
			
			case GB_KeyLeftPress:
				if(Snake_Head.x != 0) {
					Snake_DrawBlock(&Snake_Head, GB_SnakeColorBackground);
					Snake_Head.x--;
					Snake_DrawBlock(&Snake_Head, GB_SnakeColorBody);
				}
				RefreshRequest = true;
				break;
			
			case GB_KeyRightPress:
				if(Snake_Head.x < SNAKE_BLOCK_X_MAX) {
					Snake_DrawBlock(&Snake_Head, GB_SnakeColorBackground);
					Snake_Head.x++;
					Snake_DrawBlock(&Snake_Head, GB_SnakeColorBody);
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
		Snake_DrawBlock(&Snake_Head, GB_SnakeColorBody);
		
		// Print food
		Snake_DrawBlock(&Snake_Food, GB_SnakeColorFood);
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
