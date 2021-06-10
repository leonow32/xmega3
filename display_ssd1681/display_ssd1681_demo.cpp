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
		Print("\r\nx0 = ");
		Print_Dec(SSD1681_CursorX);
		Print("p0 = ");
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

/*

// Set foreground color
void SSD1681_CmdColorFront(uint8_t argc, uint8_t * argv[]) {
	switch(*argv[1]) {
		case 'k':	SSD1681_ColorFrontSet(SSD1681_COLOR_BLACK_RGB565);			break;
		case 'r':	SSD1681_ColorFrontSet(SSD1681_COLOR_RED_RGB565);			break;
		case 'g':	SSD1681_ColorFrontSet(SSD1681_COLOR_GREEN_RGB565);			break;
		case 'y':	SSD1681_ColorFrontSet(SSD1681_COLOR_YELLOW_RGB565);			break;
		case 'b':	SSD1681_ColorFrontSet(SSD1681_COLOR_BLUE_RGB565);			break;
		case 'm':	SSD1681_ColorFrontSet(SSD1681_COLOR_MAGENTA_RGB565);		break;
		case 'c':	SSD1681_ColorFrontSet(SSD1681_COLOR_CYAN_RGB565);			break;
		case 'w':	SSD1681_ColorFrontSet(SSD1681_COLOR_WHITE_RGB565);			break;
		default:	Print_ResponseError();										return;
	}
	Print_ResponseOK();
}

// Set background color
void SSD1681_CmdColorBack(uint8_t argc, uint8_t * argv[]) {
	switch(*argv[1]) {
		case 'k':	SSD1681_ColorBackSet(SSD1681_COLOR_BLACK_RGB565);			break;
		case 'r':	SSD1681_ColorBackSet(SSD1681_COLOR_RED_RGB565);				break;
		case 'g':	SSD1681_ColorBackSet(SSD1681_COLOR_GREEN_RGB565);			break;
		case 'y':	SSD1681_ColorBackSet(SSD1681_COLOR_YELLOW_RGB565);			break;
		case 'b':	SSD1681_ColorBackSet(SSD1681_COLOR_BLUE_RGB565);			break;
		case 'm':	SSD1681_ColorBackSet(SSD1681_COLOR_MAGENTA_RGB565);			break;
		case 'c':	SSD1681_ColorBackSet(SSD1681_COLOR_CYAN_RGB565);			break;
		case 'w':	SSD1681_ColorBackSet(SSD1681_COLOR_WHITE_RGB565);			break;
		default:	Print_ResponseError();										return;
	}
	Print_ResponseOK();
}

// ========================================
// Fonts and text
// ========================================

// Print text
void SSD1681_CmdText(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 2 optional - text align
	uint8_t Align = 0;
	if(argc == 3) {
		switch(*argv[2]) {
			case '1':	Align = SSD1681_HALIGN_LEFT   | SSD1681_VALIGN_BOTTOM;	break;
			case '2':	Align = SSD1681_HALIGN_CENTER | SSD1681_VALIGN_BOTTOM;	break;
			case '3':	Align = SSD1681_HALIGN_RIGHT  | SSD1681_VALIGN_BOTTOM;	break;
			case '4':	Align = SSD1681_HALIGN_LEFT   | SSD1681_VALIGN_CENTER;	break;
			case '5':	Align = SSD1681_HALIGN_CENTER | SSD1681_VALIGN_CENTER;	break;
			case '6':	Align = SSD1681_HALIGN_RIGHT  | SSD1681_VALIGN_CENTER;	break;
			case '7':	Align = SSD1681_HALIGN_LEFT   | SSD1681_VALIGN_TOP;		break;
			case '8':	Align = SSD1681_HALIGN_CENTER | SSD1681_VALIGN_TOP;		break;
			case '9':	Align = SSD1681_HALIGN_RIGHT  | SSD1681_VALIGN_TOP;		break;
			default:	Align = 0;	break;
		}
	}
	
	// Execute command
	SSD1681_Text((const char *)argv[1], Align);
	Print_ResponseOK();
}

// Change font
void SSD1681_CmdFont(uint8_t argc, uint8_t * argv[]) {
	switch(*argv[1]) {
		
		#if SSD1681_FONT_CONSOLE8x6
			case '1':	SSD1681_FontSet(&SSD1681_FontConsole8x6);		break;
		#endif
		
		#if SSD1681_FONT_DOS8x8
			case '2':	SSD1681_FontSet(&SSD1681_FontDos8x8);			break;
		#endif
		
		#if SSD1681_FONT_DOS16x8
			case '3':	SSD1681_FontSet(&SSD1681_FontDos16x8);			break;
		#endif
		
		#if SSD1681_FONT_SANS16_PL
			case '4':	SSD1681_FontSet(&SSD1681_FontSans16_PL);		break;
		#endif
		
		#if SSD1681_FONT_SANS16B_PL
			case '5':	SSD1681_FontSet(&SSD1681_FontSans16B_PL);		break;
		#endif
		
		#if SSD1681_FONT_SANS24_PL
			case '6':	SSD1681_FontSet(&SSD1681_FontSans24_PL);		break;
		#endif
		
		default:
			Print_ResponseError();
			return;
	}
	
	Print_ResponseOK();
}

// Display all characters from Dos8x8 font
#if SSD1681_FONT_DOS8x8
void SSD1681_CmdDemoFontDos8x8(uint8_t argc, uint8_t * argv[]) {
	
	uint8_t Char = 0;
	SSD1681_FontSet(&SSD1681_FontDos8x8);
	
	for(uint8_t Line = 0; Line < 16; Line++) {
		SSD1681_CursorSet(0, Line * 8);
		
		for(uint8_t i=0; i<16; i++) {
			SSD1681_ColorFrontSet(SSD1681_ColorNameToRGB565((i & 0b00000111)+1));
			SSD1681_PrintChar(Char++);
		}
	}
}
#endif

// Test all fonts
void SSD1681_CmDDemoFontTest(uint8_t argc, uint8_t * argv[]) {
	
	SSD1681_Clear();
	
	#if SSD1681_FONT_CONSOLE8x6
		SSD1681_ColorFrontSet(255, 255, 255);
		SSD1681_ColorBackSet(0, 0, 0);
		SSD1681_FontSet(&SSD1681_FontConsole8x6);
		SSD1681_CursorSet(0, 0);
		SSD1681_Text("ABCDEFGHIJKLMNOPQRSTU");
		SSD1681_CursorSet(0, 8);
		SSD1681_Text("abcdefghijk0123456789");
	#endif
	
	#if SSD1681_FONT_DOS8x8
		SSD1681_ColorFrontSet(255, 0, 0);
		SSD1681_CursorSet(0, 17);
		SSD1681_FontSet(&SSD1681_FontDos8x8);
		SSD1681_Text("ABCDEFGHIJKLMNOP");
	#endif
	
	#if SSD1681_FONT_SANS16_PL
		SSD1681_ColorFrontSet(255, 255, 0);
		SSD1681_CursorSet(0, 24);
		SSD1681_FontSet(&SSD1681_FontSans16_PL);
		SSD1681_Text("ABCDEFGHIJKLMNO");
		SSD1681_CursorSet(0, 36);
		SSD1681_Text("abcdefghijklmn1234567");
	#endif
	
	#if SSD1681_FONT_SANS16B_PL
		SSD1681_ColorFrontSet(0, 255, 0);
		SSD1681_CursorSet(0, 51);
		SSD1681_FontSet(&SSD1681_FontSans16B_PL);
		SSD1681_Text("ABCDEFGHIJKLMN");
		SSD1681_CursorSet(0, 63);
		SSD1681_Text("abcdefghijklmn1234");
	#endif
	
	#if SSD1681_FONT_SANS24_PL
		SSD1681_ColorFrontSet(0, 0, 255);
		SSD1681_CursorSet(0, 78);
		SSD1681_FontSet(&SSD1681_FontSans24_PL);
		SSD1681_Text("ABCDEFGHIJ");
		SSD1681_CursorSet(0, 97);
		SSD1681_Text("abcdefghij123");
	#endif
	
	#if SSD1681_FONT_DOS8x8
		SSD1681_ColorFrontSet(255, 0, 255);
		SSD1681_CursorSet(0, 119);
		SSD1681_FontSet(&SSD1681_FontDos8x8);
		SSD1681_Text("123!@#$");
	#endif
}

// Print some messages in varoius positions
void SSD1681_CmdDemoTextAlign(uint8_t argc, uint8_t * argv[]) {
	SSD1681_Chessboard();
	SSD1681_Text("TL",		SSD1681_HALIGN_LEFT		| SSD1681_VALIGN_TOP);
	SSD1681_Text("Top",		SSD1681_HALIGN_CENTER	| SSD1681_VALIGN_TOP);
	SSD1681_Text("TR",		SSD1681_HALIGN_RIGHT	| SSD1681_VALIGN_TOP);
	SSD1681_Text("Left",	SSD1681_HALIGN_LEFT		| SSD1681_VALIGN_CENTER);
	SSD1681_Text("Center",	SSD1681_HALIGN_CENTER	| SSD1681_VALIGN_CENTER);
	SSD1681_Text("Right",	SSD1681_HALIGN_RIGHT	| SSD1681_VALIGN_CENTER);
	SSD1681_Text("BL",		SSD1681_HALIGN_LEFT		| SSD1681_VALIGN_BOTTOM);
	SSD1681_Text("Bottom",	SSD1681_HALIGN_CENTER	| SSD1681_VALIGN_BOTTOM);
	SSD1681_Text("BR",		SSD1681_HALIGN_RIGHT	| SSD1681_VALIGN_BOTTOM);
	
	SSD1681_CursorSet(10, 90);
	SSD1681_Text("Somewhere else");
}

// Display all characters from Dos16x8 font
#if SSD1681_FONT_DOS16x8
void SSD1681_CmdDemoFontDos16x8(uint8_t argc, uint8_t * argv[]) {
	
	static uint8_t Char = 0;
	SSD1681_FontSet(&SSD1681_FontDos16x8);
	
	for(uint8_t Line = 0; Line < 8; Line++) {
		SSD1681_CursorSet(0, Line * 16);
		SSD1681_ColorFrontSet(SSD1681_ColorNameToRGB565(Line+1));
		
		for(uint8_t i=0; i<16; i++) {
			SSD1681_PrintChar(Char++);
		}
	}
}
#endif

void SSD1681_CmdDemoColorPalette(uint8_t argc, uint8_t * argv[]) {
	
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint16_t Color;
	
	SSD1681_Clear();
	
	SSD1681_CHIP_SELECT;
	
	// Czerwony -> ¿ó³ty
	R = 255;
	G = 0;
	B = 0;
	for(uint8_t i=0; i<21; i++) {
		G = G + 12;
		Color = SSD1681_ColorRGB888toRGB565(R, G, B);
		Spi_Repeat(Color >> 8, Color & 0x00FF, 128);
	}
	
	// ¯ó³ty -> zielony
	R = 255;
	G = 255;
	B = 0;
	for(uint8_t i=0; i<21; i++) {
		R = R - 12;
		Color = SSD1681_ColorRGB888toRGB565(R, G, B);
		Spi_Repeat(Color >> 8, Color & 0x00FF, 128);
	}
	
	// Zielony -> cyjan
	R = 0;
	G = 255;
	B = 0;
	for(uint8_t i=0; i<21; i++) {
		B = B + 12;
		Color = SSD1681_ColorRGB888toRGB565(R, G, B);
		Spi_Repeat(Color >> 8, Color & 0x00FF, 128);
	}
	
	// Cyjan -> niebieski
	R = 0;
	G = 255;
	B = 255;
	for(uint8_t i=0; i<21; i++) {
		G = G - 12;
		Color = SSD1681_ColorRGB888toRGB565(R, G, B);
		Spi_Repeat(Color >> 8, Color & 0x00FF, 128);
	}
	
	// Niebieski -> magenta
	R = 0;
	G = 0;
	B = 255;
	for(uint8_t i=0; i<21; i++) {
		R = R + 12;
		Color = SSD1681_ColorRGB888toRGB565(R, G, B);
		Spi_Repeat(Color >> 8, Color & 0x00FF, 128);
	}
	
	// Magenta -> czerowny
	R = 255;
	G = 0;
	B = 255;
	for(uint8_t i=0; i<21; i++) {
		B = B - 12;
		Color = SSD1681_ColorRGB888toRGB565(R, G, B);
		Spi_Repeat(Color >> 8, Color & 0x00FF, 128);
	}
	
	SSD1681_CHIP_DESELECT;
}
*/
// ========================================
// Bitmaps
// ========================================

void SSD1681_CmdBitmap(uint8_t argc, uint8_t * argv[]) {
	
	const SSD1681_Bitmap_t * Pointer;
	switch(*argv[1]) {
		
		#if SSD1681_BITMAP_EXTRONIC_LOGO
			case '1':	Pointer = &SSD1681_BitmapExtronicLogo;			break;
		#endif
		
		default:	Print_ResponseError();	return;
	}
	
	SSD1681_CursorXSet((SSD1681_DISPLAY_SIZE_X - Pointer->Width) / 2);
//	SSD1681_CursorYSet((SSD1681_DISPLAY_SIZE_Y - Pointer->Height) / 2);
	SSD1681_CursorPageSet(0);
	SSD1681_Bitmap(Pointer);
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
			case '1':	Align = SSD1681_AlignLeft;	break;
			case '2':	Align = SSD1681_AlignCenter;	break;
			case '3':	Align = SSD1681_AlignRight;	break;
			default:	Align = SSD1681_AlignNone;	break;
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
			case 3:	SSD1681_FontSet(&SSD1681_FontDos16x8);		break;
		#endif
		
		#if SSD1681_FONT_SANS8
			case 5:	SSD1681_FontSet(&SSD1681_FontSans8);			break;
		#endif
		
		#if SSD1681_FONT_SANS16
			case 6:	SSD1681_FontSet(&SSD1681_FontSans16);			break;
		#endif
		
		#if SSD1681_FONT_SANS16B
			case 7:	SSD1681_FontSet(&SSD1681_FontSans16B);		break;
		#endif
		
		#if SSD1681_FONT_SANS24
			case 8:	SSD1681_FontSet(&SSD1681_FontSans24);			break;
		#endif
		
		#if SSD1681_FONT_SANS24B
			case 9:	SSD1681_FontSet(&SSD1681_FontSans24B);		break;
		#endif
		
		default:
			Print_ResponseError();
			return;
	}
	
	Print_ResponseOK();
}

void SSD1681_CmdFontDemo(uint8_t argc, uint8_t * argv[]) {
	SSD1681_Clear();
	
	#if SSD1681_FONT_CONSOLE8x6
		SSD1681_CursorSet(0, 0);
		SSD1681_FontSet(&SSD1681_FontConsole8x6);
		SSD1681_Text("Left", SSD1681_AlignLeft);
		SSD1681_Text("Center", SSD1681_AlignCenter);
		SSD1681_Text("Right", SSD1681_AlignRight);
	#endif
	
	#if SSD1681_FONT_DOS16x8
		SSD1681_CursorSet(0, 1);
		SSD1681_FontSet(&SSD1681_FontDos16x8);
		SSD1681_Text("Abcdefghij");
	#endif
	
	#if SSD1681_FONT_DOS8x8
		SSD1681_CursorSet(85, 1);
		SSD1681_FontSet(&SSD1681_FontDos8x8);
		SSD1681_Text("Abcde");
		SSD1681_CursorSet(85, 2);
		SSD1681_Text("fghij");
	#endif
	
	#if SSD1681_FONT_SANS16
		SSD1681_CursorSet(0, 3);
		SSD1681_FontSet(&SSD1681_FontSans16);
		SSD1681_Text("Abciwg123");
	#endif
	
	#if SSD1681_FONT_SANS16B
		SSD1681_FontSet(&SSD1681_FontSans16B);
		SSD1681_Text("Abciwg1", SSD1681_AlignRight);
	#endif
	
	#if SSD1681_FONT_SANS24
		SSD1681_CursorSet(0, 5);
		SSD1681_FontSet(&SSD1681_FontSans24);
		SSD1681_Text("Abciwg1");
	#endif
	
	#if SSD1681_FONT_SANS24B
		SSD1681_FontSet(&SSD1681_FontSans24B);
		SSD1681_Text("Abc", SSD1681_AlignRight);
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

// ========================================
// Animated demos
// ========================================
/*
void SSD1681_CmdSnake(uint8_t argc, uint8_t * argv[]) {
	if(*argv[1] == '0') {
		TaskClose(SSD1681_TaskSnake);
	}
	else {
		TaskAdd(SSD1681_TaskSnake, TaskMsToTicks(50));
	}
}

task_t SSD1681_TaskSnake(runmode_t RunMode) {
	
	// Zmienne
	static uint8_t x = 64;
	static uint8_t y = 64;
	static uint8_t PrevX = 64;;
	static uint8_t PrevY = 64;;
	static uint8_t R = 255;
	static uint8_t G = 0;
	static uint8_t B = 0;
	static uint8_t ColorMode = 0;
	
	uint8_t NewX;
	uint8_t NewY;
	uint8_t Random;
	
	// Tryb wywo³ania
	switch(RunMode) {
		
		// Konstruktor
		case FirstRun:
			x = 64;
			y = 64;
			return TaskOK;
		
		// Destruktor
		case Close:
			
			return TaskDone;
		
		// Wywo³anie identyfikacyjne
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Print("Snake");
			return TaskOK;
		#endif
		
		// Normalne wywo³anie przez Sheduler
		case Run:
		
			switch(ColorMode) {
				case 0:				// Red -> Yellow
					R = 255;
					G = G + 16;
					B = 0;
					if(G == 0) {
						G = 255;
						ColorMode++;
					}
					break;
				
				case 1:				// Yellow -> Green
					R = R - 16;
					G = 255;
					B = 0;
					if(R == 15) {
						ColorMode++;
					}
					break;
				
				case 2:				// Green -> Cyan
					R = 0;
					G = 255;
					B = B + 16;
					if(B == 0) {
						B = 255;
						ColorMode++;
					}
					break;
				
				case 3:				// Cyan -> Blue
					R = 0;
					G = G - 16;
					B = 255;
					if(G == 15) {
						ColorMode++;
					}
					break;
				
				case 4:				// Blue -> Magenta
					R = R + 16;
					G = 0;
					B = 255;
					if(R == 0) {
						R = 255;
						ColorMode++;
					}
					break;
				
				case 5:				// Blue -> Magenta
					R = 255;
					G = 0;
					B = B - 16;
					if(B == 15) {
						B = 0;
						ColorMode = 0;
					}
					break;
			}
			
			
			Random = rand();
			NewX = Random & 0b01111111;
			Random = rand();
			NewY = Random & 0b01111111;
			
			SSD1681_ColorFrontSet(0, 0, 0);
			SSD1681_DrawLine(PrevX, PrevY, x, y);
			SSD1681_ColorFrontSet(R, G, B);
			SSD1681_DrawLine(x, y, NewX, NewY);
			
			PrevX = x;
			PrevY = y;
			x = NewX;
			y = NewY;
			
			// Je¿eli podczas normalnego wywo³ania task nie bêdzie ju¿ wiêcej potrzebny
			// to mo¿e zwróciæ TaskDane, aby Sheduler usun¹³ go z tablicy tasków
			return TaskOK;
	}
	
	return TaskOK;
}

// Animated faces
#if SSD1681_FONT_DOS8x8 || SSD1681_FONT_DOS16x8
void SSD1681_CmdFace(uint8_t argc, uint8_t * argv[]) {
	task_t (*TaskPointer)(runmode_t RunMode);
	switch(*argv[1]) {
		#if SSD1681_FONT_DOS8x8
			case '1':	TaskPointer = SSD1681_TaskFace1;	break;
			case '2':	TaskPointer = SSD1681_TaskFace2;	break;
		#endif
		
		#if SSD1681_FONT_DOS16x8
			case '3':	TaskPointer = SSD1681_TaskFace3;	break;
			case '4':	TaskPointer = SSD1681_TaskFace4;	break;
		#endif
		
		default:	Print_ResponseError();				return;
	}
	
	if(TaskFind(TaskPointer) == OsNotFound) {
		TaskAdd(TaskPointer, TaskMsToTicks(10));
	}
	else {
		TaskClose(TaskPointer);
	}
	Print_ResponseOK();
}
#endif

#if SSD1681_FONT_DOS8x8
task_t SSD1681_TaskFace1(runmode_t RunMode) {
	
	static uint8_t X = 0;
	static uint8_t Y = 0;
	static uint8_t Char = 1;
	static uint8_t Dir = 0;
	static uint8_t StepsToDo = 0;
	uint8_t Rand; 
	
	switch(RunMode) {
		case FirstRun:
			X = 64;
			Y = 64;
			Dir = 0;
			StepsToDo = 0;
			return TaskOK;
			
		case Run:
			
			// Losowanie nowego kierunku i liczby kroków, je¿eli zadana liczba kroków zosta³a ju¿ wykonana
			if(StepsToDo == 0) {
				Rand = (uint8_t)random();
				Dir = Rand & 0b00000011;
				StepsToDo = 1 + ((Rand & 0b11111100) >> 2);
			}
			
			// Zmniejszanie liczby kroków do wykonania
			StepsToDo--;
			
			// Ustawienie czcionki
			SSD1681_FontSet(&SSD1681_FontDos8x8);
			SSD1681_ColorFrontSet(255, 0, 0);
			
			// Ukrywanie poprzednio wyœwietlonego znaku
			SSD1681_CursorSet(X, Y);
			SSD1681_PrintChar(0);
			
			// Przesuwanie pozycji
			switch(Dir) {
				
				// W lewo
				case 0:
					if(X > 0) X--;
					else X = SSD1681_DISPLAY_SIZE_X-8;
					break;
				
				// w prawo
				case 1:
					if(X < SSD1681_DISPLAY_SIZE_X-8) X++;
					else X = 0;
					break;
				
				// w górê
				case 2:
					if(Y > 0) Y--;
					else Y = SSD1681_DISPLAY_SIZE_Y-8; 
					break;
				
				// w dó³
				case 3:
					if(Y < 120) Y++;
					else Y = 0;
					break;
			}
			
			// Ustawienie pozycji kursora i wyœwietlenie znaku
			SSD1681_CursorSet(X, Y);
			SSD1681_PrintChar(Char);
			
			return TaskOK;
		
		case Close:
			SSD1681_CursorSet(X, Y);
			SSD1681_PrintChar(0);
			return TaskDone;
		
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Print("Face1");
			return TaskOK;
		#endif
	}

	return TaskOK;
}
#endif

#if SSD1681_FONT_DOS8x8
task_t SSD1681_TaskFace2(runmode_t RunMode) {
	
	static uint8_t X = 0;
	static uint8_t Y = 0;
	static uint8_t Char = 2;
	static uint8_t Dir = 0;
	static uint8_t StepsToDo = 0;
	uint8_t Rand; 
	
	switch(RunMode) {
		case FirstRun:
			X = 64;
			Y = 64;
			Dir = 0;
			StepsToDo = 0;
			return TaskOK;
		
		case Run:
			
			// Losowanie nowego kierunku i liczby kroków, je¿eli zadana liczba kroków zosta³a ju¿ wykonana
			if(StepsToDo == 0) {
				Rand = (uint8_t)random();
				Dir = Rand & 0b00000011;
				StepsToDo = 1 + ((Rand & 0b11111100) >> 2);
			}
			
			// Zmniejszanie liczby kroków do wykonania
			StepsToDo--;
			
			// Ustawienie czcionki
			SSD1681_FontSet(&SSD1681_FontDos8x8);
			SSD1681_ColorFrontSet(0, 0, 255);
			
			// Ukrywanie poprzednio wyœwietlonego znaku
			SSD1681_CursorSet(X, Y);
			SSD1681_PrintChar(0);
			
			// Przesuwanie pozycji
			switch(Dir) {
				
				// W lewo
				case 0:
					if(X > 0) X--;
					else X = SSD1681_DISPLAY_SIZE_X-8;
					break;
				
				// w prawo
				case 1:
					if(X < SSD1681_DISPLAY_SIZE_X-8) X++;
					else X = 0;
					break;
				
				// w górê
				case 2:
					if(Y > 0) Y--;
					else Y = SSD1681_DISPLAY_SIZE_Y-8; 
					break;
				
				// w dó³
				case 3:
					if(Y < SSD1681_DISPLAY_SIZE_Y-8) Y++;
					else Y = 0;
					break;
			}
			
			// Ustawienie pozycji kursora i wyœwietlenie znaku
			SSD1681_CursorSet(X, Y);
			SSD1681_PrintChar(Char);
			
			return TaskOK;
		
		case Close:
			SSD1681_CursorSet(X, Y);
			SSD1681_PrintChar(0);
			return TaskDone;
		
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Print("Face2");
			return TaskOK;
		#endif
	}
	
	return TaskOK;
}
#endif

#if SSD1681_FONT_DOS16x8
task_t SSD1681_TaskFace3(runmode_t RunMode) {
	
	static uint8_t X = 0;
	static uint8_t Y = 0;
	static uint8_t Char = 1;
	static uint8_t Dir = 0;
	static uint8_t StepsToDo = 0;
	uint8_t Rand; 
	
	switch(RunMode) {
		case FirstRun:
			X = 64;
			Y = 64;
			Dir = 0;
			StepsToDo = 0;
			return TaskOK;
		
		case Run:
			
			// Losowanie nowego kierunku i liczby kroków, je¿eli zadana liczba kroków zosta³a ju¿ wykonana
			if(StepsToDo == 0) {
				Rand = (uint8_t)random();
				Dir = Rand & 0b00000011;
				StepsToDo = 1 + ((Rand & 0b11111100) >> 2);
			}
			
			// Zmniejszanie liczby kroków do wykonania
			StepsToDo--;
			
			// Ustawienie czcionki
			SSD1681_FontSet(&SSD1681_FontDos16x8);
			SSD1681_ColorFrontSet(255, 255, 0);
			
			// Ukrywanie poprzednio wyœwietlonego znaku
			SSD1681_CursorSet(X, Y);
			SSD1681_PrintChar(0);
			
			// Przesuwanie pozycji
			switch(Dir) {
				
				// W lewo
				case 0:
					if(X > 0) X--;
					else X = SSD1681_DISPLAY_SIZE_X-8;
					break;
				
				// w prawo
				case 1:
					if(X < SSD1681_DISPLAY_SIZE_X-8) X++;
					else X = 0;
					break;
				
				// w górê
				case 2:
					if(Y > 0) Y--;
					else Y = SSD1681_DISPLAY_SIZE_Y-16; 
					break;
				
				// w dó³
				case 3:
					if(Y < SSD1681_DISPLAY_SIZE_Y-16) Y++;
					else Y = 0;
					break;
			}
			
			// Ustawienie pozycji kursora i wyœwietlenie znaku
			SSD1681_CursorSet(X, Y);
			SSD1681_PrintChar(Char);
			
			return TaskOK;
		
		case Close:
			SSD1681_CursorSet(X, Y);
			SSD1681_PrintChar(0);
			return TaskDone;
		
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Print("Face3");
			return TaskOK;
		#endif
	}
	
	return TaskOK;
}
#endif

#if SSD1681_FONT_DOS16x8
task_t SSD1681_TaskFace4(runmode_t RunMode) {
	
	static uint8_t X = 0;
	static uint8_t Y = 0;
	static uint8_t Char = 2;
	static uint8_t Dir = 0;
	static uint8_t StepsToDo = 0;
	uint8_t Rand; 
	
	switch(RunMode) {
		case FirstRun:
			X = 64;
			Y = 64;
			Dir = 0;
			StepsToDo = 0;
			return TaskOK;
			
		case Run:
			
			// Losowanie nowego kierunku i liczby kroków, je¿eli zadana liczba kroków zosta³a ju¿ wykonana
			if(StepsToDo == 0) {
				Rand = (uint8_t)random();
				Dir = Rand & 0b00000011;
				StepsToDo = 1 + ((Rand & 0b11111100) >> 2);
			}
			
			// Zmniejszanie liczby kroków do wykonania
			StepsToDo--;
			
			// Ustawienie czcionki
			SSD1681_FontSet(&SSD1681_FontDos16x8);
			SSD1681_ColorFrontSet(0, 255, 0);
			
			// Ukrywanie poprzednio wyœwietlonego znaku
			SSD1681_CursorSet(X, Y);
			SSD1681_PrintChar(0);
			
			// Przesuwanie pozycji
			switch(Dir) {
				
				// W lewo
				case 0:
					if(X > 0) X--;
					else X = SSD1681_DISPLAY_SIZE_X-8;
					break;
				
				// w prawo
				case 1:
					if(X < SSD1681_DISPLAY_SIZE_X-8) X++;
					else X = 0;
					break;
				
				// w górê
				case 2:
					if(Y > 0) Y--;
					else Y = SSD1681_DISPLAY_SIZE_Y-16; 
					break;
				
				// w dó³
				case 3:
					if(Y < SSD1681_DISPLAY_SIZE_Y-16) Y++;
					else Y = 0;
					break;
			}
			
			// Ustawienie pozycji kursora i wyœwietlenie znaku
			SSD1681_CursorSet(X, Y);
			SSD1681_PrintChar(Char);
			
			return TaskOK;
		
		case Close:
			SSD1681_CursorSet(X, Y);
			SSD1681_PrintChar(0);
			return TaskDone;
		
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Print("Face4");
			return TaskOK;
		#endif
	}
	
	return TaskOK;
}
#endif

*/
#endif
#endif
