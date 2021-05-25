#if COMPONENT_DISPLAY_SSD1681

#include	"display_ssd1681.h"

// ========================================
// Global variables
// ========================================

uint8_t SSD1681_CursorP			= 0;
uint8_t SSD1681_CursorP_Max		= SSD1681_PAGE_COUNT - 1;
uint8_t SSD1681_CursorX			= 0;
uint8_t SSD1681_CursorX_Max		= SSD1681_DISPLAY_SIZE_Y - 1;

static SSD1681_Color_t SSD1681_Color = SSD1681_ColorBlack;
//const static SSD1681_FontDef_t * SSD1681_Font = &SSD1681_DEFAULT_FONT;
// static uint8_t SSD1681_ColorFrontH		= 0xFF;		// White
// static uint8_t SSD1681_ColorFrontL		= 0xFF;
// static uint8_t SSD1681_ColorBackH		= 0x00;		// Black
// static uint8_t SSD1681_ColorBackL		= 0x00;

const uint8_t lut_full_update[] = {
	0x02, 0x02, 0x01, 0x11, 0x12, 0x12, 0x22, 0x22,
	0x66, 0x69, 0x69, 0x59, 0x58, 0x99, 0x99, 0x88,
	0x00, 0x00, 0x00, 0x00, 0xF8, 0xB4, 0x13, 0x51,
	0x35, 0x51, 0x51, 0x19, 0x01, 0x00
};

const uint8_t lut_partial_update[] = {
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
	SSD1681_DATA,		0b00000100,					// X decrement; Y decrement, pointer move in Y direction
	
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
		//Spi_1(lut_full_update[i]);
		Spi_1(lut_partial_update[i]);
	}
	
	SSD1681_CHIP_DESELECT;
	
	#if SSD1681_CLEAR_AFERT_INIT
//	SSD1681_Clear();
//	SSD1681_WriteCommand(SSD1681_SLEEP_MODE_OFF);
	#endif
}

void SSD1681_WaitForReady(void) {
	while(SSD1681_BUSY_READ) {
		asm volatile("wdr");
	}
}

// Send command
void SSD1681_WriteCommand(const uint8_t Command) {
	SSD1681_WaitForReady();
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(Command);
	SSD1681_CHIP_DESELECT;
}

// Send data
void SSD1681_WriteData(const uint8_t Data) {
	SSD1681_WaitForReady();
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(WRITE_RAM);
	SSD1681_DC_DATA;
	Spi_1(Data);
	SSD1681_CHIP_DESELECT;
}

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
	SSD1681_WaitForReady();
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(DISPLAY_UPDATE_CONTROL_2);
	SSD1681_DC_DATA;
	Spi_1(0xC4);
	SSD1681_DC_COMMAND;
	Spi_2(MASTER_ACTIVATION, TERMINATE_FRAME_READ_WRITE);
	SSD1681_CHIP_DESELECT;
}

// Clear display
void SSD1681_Clear(void) {
	SSD1681_WaitForReady();
	
	// Set active area to fill all the screen
	SSD1681_ActiveAreaSet(0, 0, SSD1681_DISPLAY_SIZE_Y-1, SSD1681_PAGE_COUNT-1);
	
	// Loop for each page
	for(uint8_t Page = 0; Page < SSD1681_PAGE_COUNT; Page++) {
		SSD1681_CursorSet(0, Page);
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
	SSD1681_WaitForReady();
	
	// Set active area to fill all the screen
	SSD1681_ActiveAreaSet(0, 0, SSD1681_DISPLAY_SIZE_Y-1, SSD1681_PAGE_COUNT-1);
	
	// Loop for each page
	for(uint8_t Page = 0; Page < SSD1681_PAGE_COUNT; Page++) {
		SSD1681_CursorSet(0, Page);
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
	SSD1681_WaitForReady();
	
	// Set active area to fill all the screen
	SSD1681_ActiveAreaSet(0, 0, SSD1681_DISPLAY_SIZE_Y-1, SSD1681_PAGE_COUNT-1);
	
	// Loop for each page
	for(uint8_t Page = 0; Page < SSD1681_PAGE_COUNT; Page++) {
		SSD1681_CursorSet(0, Page);
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

void SSD1681_CursorSet(uint8_t x, uint8_t p) {
	SSD1681_CursorPageSet(p);
	SSD1681_CursorXSet(x);
}

uint8_t SSD1681_CursorPageGet(void) {
	return SSD1681_CursorP;
}

void SSD1681_CursorPageSet(uint8_t p) {
	SSD1681_WaitForReady();
	p = p < SSD1681_PAGE_COUNT ? p : SSD1681_PAGE_COUNT-1;
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(SET_RAM_X_ADDRESS_COUNTER);
	SSD1681_DC_DATA;
	//Spi_1((SSD1681_PAGE_COUNT-1) - Page);
	Spi_1(p);
	SSD1681_CHIP_DESELECT;
	SSD1681_CursorP = p;
}

uint8_t SSD1681_CursorXGet(void) {
	return SSD1681_CursorX;
}

void SSD1681_CursorXSet(uint8_t x) {
	SSD1681_WaitForReady();
	x = x < SSD1681_DISPLAY_SIZE_Y ? x : SSD1681_DISPLAY_SIZE_Y-1;
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(SET_RAM_Y_ADDRESS_COUNTER);
	SSD1681_DC_DATA;
	//Spi_2(y, 0);
	Spi_2((SSD1681_DISPLAY_SIZE_Y-1) - x, 0);
	SSD1681_CHIP_DESELECT;
	SSD1681_CursorX = x;
}

// Set active area to write to in next operation
void SSD1681_ActiveAreaSet(uint8_t x0, uint8_t p0, uint8_t x1, uint8_t p1) {
	SSD1681_ActiveAreaPageSet(p0, p1);
	SSD1681_ActiveAreaXSet(x0, x1);
}

// Change active area only in X dimension
void SSD1681_ActiveAreaPageSet(uint8_t p0, uint8_t p1) {
	SSD1681_WaitForReady();
	
	// Sanity check
	p0 = p0 < SSD1681_PAGE_COUNT ? p0 : SSD1681_PAGE_COUNT-1;
	p1 = p1 < SSD1681_PAGE_COUNT ? p1 : SSD1681_PAGE_COUNT-1;
	
	// Set active area
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(SET_RAM_X_ADDRESS_START_END_POSITION);
	SSD1681_DC_DATA;
	Spi_2(p0, p1);
	//Spi_2((SSD1681_PAGE_COUNT-1) - p0, (SSD1681_PAGE_COUNT-1) - p1);
	SSD1681_CHIP_DESELECT;
	
	// Set cursor
	SSD1681_CursorPageSet(p0);
	SSD1681_CursorP = p0;
	SSD1681_CursorX_Max = p1;
}

// Change active area only in Y dimension
void SSD1681_ActiveAreaXSet(uint8_t x0, uint8_t x1) {
	SSD1681_WaitForReady();
	
	// Sanity check
	x0 = x0 < SSD1681_DISPLAY_SIZE_Y ? x0 : SSD1681_DISPLAY_SIZE_Y-1;
	x1 = x1 < SSD1681_DISPLAY_SIZE_Y ? x1 : SSD1681_DISPLAY_SIZE_Y-1;
	
	// Set active area
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(SET_RAM_Y_ADDRESS_START_END_POSITION);
	SSD1681_DC_DATA;
	//Spi_4(y0, 0, y1, 0);
	Spi_4((SSD1681_DISPLAY_SIZE_Y-1) - x0, 0, (SSD1681_DISPLAY_SIZE_Y-1) - x1, 0);
	SSD1681_CHIP_DESELECT;
	
	// Set cursor
	SSD1681_CursorXSet(x0);
	
	// Update globals
	SSD1681_CursorX = x0;
	SSD1681_CursorX_Max = x1;
}


// ========================================
// Colors
// ========================================

// Get foreground color
SSD1681_Color_t SSD1681_ColorGet(void) {
	return SSD1681_Color;
}

// Set background color
void SSD1681_ColorSet(SSD1681_Color_t Color) {
	SSD1681_Color = Color;
}


// ========================================
// Drawing of geometric shapes
// ========================================

// Single pixel
void SSD1681_DrawPixel(uint8_t x, uint8_t y) {
	uint8_t p = y / SSD1681_PAGE_HEIGHT;
	SSD1681_ActiveAreaSet(x, p, x, p);
	SSD1681_WaitForReady();
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(WRITE_RAM);
	SSD1681_DC_DATA;
	Spi_1(~(1 << (y % SSD1681_PAGE_HEIGHT)));
	SSD1681_CHIP_DESELECT;
}

// Horizontal line from (x0, y0) to the right
// Horizontal line, thickness is 1 pixel
// Begin at x0, y0 and draw right
void SSD1681_DrawLineHorizontal(uint8_t x0, uint8_t y0, uint8_t Length) {
	
	Print("L- ");
	Print_Dec(x0);
	Print(' ');
	Print_Dec(y0);
	Print(' ');
	Print_Dec(Length);
	
	// Calculate y0 to page number and set cursor
	uint8_t p = y0 / SSD1681_PAGE_HEIGHT;
	SSD1681_ActiveAreaSet(x0, p, x0 + Length, p);
	SSD1681_WaitForReady();
	uint8_t Pattern = ~(1 << (y0 % SSD1681_PAGE_HEIGHT));
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(WRITE_RAM);
	SSD1681_DC_DATA;
	Spi_Repeat(Pattern, Length);
	SSD1681_CHIP_DESELECT;
}

// Verical line, thickness is 1 pixel
// Begin at x0, y0 and draw bottom
void SSD1681_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length) {
	
	uint8_t PageStart			=	y0 / SSD1681_PAGE_HEIGHT;
	uint8_t PageEnd				=	(y0+Length-1) / SSD1681_PAGE_HEIGHT;
	uint8_t PagePatternStart	=	0xFF << (y0 % SSD1681_PAGE_HEIGHT);
	uint8_t PagePatternEnd		=	~(0xFF << ((y0+Length) % SSD1681_PAGE_HEIGHT));
	if(PagePatternEnd == 0) {
		PagePatternEnd = 0xFF;
	}
	Print("PageStart = ");
	Print_Dec(PageStart);
	Print("\r\nPageEnd =   ");
	Print_Dec(PageEnd);
	Print("\r\nParrterStart = ");
	Print_Bin(PagePatternStart);
	Print("\r\nParrterEnd =   ");
	Print_Bin(PagePatternEnd);
	
	if(PageStart == PageEnd) {
		// Tha line fits to single page (<= 8 pixels)
		SSD1681_CursorSet(x0, PageStart);
// 		SSD1681_CursorXSet(x0);
// 		SSD1681_CursorPageSet(PageStart);
		SSD1681_WriteData(~(PagePatternStart & PagePatternEnd));
	}
	else {
		// The line doesn;t fit in single page
		// Draw biginning of the line
		SSD1681_CursorSet(x0, PageStart);
// 		SSD1681_CursorXSet(x0);
// 		SSD1681_CursorPageSet(PageStart);
		SSD1681_WriteData(~PagePatternStart);
			
		// Draw enging of the line
		if(PagePatternEnd) {
			SSD1681_CursorSet(x0, PageEnd);
// 			SSD1681_CursorXSet(x0);
// 			SSD1681_CursorPageSet(PageEnd);
			SSD1681_WriteData(~PagePatternEnd);
		}
			
		// Draw middle part of the line, if there's need to
		while(PageEnd - PageStart >= 2) {
			SSD1681_CursorSet(x0, ++PageStart);
// 			SSD1681_CursorXSet(x0);
// 			SSD1681_CursorPageSet(++PageStart);
			SSD1681_WriteData(0x00);
		}
	}
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
	// This is very similar to SSD1681_DrawLineVertical
	uint8_t PageStart			=	y0 / SSD1681_PAGE_HEIGHT;
	uint8_t PageEnd				=	y1 / SSD1681_PAGE_HEIGHT;
	uint8_t PagePatternStart	=	0xFF << (y0 % SSD1681_PAGE_HEIGHT);
	uint8_t PagePatternEnd		=	~(0xFF << ((y1+1) % SSD1681_PAGE_HEIGHT));
	if(PagePatternEnd == 0) {
		PagePatternEnd = 0xFF;
	}
	Print("PageStart = ");
	Print_Dec(PageStart);
	Print("\r\nPageEnd =   ");
	Print_Dec(PageEnd);
	Print("\r\nParrterStart = ");
	Print_Bin(PagePatternStart);
	Print("\r\nParrterEnd =   ");
	Print_Bin(PagePatternEnd);
	
	if(PageStart == PageEnd) {
		// Tha line fits to single page (<= 8 pixels)
		SSD1681_CursorSet(x0, PageStart);
// 		SSD1681_CursorXSet(x0);
// 		SSD1681_CursorPageSet(PageStart);
		for(uint8_t i = 0; i < y1 - y0 + 1; i++) {
			SSD1681_WriteData(~(PagePatternStart & PagePatternEnd));
		}
	}
	else {
		// The line doesn't fit in single page
		// Draw biginning of the line
		SSD1681_CursorSet(x0, PageStart);
// 		SSD1681_CursorXSet(x0);
// 		SSD1681_CursorPageSet(PageStart);
		for(uint8_t i = 0; i < y1 - y0 + 1; i++) {
			SSD1681_WriteData(~PagePatternStart);
		}
		
		// Draw enging of the line
		if(PagePatternEnd) {
			SSD1681_CursorSet(x0, PageEnd);
// 			SSD1681_CursorXSet(x0);
// 			SSD1681_CursorPageSet(PageEnd);
			for(uint8_t i = 0; i < y1 - y0 + 1; i++) {
				SSD1681_WriteData(~PagePatternEnd);
			}
		}
		
		// Draw middle part of the line, if there's need to
		while(PageEnd - PageStart >= 2) {
			SSD1681_CursorSet(x0, ++PageStart);
// 			SSD1681_CursorXSet(x0);
// 			SSD1681_CursorPageSet(++PageStart);
			for(uint8_t i = 0; i < y1 - y0 + 1; i++) {
				SSD1681_WriteData(0x00);
			}
		}
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
#if 0
// ========================================
// Bitmap
// ========================================

// Draw bitmap
void SSD1681_Bitmap(const SSD1681_Bitmap_t * Bitmap) {
	uint16_t Address;
	uint8_t Page = Bitmap->Height / SSD1681_PAGE_HEIGHT - 1;
	
	uint8_t CursorX_Old = SSD1681_CursorX;
	uint8_t CursorL_Old = SSD1681_CursorP;
	
	do {
		Address = Page;
		
		SSD1681_CHIP_SELECT;
		SSD1681_DC_DATA;
		for(uint8_t i = 0; i < Bitmap->Width; i++) {
			Spi_1(SSD1681_Color ? Bitmap->Array[Address] : ~Bitmap->Array[Address]);
			Address = Address + Bitmap->Height / SSD1681_PAGE_HEIGHT;
		}
		SSD1681_CHIP_DESELECT;
		
		// If this was lat page
		if(Page == 0) {
			// It was the last page
			
			// Set curson at the begining of the bitmap
			if(Bitmap->Height / SSD1681_PAGE_HEIGHT > 1) {
				SSD1681_CursorPageSet(CursorL_Old);
			}
			
			// Set cursor at the end of the bitmap
			SSD1681_CursorX = CursorX_Old + Bitmap->Width;
			if(SSD1681_CursorX >= SSD1681_DISPLAY_SIZE_X) {
				SSD1681_CursorX = SSD1681_CursorX - SSD1681_DISPLAY_SIZE_X;
			}
		}
		else {
			// It was not the last page
			
			// Set cursor back at the beginnign of the page
			SSD1681_CursorSet(CursorX_Old, SSD1681_CursorP + 1);
			
// 			SSD1681_CursorXSet(CursorX_Old);
// 			
// 			// Move curson on page below
// 			SSD1681_CursorPageSet(SSD1681_CursorP + 1);
		}
	} while(Page--);
}

// ========================================
// Text
// ========================================

// Get actual font
const SSD1681_FontDef_t * SSD1681_FontGet(void) {
	return SSD1681_Font;
}

// Set font
void SSD1681_FontSet(const SSD1681_FontDef_t * Font) {
	SSD1681_Font = Font;
}
// Print single character
void SSD1681_PrintChar(uint8_t Char) {
	
	// Check if the character is supported by the font
	if(Char < SSD1681_Font->FirstChar) Char = SSD1681_Font->LastChar;
	if(Char > SSD1681_Font->LastChar) Char = SSD1681_Font->LastChar;
	
	// Calculate character offset, because font table doesn't have to befin with 0x00 character
	Char = Char - SSD1681_Font->FirstChar;
	
	// Find width of the character and its position is bitmap table
	uint8_t Width;
	uint8_t Height = SSD1681_Font->Height;
	uint16_t Address;
	if(SSD1681_Font->Width > 0) {
		Width = SSD1681_Font->Width;
		Address = Char * Width * Height;
	}
	else {
		Width = SSD1681_Font->Descriptors[Char].Width;
		Address = SSD1681_Font->Descriptors[Char].Offset;
	}
	
	// If Address is null and width = 0 then print last charachter from table (badchar)
	if((Address == 0) && (Width == 0)) {
		Char = SSD1681_Font->LastChar - SSD1681_Font->FirstChar;
		Address = SSD1681_Font->Descriptors[Char].Offset;
		Width = SSD1681_Font->Descriptors[Char].Width;
	}
	
	// Update cursor position
	uint8_t CursorX_Old = SSD1681_CursorX;
	uint8_t CursorL_Old = SSD1681_CursorP;
	uint16_t Address_Old = Address;
	
	// Loop iterator
	uint8_t Linia = Height - 1;
	
	// Print all bytes of all pages
	do {
		
		Address = Address + Linia;
		
		// Print part of the charater that is proper for this page
		SSD1681_CHIP_SELECT;
		SSD1681_DC_DATA;
				
		// Char
		for(uint8_t i=0; i<Width; i++) {
			Spi_1(SSD1681_Color ? SSD1681_Font->Bitmaps[Address] : ~SSD1681_Font->Bitmaps[Address]);
			Address = Address + Height;
		}
		Address = Address + Height;
				
		// Spacing
		for(uint8_t i = SSD1681_Font->Spacing; i; i--) {
			Spi_1(SSD1681_Color ? 0x00 : 0xFF);
		}
				
		SSD1681_CHIP_DESELECT;
		
		// CzyIf this was the last line
		if(Linia == 0) {
			
			if(Height > 1) {
				SSD1681_CursorPageSet(CursorL_Old);
			}
			
			SSD1681_CursorX = CursorX_Old + Width + SSD1681_Font->Spacing;
			if(SSD1681_CursorX >= SSD1681_DISPLAY_SIZE_X) {
				SSD1681_CursorX = SSD1681_CursorX - SSD1681_DISPLAY_SIZE_X;
			}
		}
		else {
			// It was not the last line
			SSD1681_CursorSet(CursorX_Old, SSD1681_CursorP + 1);
// 			SSD1681_CursorXSet(CursorX_Old);
// 			SSD1681_CursorPageSet(SSD1681_CursorP + 1);
			Address = Address_Old;
		}
	} while(Linia--);
}

// Calculate text width
uint16_t SSD1681_TextWidth(const char * Text) {
	uint16_t Width = 0;
	uint16_t Offset = SSD1681_Font->FirstChar;
	
	// Check if the font has characters with fixed width
	if(SSD1681_Font->Width) {
		
		// Count number of characters
		while(*Text++) Width++;
		
		// Spacing after every character
		Width = Width + SSD1681_Font->Spacing;
		
		// Multiply by width of single character
		Width = Width * (SSD1681_Font->Width);
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
void SSD1681_Text(const char * Text, SSD1681_align_t Align) {
	
	// Set cursor position to match text widht and align
	uint16_t Width;
	switch(Align) {
		
		case SSD1681_AlignLeft:
			SSD1681_CursorXSet(0);
			break;
		
		case SSD1681_AlignRight:
			Width = SSD1681_TextWidth(Text);
			SSD1681_CursorXSet(SSD1681_DISPLAY_SIZE_X - Width);
			break;
		
		case SSD1681_AlignCenter:
			Width = SSD1681_TextWidth(Text);
			SSD1681_CursorXSet(SSD1681_DISPLAY_SIZE_X/2 - Width/2);
			break;
		
		default:
			break;
	}
	
	// Print text
	while(*Text) SSD1681_PrintChar(*Text++);
}



#endif

void SSD1681_Bytes(uint8_t Pattern, uint16_t Times) {
	SSD1681_WaitForReady();
	SSD1681_CHIP_SELECT;
	SSD1681_DC_COMMAND;
	Spi_1(WRITE_RAM);
	SSD1681_DC_DATA;
	Spi_Repeat(Pattern, Times);
	SSD1681_CHIP_DESELECT;
}

#endif
