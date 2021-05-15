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

#endif
#endif
