#if COMPONENT_DISPLAY_SSD1309
#include "display_ssd1309_demo.h"
#if SSD1309_USE_DEMO_COMMANDS

// Init
void SSD1309_CmdInit(uint8_t argc, uint8_t * argv[]) {
	SSD1309_Init();
	Print_ResponseOK();
}

// Clear display
void SSD1309_CmdClear(uint8_t argc, uint8_t * argv[]) {
	SSD1309_Clear();
	Print_ResponseOK();
}

// Light all pixels
void SSD1309_CmdFill(uint8_t argc, uint8_t * argv[]) {
	SSD1309_Fill();
	Print_ResponseOK();
}

// Draw chessboard
void SSD1309_CmdDrawChessboard(uint8_t argc, uint8_t * argv[]) {
	SSD1309_Chessboard();
	Print_ResponseOK();
}

// Draw chessboard
void SSD1309_CmdDrawSlash(uint8_t argc, uint8_t * argv[]) {
	SSD1309_Slash();
	Print_ResponseOK();
}

// Set contrast
void SSD1309_CmdContrast(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - contrast value
	uint8_t Contrast;
	if(Parse_Dec8(argv[1], &Contrast)) return;
	
	// Execute command
	SSD1309_ContrastSet(Contrast);
	Print_ResponseOK();
}

// Set color - 1 white, 0 black
void SSD1309_CmdColor(uint8_t argc, uint8_t * argv[]) {
	switch(*argv[1]) {
		case '0':	SSD1309_ColorSet(0);				break;
		case '1':	SSD1309_ColorSet(1);				break;
		default:	Print_Dec(SSD1309_ColorGet());	return;
	}
	Print_ResponseOK();
}

// Draw pixel
void SSD1309_CmdPixel(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X
	uint8_t x;
	if(Parse_Dec8(argv[1], &x, SSD1309_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y
	uint8_t y;
	if(Parse_Dec8(argv[2], &y, SSD1309_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SSD1309_DrawPixel(x, y);
	//SSD1309_DrawPixel(x, y, SSD1309_RmwAdd);
	Print_ResponseOK();
}

// Draw line
void SSD1309_CmdLine(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X0
	uint8_t x0;
	if(Parse_Dec8(argv[1], &x0, SSD1309_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y0;
	if(Parse_Dec8(argv[2], &y0, SSD1309_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 1 - coordinate X0
	uint8_t x1;
	if(Parse_Dec8(argv[3], &x1, SSD1309_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y1;
	if(Parse_Dec8(argv[4], &y1, SSD1309_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SSD1309_DrawLine(x0, y0, x1, y1);
	Print_ResponseOK();
}

// Draw rectangle
void SSD1309_CmdRectangle(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X0
	uint8_t x0;
	if(Parse_Dec8(argv[1], &x0, SSD1309_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y0;
	if(Parse_Dec8(argv[2], &y0, SSD1309_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 1 - coordinate X0
	uint8_t x1;
	if(Parse_Dec8(argv[3], &x1, SSD1309_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y1;
	if(Parse_Dec8(argv[4], &y1, SSD1309_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SSD1309_DrawRectangle(x0, y0, x1, y1);
	Print_ResponseOK();
}

// Draw rectangle and fill
void SSD1309_CmdRectangleFill(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X0
	uint8_t x0;
	if(Parse_Dec8(argv[1], &x0, SSD1309_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y0;
	if(Parse_Dec8(argv[2], &y0, SSD1309_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 1 - coordinate X0
	uint8_t x1;
	if(Parse_Dec8(argv[3], &x1, SSD1309_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y0
	uint8_t y1;
	if(Parse_Dec8(argv[4], &y1, SSD1309_DISPLAY_SIZE_Y-1)) return;
	
	// Execute command
	SSD1309_DrawRectangleFill(x0, y0, x1, y1);
	Print_ResponseOK();
}

// Craw circle
void SSD1309_CmdDrawCircle(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 1 - coordinate X
	uint8_t x;
	if(Parse_Dec8(argv[1], &x, SSD1309_DISPLAY_SIZE_X-1)) return;
	
	// Argument 2 - coordinate Y
	uint8_t y;
	if(Parse_Dec8(argv[2], &y, SSD1309_DISPLAY_SIZE_Y-1)) return;
	
	// Argument 1 - radius
	uint8_t r;
	if(Parse_Dec8(argv[3], &r)) return;
	
	// Execute command
	SSD1309_DrawCircle(x, y, r);
	Print_ResponseOK();
}

// Set or get cursor position
void SSD1309_CmdCursor(uint8_t argc, uint8_t * argv[]) {
	
	// If no arguments, then print actual cursor position
	if(argc == 1) {
		uint8_t x = SSD1309_CursorXGet();
		uint8_t y = SSD1309_CursorPageGet();
		Print("x = ");
		Print_Dec(x);
		Print("\r\np = ");
		Print_Dec(y);
	}
	
	// If arguments given, then set cursor position
	else {
		// Argument 1 - coordinate X
		uint8_t x;
		if(Parse_Dec8(argv[1], &x, SSD1309_DISPLAY_SIZE_X-1)) return;
		
		// Argument 2 - cpage
		uint8_t p;
		if(Parse_Dec8(argv[2], &p, SSD1309_DISPLAY_SIZE_Y-1)) return;
		
		// Execute command
		SSD1309_CursorXSet(x);
		SSD1309_CursorPageSet(p);
		Print_ResponseOK();
	}
}

// ========================================
// Fonts and text
// ========================================

// Print text
void SSD1309_CmdText(uint8_t argc, uint8_t * argv[]) {
	
	// Argument 2 optional - text align
	SSD1309_align_t Align = SSD1309_AlignNone;
	if(argc == 3) {
		switch(*argv[2]) {
			case '1':	Align = SSD1309_AlignLeft;	break;
			case '2':	Align = SSD1309_AlignCenter;	break;
			case '3':	Align = SSD1309_AlignRight;	break;
			default:	Align = SSD1309_AlignNone;	break;
		}
	}
	
	// Execute command
	SSD1309_Text((const char *)argv[1], Align);
	Print_ResponseOK();
}

// Change font
void SSD1309_CmdFont(uint8_t argc, uint8_t * argv[]) {
	
	uint8_t FontNumber;
	if(Parse_Dec8(argv[1], &FontNumber)) return;
	
	switch(FontNumber) {
		
		#if SSD1309_FONT_CONSOLE8x6
			case 1:	SSD1309_FontSet(&SSD1309_FontConsole8x6);		break;
		#endif
		
		#if SSD1309_FONT_DOS8x8
			case 2:	SSD1309_FontSet(&SSD1309_FontDos8x8);			break;
		#endif
		
		#if SSD1309_FONT_DOS16x8
			case 3:	SSD1309_FontSet(&SSD1309_FontDos16x8);		break;
		#endif
		
		#if SSD1309_FONT_SANS8
			case 5:	SSD1309_FontSet(&SSD1309_FontSans8);			break;
		#endif
		
		#if SSD1309_FONT_SANS16
			case 6:	SSD1309_FontSet(&SSD1309_FontSans16);			break;
		#endif
		
		#if SSD1309_FONT_SANS16B
			case 7:	SSD1309_FontSet(&SSD1309_FontSans16B);		break;
		#endif
		
		#if SSD1309_FONT_SANS24
			case 8:	SSD1309_FontSet(&SSD1309_FontSans24);			break;
		#endif
		
		#if SSD1309_FONT_SANS24B
			case 9:	SSD1309_FontSet(&SSD1309_FontSans24B);		break;
		#endif
		
		default:
			Print_ResponseError();
			return;
	}
	
	Print_ResponseOK();
}

void SSD1309_CmdFontDemo(uint8_t argc, uint8_t * argv[]) {
	SSD1309_Clear();
	
// 	SSD1309_CursorXSet(0);
// 	SSD1309_CursorPageSet(0);
// 	SSD1309_FontSet(&SSD1309_FontConsole8x6);
// 	SSD1309_Text("Left", SSD1309_AlignLeft);
// 	SSD1309_Text("Center", SSD1309_AlignCenter);
// 	SSD1309_Text("Right", SSD1309_AlignRight);
	
	SSD1309_CursorXSet(0);
	SSD1309_CursorPageSet(1);
	SSD1309_FontSet(&SSD1309_FontDos16x8);
	SSD1309_Text("Abcdefghij");
// 	
// 	SSD1309_CursorXSet(85);
// 	SSD1309_CursorPageSet(1);
// 	SSD1309_FontSet(&SSD1309_FontDos8x8);
// 	SSD1309_Text("Abcde");
// 	
// 	SSD1309_CursorXSet(85);
// 	SSD1309_CursorPageSet(2);
// 	SSD1309_Text("fghij");
// 	
// 	SSD1309_CursorXSet(0);
// 	SSD1309_CursorPageSet(3);
// 	SSD1309_FontSet(&SSD1309_FontSans16);
// 	SSD1309_Text("Abciwg123");
// 	
// 	SSD1309_CursorPageSet(3);
// 	SSD1309_FontSet(&SSD1309_FontSans16B);
// 	SSD1309_Text("Abciwg1", SSD1309_AlignRight);
// 	
// 	SSD1309_CursorXSet(0);
// 	SSD1309_CursorPageSet(5);
// 	SSD1309_FontSet(&SSD1309_FontSans24);
// 	SSD1309_Text("Abciwg1");
// 	
// 	SSD1309_CursorPageSet(5);
// 	SSD1309_FontSet(&SSD1309_FontSans24B);
// 	SSD1309_Text("Abc", SSD1309_AlignRight);
	
	Print_ResponseOK();
}

// ========================================
// Bitmaps
// ========================================

void SSD1309_CmdBitmap(uint8_t argc, uint8_t * argv[]) {
	
	const SSD1309_Bitmap_t * Pointer;
	
	// Pseudo bitmap made of character from a font
	SSD1309_Bitmap_t Smile = {
		.Height = 16,
		.Width = 8,
		.Array = &SSD1309_BitmapDos16x8[16],
	};
	
	switch(*argv[1]) {
		
		#if SSD1309_FONT_DOS16x8
			case '0':	Pointer = &Smile;								break;
		#endif
		
		#if SSD1309_BITMAP_EXTRONIC_LOGO
			case '1':	Pointer = &SSD1309_BitmapExtronicLogo;			break;
		#endif
		
		
		
		default:	Print_ResponseError();	return;
	}
	
	SSD1309_CursorXSet((SSD1309_DISPLAY_SIZE_X - Pointer->Width) / 2);
	SSD1309_CursorPageSet(((SSD1309_DISPLAY_SIZE_Y - Pointer->Height) / 2) / SSD1309_PAGE_COUNT);
	SSD1309_Bitmap(Pointer);
	Print_ResponseOK();
}

// ========================================
// Animated demos
// ========================================

void SSD1309_CmdSnake(uint8_t argc, uint8_t * argv[]) {
	if(*argv[1] == '0') {
		TaskClose(SSD1309_TaskSnake);
	}
	else {
		uint16_t Period;
		if(Parse_Dec16(argv[1], &Period)) return;
		TaskAdd(SSD1309_TaskSnake, TaskMsToTicks(Period));
	}
	Print_ResponseOK();
}

task_t SSD1309_TaskSnake(runmode_t RunMode) {
	
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
			
			SSD1309_ColorSet(0);
 			SSD1309_DrawLine(PrevX, PrevY, x, y);
			SSD1309_ColorSet(1);
			SSD1309_DrawLine(x, y, NewX, NewY);
			
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

void SSD1309_CmdPixels(uint8_t argc, uint8_t * argv[]) {
	if(*argv[1] == '0') {
		TaskClose(SSD1309_TaskPixels);
	}
	else {
		uint16_t Period;
		if(Parse_Dec16(argv[1], &Period)) return;
		TaskAdd(SSD1309_TaskPixels, TaskMsToTicks(Period));
	}
	Print_ResponseOK();
}

task_t SSD1309_TaskPixels(runmode_t RunMode) {
	
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
			
			SSD1309_DrawPixel(x, y);
			
			// Je¿eli podczas normalnego wywo³ania task nie bêdzie ju¿ wiêcej potrzebny
			// to mo¿e zwróciæ TaskDane, aby Sheduler usun¹³ go z tablicy tasków
			return TaskOK;
	}
	
	return TaskOK;
}

// Animated faces
void SSD1309_CmdFace(uint8_t argc, uint8_t * argv[]) {
	task_t (*TaskPointer)(runmode_t RunMode);
	switch(*argv[1]) {
		#if SSD1309_FONT_DOS8x8
			case '1':	TaskPointer = SSD1309_TaskFace1;	break;
			//case '2':	TaskPointer = SSD1309_TaskFace2;	break;
		#endif
		
		#if SSD1309_FONT_DOS16x8
			//case '3':	TaskPointer = SSD1309_TaskFace3;	break;
			//case '4':	TaskPointer = SSD1309_TaskFace4;	break;
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

task_t SSD1309_TaskFace1(runmode_t RunMode) {
	
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
			
			SSD1309_ColorSet(0);
			SSD1309_DrawCircle(X, Y, 8);
			
			// Przesuwanie pozycji
			switch(Dir) {
				
				// W lewo
				case 0:
					if(X > 8) X--;
					else X = SSD1309_DISPLAY_SIZE_X-8;
					break;
				
				// w prawo
				case 1:
					if(X < SSD1309_DISPLAY_SIZE_X-8) X++;
					else X = 8;
					break;
				
				// w górê
				case 2:
					if(Y > 8) Y--;
					else Y = SSD1309_DISPLAY_SIZE_Y-8; 
					break;
				
				// w dó³
				case 3:
					if(Y < SSD1309_DISPLAY_SIZE_Y-8) Y++;
					else Y = 8;
					break;
			}
			
			// Ustawienie pozycji kursora i wyœwietlenie znaku
			SSD1309_ColorSet(1);
			SSD1309_DrawCircle(X, Y, 8);
			
			return TaskOK;
		
		case Close:
			SSD1309_ColorSet(0);
			SSD1309_DrawCircle(X, Y, 8);
			SSD1309_ColorSet(1);
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
#if SSD1309_FONT_DOS8x8
void SSD1309_CmdDemoFontDos8x8(uint8_t argc, uint8_t * argv[]) {
	
	static uint8_t Char = 0;
	SSD1309_FontSet(&SSD1309_FontDos8x8);
	
	for(uint8_t Line = 0; Line < SSD1309_PAGE_COUNT; Line++) {
		SSD1309_CursorPageSet(Line);
		SSD1309_CursorXSet(0);
		
		for(uint8_t i = 0; i < SSD1309_DISPLAY_SIZE_X / SSD1309_FontDos8x8.Width; i++) {
			SSD1309_PrintChar(Char++);
		}
	}
	
	Print_ResponseOK();
}
#endif

// Display all characters from Dos16x8 font
#if SSD1309_FONT_DOS16x8
void SSD1309_CmdDemoFontDos16x8(uint8_t argc, uint8_t * argv[]) {
	
	static uint8_t Char = 0;
	SSD1309_FontSet(&SSD1309_FontDos16x8);
	
	for(uint8_t Line = 0; Line < (SSD1309_PAGE_COUNT / 2); Line++) {
		SSD1309_CursorPageSet(2*Line);
		SSD1309_CursorXSet(0);
		
		for(uint8_t i = 0; i < SSD1309_DISPLAY_SIZE_X / SSD1309_FontDos16x8.Width; i++) {
			SSD1309_PrintChar(Char++);
		}
	}
	
	Print_ResponseOK();
}
#endif

// ========================================
// Benchmarks
// ========================================

void SSD1309_CmdCircles(uint8_t argc, uint8_t * argv[]) {
	SSD1309_Clear();
	for(uint8_t r = 0; r < 32; r = r + 2) {
		SSD1309_DrawCircle(64, 32, r);
	}
	
	Print_ResponseOK();
}

#endif
#endif
