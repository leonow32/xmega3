#if COMPONENT_DISPLAY_SSD1681

#include	"display_ssd1681.h"

// ========================================
// Global variables
// ========================================

uint8_t SSD1681_CursorP			= 0;
uint8_t SSD1681_CursorP_Max		= SSD1681_PAGE_COUNT - 1;
uint8_t SSD1681_CursorY			= 0;
uint8_t SSD1681_CursorY_Max		= SSD1681_DISPLAY_SIZE_Y - 1;

//const static SSD1681_FontDef_t * SSD1681_Font = &SSD1681_DEFAULT_FONT;
// static uint8_t SSD1681_ColorFrontH		= 0xFF;		// White
// static uint8_t SSD1681_ColorFrontL		= 0xFF;
// static uint8_t SSD1681_ColorBackH		= 0x00;		// Black
// static uint8_t SSD1681_ColorBackL		= 0x00;

const uint8_t lut_full_update[] =
{
	0x02, 0x02, 0x01, 0x11, 0x12, 0x12, 0x22, 0x22,
	0x66, 0x69, 0x69, 0x59, 0x58, 0x99, 0x99, 0x88,
	0x00, 0x00, 0x00, 0x00, 0xF8, 0xB4, 0x13, 0x51,
	0x35, 0x51, 0x51, 0x19, 0x01, 0x00
};

const uint8_t lut_partial_update[] =
{
	0x10, 0x18, 0x18, 0x08, 0x18, 0x18, 0x08, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x13, 0x14, 0x44, 0x12,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Display config for init function



static const uint8_t SSD1681_InitSequence[] = {
	
	SSD1681_COMMAND,	DRIVER_OUTPUT_CONTROL,
	SSD1681_DATA,		(SSD1681_DISPLAY_SIZE_Y - 1) & 0xFF,
	SSD1681_DATA,		((SSD1681_DISPLAY_SIZE_Y - 1) >> 8) & 0xFF,
	SSD1681_DATA,		0x00,
	
	SSD1681_COMMAND,	BOOSTER_SOFT_START_CONTROL,
	SSD1681_DATA,		0xD7,
	SSD1681_DATA,		0xD6,
	SSD1681_DATA,		0x9D,
	
	SSD1681_COMMAND,	WRITE_VCOM_REGISTER,
	SSD1681_DATA,		0xA8,
	
	SSD1681_COMMAND,	SET_DUMMY_LINE_PERIOD,
	SSD1681_DATA,		0x1A,						// 4 dummy lines per gate
	
	SSD1681_COMMAND,	SET_GATE_TIME,
	SSD1681_DATA,		0x08,						// 2us per line
	
	SSD1681_COMMAND,	DATA_ENTRY_MODE_SETTING,
	SSD1681_DATA,		0b00000110,					// X decrement; Y increment, data increment in Y direction
	
	SSD1681_COMMAND,	WRITE_LUT_REGISTER,
};

// ========================================
// Basic functions
// ========================================

// Initialization
void SSD1681_Init(void) {
	
	SSD1681_CHIP_SELECT_INIT;
	SSD1681_CHIP_DESELECT;
	SSD1681_DC_INIT;
	SSD1681_BUSY_INIT;
	
	const uint8_t * Index = SSD1681_InitSequence;
	const uint8_t * Limit = SSD1681_InitSequence + sizeof(SSD1681_InitSequence);
	
	SSD1681_CHIP_SELECT;
	
	// Transmit array SSD1681_InitSequence
	while(Index != Limit) {
		if(*Index++) {
			SSD1681_DC_COMMAND;
		}
		else {
			SSD1681_DC_DATA;
		}
		Spi_1(*Index++);
	}
	
	// Transmit LUT array
	SSD1681_DC_DATA;
	for (uint8_t i = 0; i < SSD1681_LUT_LENGTH; i++) {
		Spi_1(lut_full_update[i]);
	}
	
	SSD1681_CHIP_DESELECT;
	
	#if SSD1681_CLEAR_AFERT_INIT
//	SSD1681_Clear();
//	SSD1681_WriteCommand(SSD1681_SLEEP_MODE_OFF);
	#endif
}

void SSD1681_WaitUntilReady(void) {
	while(SSD1681_BUSY_READ) {
		asm volatile("wdr");
	}
}

// Send command
// void SSD1681_WriteCommand(const uint8_t Command) {
// 	SSD1681_CHIP_SELECT;
// 	SSD1681_DC_COMMAND;
// 	Spi_1(Command);
// 	SSD1681_CHIP_DESELECT;
// }

// Send data
// void SSD1681_WriteData(const uint8_t Data) {
// 	SSD1681_CHIP_SELECT;
// 	SSD1681_DC_DATA;
// 	Spi_1(Data);
// 	SSD1681_CHIP_DESELECT;
// }

// Send LUT
// void SSD1681_WriteLUT(const uint8_t * LUT) {
// 	//SSD13
// 	SSD1681_WriteCommand(WRITE_LUT_REGISTER);
// 	for (uint8_t i = 0; i < SSD1681_LUT_LENGTH; i++) {
// 		SSD1681_WriteData(LUT[i]);
// 	}
// }

// Refresh display
void SSD1681_Refresh(void) {
	SSD1681_WaitUntilReady();
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(DISPLAY_UPDATE_CONTROL_2);
	SSD1681_DC_DATA;
	Spi_1(0xC4);
	SSD1681_DC_COMMAND;
	Spi_2(MASTER_ACTIVATION, TERMINATE_FRAME_READ_WRITE);
	SSD1681_CHIP_DESELECT;
// 	SSD1681_WriteCommand(DISPLAY_UPDATE_CONTROL_2);
// 	SSD1681_WriteData(0xC4);
// 	SSD1681_WriteCommand(MASTER_ACTIVATION);
// 	SSD1681_WriteCommand(TERMINATE_FRAME_READ_WRITE);
//	SSD1681_WaitUntilReady();
// 	_delay_ms(500);
// 	SSD1681_WriteCommand(DISPLAY_UPDATE_CONTROL_2);
// 	SSD1681_WriteData(0xC4);
// 	SSD1681_WriteCommand(MASTER_ACTIVATION);
// 	SSD1681_WriteCommand(TERMINATE_FRAME_READ_WRITE);
}

// Clear display
void SSD1681_Clear(void) {
	SSD1681_WaitUntilReady();
	
	// Set active area to fill all the screen
	SSD1681_ActiveAreaSet(0, 0, SSD1681_PAGE_COUNT-1, SSD1681_DISPLAY_SIZE_Y-1);
	
	// Loop for each page
	for(uint8_t Page = 0; Page < SSD1681_PAGE_COUNT; Page++) {
		SSD1681_CursorSet(Page, 0);
		SSD1681_CHIP_SELECT;
		SSD1681_DC_COMMAND;
		Spi_1(WRITE_RAM);
		SSD1681_DC_DATA;
		Spi_Repeat(0xFF, SSD1681_DISPLAY_SIZE_Y);
		SSD1681_CHIP_DESELECT;
	}
}

// Fill display
void SSD1681_Fill(void) {
	SSD1681_WaitUntilReady();
	
	// Set active area to fill all the screen
	SSD1681_ActiveAreaSet(0, 0, SSD1681_PAGE_COUNT-1, SSD1681_DISPLAY_SIZE_Y-1);
	
	// Loop for each page
	for(uint8_t Page = 0; Page < SSD1681_PAGE_COUNT; Page++) {
		SSD1681_CursorSet(Page, 0);
		SSD1681_CHIP_SELECT;
		SSD1681_DC_COMMAND;
		Spi_1(WRITE_RAM);
		SSD1681_DC_DATA;
		Spi_Repeat(0x00, SSD1681_DISPLAY_SIZE_Y);
		SSD1681_CHIP_DESELECT;
	}
}

// Print chessboard on the display
void SSD1681_Chessboard(void) {
	SSD1681_WaitUntilReady();
	
	// Set active area to fill all the screen
	SSD1681_ActiveAreaSet(0, 0, SSD1681_PAGE_COUNT-1, SSD1681_DISPLAY_SIZE_Y-1);
		
	// Loop for each page
	for(uint8_t Page = 0; Page < SSD1681_PAGE_COUNT; Page++) {
		SSD1681_CursorSet(Page, 0);
		SSD1681_CHIP_SELECT;
		SSD1681_DC_COMMAND;
		Spi_1(WRITE_RAM);
		SSD1681_DC_DATA;
		Spi_Repeat(0b10101010, 0b01010101, SSD1681_DISPLAY_SIZE_Y / 2);
		SSD1681_CHIP_DESELECT;
	}
}


// Allow to display data
// void SSD1681_WriteRamEnable(void) {
// 	SSD1681_CHIP_SELECT;
// 	SSD1681_DC_COMMAND;
// 	Spi_1(SSD1681_RAM_WRITE);
// 	SSD1681_CHIP_DESELECT;
// }


// ========================================
// Cursor position
// ========================================

void SSD1681_CursorSet(uint8_t p, uint8_t y) {
	SSD1681_CursorP = p < SSD1681_PAGE_COUNT ? p : SSD1681_PAGE_COUNT-1;
	SSD1681_CursorY = y < SSD1681_DISPLAY_SIZE_Y ? y : SSD1681_DISPLAY_SIZE_Y-1;
	SSD1681_CursorPageSet(SSD1681_CursorP);
	SSD1681_CursorYSet(SSD1681_CursorY);
}

uint8_t SSD1681_CursorPageGet(void) {
	return SSD1681_CursorP;
}

void SSD1681_CursorPageSet(uint8_t Page) {
	SSD1681_WaitUntilReady();
	SSD1681_CursorP = Page < SSD1681_PAGE_COUNT ? Page : SSD1681_PAGE_COUNT-1;
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(SET_RAM_X_ADDRESS_COUNTER);
	SSD1681_DC_DATA;
	Spi_1((SSD1681_PAGE_COUNT-1) - SSD1681_CursorP);
	SSD1681_CHIP_DESELECT;
}

uint8_t SSD1681_CursorYGet(void) {
	return SSD1681_CursorY;
}

void SSD1681_CursorYSet(uint8_t y) {
	SSD1681_WaitUntilReady();
	SSD1681_CursorY = y < SSD1681_DISPLAY_SIZE_Y ? y : SSD1681_DISPLAY_SIZE_Y-1;
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(SET_RAM_Y_ADDRESS_COUNTER);
	SSD1681_DC_DATA;
	Spi_2(SSD1681_CursorY, 0);
	SSD1681_CHIP_DESELECT;
}

// Set active area to write to in next operation
void SSD1681_ActiveAreaSet(uint8_t p0, uint8_t y0, uint8_t p1, uint8_t y1) {
	SSD1681_ActiveAreaPageSet(p0, p1);
	SSD1681_ActiveAreaYSet(y0, y1);
}

// Change active area only in X dimension
void SSD1681_ActiveAreaPageSet(uint8_t p0, uint8_t p1) {
	SSD1681_WaitUntilReady();
	
	// Sanity check
	SSD1681_CursorP			= p0 < SSD1681_PAGE_COUNT ? p0 : SSD1681_PAGE_COUNT-1;
	SSD1681_CursorP_Max		= p1 < SSD1681_PAGE_COUNT ? p1 : SSD1681_PAGE_COUNT-1;
	
	// Send to display
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(SET_RAM_X_ADDRESS_START_END_POSITION);
	SSD1681_DC_DATA;
	Spi_2(SSD1681_CursorP, SSD1681_CursorP_Max);
	SSD1681_CHIP_DESELECT;
}

// Change active area only in Y dimension
void SSD1681_ActiveAreaYSet(uint8_t y0, uint8_t y1) {
	SSD1681_WaitUntilReady();
	
	// Sanity check
	SSD1681_CursorY			= y0 < SSD1681_DISPLAY_SIZE_Y ? y0 : SSD1681_DISPLAY_SIZE_Y-1;
	SSD1681_CursorY_Max		= y1 < SSD1681_DISPLAY_SIZE_Y ? y1 : SSD1681_DISPLAY_SIZE_Y-1;
	
	// Send to display
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(SET_RAM_Y_ADDRESS_START_END_POSITION);
	SSD1681_DC_DATA;
	Spi_4(SSD1681_CursorY, 0, SSD1681_CursorY_Max, 0);
	SSD1681_CHIP_DESELECT;
}

#if 0
// ========================================
// Colors
// ========================================

// Get foreground color
uint16_t SSD1681_ColorFrontGet(void) {
	return (uint16_t)SSD1681_ColorFrontH << 8 | SSD1681_ColorFrontL;
}

// Set background color
void SSD1681_ColorFrontSet(uint16_t ColorRGB565) {
	SSD1681_ColorFrontH = (uint8_t)(ColorRGB565 >> 8);
	SSD1681_ColorFrontL = (uint8_t)(ColorRGB565 & 0x00FF);
}

// Set foreground color, each color speparate
void SSD1681_ColorFrontSet(uint8_t R, uint8_t G, uint8_t B) {
	
	// Convert RGB888 to RGB565
	R = R & 0b11111000;
	G = G & 0b11111100;
	B = B & 0b11111000;
	SSD1681_ColorFrontH = R | (G >> 5);
	SSD1681_ColorFrontL = (G << 3) | (B >> 3);
}

// Get foreground color as RGB565
uint16_t SSD1681_ColorBackGet(void) {
	return (uint16_t)SSD1681_ColorBackH << 8 | SSD1681_ColorBackL;
}

// Set background color
void SSD1681_ColorBackSet(uint16_t ColorRGB565) {
	SSD1681_ColorBackH = (uint8_t)(ColorRGB565 >> 8);
	SSD1681_ColorBackL = (uint8_t)(ColorRGB565 & 0x00FF);
}

// Set background color, each color speparate
void SSD1681_ColorBackSet(uint8_t R, uint8_t G, uint8_t B) {
	
	// Convert RGB888 to RGB565
	R = R & 0b11111000;
	G = G & 0b11111100;
	B = B & 0b11111000;
	SSD1681_ColorBackH = R | (G >> 5);
	SSD1681_ColorBackL = (G << 3) | (B >> 3);
}

// Convert color name to RGB565
uint16_t SSD1681_ColorNameToRGB565(uint8_t ColorName) {
	switch(ColorName) {
		case SSD1681_COLOR_BLACK_ID:			return SSD1681_COLOR_BLACK_RGB565;
		case SSD1681_COLOR_RED_ID:				return SSD1681_COLOR_RED_RGB565;
		case SSD1681_COLOR_GREEN_ID:			return SSD1681_COLOR_GREEN_RGB565;
		case SSD1681_COLOR_YELLOW_ID:			return SSD1681_COLOR_YELLOW_RGB565;
		case SSD1681_COLOR_BLUE_ID:				return SSD1681_COLOR_BLUE_RGB565;
		case SSD1681_COLOR_MAGENTA_ID:			return SSD1681_COLOR_MAGENTA_RGB565;
		case SSD1681_COLOR_CYAN_ID:				return SSD1681_COLOR_CYAN_RGB565;
		case SSD1681_COLOR_WHITE_ID:			return SSD1681_COLOR_WHITE_RGB565;
		case SSD1681_COLOR_GRAY_ID:				return SSD1681_COLOR_GRAY_RGB565;
		case SSD1681_COLOR_LIGHTRED_ID:			return SSD1681_COLOR_LIGHTRED_RGB565;
		case SSD1681_COLOR_LIGHTGREEN_ID:		return SSD1681_COLOR_LIGHTGREEN_RGB565;
		case SSD1681_COLOR_LIGHTYELLOW_ID:		return SSD1681_COLOR_LIGHTYELLOW_RGB565;
		case SSD1681_COLOR_LIGHTBLUE_ID:		return SSD1681_COLOR_LIGHTBLUE_RGB565;
		case SSD1681_COLOR_LIGHTMAGENTA_ID:		return SSD1681_COLOR_LIGHTMAGENTA_RGB565;
		case SSD1681_COLOR_LIGHTCYAN_ID:		return SSD1681_COLOR_LIGHTCYAN_RGB565;
		case SSD1681_COLOR_LIGHTGRAY_ID:		return SSD1681_COLOR_LIGHTGRAY_RGB565;
		default:								return 0;
	}
}

// Convert RGB888 na RGB565
uint16_t SSD1681_ColorRGB888toRGB565(uint8_t R, uint8_t G, uint8_t B) {
	
	R = R & 0b11111000;
	G = G & 0b11111100;
	B = B & 0b11111000;
	uint8_t ColorH = R | (G >> 5);
	uint8_t ColorL = (G << 3) | (B >> 3);
	
	return ((uint16_t)ColorH << 8) | ColorL;
}

// Convert RGB323 na RGB565
uint16_t SSD1681_ColorRGB332toRGB565(uint8_t Color332) {
	
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
void SSD1681_DrawPixel(uint8_t x, uint8_t y) {
	SSD1681_ActiveAreaSet(x, x, y, y);
	SSD1681_CHIP_SELECT;
	Spi_2(SSD1681_ColorFrontH, SSD1681_ColorFrontL);
	SSD1681_CHIP_DESELECT;
}

// Horizontal line from (x0, y0) to the right
void SSD1681_DrawLineHorizontal(uint8_t x0, uint8_t y0, uint8_t Length) {
	SSD1681_ActiveAreaSet(x0, x0 + Length - 1, y0, y0);
	SSD1681_CHIP_SELECT;
	Spi_Repeat(SSD1681_ColorFrontH, SSD1681_ColorFrontL, Length);
	SSD1681_CHIP_DESELECT;
}

// Vertical line from (x0, y0) to the bottom
void SSD1681_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length) {
	SSD1681_ActiveAreaSet(x0, x0, y0, y0 + Length - 1);
	SSD1681_CHIP_SELECT;
	Spi_Repeat(SSD1681_ColorFrontH, SSD1681_ColorFrontL, Length);
	SSD1681_CHIP_DESELECT;
}

// Draw line with Bresenham's algorithm
void SSD1681_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	
	if(x0 == x1) {
		if(y0 > y1) {
			uint8_t temp = y0;
			y0 = y1;
			y1 = temp;
		}
		SSD1681_DrawLineVertical(x0, y0, y1-y0+1);
		return;
	}
	
	if(y0 == y1) {
		if(x0 > x1) {
			uint8_t temp = x0;
			x0 = x1;
			x1 = temp;
		}
		SSD1681_DrawLineHorizontal(x0, y0, x1-x0+1);
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
		SSD1681_DrawPixel(x0, y0);
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
void SSD1681_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	SSD1681_DrawLineVertical(x0, y0, y1-y0+1);
	SSD1681_DrawLineVertical(x1, y0, y1-y0+1);
	SSD1681_DrawLineHorizontal(x0+1, y0, x1-x0-1);
	SSD1681_DrawLineHorizontal(x0+1, y1, x1-x0-1);
}

// Rectangle with fill
void SSD1681_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	for(uint8_t y=y0; y<=y1; y++) {
		SSD1681_DrawLineHorizontal(x0, y, y1-y0+1);
	}
}

// Circle
void SSD1681_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r) {
	
	int16_t d = 5 - 4*r;
	int16_t x = 0;
	int16_t y = r;
	int16_t deltaA = (-2*r + 5) * 4;
	int16_t deltaB = 3*4;
	
	while (x <= y) {
		SSD1681_DrawPixel(x0-x, y0-y);
		SSD1681_DrawPixel(x0-x, y0+y);
		SSD1681_DrawPixel(x0+x, y0-y);
		SSD1681_DrawPixel(x0+x, y0+y);
		SSD1681_DrawPixel(x0-y, y0-x);
		SSD1681_DrawPixel(x0-y, y0+x);
		SSD1681_DrawPixel(x0+y, y0-x);
		SSD1681_DrawPixel(x0+y, y0+x);
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

void SSD1681_Bitmap(const SSD1681_Bitmap_t * Bitmap) {
	switch(Bitmap->ColorDepth) {
		case SSD1681_ColorMono:		SSD1681_BitmapMono(Bitmap);		break;
		case SSD1681_ColorRGB332:	SSD1681_BitmapRGB332(Bitmap);	break;
		case SSD1681_ColorRGB565:	SSD1681_BitmapRGB565(Bitmap);	break;
	}
}

// Draw a monochrome bitmap
// Foreground color, background color, XY coordinates set before calling SSD1681_BitmapMono()
void SSD1681_BitmapMono(const SSD1681_Bitmap_t * Bitmap) {
	
	// Get size fo bitmap
	uint8_t WidthPixels = Bitmap->Width;
	uint8_t HeightPixels = Bitmap->Height;
	
	// Set active area to draw in
	SSD1681_ActiveAreaSet(SSD1681_CursorX, SSD1681_CursorX + WidthPixels - 1, SSD1681_CursorY, SSD1681_CursorY + HeightPixels - 1);
	
	// Column loop
	uint8_t Buffer = 0;
	uint16_t Address = 0;
	SSD1681_CHIP_SELECT;
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
				Spi_2(SSD1681_ColorFrontH, SSD1681_ColorFrontL);
			}
			else {
				// Background color
				Spi_2(SSD1681_ColorBackH, SSD1681_ColorBackL);
			}
			
			// Move bitmask
			BitMask = BitMask >> 1;
		}
	}
	SSD1681_CHIP_DESELECT;
}

// Draw a bitmap saved in format RGB565
// Set XY coordinates set before calling
void SSD1681_BitmapRGB565(const SSD1681_Bitmap_t * Bitmap) {
	
	// Get size fo bitmap
	uint8_t WidthPixels = Bitmap->Width;
	uint8_t HeightPixels = Bitmap->Height;
	
	// Set active area to draw into
	SSD1681_ActiveAreaSet(SSD1681_CursorX, SSD1681_CursorX + WidthPixels - 1, SSD1681_CursorY, SSD1681_CursorY + HeightPixels - 1);
	
	// Stream all pixels
	SSD1681_CHIP_SELECT;
	Spi_Write(Bitmap->Bitmaps, WidthPixels * HeightPixels * 2);
	SSD1681_CHIP_DESELECT;
}

// Draw a bitmap saved in format RGB5332
// Set XY coordinates set before calling
void SSD1681_BitmapRGB332(const SSD1681_Bitmap_t * Bitmap) {
	
	// Get size fo bitmap
	uint8_t WidthPixels = Bitmap->Width;
	uint8_t HeightPixels = Bitmap->Height;
	uint16_t Size = WidthPixels * HeightPixels;
	uint16_t Color565;
	const uint8_t * BitmapPointer = Bitmap->Bitmaps;
	
	// Set active area to draw in
	SSD1681_ActiveAreaSet(SSD1681_CursorX, SSD1681_CursorX + WidthPixels - 1, SSD1681_CursorY, SSD1681_CursorY + HeightPixels - 1);
	
	// Transmit all pixels
	SSD1681_CHIP_SELECT;
	while(Size--) {
		Color565 = SSD1681_ColorRGB332toRGB565(*BitmapPointer++);
		Spi_2(Color565 >> 8, Color565 & 0xFF);
	}
	SSD1681_CHIP_DESELECT;
}

// ========================================
// Fonts
// ========================================

// Get actual font
const SSD1681_FontDef_t * SSD1681_FontGet(void) {
	return SSD1681_Font;
}

// Set actual font
void SSD1681_FontSet(const SSD1681_FontDef_t * Font) {
	SSD1681_Font = Font;
}

// Print single character
void SSD1681_PrintChar(uint8_t Char) {
	
	// Check if character is supported by font
	if(Char < SSD1681_Font->FirstChar) Char = SSD1681_Font->LastChar;
	if(Char > SSD1681_Font->LastChar) Char = SSD1681_Font->LastChar;
	
	// Calculate character offset, because font table doesn't have to befin with 0x00 character
	Char = Char - SSD1681_Font->FirstChar;
	
	// Find width of the character and its position is bitmap table
	uint8_t Width;
	uint8_t Height = SSD1681_Font->Height;
	uint8_t Spacing = SSD1681_Font->Spacing;
	uint16_t Address;
	if(SSD1681_Font->Width > 0) {
		// For font with fixed width of all characters
		Width = SSD1681_Font->Width;
		Address = Char * Width * (Height/8);
	}
	else {
		// For font with characters with variable width
		Width = SSD1681_Font->Descriptors[Char].Width;
		Address = SSD1681_Font->Descriptors[Char].Offset;
	}
	
	// If Address is null and width = 0 then print last charachter from table (badchar)
	if((Address == 0) && (Width == 0)) {
		Char = SSD1681_Font->LastChar - SSD1681_Font->FirstChar;
		Address = SSD1681_Font->Descriptors[Char].Offset;
		Width = SSD1681_Font->Descriptors[Char].Width;
	}
	
	// Set active area to write into
	SSD1681_ActiveAreaSet(SSD1681_CursorX, SSD1681_CursorX + Width + Spacing - 1, SSD1681_CursorY, SSD1681_CursorY + Height - 1);
	
	// Stream all pixels
	uint8_t Buffer = 0;
	SSD1681_CHIP_SELECT;
	
	// Column loop
	for(uint8_t ActualColumn = 0; ActualColumn < Width; ActualColumn++) {
		
		uint8_t ActualRow = Height;
		uint8_t BitMask = 0;
		
		// Row loop
		while(ActualRow--) {
			if(BitMask == 0) {
				BitMask = 0b10000000;
				Buffer = SSD1681_Font->Bitmaps[Address++];
			}
			
			if(Buffer & BitMask) {
				// Transmit foreground color
				Spi_2(SSD1681_ColorFrontH, SSD1681_ColorFrontL);
			}
			else {
				// Transmit background color
				Spi_2(SSD1681_ColorBackH, SSD1681_ColorBackL);
			}
			
			BitMask = BitMask >> 1;
		}
	}
	
	// Spacing
	for(uint8_t Column = 0; Column < Spacing; Column++) {
		for(uint8_t i=0; i<Height; i++) {
			Spi_2(SSD1681_ColorBackH, SSD1681_ColorBackL);
		}
	}
	
	// End of transmission
	SSD1681_CHIP_DESELECT;
	
	// Move cursor at the end of character
	SSD1681_CursorX = SSD1681_CursorX + Width + Spacing;
	if(SSD1681_CursorX > SSD1681_DISPLAY_SIZE_X) {
		SSD1681_CursorX = SSD1681_CursorX - SSD1681_DISPLAY_SIZE_X;
	}
}

// Calculate text width
uint8_t SSD1681_TextWidthGet(const char * Text) {
	uint8_t Width = 0;
	uint16_t Offset = SSD1681_Font->FirstChar;
	
	// Check if the font has characters with fixed width
	if(SSD1681_Font->Width) {
		
		// Count number of characters
		while(*Text++) Width++;
		
		// Multiply by width of single character
		Width = Width * (SSD1681_Font->Width + SSD1681_Font->Spacing);
	}
	else {
		// Font with variable character width
		while(*Text) {
			Width += SSD1681_Font->Descriptors[(*Text) - Offset].Width + SSD1681_Font->Spacing;
			Text++;
		}
	}
	
	return Width;
}

// Print text. Remember to set font first!
void SSD1681_Text(const char * Text, uint8_t Align) {
	
	// Set cursor position to match text widht and align
	uint8_t Width = SSD1681_TextWidthGet(Text);
	uint8_t Height = SSD1681_Font->Height;
	
	// Horizontal align
	switch(Align & 0x0F) {
		case SSD1681_HALIGN_LEFT:
		SSD1681_CursorX = 0;
		break;
		case SSD1681_HALIGN_CENTER:
		SSD1681_CursorX = SSD1681_DISPLAY_SIZE_X/2 - Width/2;
		break;
		case SSD1681_HALIGN_RIGHT:
		SSD1681_CursorX = SSD1681_DISPLAY_SIZE_X - Width;
		break;
	}
	
	// Vertical align
	switch(Align & 0xF0) {
		case SSD1681_VALIGN_TOP:
		SSD1681_CursorY = 0;
		break;
		case SSD1681_VALIGN_CENTER:
		SSD1681_CursorY = SSD1681_DISPLAY_SIZE_Y/2 - Height/2;
		break;
		case SSD1681_VALIGN_BOTTOM:
		SSD1681_CursorY = SSD1681_DISPLAY_SIZE_Y - Height;
		break;
	}
	// Print text
	while(*Text) SSD1681_PrintChar(*Text++);
}


#endif

void SSD1681_Bytes(uint8_t Pattern, uint16_t Times) {
	SSD1681_WaitUntilReady();
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(WRITE_RAM);
	SSD1681_DC_DATA;
	Spi_Repeat(Pattern, Times);
	SSD1681_CHIP_DESELECT;
}

#endif
