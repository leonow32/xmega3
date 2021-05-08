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

// ========================================
// Fonts and text
// ========================================

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
			case '1':	SSD1351_FontSet(&SSD1351_FontConsole8x6);		break;
		#endif
		
		#if SSD1351_FONT_DOS8x8
			case '2':	SSD1351_FontSet(&SSD1351_FontDos8x8);			break;
		#endif
		
		#if SSD1351_FONT_DOS16x8
			case '3':	SSD1351_FontSet(&SSD1351_FontDos16x8);			break;
		#endif
		
		#if SSD1351_FONT_SANS16_PL
			case '4':	SSD1351_FontSet(&SSD1351_FontSans16_PL);		break;
		#endif
		
		#if SSD1351_FONT_SANS16B_PL
			case '5':	SSD1351_FontSet(&SSD1351_FontSans16B_PL);		break;
		#endif
		
		#if SSD1351_FONT_SANS24_PL
			case '6':	SSD1351_FontSet(&SSD1351_FontSans24_PL);		break;
		#endif
		
		default:
			Print_ResponseError();
			return;
	}
	
	Print_ResponseOK();
}

// Display all characters from Dos8x8 font
#if SSD1351_FONT_DOS8x8
void SSD1351_CmdDemoFontDos8x8(uint8_t argc, uint8_t * argv[]) {
	
	uint8_t Char = 0;
	SSD1351_FontSet(&SSD1351_FontDos8x8);
	
	for(uint8_t Line = 0; Line < 16; Line++) {
		SSD1351_CursorSet(0, Line * 8);
		
		for(uint8_t i=0; i<16; i++) {
			SSD1351_ColorFrontSet(SSD1351_ColorNameToRGB565((i & 0b00000111)+1));
			SSD1351_PrintChar(Char++);
		}
	}
}
#endif

// Test all fonts
void SSD1351_CmDDemoFontTest(uint8_t argc, uint8_t * argv[]) {
	
	SSD1351_Clear();
	
	#if SSD1351_FONT_CONSOLE8x8
		SSD1351_ColorFrontSet(255, 255, 255);
		SSD1351_ColorBackSet(0, 0, 0);
		SSD1351_FontSet(&SSD1351_FontConsole8x6);
		SSD1351_CursorSet(0, 0);
		SSD1351_Text("ABCDEFGHIJKLMNOPQRSTU");
		SSD1351_CursorSet(0, 8);
		SSD1351_Text("abcdefghijk0123456789");
	#endif
	
	#if SSD1351_FONT_DOS8x8
		SSD1351_ColorFrontSet(255, 0, 0);
		SSD1351_CursorSet(0, 17);
		SSD1351_FontSet(&SSD1351_FontDos8x8);
		SSD1351_Text("ABCDEFGHIJKLMNOP");
	#endif
	
	#if SSD1351_FONT_SANS16_PL
		SSD1351_ColorFrontSet(255, 255, 0);
		SSD1351_CursorSet(0, 24);
		SSD1351_FontSet(&SSD1351_FontSans16_PL);
		SSD1351_Text("ABCDEFGHIJKLMNO");
		SSD1351_CursorSet(0, 36);
		SSD1351_Text("abcdefghijklmn1234567");
	#endif
	
	#if SSD1351_FONT_SANS16B_PL
		SSD1351_ColorFrontSet(0, 255, 0);
		SSD1351_CursorSet(0, 51);
		SSD1351_FontSet(&SSD1351_FontSans16B_PL);
		SSD1351_Text("ABCDEFGHIJKLMN");
		SSD1351_CursorSet(0, 63);
		SSD1351_Text("abcdefghijklmn1234");
	#endif
	
	#if SSD1351_FONT_SANS24_PL
		SSD1351_ColorFrontSet(0, 0, 255);
		SSD1351_CursorSet(0, 78);
		SSD1351_FontSet(&SSD1351_FontSans24_PL);
		SSD1351_Text("ABCDEFGHIJ");
		SSD1351_CursorSet(0, 97);
		SSD1351_Text("abcdefghij123");
	#endif
	
	#if SSD1351_FONT_DOS8x8
		SSD1351_ColorFrontSet(255, 0, 255);
		SSD1351_CursorSet(0, 119);
		SSD1351_FontSet(&SSD1351_FontDos8x8);
		SSD1351_Text("123!@#$");
	#endif
}

// Print some messages in varoius positions
void SSD1351_CmdDemoTextAlign(uint8_t argc, uint8_t * argv[]) {
	SSD1351_Chessboard();
	SSD1351_Text("TL",		SSD1351_HALIGN_LEFT		| SSD1351_VALIGN_TOP);
	SSD1351_Text("Top",		SSD1351_HALIGN_CENTER	| SSD1351_VALIGN_TOP);
	SSD1351_Text("TR",		SSD1351_HALIGN_RIGHT	| SSD1351_VALIGN_TOP);
	SSD1351_Text("Left",	SSD1351_HALIGN_LEFT		| SSD1351_VALIGN_CENTER);
	SSD1351_Text("Center",	SSD1351_HALIGN_CENTER	| SSD1351_VALIGN_CENTER);
	SSD1351_Text("Right",	SSD1351_HALIGN_RIGHT	| SSD1351_VALIGN_CENTER);
	SSD1351_Text("BL",		SSD1351_HALIGN_LEFT		| SSD1351_VALIGN_BOTTOM);
	SSD1351_Text("Bottom",	SSD1351_HALIGN_CENTER	| SSD1351_VALIGN_BOTTOM);
	SSD1351_Text("BR",		SSD1351_HALIGN_RIGHT	| SSD1351_VALIGN_BOTTOM);
	
	SSD1351_CursorSet(10, 90);
	SSD1351_Text("Somewhere else");
}

// Display all characters from Dos16x8 font
#if SSD1351_FONT_DOS16x8
void SSD1351_CmdDemoFontDos16x8(uint8_t argc, uint8_t * argv[]) {
	
	static uint8_t Char = 0;
	SSD1351_FontSet(&SSD1351_FontDos16x8);
	
	for(uint8_t Line = 0; Line < 8; Line++) {
		SSD1351_CursorSet(0, Line * 16);
		SSD1351_ColorFrontSet(SSD1351_ColorNameToRGB565(Line+1));
		
		for(uint8_t i=0; i<16; i++) {
			SSD1351_PrintChar(Char++);
		}
	}
}
#endif

void SSD1351_CmdDemoColorPalette(uint8_t argc, uint8_t * argv[]) {
	
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint16_t Color;
	
	SSD1351_Clear();
	
	SSD1351_CHIP_SELECT;
	
	// Czerwony -> ¿ó³ty
	R = 255;
	G = 0;
	B = 0;
	for(uint8_t i=0; i<21; i++) {
		G = G + 12;
		Color = SSD1351_ColorRGB888toRGB565(R, G, B);
		Spi_Repeat(Color >> 8, Color & 0x00FF, 128);
	}
	
	// ¯ó³ty -> zielony
	R = 255;
	G = 255;
	B = 0;
	for(uint8_t i=0; i<21; i++) {
		R = R - 12;
		Color = SSD1351_ColorRGB888toRGB565(R, G, B);
		Spi_Repeat(Color >> 8, Color & 0x00FF, 128);
	}
	
	// Zielony -> cyjan
	R = 0;
	G = 255;
	B = 0;
	for(uint8_t i=0; i<21; i++) {
		B = B + 12;
		Color = SSD1351_ColorRGB888toRGB565(R, G, B);
		Spi_Repeat(Color >> 8, Color & 0x00FF, 128);
	}
	
	// Cyjan -> niebieski
	R = 0;
	G = 255;
	B = 255;
	for(uint8_t i=0; i<21; i++) {
		G = G - 12;
		Color = SSD1351_ColorRGB888toRGB565(R, G, B);
		Spi_Repeat(Color >> 8, Color & 0x00FF, 128);
	}
	
	// Niebieski -> magenta
	R = 0;
	G = 0;
	B = 255;
	for(uint8_t i=0; i<21; i++) {
		R = R + 12;
		Color = SSD1351_ColorRGB888toRGB565(R, G, B);
		Spi_Repeat(Color >> 8, Color & 0x00FF, 128);
	}
	
	// Magenta -> czerowny
	R = 255;
	G = 0;
	B = 255;
	for(uint8_t i=0; i<21; i++) {
		B = B - 12;
		Color = SSD1351_ColorRGB888toRGB565(R, G, B);
		Spi_Repeat(Color >> 8, Color & 0x00FF, 128);
	}
	
	SSD1351_CHIP_DESELECT;
}

// ========================================
// Bitmaps
// ========================================

void SSD1351_CmdBitmap(uint8_t argc, uint8_t * argv[]) {
	
	const SSD1351_Bitmap_t * Pointer;
	switch(*argv[1]) {
		
		#if SSD1351_BITMAP_ARROW
			case '1':	Pointer = &SSD1351_BitmapArrow;						break;
		#endif
		
		#if SSD1351_BITMAP_EXTRONIC_LOGO_MONO
			case '2':	Pointer = &SSD1351_BitmapExtronicLogoMono;			break;
		#endif
		
		#if SSD1351_BITMAP_EXTRONIC_LOGO_RGB565
			case '3':	Pointer = &SSD1351_BitmapExtronicLogoRGB565;		break;
		#endif
		
		#if SSD1351_BITMAP_ME_AND_MY_GIRLFRIEND
			case '4':	Pointer = &SSD1351_BitmapMeAndMyGirlfriend;			break;
		#endif
		
		#if SSD1351_BITMAP_CASSINI_RGB332
			case '5':	Pointer = &SSD1351_BitmapCassiniRGB332;				break;
		#endif
		
		#if SSD1351_BITMAP_CASSINI_RGB565
			case '6':	Pointer = &SSD1351_BitmapCassiniRGB565;				break;
		#endif
		
		default:	Print_ResponseError();	return;
	}
	
	SSD1351_CursorXSet((SSD1351_DISPLAY_SIZE_X - Pointer->Width) / 2);
	SSD1351_CursorYSet((SSD1351_DISPLAY_SIZE_Y - Pointer->Height) / 2);
	SSD1351_Bitmap(Pointer);
}

// ========================================
// Animated demos
// ========================================

void SSD1351_CmdSnake(uint8_t argc, uint8_t * argv[]) {
	if(*argv[1] == '0') {
		TaskClose(SSD1351_TaskSnake);
	}
	else {
		TaskAdd(SSD1351_TaskSnake, TaskMsToTicks(100));
	}
}

task_t SSD1351_TaskSnake(runmode_t RunMode) {
	
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
			
			SSD1351_ColorFrontSet(0, 0, 0);
			SSD1351_DrawLine(PrevX, PrevY, x, y);
			SSD1351_ColorFrontSet(R, G, B);
			SSD1351_DrawLine(x, y, NewX, NewY);
			
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
#if SSD1351_FONT_DOS8x8 || SSD1351_FONT_DOS16x8
void SSD1351_CmdFace(uint8_t argc, uint8_t * argv[]) {
	task_t (*TaskPointer)(runmode_t RunMode);
	switch(*argv[1]) {
		#if SSD1351_FONT_DOS8x8
			case '1':	TaskPointer = SSD1351_TaskFace1;	break;
			case '2':	TaskPointer = SSD1351_TaskFace2;	break;
		#endif
		
		#if SSD1351_FONT_DOS16x8
			case '3':	TaskPointer = SSD1351_TaskFace3;	break;
			case '4':	TaskPointer = SSD1351_TaskFace4;	break;
		#endif
		
		default:	Print_ResponseError();				return;
	}
	
	if(TaskFind(TaskPointer) == OsNotFound) {
		TaskAdd(TaskPointer, TaskMsToTicks(100));
	}
	else {
		TaskClose(TaskPointer);
	}
	Print_ResponseOK();
}
#endif

#if SSD1351_FONT_DOS8x8
task_t SSD1351_TaskFace1(runmode_t RunMode) {
	
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
			SSD1351_FontSet(&SSD1351_FontDos8x8);
			SSD1351_ColorFrontSet(255, 0, 0);
			
			// Ukrywanie poprzednio wyœwietlonego znaku
			SSD1351_CursorSet(X, Y);
			SSD1351_PrintChar(0);
			
			// Przesuwanie pozycji
			switch(Dir) {
				
				// W lewo
				case 0:
					if(X > 0) X--;
					else X = SSD1351_DISPLAY_SIZE_X-8;
					break;
				
				// w prawo
				case 1:
					if(X < SSD1351_DISPLAY_SIZE_X-8) X++;
					else X = 0;
					break;
				
				// w górê
				case 2:
					if(Y > 0) Y--;
					else Y = SSD1351_DISPLAY_SIZE_Y-8; 
					break;
				
				// w dó³
				case 3:
					if(Y < 120) Y++;
					else Y = 0;
					break;
			}
			
			// Ustawienie pozycji kursora i wyœwietlenie znaku
			SSD1351_CursorSet(X, Y);
			SSD1351_PrintChar(Char);
			
			return TaskOK;
		
		case Close:
			SSD1351_CursorSet(X, Y);
			SSD1351_PrintChar(0);
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

#if SSD1351_FONT_DOS8x8
task_t SSD1351_TaskFace2(runmode_t RunMode) {
	
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
			SSD1351_FontSet(&SSD1351_FontDos8x8);
			SSD1351_ColorFrontSet(0, 0, 255);
			
			// Ukrywanie poprzednio wyœwietlonego znaku
			SSD1351_CursorSet(X, Y);
			SSD1351_PrintChar(0);
			
			// Przesuwanie pozycji
			switch(Dir) {
				
				// W lewo
				case 0:
					if(X > 0) X--;
					else X = SSD1351_DISPLAY_SIZE_X-8;
					break;
				
				// w prawo
				case 1:
					if(X < SSD1351_DISPLAY_SIZE_X-8) X++;
					else X = 0;
					break;
				
				// w górê
				case 2:
					if(Y > 0) Y--;
					else Y = SSD1351_DISPLAY_SIZE_Y-8; 
					break;
				
				// w dó³
				case 3:
					if(Y < SSD1351_DISPLAY_SIZE_Y-8) Y++;
					else Y = 0;
					break;
			}
			
			// Ustawienie pozycji kursora i wyœwietlenie znaku
			SSD1351_CursorSet(X, Y);
			SSD1351_PrintChar(Char);
			
			return TaskOK;
		
		case Close:
			SSD1351_CursorSet(X, Y);
			SSD1351_PrintChar(0);
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

#if SSD1351_FONT_DOS16x8
task_t SSD1351_TaskFace3(runmode_t RunMode) {
	
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
			SSD1351_FontSet(&SSD1351_FontDos16x8);
			SSD1351_ColorFrontSet(255, 255, 0);
			
			// Ukrywanie poprzednio wyœwietlonego znaku
			SSD1351_CursorSet(X, Y);
			SSD1351_PrintChar(0);
			
			// Przesuwanie pozycji
			switch(Dir) {
				
				// W lewo
				case 0:
					if(X > 0) X--;
					else X = SSD1351_DISPLAY_SIZE_X-8;
					break;
				
				// w prawo
				case 1:
					if(X < SSD1351_DISPLAY_SIZE_X-8) X++;
					else X = 0;
					break;
				
				// w górê
				case 2:
					if(Y > 0) Y--;
					else Y = SSD1351_DISPLAY_SIZE_Y-16; 
					break;
				
				// w dó³
				case 3:
					if(Y < SSD1351_DISPLAY_SIZE_Y-16) Y++;
					else Y = 0;
					break;
			}
			
			// Ustawienie pozycji kursora i wyœwietlenie znaku
			SSD1351_CursorSet(X, Y);
			SSD1351_PrintChar(Char);
			
			return TaskOK;
		
		case Close:
			SSD1351_CursorSet(X, Y);
			SSD1351_PrintChar(0);
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

#if SSD1351_FONT_DOS16x8
task_t SSD1351_TaskFace4(runmode_t RunMode) {
	
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
			SSD1351_FontSet(&SSD1351_FontDos16x8);
			SSD1351_ColorFrontSet(0, 255, 0);
			
			// Ukrywanie poprzednio wyœwietlonego znaku
			SSD1351_CursorSet(X, Y);
			SSD1351_PrintChar(0);
			
			// Przesuwanie pozycji
			switch(Dir) {
				
				// W lewo
				case 0:
					if(X > 0) X--;
					else X = SSD1351_DISPLAY_SIZE_X-8;
					break;
				
				// w prawo
				case 1:
					if(X < SSD1351_DISPLAY_SIZE_X-8) X++;
					else X = 0;
					break;
				
				// w górê
				case 2:
					if(Y > 0) Y--;
					else Y = SSD1351_DISPLAY_SIZE_Y-16; 
					break;
				
				// w dó³
				case 3:
					if(Y < SSD1351_DISPLAY_SIZE_Y-16) Y++;
					else Y = 0;
					break;
			}
			
			// Ustawienie pozycji kursora i wyœwietlenie znaku
			SSD1351_CursorSet(X, Y);
			SSD1351_PrintChar(Char);
			
			return TaskOK;
		
		case Close:
			SSD1351_CursorSet(X, Y);
			SSD1351_PrintChar(0);
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


#endif
#endif
