#if COMPONENT_DISPLAY_SH1106
#include "display_sh1106_demo.h"
#if SH1106_USE_DEMO_COMMANDS

// Init
void SH1106_CmdInit(uint8_t argc, uint8_t * argv[]) {
	SH1106_Init();
}

// Clear display
void SH1106_CmdClear(uint8_t argc, uint8_t * argv[]) {
	SH1106_Clear();
}

// Light all pixels
void SH1106_CmdFill(uint8_t argc, uint8_t * argv[]) {
	SH1106_Fill();
}

// Draw chessboard
void SH1106_CmdDrawChessboard(uint8_t argc, uint8_t * argv[]) {
	SH1106_Chessboard();
}

// Draw chessboard
void SH1106_CmdDrawSlash(uint8_t argc, uint8_t * argv[]) {
	SH1106_Slash();
}

// Set contrast
void SH1106_CmdContrast(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - contrast value
	uint8_t Contrast;
	if(Parse_Dec8(argv[1], &Contrast)) return;
	
	// Execute command
	SH1106_ContrastSet(Contrast);
	Print_ResponseOK();
}

// Draw pixel
void SH1106_CmdPixel(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X
	uint8_t x;
	if(Parse_Dec8(argv[1], &x, SH1106_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y
	uint8_t y;
	if(Parse_Dec8(argv[2], &y, SH1106_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SH1106_DrawPixel(x, y);
	Print_ResponseOK();
}

// Draw line
void SH1106_CmdLine(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X0
	uint8_t x0;
	if(Parse_Dec8(argv[1], &x0, SH1106_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y0;
	if(Parse_Dec8(argv[2], &y0, SH1106_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 1 - coordinate X0
	uint8_t x1;
	if(Parse_Dec8(argv[3], &x1, SH1106_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y1;
	if(Parse_Dec8(argv[4], &y1, SH1106_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SH1106_DrawLine(x0, y0, x1, y1);
	Print_ResponseOK();
}

// Draw rectangle
void SH1106_CmdRectangle(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X0
	uint8_t x0;
	if(Parse_Dec8(argv[1], &x0, SH1106_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y0;
	if(Parse_Dec8(argv[2], &y0, SH1106_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 1 - coordinate X0
	uint8_t x1;
	if(Parse_Dec8(argv[3], &x1, SH1106_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y1;
	if(Parse_Dec8(argv[4], &y1, SH1106_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SH1106_DrawRectangle(x0, y0, x1, y1);
	Print_ResponseOK();
}

// Draw rectangle and fill
void SH1106_CmdRectangleFill(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X0
	uint8_t x0;
	if(Parse_Dec8(argv[1], &x0, SH1106_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y0;
	if(Parse_Dec8(argv[2], &y0, SH1106_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 1 - coordinate X0
	uint8_t x1;
	if(Parse_Dec8(argv[3], &x1, SH1106_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y1;
	if(Parse_Dec8(argv[4], &y1, SH1106_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SH1106_DrawRectangleFill(x0, y0, x1, y1);
	Print_ResponseOK();
}

// Craw circle
void SH1106_CmdDrawCircle(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X
	uint8_t x;
	if(Parse_Dec8(argv[1], &x, SH1106_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y
	uint8_t y;
	if(Parse_Dec8(argv[2], &y, SH1106_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 1 - radius
	uint8_t r;
	if(Parse_Dec8(argv[3], &r)) return;
	
	// Execute command
	SH1106_DrawCircle(x, y, r);
	Print_ResponseOK();
}

// Set or get cursor position
void SH1106_CmdCursor(uint8_t argc, uint8_t * argv[]) {
	
	// If no arguments, then print actual cursor position
	if(argc == 1) {
		uint8_t x = SH1106_CursorXGet();
		uint8_t y = SH1106_CursorPageGet();
		Print("x = ");
		Print_Dec(x);
		Print("\r\np = ");
		Print_Dec(y);
	}
	
	// If arguments given, then set cursor position
	else {
		// Argument 1 - coordinate X
		uint8_t x;
		if(Parse_Dec8(argv[1], &x, SH1106_DISPLAY_SIZE_X-1)) return;
		
		// Argument 2 - cpage
		uint8_t p;
		if(Parse_Dec8(argv[2], &p, SH1106_DISPLAY_SIZE_Y-1)) return;
		
		// Execute command
		SH1106_CursorXSet(x);
		SH1106_CursorPageSet(p);
		Print_ResponseOK();
	}
}

// ========================================
// Fonts and text
// ========================================

// Print text
void SH1106_CmdText(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 2 optional - text align
	SH1106_align_t Align = SH1106_AlignNone;
	if(argc == 3) {
		switch(*argv[2]) {
			case '1':	Align = SH1106_AlignLeft;	break;
			case '2':	Align = SH1106_AlignCenter;	break;
			case '3':	Align = SH1106_AlignRight;	break;
			default:	Align = SH1106_AlignNone;	break;
		}
	}
	
	// Execute command
	SH1106_Text((const char *)argv[1], Align);
	Print_ResponseOK();
}

// Change font
void SH1106_CmdFont(uint8_t argc, uint8_t * argv[]) {
	
	uint8_t FontNumber;
	if(Parse_Dec8(argv[1], &FontNumber)) return;
	
	switch(FontNumber) {
		
		#if SH1106_FONT_CONSOLE8x6
			case 1:	SH1106_FontSet(&SH1106_FontConsole8x6);		break;
		#endif
		
		#if SH1106_FONT_DOS8x8
			case 2:	SH1106_FontSet(&SH1106_FontDos8x8);			break;
		#endif
		
		#if SH1106_FONT_DOS16x8
			case 3:	SH1106_FontSet(&SH1106_FontDos16x8);		break;
		#endif
		
		#if SH1106_FONT_SANS8
			case 5:	SH1106_FontSet(&SH1106_FontSans8);			break;
		#endif
		
		#if SH1106_FONT_SANS16
			case 6:	SH1106_FontSet(&SH1106_FontSans16);			break;
		#endif
		
		#if SH1106_FONT_SANS16B
			case 7:	SH1106_FontSet(&SH1106_FontSans16B);		break;
		#endif
		
		#if SH1106_FONT_SANS24
			case 8:	SH1106_FontSet(&SH1106_FontSans24);			break;
		#endif
		
		#if SH1106_FONT_SANS24B
			case 9:	SH1106_FontSet(&SH1106_FontSans24B);		break;
		#endif
		
		default:
			Print_ResponseError();
			return;
	}
	
	Print_ResponseOK();
}

// ========================================
// Bitmaps
// ========================================

void SH1106_CmdBitmap(uint8_t argc, uint8_t * argv[]) {
	
	const SH1106_Bitmap_t * Pointer;
	switch(*argv[1]) {
		
		#if SH1106_BITMAP_EXTRONIC_LOGO
			case '1':	Pointer = &SH1106_BitmapExtronicLogo;			break;
		#endif
		
		default:	Print_ResponseError();	return;
	}
	
	SH1106_CursorXSet((SH1106_DISPLAY_SIZE_X - Pointer->Width) / 2);
	SH1106_CursorPageSet(((SH1106_DISPLAY_SIZE_Y - Pointer->Height) / 2) / SH1106_PAGE_COUNT);
	SH1106_Bitmap(Pointer);
}

// ========================================
// Animated demos
// ========================================

void SH1106_CmdSnake(uint8_t argc, uint8_t * argv[]) {
	if(*argv[1] == '0') {
		TaskClose(SH1106_TaskSnake);
	}
	else {
		TaskAdd(SH1106_TaskSnake, TaskMsToTicks(50));
	}
}

task_t SH1106_TaskSnake(runmode_t RunMode) {
	
	// Zmienne
	static uint8_t x = 64;
	static uint8_t y = 32;
	static uint8_t PrevX = 64;;
	static uint8_t PrevY = 32;;
	
	uint8_t NewX;
	uint8_t NewY;
	uint8_t Random;
	
	// Tryb wywo�ania
	switch(RunMode) {
		
		// Konstruktor
		case FirstRun:
			x = 64;
			y = 32;
			return TaskOK;
		
		// Destruktor
		case Close:
			
			return TaskDone;
		
		// Wywo�anie identyfikacyjne
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Print("Snake");
			return TaskOK;
		#endif
		
		// Normalne wywo�anie przez Sheduler
		case Run:
			Random = rand();
			NewX = Random & 0b01111111;
			Random = rand();
			NewY = Random & 0b00111111;
			
// 			SH1106_ColorFrontSet(0, 0, 0);
// 			SH1106_DrawLine(PrevX, PrevY, x, y);
//			SH1106_ColorFrontSet(R, G, B);
			SH1106_DrawLine(x, y, NewX, NewY);
			
			PrevX = x;
			PrevY = y;
			x = NewX;
			y = NewY;
			
			// Je�eli podczas normalnego wywo�ania task nie b�dzie ju� wi�cej potrzebny
			// to mo�e zwr�ci� TaskDane, aby Sheduler usun�� go z tablicy task�w
			return TaskOK;
	}
	
	return TaskOK;
}

#endif
#endif
