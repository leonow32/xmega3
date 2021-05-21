#if COMPONENT_DISPLAY_SH1106
#include "display_sh1106_demo.h"
#if SH1106_USE_DEMO_COMMANDS

// Init
void SH1106_CmdInit(uint8_t argc, uint8_t * argv[]) {
	SH1106_Init();
	Print_ResponseOK();
}

// Clear display
void SH1106_CmdClear(uint8_t argc, uint8_t * argv[]) {
	SH1106_Clear();
	Print_ResponseOK();
}

// Light all pixels
void SH1106_CmdFill(uint8_t argc, uint8_t * argv[]) {
	SH1106_Fill();
	Print_ResponseOK();
}

// Draw chessboard
void SH1106_CmdDrawChessboard(uint8_t argc, uint8_t * argv[]) {
	SH1106_Chessboard();
	Print_ResponseOK();
}

// Draw chessboard
void SH1106_CmdDrawSlash(uint8_t argc, uint8_t * argv[]) {
	SH1106_Slash();
	Print_ResponseOK();
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

// Set color - 1 white, 0 black
void SH1106_CmdColor(uint8_t argc, uint8_t * argv[]) {
	switch(*argv[1]) {
		case '0':	SH1106_ColorSet(0);				break;
		case '1':	SH1106_ColorSet(1);				break;
		default:	Print_Dec(SH1106_ColorGet());	return;
	}
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
	//SH1106_DrawPixel(x, y, SH1106_RmwAdd);
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
	
	// Pseudo bitmap made of character from a font
	SH1106_Bitmap_t Smile = {
		.Height = 16,
		.Width = 8,
		.Array = &SH1106_BitmapDos16x8[16],
	};
	
	switch(*argv[1]) {
		
		#if SH1106_FONT_DOS16x8
			case '0':	Pointer = &Smile;								break;
		#endif
		
		#if SH1106_BITMAP_EXTRONIC_LOGO
			case '1':	Pointer = &SH1106_BitmapExtronicLogo;			break;
		#endif
		
		
		
		default:	Print_ResponseError();	return;
	}
	
	SH1106_CursorXSet((SH1106_DISPLAY_SIZE_X - Pointer->Width) / 2);
	SH1106_CursorPageSet(((SH1106_DISPLAY_SIZE_Y - Pointer->Height) / 2) / SH1106_PAGE_COUNT);
	SH1106_Bitmap(Pointer);
	Print_ResponseOK();
}

// ========================================
// Animated demos
// ========================================

void SH1106_CmdSnake(uint8_t argc, uint8_t * argv[]) {
	if(*argv[1] == '0') {
		TaskClose(SH1106_TaskSnake);
	}
	else {
		uint16_t Period;
		if(Parse_Dec16(argv[1], &Period)) return;
		TaskAdd(SH1106_TaskSnake, TaskMsToTicks(Period));
	}
	Print_ResponseOK();
}

task_t SH1106_TaskSnake(runmode_t RunMode) {
	
	// Zmienne
	static uint8_t x = 64;
	static uint8_t y = 32;
	static uint8_t PrevX = 64;
	static uint8_t PrevY = 32;
	
	uint8_t NewX;
	uint8_t NewY;
	uint8_t Random;
	
	// Tryb wywo³ania
	switch(RunMode) {
		
		// Konstruktor
		case FirstRun:
			x = 64;
			y = 32;
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
			Random = rand();
			NewX = Random & 0b01111111;
			Random = rand();
			NewY = Random & 0b00111111;
			
			SH1106_ColorSet(0);
 			SH1106_DrawLine(PrevX, PrevY, x, y);
			SH1106_ColorSet(1);
			SH1106_DrawLine(x, y, NewX, NewY);
			
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

void SH1106_CmdPixels(uint8_t argc, uint8_t * argv[]) {
	if(*argv[1] == '0') {
		TaskClose(SH1106_TaskPixels);
	}
	else {
		uint16_t Period;
		if(Parse_Dec16(argv[1], &Period)) return;
		TaskAdd(SH1106_TaskPixels, TaskMsToTicks(Period));
	}
	Print_ResponseOK();
}

task_t SH1106_TaskPixels(runmode_t RunMode) {
	
	// Zmienne
	uint8_t x;
	uint8_t y;
	uint8_t Random;
	
	// Tryb wywo³ania
	switch(RunMode) {
		
		// Konstruktor
		case FirstRun:
			return TaskOK;
		
		// Destruktor
		case Close:
			return TaskDone;
		
		// Wywo³anie identyfikacyjne
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Print("Pixels");
			return TaskOK;
		#endif
		
		// Normalne wywo³anie przez Sheduler
		case Run:
			Random = rand();
			x = Random & 0b01111111;
			Random = rand();
			y = Random & 0b00111111;
			
			SH1106_DrawPixel(x, y);
			
			// Je¿eli podczas normalnego wywo³ania task nie bêdzie ju¿ wiêcej potrzebny
			// to mo¿e zwróciæ TaskDane, aby Sheduler usun¹³ go z tablicy tasków
			return TaskOK;
	}
	
	return TaskOK;
}

// Animated faces
void SH1106_CmdFace(uint8_t argc, uint8_t * argv[]) {
	task_t (*TaskPointer)(runmode_t RunMode);
	switch(*argv[1]) {
		#if SH1106_FONT_DOS8x8
			case '1':	TaskPointer = SH1106_TaskFace1;	break;
			//case '2':	TaskPointer = SH1106_TaskFace2;	break;
		#endif
		
		#if SH1106_FONT_DOS16x8
			//case '3':	TaskPointer = SH1106_TaskFace3;	break;
			//case '4':	TaskPointer = SH1106_TaskFace4;	break;
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

task_t SH1106_TaskFace1(runmode_t RunMode) {
	
	static uint8_t X = 0;
	static uint8_t Y = 0;
	static uint8_t Dir = 0;
	static uint8_t StepsToDo = 0;
	uint8_t Rand; 
	
	switch(RunMode) {
		case FirstRun:
			X = 32;
			Y = 64;
			Dir = 0;
			StepsToDo = 0;
			return TaskOK;
			
		case Run:
			
			// Losowanie nowego kierunku i liczby kroków, je¿eli zadana liczba kroków zosta³a ju¿ wykonana
			if(StepsToDo == 0) {
				Rand = (uint8_t)random();
				Dir = Rand & 0b00000011;
				StepsToDo = 1 + (Rand & 0b00111111);
			}
			
			// Zmniejszanie liczby kroków do wykonania
			StepsToDo--;
			
			SH1106_ColorSet(0);
			SH1106_DrawCircle(X, Y, 8);
			
			// Przesuwanie pozycji
			switch(Dir) {
				
				// W lewo
				case 0:
					if(X > 8) X--;
					else X = SH1106_DISPLAY_SIZE_X-8;
					break;
				
				// w prawo
				case 1:
					if(X < SH1106_DISPLAY_SIZE_X-8) X++;
					else X = 8;
					break;
				
				// w górê
				case 2:
					if(Y > 8) Y--;
					else Y = SH1106_DISPLAY_SIZE_Y-8; 
					break;
				
				// w dó³
				case 3:
					if(Y < SH1106_DISPLAY_SIZE_Y-8) Y++;
					else Y = 8;
					break;
			}
			
			// Ustawienie pozycji kursora i wyœwietlenie znaku
			SH1106_ColorSet(1);
			SH1106_DrawCircle(X, Y, 8);
			
			return TaskOK;
		
		case Close:
			SH1106_ColorSet(0);
			SH1106_DrawCircle(X, Y, 8);
			SH1106_ColorSet(1);
			return TaskDone;
		
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Print("Face1");
			return TaskOK;
		#endif
	}

	return TaskOK;
}

// Display all characters from Dos8x8 font
#if SH1106_FONT_DOS8x8
void SH1106_CmdDemoFontDos8x8(uint8_t argc, uint8_t * argv[]) {
	
	static uint8_t Char = 0;
	SH1106_FontSet(&SH1106_FontDos8x8);
	
	for(uint8_t Line = 0; Line < SH1106_PAGE_COUNT; Line++) {
		SH1106_CursorPageSet(Line);
		SH1106_CursorXSet(0);
		
		for(uint8_t i = 0; i < SH1106_DISPLAY_SIZE_X / SH1106_FontDos8x8.Width; i++) {
			SH1106_PrintChar(Char++);
		}
	}
	
	Print_ResponseOK();
}
#endif

// Display all characters from Dos16x8 font
#if SH1106_FONT_DOS16x8
void SH1106_CmdDemoFontDos16x8(uint8_t argc, uint8_t * argv[]) {
	
	static uint8_t Char = 0;
	SH1106_FontSet(&SH1106_FontDos16x8);
	
	for(uint8_t Line = 0; Line < (SH1106_PAGE_COUNT / 2); Line++) {
		SH1106_CursorPageSet(2*Line);
		SH1106_CursorXSet(0);
		
		for(uint8_t i = 0; i < SH1106_DISPLAY_SIZE_X / SH1106_FontDos16x8.Width; i++) {
			SH1106_PrintChar(Char++);
		}
	}
	
	Print_ResponseOK();
}
#endif

// ========================================
// Benchmarks
// ========================================

void SH1106_CmdCircles(uint8_t argc, uint8_t * argv[]) {
	SH1106_Clear();
	for(uint8_t r = 0; r < 32; r = r + 2) {
		SH1106_DrawCircle(64, 32, r);
	}
	
	Print_ResponseOK();
}

#endif
#endif
