#if COMPONENT_DISPLAY_SSD1351

#include	"display_ssd1351.h"

// ========================================
// Global variables
// ========================================

static uint8_t SSD1351_CursorX			= 0;
static uint8_t SSD1351_CursorX_Max		= SSD1351_DISPLAY_SIZE_X - 1;
static uint8_t SSD1351_CursorY			= 0;
static uint8_t SSD1351_CursorY_Max		= SSD1351_DISPLAY_SIZE_Y - 1;

const static SSD1351_FontDef_t * SSD1351_Font = &SSD1351_DEFAULT_FONT;
static uint8_t SSD1351_ColorFrontH		= 0xFF;		// White
static uint8_t SSD1351_ColorFrontL		= 0xFF;
static uint8_t SSD1351_ColorBackH		= 0x00;		// Black
static uint8_t SSD1351_ColorBackL		= 0x00;

// Display config for init function
static const uint8_t SSD1351_InitSequence[] = {
	1,	SSD1351_SET_LOCK_COMMAND,
	0,	0x12,
	
	1,	SSD1351_SET_LOCK_COMMAND,			// Command lock
	0,	0xB1,								// Command A2,B1,B3,BB,BE,C1 accessible if in unlock state
	
	1,	SSD1351_SLEEP_MODE_ON,				// Display off
	
	1, SSD1351_SET_DISPLAY_MODE_OFF,		// Normal Display mode
	
	1, SSD1351_COLUMN_RANGE,				// Set column address
	0, 0x00,								// Column address start value
	0, 0x7F,								// Column address end value
	
	1, SSD1351_ROW_RANGE,					// Set row address
	0, 0x00,								// Row address start value
	0, 0x7F,								// Row address end value
	
	1, SSD1351_CLOCK_DIVIDER_OSC_FREQ,
	0, 0xF1,
	
	1, SSD1351_SET_MUX_RATIO,
	0, 0x7F,
	
	1, SSD1351_REMAP_COLOR_DEPTH,			// Set re-map & data format
	0, 0b01110101,							// Vertical address increment 0b01110101
											// bit 0 - 1: kursor od lewej do prawej, 1 od góry do do³u
											// bit 1 - lustrzane odbicie Y
											// bit 2 - zamiana kolorów
											// bit 3 - nieu¿ywany
											// bit 4 - lustrzane odbicie X
											// bit 5 - naprzemienne linie (nie u¿ywaæ)
											// bit 67 - format koloru
	
	1, SSD1351_SET_DISPLAY_START_LINE,		// Set display start line
	0, 0x00,
	
	1, SSD1351_SET_DISPLAY_OFFSET,			// Set display offset
	0, 0x00,
	
	1, SSD1351_FUNCTION_SELECTION,
	0, 0x01,
	
	1, SSD1351_SET_SEGMENT_LOW_VOLTAGE,
	0, 0xA0,
	0, 0xB5,
	0, 0x55,
	
	1, SSD1351_SET_CONTRAST,
	0, SSD1351_DEFAULT_CONTRAST,
	0, SSD1351_DEFAULT_CONTRAST,
	0, SSD1351_DEFAULT_CONTRAST,
	
	1, SSD1351_MASTER_CONTRAST_CURRENT,
	0, 0x0F,
	
	1, SSD1351_SET_RESET_PRECHARGE,
	0, 0x32,
	
	1, SSD1351_DISPLAY_ENHANCEMENT,
	0, 0xA4,
	0, 0x00,
	0, 0x00,
	
	1, SSD1351_SET_PRECHARGE_VOLTAGE,
	0, 0x17,
	
	1, SSD1351_SET_SECOND_PRECHARGE,
	0, 0x01,
	
	1, SSD1351_SET_VCOMH_VOLTAGE,
	0, 0x05,
	
	1, SSD1351_SET_DISPLAY_MODE_RESET,
	
	#if SSD1351_CLEAR_AFERT_INIT == 0
		1, SSD1351_SLEEP_MODE_OFF,				// Display on
	#endif
};

// ========================================
// Basic functions
// ========================================

// Initialization
void SSD1351_Init(void) {
	
	SSD1351_CHIP_SELECT_INIT;
	SSD1351_DC_INIT;
	
	const uint8_t * Index = SSD1351_InitSequence;
	const uint8_t * Limit = SSD1351_InitSequence + sizeof(SSD1351_InitSequence);
	
	SSD1351_CHIP_SELECT;
	
	// Transmit array SSD1351_InitSequence
	while(Index != Limit) {
		if(*Index++) SSD1351_DC_COMMAND;
		else SSD1351_DC_DATA;
		Spi_1(*Index++);
	}
	
	SSD1351_CHIP_DESELECT;
	
	#if SSD1351_CLEAR_AFERT_INIT
		SSD1351_Clear();
		SSD1351_WriteCommand(SSD1351_SLEEP_MODE_OFF);
	#endif
}

// Send command
void SSD1351_WriteCommand(const uint8_t Command) {
	SSD1351_CHIP_SELECT;
	SSD1351_DC_COMMAND;
	Spi_1(Command);
	SSD1351_CHIP_DESELECT;
}

// Send data
void SSD1351_WriteData(const uint8_t Data) {
	SSD1351_CHIP_SELECT;
	SSD1351_DC_DATA;
	Spi_1(Data);
	SSD1351_CHIP_DESELECT;
}

// Allow to display data
void SSD1351_WriteRamEnable(void) {
	SSD1351_CHIP_SELECT;
	SSD1351_DC_COMMAND;
	Spi_1(SSD1351_RAM_WRITE);
	SSD1351_CHIP_DESELECT;	
}

// Set contrast
void SSD1351_ContrastSet(const uint8_t Value) {
	SSD1351_CHIP_SELECT;
	SSD1351_DC_COMMAND;
	Spi_1(SSD1351_SET_CONTRAST);
	SSD1351_DC_DATA;
	Spi_Repeat(Value, 3);
	SSD1351_DC_COMMAND;
	Spi_1(SSD1351_RAM_WRITE);
	SSD1351_DC_DATA;
	SSD1351_CHIP_DESELECT;
}

// Clear display
void SSD1351_Clear(void) {
	
	// Set active area to fill all the screen
	SSD1351_ActiveAreaSet(0, SSD1351_DISPLAY_SIZE_X-1, 0, SSD1351_DISPLAY_SIZE_Y-1);
	
	// Fill with background colored pixels
	SSD1351_CHIP_SELECT;
	Spi_Repeat(SSD1351_ColorBackH, SSD1351_ColorBackL, SSD1351_DISPLAY_SIZE_X * SSD1351_DISPLAY_SIZE_Y);
	SSD1351_CHIP_DESELECT;
}

// Print chessboard on the display
void SSD1351_Chessboard(void) {
	
	// For all range of X
	SSD1351_ActiveAreaXSet(0, SSD1351_DISPLAY_SIZE_X-1);
	
	// For all range of Y
	for(uint8_t y=0; y<SSD1351_DISPLAY_SIZE_Y; y++) {
		SSD1351_ActiveAreaYSet(y, y);
		SSD1351_CHIP_SELECT;
		if(y & 0x01) {
			// Odd lines
			for(uint8_t x=0; x<(SSD1351_DISPLAY_SIZE_X/2); x++) {
				Spi_4(SSD1351_ColorFrontH, SSD1351_ColorFrontL, SSD1351_ColorBackH, SSD1351_ColorBackL);
			}
		}
		else {
			// Even lines
			for(uint8_t x=0; x<(SSD1351_DISPLAY_SIZE_X/2); x++) {
				Spi_4(SSD1351_ColorBackH, SSD1351_ColorBackL, SSD1351_ColorFrontH, SSD1351_ColorFrontL);
			}
		}
		SSD1351_CHIP_DESELECT;
	}
	
	SSD1351_ActiveAreaSet(0, SSD1351_DISPLAY_SIZE_X-1, 0, SSD1351_DISPLAY_SIZE_Y-1);
}

// ========================================
// Cursor position
// ========================================

void SSD1351_CursorSet(uint8_t x, uint8_t y) {
	SSD1351_CursorX = x < SSD1351_DISPLAY_SIZE_X ? x : SSD1351_DISPLAY_SIZE_X-1;
	SSD1351_CursorY = y < SSD1351_DISPLAY_SIZE_Y ? y : SSD1351_DISPLAY_SIZE_Y-1;
}

uint8_t SSD1351_CursorXGet(void) {
	return SSD1351_CursorX;
}

void SSD1351_CursorXSet(uint8_t x) {
 	SSD1351_CursorX = x < SSD1351_DISPLAY_SIZE_X ? x : SSD1351_DISPLAY_SIZE_X-1;
}

uint8_t SSD1351_CursorYGet(void) {
	return SSD1351_CursorY;
}

void SSD1351_CursorYSet(uint8_t y) {
 	SSD1351_CursorY = y < SSD1351_DISPLAY_SIZE_Y ? y : SSD1351_DISPLAY_SIZE_Y-1;
}

// Set active area to write to in next operation
void SSD1351_ActiveAreaSet(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2) {
	
	// Sanity check
	SSD1351_CursorX			= x1 < SSD1351_DISPLAY_SIZE_X ? x1 : SSD1351_DISPLAY_SIZE_X-1;
	SSD1351_CursorX_Max		= x2 < SSD1351_DISPLAY_SIZE_X ? x2 : SSD1351_DISPLAY_SIZE_X-1;
	SSD1351_CursorY			= y1 < SSD1351_DISPLAY_SIZE_Y ? y1 : SSD1351_DISPLAY_SIZE_Y-1;
	SSD1351_CursorY_Max		= y2 < SSD1351_DISPLAY_SIZE_Y ? y2 : SSD1351_DISPLAY_SIZE_Y-1;
	
	// Send to display
	SSD1351_CHIP_SELECT;
	SSD1351_DC_COMMAND;
	Spi_1(SSD1351_COLUMN_RANGE);
	SSD1351_DC_DATA;
	Spi_2(SSD1351_CursorX, SSD1351_CursorX_Max);
	SSD1351_DC_COMMAND;
	Spi_1(SSD1351_ROW_RANGE);
	SSD1351_DC_DATA;
	Spi_2(SSD1351_CursorY, SSD1351_CursorY_Max);
	SSD1351_DC_COMMAND;
	Spi_1(SSD1351_RAM_WRITE);
	SSD1351_DC_DATA;
	SSD1351_CHIP_DESELECT;
}

// Change active area only in X dimension
void SSD1351_ActiveAreaXSet(uint8_t x1, uint8_t x2) {
	
	// Sanity check
	SSD1351_CursorX			= x1 < SSD1351_DISPLAY_SIZE_X ? x1 : SSD1351_DISPLAY_SIZE_X-1;
	SSD1351_CursorX_Max		= x2 < SSD1351_DISPLAY_SIZE_X ? x2 : SSD1351_DISPLAY_SIZE_X-1;
	
	// Send to display
	SSD1351_CHIP_SELECT;
	SSD1351_DC_COMMAND;
	Spi_1(SSD1351_COLUMN_RANGE);
	SSD1351_DC_DATA;
	Spi_2(SSD1351_CursorX, SSD1351_CursorX_Max);
	SSD1351_DC_COMMAND;
	Spi_1(SSD1351_RAM_WRITE);
	SSD1351_DC_DATA;
	SSD1351_CHIP_DESELECT;
}

// Change active area only in Y dimension
void SSD1351_ActiveAreaYSet(uint8_t y1, uint8_t y2) {
	
	// Sanity check
	SSD1351_CursorY			= y1 < SSD1351_DISPLAY_SIZE_Y ? y1 : SSD1351_DISPLAY_SIZE_Y-1;
	SSD1351_CursorY_Max		= y2 < SSD1351_DISPLAY_SIZE_Y ? y2 : SSD1351_DISPLAY_SIZE_Y-1;
	
	// Send to display
	SSD1351_CHIP_SELECT;
	SSD1351_DC_COMMAND;
	Spi_1(SSD1351_ROW_RANGE);
	SSD1351_DC_DATA;
	Spi_2(SSD1351_CursorY, SSD1351_CursorY_Max);
	SSD1351_DC_COMMAND;
	Spi_1(SSD1351_RAM_WRITE);
	SSD1351_DC_DATA;
	SSD1351_CHIP_DESELECT;
}

// ========================================
// Colors
// ========================================

// Get foreground color
uint16_t SSD1351_ColorFrontGet(void) {
	return (uint16_t)SSD1351_ColorFrontH << 8 | SSD1351_ColorFrontL;
}

// Set background color
void SSD1351_ColorFrontSet(uint16_t ColorRGB565) {
	SSD1351_ColorFrontH = (uint8_t)(ColorRGB565 >> 8);
	SSD1351_ColorFrontL = (uint8_t)(ColorRGB565 & 0x00FF);
}

// Set foreground color, each color speparate
void SSD1351_ColorFrontSet(uint8_t R, uint8_t G, uint8_t B) {
	
	// Convert RGB888 to RGB565
	R = R & 0b11111000;
	G = G & 0b11111100;
	B = B & 0b11111000;
	SSD1351_ColorFrontH = R | (G >> 5);
	SSD1351_ColorFrontL = (G << 3) | (B >> 3);
}

// Get foreground color as RGB565
uint16_t SSD1351_ColorBackGet(void) {
	return (uint16_t)SSD1351_ColorBackH << 8 | SSD1351_ColorBackL;
}

// Set background color
void SSD1351_ColorBackSet(uint16_t ColorRGB565) {
	SSD1351_ColorBackH = (uint8_t)(ColorRGB565 >> 8);
	SSD1351_ColorBackL = (uint8_t)(ColorRGB565 & 0x00FF);
}

// Set background color, each color speparate
void SSD1351_ColorBackSet(uint8_t R, uint8_t G, uint8_t B) {
	
	// Convert RGB888 to RGB565
	R = R & 0b11111000;
	G = G & 0b11111100;
	B = B & 0b11111000;
	SSD1351_ColorBackH = R | (G >> 5);
	SSD1351_ColorBackL = (G << 3) | (B >> 3);
}

// Convert color name to RGB565
uint16_t SSD1351_ColorNameToRGB565(uint8_t ColorName) {
	switch(ColorName) {
		case SSD1351_COLOR_BLACK_ID:			return SSD1351_COLOR_BLACK_RGB565;
		case SSD1351_COLOR_RED_ID:				return SSD1351_COLOR_RED_RGB565;
		case SSD1351_COLOR_GREEN_ID:			return SSD1351_COLOR_GREEN_RGB565;
		case SSD1351_COLOR_YELLOW_ID:			return SSD1351_COLOR_YELLOW_RGB565;
		case SSD1351_COLOR_BLUE_ID:				return SSD1351_COLOR_BLUE_RGB565;
		case SSD1351_COLOR_MAGENTA_ID:			return SSD1351_COLOR_MAGENTA_RGB565;
		case SSD1351_COLOR_CYAN_ID:				return SSD1351_COLOR_CYAN_RGB565;
		case SSD1351_COLOR_WHITE_ID:			return SSD1351_COLOR_WHITE_RGB565;
		case SSD1351_COLOR_GRAY_ID:				return SSD1351_COLOR_GRAY_RGB565;
		case SSD1351_COLOR_LIGHTRED_ID:			return SSD1351_COLOR_LIGHTRED_RGB565;
		case SSD1351_COLOR_LIGHTGREEN_ID:		return SSD1351_COLOR_LIGHTGREEN_RGB565;
		case SSD1351_COLOR_LIGHTYELLOW_ID:		return SSD1351_COLOR_LIGHTYELLOW_RGB565;
		case SSD1351_COLOR_LIGHTBLUE_ID:		return SSD1351_COLOR_LIGHTBLUE_RGB565;
		case SSD1351_COLOR_LIGHTMAGENTA_ID:		return SSD1351_COLOR_LIGHTMAGENTA_RGB565;
		case SSD1351_COLOR_LIGHTCYAN_ID:		return SSD1351_COLOR_LIGHTCYAN_RGB565;
		case SSD1351_COLOR_LIGHTGRAY_ID:		return SSD1351_COLOR_LIGHTGRAY_RGB565;
		default:								return 0;
	}
}

// Convert RGB888 na RGB565
uint16_t SSD1351_ColorRGB888toRGB565(uint8_t R, uint8_t G, uint8_t B) {
	
	R = R & 0b11111000;
	G = G & 0b11111100;
	B = B & 0b11111000;
	uint8_t ColorH = R | (G >> 5);
	uint8_t ColorL = (G << 3) | (B >> 3);
	
	return ((uint16_t)ColorH << 8) | ColorL;
}

// Convert RGB323 na RGB565
uint16_t SSD1351_ColorRGB332toRGB565(uint8_t Color332) {
	
	// Tabele konwersji palety
	const uint8_t b3to6lookup[8] = {0, 9, 18, 27, 36, 45, 54, 63};
	const uint8_t b3to5lookup[8] = {0, 4, 9, 13, 18, 22, 27, 31};
	const uint8_t b2to5lookup[4] = {0, 10, 21, 31};
	
	uint16_t red, green, blue;
	
	red = (Color332 & 0xe0) >> 5;			// rgb332 3 red bits now right justified
	red = (uint16_t)b3to5lookup[red];		// 3 bits converted to 5 bits
	red = red << 11;						// red bits now 5 MSB bits
	
	green = (Color332 & 0x1c) >> 2;			// rgb332 3 green bits now right justified
	green = (uint16_t)b3to6lookup[green];	// 3 bits converted to 6 bits
	green = green << 5;						// green bits now 6 "middle" bits
	
	blue = Color332 & 0x03;					// rgb332 2 blue bits are right justified
	blue = (uint16_t)b2to5lookup[blue];		// 2 bits converted to 5 bits, right justified
	
	return (uint16_t)(red | green | blue);
}

// ========================================
// Drawing of geometric shapes
// ========================================

// Single pixel
void SSD1351_DrawPixel(uint8_t x, uint8_t y) {
	SSD1351_ActiveAreaSet(x, x, y, y);
	SSD1351_CHIP_SELECT;
	Spi_2(SSD1351_ColorFrontH, SSD1351_ColorFrontL);
	SSD1351_CHIP_DESELECT;
}

// Horizontal line from (x0, y0) to the right
void SSD1351_DrawLineHorizontal(uint8_t x0, uint8_t y0, uint8_t Length) {
	SSD1351_ActiveAreaSet(x0, x0 + Length - 1, y0, y0);
	SSD1351_CHIP_SELECT;
	Spi_Repeat(SSD1351_ColorFrontH, SSD1351_ColorFrontL, Length);
	SSD1351_CHIP_DESELECT;
}

// Vertical line from (x0, y0) to the bottom
void SSD1351_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length) {
	SSD1351_ActiveAreaSet(x0, x0, y0, y0 + Length - 1);
	SSD1351_CHIP_SELECT;
	Spi_Repeat(SSD1351_ColorFrontH, SSD1351_ColorFrontL, Length);
	SSD1351_CHIP_DESELECT;
}

// Draw line with Bresenham's algorithm
void SSD1351_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	
	if(x0 == x1) {
		if(y0 > y1) {
			uint8_t temp = y0;
			y0 = y1;
			y1 = temp;
		}
		SSD1351_DrawLineVertical(x0, y0, y1-y0+1);
		return;
	}
	
	if(y0 == y1) {
		if(x0 > x1) {
			uint8_t temp = x0;
			x0 = x1;
			x1 = temp;
		}
		SSD1351_DrawLineHorizontal(x0, y0, x1-x0+1);
	}
	
	int16_t Sx;
	int16_t Sy;
	int16_t E2;
	int16_t Error;
	int16_t Dx = (x1 - x0);
	if(Dx < 0) Dx = -Dx;
	int16_t Dy = (y1 - y0);
	if(Dy < 0) Dy = -Dy;
	if (x0 < x1) Sx = 1; else Sx = -1;
	if (y0 < y1) Sy = 1; else Sy = -1;
	Error = Dx - Dy;
	while(1) {
		SSD1351_DrawPixel(x0, y0);
		if (x0==x1 && y0==y1) return;
		E2 = Error << 1;
		if (E2 > -Dy) { 
			Error = Error - Dy; 
			x0 = x0 + Sx; 
		}
		if (E2 < Dx) { 
			Error = Error + Dx; 
			y0 = y0 + Sy;
		}
	}
}

// Rectangle without fill
void SSD1351_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	SSD1351_DrawLineVertical(x0, y0, y1-y0+1);
	SSD1351_DrawLineVertical(x1, y0, y1-y0+1);
	SSD1351_DrawLineHorizontal(x0+1, y0, x1-x0-1);
	SSD1351_DrawLineHorizontal(x0+1, y1, x1-x0-1);
}

// Rectangle with fill
void SSD1351_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	for(uint8_t y=y0; y<=y1; y++) {
		SSD1351_DrawLineHorizontal(x0, y, y1-y0+1);
	}
}

// Circle
void SSD1351_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r) {
	
	int16_t d = 5 - 4*r;
	int16_t x = 0;
	int16_t y = r;
	int16_t deltaA = (-2*r + 5) * 4;
	int16_t deltaB = 3*4;
	
	while (x <= y) {
		SSD1351_DrawPixel(x0-x, y0-y);
		SSD1351_DrawPixel(x0-x, y0+y);
		SSD1351_DrawPixel(x0+x, y0-y);
		SSD1351_DrawPixel(x0+x, y0+y);
		SSD1351_DrawPixel(x0-y, y0-x);
		SSD1351_DrawPixel(x0-y, y0+x);
		SSD1351_DrawPixel(x0+y, y0-x);
		SSD1351_DrawPixel(x0+y, y0+x);
		if(d > 0) {
			d += deltaA;
			y--;
			x++;
			deltaA += 4*4;
			deltaB += 2*4;
		}
		else {
			d += deltaB;
			x++;
			deltaA += 2*4;
			deltaB += 2*4;
		}
	}
}

// ========================================
// Bitmaps
// ========================================

void SSD1351_Bitmap(const SSD1351_Bitmap_t * Bitmap) {
	switch(Bitmap->ColorDepth) {
		case SSD1351_ColorMono:		SSD1351_BitmapMono(Bitmap);		break;
		case SSD1351_ColorRGB332:	SSD1351_BitmapRGB332(Bitmap);	break;
		case SSD1351_ColorRGB565:	SSD1351_BitmapRGB565(Bitmap);	break;
	}
}

// Draw a monochrome bitmap
// Foreground color, background color, XY coordinates set before calling SSD1351_BitmapMono()
void SSD1351_BitmapMono(const SSD1351_Bitmap_t * Bitmap) {
	
	// Get size fo bitmap
	uint8_t WidthPixels = Bitmap->Width;
	uint8_t HeightPixels = Bitmap->Height;
	
	// Set active area to draw in
	SSD1351_ActiveAreaSet(SSD1351_CursorX, SSD1351_CursorX + WidthPixels - 1, SSD1351_CursorY, SSD1351_CursorY + HeightPixels - 1);
	
	// Column loop
	uint8_t Buffer = 0;
	uint16_t Address = 0;
	SSD1351_CHIP_SELECT;
	for(uint8_t ActualColumn = 0; ActualColumn < WidthPixels; ActualColumn++) {
		
		uint8_t ActualRow = HeightPixels;
		uint8_t BitMask = 0;
		
		// Row loop
		while(ActualRow--) {
			if(BitMask == 0) {
				BitMask = 0b10000000;
				Buffer = Bitmap->Bitmaps[Address++];
			}
			
			if(Buffer & BitMask) {
				// Foreground color
				Spi_2(SSD1351_ColorFrontH, SSD1351_ColorFrontL); 
			}
			else {
				// Background color
				Spi_2(SSD1351_ColorBackH, SSD1351_ColorBackL);
			}
			
			// Move bitmask
			BitMask = BitMask >> 1;
		}
	}
	SSD1351_CHIP_DESELECT;
}

// Draw a bitmap saved in format RGB565
// Set XY coordinates set before calling
void SSD1351_BitmapRGB565(const SSD1351_Bitmap_t * Bitmap) {
	
	// Get size fo bitmap
	uint8_t WidthPixels = Bitmap->Width;
	uint8_t HeightPixels = Bitmap->Height;
	
	// Set active area to draw into
	SSD1351_ActiveAreaSet(SSD1351_CursorX, SSD1351_CursorX + WidthPixels - 1, SSD1351_CursorY, SSD1351_CursorY + HeightPixels - 1);
	
	// Stream all pixels
	SSD1351_CHIP_SELECT;
	Spi_Write(Bitmap->Bitmaps, WidthPixels * HeightPixels * 2);
	SSD1351_CHIP_DESELECT;
}

// Draw a bitmap saved in format RGB5332
// Set XY coordinates set before calling
void SSD1351_BitmapRGB332(const SSD1351_Bitmap_t * Bitmap) {
	
	// Get size fo bitmap
	uint8_t WidthPixels = Bitmap->Width;
	uint8_t HeightPixels = Bitmap->Height;
	uint16_t Size = WidthPixels * HeightPixels;
	uint16_t Color565;
	const uint8_t * BitmapPointer = Bitmap->Bitmaps;
	
	// Set active area to draw in
	SSD1351_ActiveAreaSet(SSD1351_CursorX, SSD1351_CursorX + WidthPixels - 1, SSD1351_CursorY, SSD1351_CursorY + HeightPixels - 1);
	
	// Transmit all pixels
	SSD1351_CHIP_SELECT;
	while(Size--) {
		Color565 = SSD1351_ColorRGB332toRGB565(*BitmapPointer++);
		Spi_2(Color565 >> 8, Color565 & 0xFF);
	}
	SSD1351_CHIP_DESELECT;
}

// ========================================
// Fonts
// ========================================

// Get actual font
const SSD1351_FontDef_t * SSD1351_FontGet(void) {
	return SSD1351_Font;
}

// Set actual font
void SSD1351_FontSet(const SSD1351_FontDef_t * Font) {
	SSD1351_Font = Font;
}

// Print single character
void SSD1351_PrintChar(uint8_t Char) {
	
	// Check if character is supported by font
	if(Char < SSD1351_Font->FirstChar) Char = SSD1351_Font->LastChar;
	if(Char > SSD1351_Font->LastChar) Char = SSD1351_Font->LastChar;
	
	// Calculate character offset, because font table doesn't have to befin with 0x00 character
	Char = Char - SSD1351_Font->FirstChar;
	
	// Find width of the character and its position is bitmap table
	uint8_t Width;
	uint8_t Height = SSD1351_Font->Height;
	uint8_t Spacing = SSD1351_Font->Spacing;
	uint16_t Address;
	if(SSD1351_Font->Width > 0) {
		// For font with fixed width of all characters
		Width = SSD1351_Font->Width;
		Address = Char * Width * (Height/8);
	}
	else {
		// For font with characters with variable width
		Width = SSD1351_Font->Descriptors[Char].Width;
		Address = SSD1351_Font->Descriptors[Char].Offset;
	}
	
	// If Address is null and width = 0 then print last charachter from table (badchar)
	if((Address == 0) && (Width == 0)) {
		Char = SSD1351_Font->LastChar - SSD1351_Font->FirstChar;
		Address = SSD1351_Font->Descriptors[Char].Offset;
		Width = SSD1351_Font->Descriptors[Char].Width;
	}
	
	// Set active area to write into
	SSD1351_ActiveAreaSet(SSD1351_CursorX, SSD1351_CursorX + Width + Spacing - 1, SSD1351_CursorY, SSD1351_CursorY + Height - 1);
	
	// Stream all pixels
	uint8_t Buffer = 0;
	SSD1351_CHIP_SELECT;
	
	// Column loop
	for(uint8_t ActualColumn = 0; ActualColumn < Width; ActualColumn++) {
		
		uint8_t ActualRow = Height;
		uint8_t BitMask = 0;
		
		// Row loop
		while(ActualRow--) {
			if(BitMask == 0) {
				BitMask = 0b10000000;
				Buffer = SSD1351_Font->Bitmaps[Address++];
			}
			
			if(Buffer & BitMask) {
				// Transmit foreground color
				Spi_2(SSD1351_ColorFrontH, SSD1351_ColorFrontL);
			}
			else {
				// Transmit background color
				Spi_2(SSD1351_ColorBackH, SSD1351_ColorBackL);
			}
			
			BitMask = BitMask >> 1;
		}
	}
	
	// Spacing
	for(uint8_t Column = 0; Column < Spacing; Column++) {
		for(uint8_t i=0; i<Height; i++) {
			Spi_2(SSD1351_ColorBackH, SSD1351_ColorBackL);
		}
	}
	
	// End of transmission
	SSD1351_CHIP_DESELECT;
	
	// Move cursor at the end of character
	SSD1351_CursorX = SSD1351_CursorX + Width + Spacing;
	if(SSD1351_CursorX > SSD1351_DISPLAY_SIZE_X) {
		SSD1351_CursorX = SSD1351_CursorX - SSD1351_DISPLAY_SIZE_X;
	}
}

// Calculate text width
uint8_t SSD1351_TextWidthGet(const char * Text) {
	uint8_t Width = 0;
	uint16_t Offset = SSD1351_Font->FirstChar;
	
	// Check if the font has characters with fixed width
	if(SSD1351_Font->Width) {
		
		// Count number of characters
		while(*Text++) Width++;
		
		// Multiply by width of single character
		Width = Width * (SSD1351_Font->Width + SSD1351_Font->Spacing);						
	}
	else {
		// Font with variable character width
		while(*Text) {
			Width += SSD1351_Font->Descriptors[(*Text) - Offset].Width + SSD1351_Font->Spacing;			
			Text++;
		}
	}
	
	return Width;
}

// Print text. Remember to set font first!
void SSD1351_Text(const char * Text, uint8_t Align) {
	
	// Set cursor position to match text widht and align
	uint8_t Width = SSD1351_TextWidthGet(Text);
	uint8_t Height = SSD1351_Font->Height;
	
	// Horizontal align
	switch(Align & 0x0F) {
		case SSD1351_HALIGN_LEFT:
			SSD1351_CursorX = 0;
			break;
		case SSD1351_HALIGN_CENTER:
			SSD1351_CursorX = SSD1351_DISPLAY_SIZE_X/2 - Width/2;
			break;
		case SSD1351_HALIGN_RIGHT:
			SSD1351_CursorX = SSD1351_DISPLAY_SIZE_X - Width;
			break;
	}
	
	// Vertical align
	switch(Align & 0xF0) {
		case SSD1351_VALIGN_TOP:
			SSD1351_CursorY = 0;
			break;
		case SSD1351_VALIGN_CENTER:
			SSD1351_CursorY = SSD1351_DISPLAY_SIZE_Y/2 - Height/2;
			break;
		case SSD1351_VALIGN_BOTTOM:
			SSD1351_CursorY = SSD1351_DISPLAY_SIZE_Y - Height;
			break;
	}
	// Print text
	while(*Text) SSD1351_PrintChar(*Text++);
}




#endif
