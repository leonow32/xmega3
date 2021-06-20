#if COMPONENT_GAMEBOX

// ========================================
// Includes
// ========================================

#include	"snake.h"

// ========================================
// Global variables
// ========================================

Snake_Control * Snake;

// Snake_Control Snake = {
// 	.Head = {
// 		.x = 5,
// 		.y = 5,
// 	},
// 	.Food = {
// 		.x = 10,
// 		.y = 10,
// 	},
// 	.Score = 12345,
// };

// ========================================
// Functions
// ========================================

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
	itoa(Snake->Score, Score, 10);
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

// Generate new food
void Snake_NewFood(void) {
	while(1) {
		// Generate new coordinates
		Snake_Point Point;
		Snake_GenerateRandomPoint(&Point);
		
		// Check if new coordinated don't match with snake's body
		//if((Point.x == Snake_Head.x) && (Point.y == Snake_Head.y)) {
		if(Snake_ComparePoints(&Point, &Snake->Head)) {
			continue;
		}
		
		// Draw new food and update globals
		Snake_DrawBlock(&Point, GB_SnakeColorFood);
		Snake->Food.x = Point.x;
		Snake->Food.y = Point.y;
		
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

// ========================================
// Tasks
// ========================================

task_t Snake_MainTask(runmode_t RunMode) {
	
	// Variables
	//bool RefreshRequest = false;
	
	// Normal execution
	if(RunMode == Run) {
		
		// Read keyboard event
		switch(GB_KeyboardQueuePop()) {
			case GB_KeyUpPress:
				if(Snake->Direction != Snake_Down) {
					Snake->Direction = Snake_Up;
				}
				break;
			
			case GB_KeyDownPress:
				if(Snake->Direction != Snake_Up) {
					Snake->Direction = Snake_Down;
				}
				break;
			
			case GB_KeyLeftPress:
				if(Snake->Direction != Snake_Right) {
					Snake->Direction = Snake_Left;
				}
				break;
			
			case GB_KeyRightPress:
				if(Snake->Direction != Snake_Left) {
					Snake->Direction = Snake_Right;
				}
				break;
			
			default:
				break;
		}
		
		// Clear actual head position
		Snake_DrawBlock(&Snake->Head, GB_SnakeColorBackground);
		
		// Move head
		switch(Snake->Direction) {
			case Snake_Up:
				if(Snake->Head.y != 0) {
					Snake->Head.y--;
				}
				else {
					Print("Game over");
				}
				break;
			
			case Snake_Down:
				if(Snake->Head.y < SNAKE_BLOCK_Y_MAX) {
					Snake->Head.y++;
				}
				else {
					Print("Game over");
				}
				break;
			
			case Snake_Left:
				if(Snake->Head.x != 0) {
					Snake->Head.x--;
				}
				else {
					Print("Game over");
				}
				break;
			
			case Snake_Right:
				if(Snake->Head.x < SNAKE_BLOCK_X_MAX) {
					Snake->Head.x++;
				}
				else {
					Print("Game over");
				}
				break;
		}
		
		// Print actual head position
		Snake_DrawBlock(&Snake->Head, GB_SnakeColorBody);
		
// 		if(RefreshRequest) {
// 			
// 		}
	}
	
	// Constructor
	else if(RunMode == FirstRun) {
		
		GB_KeyboarQueueClear();
		
		// Create instance of control structure
		Snake = (Snake_Control*)malloc(sizeof(Snake_Control));
		memset(Snake, 0, sizeof(Snake_Control));
		Snake_GenerateRandomPoint(&Snake->Head);
		Snake_GenerateRandomPoint(&Snake->Food);
		if(Snake->Head.y > SNAKE_BLOCK_Y_MAX / 2) {
			Snake->Direction = Snake_Up;
		}
		else {
			Snake->Direction = Snake_Down;
		}
		
		// Print canvas
		Snake_DrawCanvas();
		
		// Print snake's head
		Snake_DrawBlock(&Snake->Head, GB_SnakeColorBody);
		
		// Print food
		Snake_DrawBlock(&Snake->Food, GB_SnakeColorFood);
	}
	
	// Destructor
	else if(RunMode == Close) {
		GB_Clear();
		
		free(Snake);
		Snake = NULL;
	}
	
	// Identification
	#if OS_USE_TASK_IDENTIFY
	else if(RunMode == Identify) {
		Print("Snake");
	}
	#endif
	
	return TaskOK;
}

// ========================================
// Debug
// ========================================

// Run game
void Snake_CmdRun(uint8_t argc, uint8_t * argv[]) {
	
	// If no arguments given, then close task
	if(argc == 1) {
		TaskClose(Snake_MainTask);
		return;
	}
	
	// Argument 1 - coordinate X
	uint16_t Period;
	if(Parse_Dec16(argv[1], &Period)) return;
	
	TaskAdd(Snake_MainTask, TaskMsToTicks(Period));
}

void Snake_CmdPrintStruct(uint8_t argc, uint8_t * argv[]) {
	
	Print("Size\t");
	Print_Dec(sizeof(Snake_Control));
	
	Print("\r\nAdr\t");
	Print_Hex(uint16_t(Snake));
	
	Print("\r\n.Head.x\t");
	Print_Dec(Snake->Head.x);
	
	Print("\r\n.Head.y\t");
	Print_Dec(Snake->Head.y);
	
	Print("\r\n.Food.x\t");
	Print_Dec(Snake->Food.x);
	
	Print("\r\n.Food.y\t");
	Print_Dec(Snake->Food.y);
	
	Print("\r\n.Score\t");
	Print_Dec(Snake->Score);
	
	Print("\r\n.Dir\t");
	Print_Dec(uint8_t(Snake->Direction));
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

void Snake_CmdNewFood(uint8_t argc, uint8_t * argv[]) {
	Snake_NewFood();
}

#endif
