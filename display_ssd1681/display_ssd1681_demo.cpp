#if COMPONENT_DISPLAY_SSD1681
#include "display_ssd1681_demo.h"
#if SSD1681_USE_DEMO_COMMANDS

void SSD1681_CmdCommand(uint8_t argc, uint8_t * argv[]) {
	SSD1681_DC_COMMAND;
	Print_ResponseOK();
}

void SSD1681_CmdData(uint8_t argc, uint8_t * argv[]) {
	SSD1681_DC_DATA;
	Print_ResponseOK();
}

void SSD1681_CmdInit(uint8_t argc, uint8_t * argv[]) {
	SSD1681_Init();
	Print_ResponseOK();
}

void SSD1681_CmdRefresh(uint8_t argc, uint8_t * argv[]) {
	SSD1681_Refresh();
	Print_ResponseOK();
}

// Set or get cursor position
void SSD1681_CmdCursor(uint8_t argc, uint8_t * argv[]) {
	
	// If no arguments, then print actual cursor position
	if(argc == 1) {
		uint8_t x = SSD1681_CursorXGet();
		uint8_t p = SSD1681_CursorPageGet();
		Print("x = ");
		Print_Dec(x);
		Print("\r\np = ");
		Print_Dec(p);
	}
	
	// If arguments given, then set cursor position
	else {
		// Argument 1 - coordinate x
		uint8_t x;
		if(Parse_Dec8(argv[1], &x, SSD1681_DISPLAY_SIZE_Y-1)) return;
		
		// Argument 2 - page
		uint8_t p;
		if(Parse_Dec8(argv[2], &p, SSD1681_PAGE_COUNT-1)) return;
		
		// Execute command
		SSD1681_CursorSet(x, p);
		Print_ResponseOK();
	}
}

// Set or get active area position
void SSD1681_CmdActiveArea(uint8_t argc, uint8_t * argv[]) {
	
	// If no arguments, then print actual active area
	if(argc == 1) {
		Print("nx0 = ");
		Print_Dec(SSD1681_CursorX);
		Print("\r\np0 = ");
		Print_Dec(SSD1681_CursorP);
		Print("\r\nx1 = ");
		Print_Dec(SSD1681_CursorX_Max);
		Print("\r\np1 = ");
		Print_Dec(SSD1681_CursorP_Max);
	}
	
	// If arguments given, then set the position of active area
	else {
		
		// Argument 1 - coordinate x0
		uint8_t x0;
		if(Parse_Dec8(argv[1], &x0, SSD1681_DISPLAY_SIZE_Y-1)) return;
		
		// Argument 2 - page0
		uint8_t p0;
		if(Parse_Dec8(argv[2], &p0, SSD1681_PAGE_COUNT-1)) return;
		
		// Argument 3 - coordinate x1
		uint8_t x1;
		if(Parse_Dec8(argv[3], &x1, SSD1681_DISPLAY_SIZE_Y-1)) return;
		
		// Argument 4 - page1
		uint8_t p1;
		if(Parse_Dec8(argv[4], &p1, SSD1681_PAGE_COUNT-1)) return;
		
		// Execute command
		SSD1681_ActiveAreaSet(x0, p0, x1, p1);
		SSD1681_CursorSet(x0, p0);
		Print_ResponseOK();
	}
}

void SSD1681_CmdTest(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - pattern to send and repeat
	uint8_t Pattern;
	if(Parse_Hex8(argv[1], &Pattern)) return;
	
	// Argument 2 - how many times to repeat
	uint16_t Times;
	if(Parse_Dec16(argv[2], &Times)) return;
	
	// Execute command
	SSD1681_Bytes(Pattern, Times);
	SSD1681_Refresh();
	Print_ResponseOK();
}

// Clear display
void SSD1681_CmdClear(uint8_t argc, uint8_t * argv[]) {
	SSD1681_Clear();
	SSD1681_Refresh();
	SSD1681_Clear();
	SSD1681_Refresh();
	SSD1681_ActiveAreaSet(0, 0, 199, 24);
	SSD1681_CursorSet(0, 0);
	Print_ResponseOK();
}

// Clear display
void SSD1681_CmdFill(uint8_t argc, uint8_t * argv[]) {
	SSD1681_Fill();
	SSD1681_Refresh();
	SSD1681_Fill();
	SSD1681_Refresh();
	SSD1681_ActiveAreaSet(0, 0, 199, 24);
	SSD1681_CursorSet(0, 0);
	Print_ResponseOK();
}

// Draw chessboard
void SSD1681_CmdChessboard(uint8_t argc, uint8_t * argv[]) {
	SSD1681_Chessboard();
	SSD1681_Refresh();
	SSD1681_Chessboard();
	SSD1681_Refresh();
	SSD1681_ActiveAreaSet(0, 0, 199, 24);
	SSD1681_CursorSet(0, 0);
	Print_ResponseOK();
}

// ========================================
// Colors
// ========================================

void SSD1681_CmdColor(uint8_t argc, uint8_t * argv[]) {
	
	// If no arguments, then print actual selected color name
	if(argc == 1) {
		switch(SSD1681_ColorGet()) {
			case SSD1681_ColorBlack:		Print("Black");				return;
			case SSD1681_ColorWhite:		Print("White");				return;
			#if SSD1681_USE_TRI_COLOR_DISPLAY
				case SSD1681_ColorRed:		Print("Red");				return;
			#endif
			default:						Print_ResponseUnknown();	return;
		}
	}
	else {
		switch(*argv[1]) {
			case 'b':						SSD1681_ColorSet(SSD1681_ColorBlack);	break;
			case 'w':						SSD1681_ColorSet(SSD1681_ColorWhite);	break;
			#if SSD1681_USE_TRI_COLOR_DISPLAY
				case 'r':					SSD1681_ColorSet(SSD1681_ColorRed);		break;
			#endif
			default:						Print_ResponseError();					return;
		}
	}
	Print_ResponseOK();
}

// Draw pixel
void SSD1681_CmdPixel(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X
	uint8_t x;
	if(Parse_Dec8(argv[1], &x, SSD1681_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y
	uint8_t y;
	if(Parse_Dec8(argv[2], &y, SSD1681_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SSD1681_DrawPixel(x, y);
	Print_ResponseOK();
}

// Draw line
void SSD1681_CmdLine(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X0
	uint8_t x0;
	if(Parse_Dec8(argv[1], &x0, SSD1681_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y0;
	if(Parse_Dec8(argv[2], &y0, SSD1681_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 3 - coordinate X1
	uint8_t x1;
	if(Parse_Dec8(argv[3], &x1, SSD1681_DISPLAY_SIZE_X-1)) return;
	
	// Argument 4 - coordinate Y1
	uint8_t y1;
	if(Parse_Dec8(argv[4], &y1, SSD1681_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SSD1681_DrawLine(x0, y0, x1, y1);
	Print_ResponseOK();
}

// Draw rectangle
void SSD1681_CmdRectangle(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X0
	uint8_t x0;
	if(Parse_Dec8(argv[1], &x0, SSD1681_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y0;
	if(Parse_Dec8(argv[2], &y0, SSD1681_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 3 - coordinate X1
	uint8_t x1;
	if(Parse_Dec8(argv[3], &x1, SSD1681_DISPLAY_SIZE_X-1)) return;
	
	// Argument 4 - coordinate Y1
	uint8_t y1;
	if(Parse_Dec8(argv[4], &y1, SSD1681_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SSD1681_DrawRectangle(x0, y0, x1, y1);
	Print_ResponseOK();
}

// Draw rectangle and fill
void SSD1681_CmdRectangleFill(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X0
	uint8_t x0;
	if(Parse_Dec8(argv[1], &x0, SSD1681_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y0;
	if(Parse_Dec8(argv[2], &y0, SSD1681_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 1 - coordinate X0
	uint8_t x1;
	if(Parse_Dec8(argv[3], &x1, SSD1681_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y1;
	if(Parse_Dec8(argv[4], &y1, SSD1681_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SSD1681_DrawRectangleFill(x0, y0, x1, y1);
	Print_ResponseOK();
}

// Craw circle
void SSD1681_CmdDrawCircle(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X
	uint8_t x;
	if(Parse_Dec8(argv[1], &x, SSD1681_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y
	uint8_t y;
	if(Parse_Dec8(argv[2], &y, SSD1681_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 1 - radius
	uint8_t r;
	if(Parse_Dec8(argv[3], &r)) return;
	
	// Execute command
	SSD1681_DrawCircle(x, y, r);
	Print_ResponseOK();
}

// ========================================
// Bitmaps
// ========================================

void SSD1681_CmdBitmap(uint8_t argc, uint8_t * argv[]) {
	
	const SSD1681_Bitmap_t * Pointer;
	switch(*argv[1]) {
		
		#if SSD1681_BITMAP_EXTRONIC_LOGO
			case '1':	Pointer = &SSD1681_BitmapExtronicLogo;			break;
		#endif
		
		default:		Print_ResponseError();							return;
	}
	
	SSD1681_CursorSet((SSD1681_DISPLAY_SIZE_X - Pointer->Width) / 2, ((SSD1681_DISPLAY_SIZE_Y - Pointer->Height) / 2) / SSD1681_PAGE_HEIGHT);
	SSD1681_Bitmap(Pointer);
	Print_ResponseOK();
}

// ========================================
// Fonts and text
// ========================================

// Print text
void SSD1681_CmdText(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 2 optional - text align
	SSD1681_align_t Align = SSD1681_AlignNone;
	if(argc == 3) {
		switch(*argv[2]) {
			case '1':	Align = SSD1681_AlignLeft;		break;
			case '2':	Align = SSD1681_AlignCenter;	break;
			case '3':	Align = SSD1681_AlignRight;		break;
			default:	Align = SSD1681_AlignNone;		break;
		}
	}
	
	// Execute command
	SSD1681_Text((const char *)argv[1], Align);
	Print_ResponseOK();
}

// Change font
void SSD1681_CmdFont(uint8_t argc, uint8_t * argv[]) {
	
	uint8_t FontNumber;
	if(Parse_Dec8(argv[1], &FontNumber)) return;
	
	switch(FontNumber) {
		
		#if SSD1681_FONT_CONSOLE8x6
			case 1:	SSD1681_FontSet(&SSD1681_FontConsole8x6);		break;
		#endif
		
		#if SSD1681_FONT_DOS8x8
			case 2:	SSD1681_FontSet(&SSD1681_FontDos8x8);			break;
		#endif
		
		#if SSD1681_FONT_DOS16x8
			case 3:	SSD1681_FontSet(&SSD1681_FontDos16x8);			break;
		#endif
		
		#if SSD1681_FONT_SANS8
			case 5:	SSD1681_FontSet(&SSD1681_FontSans8);			break;
		#endif
		
		#if SSD1681_FONT_SANS16
			case 6:	SSD1681_FontSet(&SSD1681_FontSans16);			break;
		#endif
		
		#if SSD1681_FONT_SANS16B
			case 7:	SSD1681_FontSet(&SSD1681_FontSans16B);			break;
		#endif
		
		#if SSD1681_FONT_SANS24
			case 8:	SSD1681_FontSet(&SSD1681_FontSans24);			break;
		#endif
		
		#if SSD1681_FONT_SANS24B
			case 9:	SSD1681_FontSet(&SSD1681_FontSans24B);			break;
		#endif
		
		default:
			Print_ResponseError();
			return;
	}
	
	Print_ResponseOK();
}

void SSD1681_CmdFontDemo(uint8_t argc, uint8_t * argv[]) {
	SSD1681_Clear();
	
	#define _SPACING 55
	
	#if SSD1681_FONT_CONSOLE8x6
		SSD1681_CursorSet(0, 0);
		SSD1681_FontSet(&SSD1681_FontConsole8x6);
		SSD1681_Text("Console8");
		SSD1681_CursorSet(_SPACING, 0);
		SSD1681_Text("Abciwg123!@");
	#endif
	
	#if SSD1681_FONT_DOS8x8
		SSD1681_CursorSet(0, 1);
		SSD1681_FontSet(&SSD1681_FontConsole8x6);
		SSD1681_Text("Dos8");
		
		SSD1681_CursorSet(_SPACING, 1);
		SSD1681_FontSet(&SSD1681_FontDos8x8);
		SSD1681_Text("Abciwg123!@");
	#endif
	
	#if SSD1681_FONT_DOS16x8
		SSD1681_CursorSet(0, 2);
		SSD1681_FontSet(&SSD1681_FontConsole8x6);
		SSD1681_Text("Dos16");
		
		SSD1681_CursorSet(_SPACING, 2);
		SSD1681_FontSet(&SSD1681_FontDos16x8);
		SSD1681_Text("Abciwg123!@");
	#endif
	
	#if SSD1681_FONT_SANS8
		SSD1681_CursorSet(0, 4);
		SSD1681_FontSet(&SSD1681_FontConsole8x6);
		SSD1681_Text("Sans8");
		
		SSD1681_CursorSet(_SPACING, 4);
		SSD1681_FontSet(&SSD1681_FontSans8);
		SSD1681_Text("Abciwg123!@");
	#endif
	
	#if SSD1681_FONT_SANS16
		SSD1681_CursorSet(0, 5);
		SSD1681_FontSet(&SSD1681_FontConsole8x6);
		SSD1681_Text("Sans16");
		
		SSD1681_CursorSet(_SPACING, 5);
		SSD1681_FontSet(&SSD1681_FontSans16);
		SSD1681_Text("Abciwg123!@");
	#endif
	
	#if SSD1681_FONT_SANS16B
		SSD1681_CursorSet(0, 7);
		SSD1681_FontSet(&SSD1681_FontConsole8x6);
		SSD1681_Text("Sans16B");
		
		SSD1681_CursorSet(_SPACING, 7);
		SSD1681_FontSet(&SSD1681_FontSans16B);
		SSD1681_Text("Abciwg123!@");
	#endif
	
	#if SSD1681_FONT_SANS24
		SSD1681_CursorSet(0, 9);
		SSD1681_FontSet(&SSD1681_FontConsole8x6);
		SSD1681_Text("Sans24");
		
		SSD1681_CursorSet(_SPACING, 9);
		SSD1681_FontSet(&SSD1681_FontSans24);
		SSD1681_Text("Abciwg123!@");
	#endif
	
	#if SSD1681_FONT_SANS24B
		SSD1681_CursorSet(0, 12);
		SSD1681_FontSet(&SSD1681_FontConsole8x6);
		SSD1681_Text("Sans24B");
		
		SSD1681_CursorSet(_SPACING, 12);
		SSD1681_FontSet(&SSD1681_FontSans24B);
		SSD1681_Text("Abciwg123!@");
	#endif
	
	#if SSD1681_FONT_CONSOLE8x6
		SSD1681_CursorSet(0, 18);
		SSD1681_FontSet(&SSD1681_FontConsole8x6);
		SSD1681_Text("Left", SSD1681_AlignLeft);
		SSD1681_Text("Center", SSD1681_AlignCenter);
		SSD1681_Text("Right", SSD1681_AlignRight);
	#endif
	
	#if SSD1681_FONT_DOS8x8
		SSD1681_CursorSet(0, 19);
		SSD1681_FontSet(&SSD1681_FontDos8x8);
		SSD1681_Text("Left", SSD1681_AlignLeft);
		SSD1681_Text("Center", SSD1681_AlignCenter);
		SSD1681_Text("Right", SSD1681_AlignRight);
	#endif
	
	#if SSD1681_FONT_SANS16
		SSD1681_CursorSet(0, 20);
		SSD1681_FontSet(&SSD1681_FontSans16B);
		SSD1681_Text("Left", SSD1681_AlignLeft);
		SSD1681_Text("Center", SSD1681_AlignCenter);
		SSD1681_Text("Right", SSD1681_AlignRight);
	#endif
	
	#if SSD1681_FONT_SANS24
		SSD1681_CursorSet(0, 22);
		SSD1681_FontSet(&SSD1681_FontSans24B);
		SSD1681_Text("Left", SSD1681_AlignLeft);
		SSD1681_Text("Center", SSD1681_AlignCenter);
		SSD1681_Text("Right", SSD1681_AlignRight);
	#endif
	
 	Print_ResponseOK();
}

// Display all characters from Dos8x8 font
#if SSD1681_FONT_DOS8x8
void SSD1681_CmdDemoFontDos8x8(uint8_t argc, uint8_t * argv[]) {
	
	static uint8_t Char = 0;
	SSD1681_FontSet(&SSD1681_FontDos8x8);
	
	for(uint8_t Line = 4; Line < 4+16; Line++) {
		SSD1681_CursorSet(36, Line);
		
		for(uint8_t i = 0; i < 16; i++) {
			SSD1681_PrintChar(Char++);
		}
	}
	
	Print_ResponseOK();
}
#endif

// Display all characters from Dos16x8 font
#if SSD1681_FONT_DOS16x8
void SSD1681_CmdDemoFontDos16x8(uint8_t argc, uint8_t * argv[]) {
	
	static uint8_t Char = 0;
	SSD1681_FontSet(&SSD1681_FontDos16x8);
	
	for(uint8_t Line = 2; Line < 2+8; Line++) {
		SSD1681_CursorSet(36, 2*Line);
		
		for(uint8_t i = 0; i < 16; i++) {
			SSD1681_PrintChar(Char++);
		}
	}
	
	Print_ResponseOK();
}
#endif


#endif
#endif
