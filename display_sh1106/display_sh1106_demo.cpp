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

#endif
#endif
