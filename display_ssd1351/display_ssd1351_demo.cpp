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
void SSD1351_CmdPixel(uint8_t argc, uint8_t * argv[]) {
	
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
void SSD1351_CmdLine(uint8_t argc, uint8_t * argv[]) {
	
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
void SSD1351_CmdRectangle(uint8_t argc, uint8_t * argv[]) {
	
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
void SSD1351_CmdRectangleFill(uint8_t argc, uint8_t * argv[]) {
	
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
		case 'k':	SSD1351_ColorFrontSet(SSD1351_COLOR_BLACK_RGB565);			break;
		case 'r':	SSD1351_ColorFrontSet(SSD1351_COLOR_RED_RGB565);			break;
		case 'g':	SSD1351_ColorFrontSet(SSD1351_COLOR_GREEN_RGB565);			break;
		case 'y':	SSD1351_ColorFrontSet(SSD1351_COLOR_YELLOW_RGB565);			break;
		case 'b':	SSD1351_ColorFrontSet(SSD1351_COLOR_BLUE_RGB565);			break;
		case 'm':	SSD1351_ColorFrontSet(SSD1351_COLOR_MAGENTA_RGB565);		break;
		case 'c':	SSD1351_ColorFrontSet(SSD1351_COLOR_CYAN_RGB565);			break;
		case 'w':	SSD1351_ColorFrontSet(SSD1351_COLOR_WHITE_RGB565);			break;
		default:	Print_ResponseError();										return;
	}
	Print_ResponseOK();
}

// Set background color
void SSD1351_CmdColorBack(uint8_t argc, uint8_t * argv[]) {
	switch(*argv[1]) {
		case 'k':	SSD1351_ColorBackSet(SSD1351_COLOR_BLACK_RGB565);			break;
		case 'r':	SSD1351_ColorBackSet(SSD1351_COLOR_RED_RGB565);				break;
		case 'g':	SSD1351_ColorBackSet(SSD1351_COLOR_GREEN_RGB565);			break;
		case 'y':	SSD1351_ColorBackSet(SSD1351_COLOR_YELLOW_RGB565);			break;
		case 'b':	SSD1351_ColorBackSet(SSD1351_COLOR_BLUE_RGB565);			break;
		case 'm':	SSD1351_ColorBackSet(SSD1351_COLOR_MAGENTA_RGB565);			break;
		case 'c':	SSD1351_ColorBackSet(SSD1351_COLOR_CYAN_RGB565);			break;
		case 'w':	SSD1351_ColorBackSet(SSD1351_COLOR_WHITE_RGB565);			break;
		default:	Print_ResponseError();										return;
	}
	Print_ResponseOK();
}

// Print text
void SSD1351_CmdText(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 2 optional - text align
	uint8_t Align = 0;
	if(argc == 3) {
		switch(*argv[2]) {
			case '1':	Align = SSD1351_HALIGN_LEFT   | SSD1351_VALIGN_BOTTOM;	break;
			case '2':	Align = SSD1351_HALIGN_CENTER | SSD1351_VALIGN_BOTTOM;	break;
			case '3':	Align = SSD1351_HALIGN_RIGHT  | SSD1351_VALIGN_BOTTOM;	break;
			case '4':	Align = SSD1351_HALIGN_LEFT   | SSD1351_VALIGN_CENTER;	break;
			case '5':	Align = SSD1351_HALIGN_CENTER | SSD1351_VALIGN_CENTER;	break;
			case '6':	Align = SSD1351_HALIGN_RIGHT  | SSD1351_VALIGN_CENTER;	break;
			case '7':	Align = SSD1351_HALIGN_LEFT   | SSD1351_VALIGN_TOP;		break;
			case '8':	Align = SSD1351_HALIGN_CENTER | SSD1351_VALIGN_TOP;		break;
			case '9':	Align = SSD1351_HALIGN_RIGHT  | SSD1351_VALIGN_TOP;		break;
			default:	Align = 0;	break;
		}
	}
	
	// Execute command
	SSD1351_Text((const char *)argv[1], Align);
	Print_ResponseOK();
}

// Change font
void SSD1351_CmdFont(uint8_t argc, uint8_t * argv[]) {
	switch(*argv[1]) {
		
		#if SSD1351_FONT_CONSOLE8x8
			case '1':	SSD1351_FontSet(&FontXF90_Console8x6);		break;
		#endif
		
		#if SSD1351_FONT_DOS8x8
			case '2':	SSD1351_FontSet(&FontXF90_Dos8x8);			break;
		#endif
		
		#if SSD1351_FONT_DOS16x8
			case '3':	SSD1351_FontSet(&FontXF90_Dos16x8);			break;
		#endif
		
		#if SSD1351_FONT_SANS16_PL
			case '4':	SSD1351_FontSet(&FontXF90_Sans16_PL);		break;
		#endif
		
		#if SSD1351_FONT_SANS16B_PL
			case '5':	SSD1351_FontSet(&FontXF90_Sans16B_PL);		break;
		#endif
		
		#if SSD1351_FONT_SANS24_PL
			case '6':	SSD1351_FontSet(&FontXF90_Sans24_PL);		break;
		#endif
		
		default:
			Print_ResponseError();
			return;
	}
	
	Print_ResponseOK();
}


#endif
#endif
