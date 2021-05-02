#if COMPONENT_DISPLAY_SSD1351
#include "display_ssd1351_demo.h"
#if SSD1351_USE_DEMO_COMMANDS

// Clear display
void SSD1351_CmdClear(uint8_t argc, uint8_t * argv[]) {
	SSD1351_Clear();
}

// Draw chessboard
void SSD1351_CmdDrawChessboard(uint8_t argc, uint8_t * argv[]) {
	SSD1351_Chessboard();
}

// Set contrast
void SSD1351_CmdContrast(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - contrast value
	uint8_t Contrast;
	if(Parse_Dec8(argv[1], &Contrast)) return;
	
	// Execute command
	SSD1351_ContrastSet(Contrast);
	Print_ResponseOK();
}

// Draw pixel
void SSD1351_CmdDrawPixel(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X
	uint8_t x;
	if(Parse_Dec8(argv[1], &x, SSD1351_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y
	uint8_t y;
	if(Parse_Dec8(argv[2], &y, SSD1351_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SSD1351_DrawPixel(x, y);
	Print_ResponseOK();
}

// Draw line
void SSD1351_CmdDrawLine(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X0
	uint8_t x0;
	if(Parse_Dec8(argv[1], &x0, SSD1351_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y0;
	if(Parse_Dec8(argv[2], &y0, SSD1351_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 1 - coordinate X0
	uint8_t x1;
	if(Parse_Dec8(argv[3], &x1, SSD1351_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y1;
	if(Parse_Dec8(argv[4], &y1, SSD1351_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SSD1351_DrawLine(x0, y0, x1, y1);
	Print_ResponseOK();
}

// Draw rectangle
void SSD1351_CmdDrawRectangle(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X0
	uint8_t x0;
	if(Parse_Dec8(argv[1], &x0, SSD1351_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y0;
	if(Parse_Dec8(argv[2], &y0, SSD1351_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 1 - coordinate X0
	uint8_t x1;
	if(Parse_Dec8(argv[3], &x1, SSD1351_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y1;
	if(Parse_Dec8(argv[4], &y1, SSD1351_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SSD1351_DrawRectangle(x0, y0, x1, y1);
	Print_ResponseOK();
}

// Draw rectangle and fill
void SSD1351_CmdDrawRectangleFill(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X0
	uint8_t x0;
	if(Parse_Dec8(argv[1], &x0, SSD1351_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y0;
	if(Parse_Dec8(argv[2], &y0, SSD1351_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 1 - coordinate X0
	uint8_t x1;
	if(Parse_Dec8(argv[3], &x1, SSD1351_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y1;
	if(Parse_Dec8(argv[4], &y1, SSD1351_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SSD1351_DrawRectangleFill(x0, y0, x1, y1);
	Print_ResponseOK();
}

// Craw circle
void SSD1351_CmdDrawCircle(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X
	uint8_t x;
	if(Parse_Dec8(argv[1], &x, SSD1351_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y
	uint8_t y;
	if(Parse_Dec8(argv[2], &y, SSD1351_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 1 - radius
	uint8_t r;
	if(Parse_Dec8(argv[3], &r)) return;
	
	// Execute command
	SSD1351_DrawCircle(x, y, r);
	Print_ResponseOK();
}

// Set or get cursor position
void SSD1351_CmdCursor(uint8_t argc, uint8_t * argv[]) {
	
	// If no arguments, then print actual cursor position
	if(argc == 1) {
		uint8_t x = SSD1351_CursorXGet();
		uint8_t y = SSD1351_CursorYGet();
		Print("x = ");
		Print_Dec(x);
		Print("\r\ny = ");
		Print_Dec(y);
	}
	
	// If arguments given, then set cursor position
	else {
		// Argument 1 - coordinate X
		uint8_t x;
		if(Parse_Dec8(argv[1], &x, SSD1351_DISPLAY_SIZE_X-1)) return;
		
		// Argument 2 - coordinate Y
		uint8_t y;
		if(Parse_Dec8(argv[2], &y, SSD1351_DISPLAY_SIZE_Y-1)) return;
		
		// Execute command
		SSD1351_CursorSet(x, y);
		Print_ResponseOK();
	}
}

// Set foreground color
void SSD1351_CmdColorFront(uint8_t argc, uint8_t * argv[]) {
	switch(*argv[1]) {
		case 'k':	SSD1351_ColorFrontSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_BLACK_ID));		break;
		case 'r':	SSD1351_ColorFrontSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_RED_ID));			break;
		case 'g':	SSD1351_ColorFrontSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_GREEN_ID));		break;
		case 'y':	SSD1351_ColorFrontSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_YELLOW_ID));		break;
		case 'b':	SSD1351_ColorFrontSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_BLUE_ID));		break;
		case 'm':	SSD1351_ColorFrontSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_MAGENTA_ID));		break;
		case 'c':	SSD1351_ColorFrontSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_CYAN_ID));		break;
		case 'w':	SSD1351_ColorFrontSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_WHITE_ID));		break;
		default:	Print_ResponseError();															return;
	}
	Print_ResponseOK();
}

// Set background color
void SSD1351_CmdColorBack(uint8_t argc, uint8_t * argv[]) {
	switch(*argv[1]) {
		case 'k':	SSD1351_ColorBackSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_BLACK_ID));		break;
		case 'r':	SSD1351_ColorBackSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_RED_ID));			break;
		case 'g':	SSD1351_ColorBackSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_GREEN_ID));		break;
		case 'y':	SSD1351_ColorBackSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_YELLOW_ID));		break;
		case 'b':	SSD1351_ColorBackSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_BLUE_ID));			break;
		case 'm':	SSD1351_ColorBackSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_MAGENTA_ID));		break;
		case 'c':	SSD1351_ColorBackSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_CYAN_ID));			break;
		case 'w':	SSD1351_ColorBackSet(SSD1351_ColorNameToRGB565(SSD1351_COLOR_WHITE_ID));		break;
		default:	Print_ResponseError();															return;
	}
	Print_ResponseOK();
}


#endif
#endif