#if COMPONENT_DISPLAY_SH1106

#include	"display_sh1106.h"

// ========================================
// Global variables
// ========================================

static uint8_t SH1106_CursorP = 0;
static uint8_t SH1106_CursorX = 0;
static uint8_t SH1106_Color	= 1;		// White
static const SH1106_FontDef_t * SH1106_Font = &SH1106_DEFAULT_FONT;

// Display config for init function
static const uint8_t SH1106_InitSequence[] = {
	SH1106_DISPLAY_OFF,						// Display OFF
	SH1106_COLUMN_LOW(SH1106_OFFSET_X),		// Low Column - select x = 0
	SH1106_COLUMN_HIGH(0),					// High Column - select x = 0
	SH1106_PAGE(0),							// First page select
	SH1106_START_LINE(0),					// Start line
	SH1106_REMAP(1),						// Remap
	SH1106_COMMON_PADS_HW_CONFIG,			// Com pins
	0x12,
	SH1106_DISPLAY_OFFSET,					// Display offset
	0x00,									// No offset
	SH1106_SCAN_DIRECTION(0),				// Scan direction
	0xC8,
	SH1106_NORMAL_REVERSE(0),				// Normal display
	SH1106_ENTRIE_DISPLAY_ON(0),			// Display ON
	SH1106_CONTRAST,						// Set contrast
	SH1106_DEFAULT_CONTRAST,				// Contrast DATA
	SH1106_MULTIPLEX_RATIO,					// Multiplex ratio
	0x3F,									// 1/64 duty
	SH1106_CLOCK_DIV_FREQ,					// Display clock divide
	0x80,
	SH1106_CHARGE_PERIOD,					// Precharge period
	0xF1,
	SH1106_VCOM_DESELECT_LEVEL,				// VCOM deselect
	0x40,
	SH1106_CHARGE_PUMP,						// Charge pump 0x8d
	0x14,
	#if SH1106_CLEAR_AFERT_INIT == 0
		SH1106_DISPLAY_ON,					// Display ON
	#endif
};

// Initialization
void SH1106_Init(void) {
	
	#if SH1106_USE_I2C
		for(uint8_t i=0; i<sizeof(SH1106_InitSequence); i++) {
			SH1106_WriteCommand(SH1106_InitSequence[i]);
		}
		
		#if SH1106_CLEAR_AFERT_INIT
			SH1106_Clear();
			SH1106_WriteCommand(SH1106_DISPLAY_ON);
		#endif
	#endif
	
	#if SH1106_USE_SPI
		SH1106_CHIP_SELECT_INIT;
		SH1106_DC_INIT;
		
		SH1106_CHIP_SELECT;
		SH1106_DC_COMMAND;
		Spi_Write(SH1106_InitSequence, sizeof(SH1106_InitSequence));
		SH1106_CHIP_DESELECT;
		
		#if SH1106_CLEAR_AFERT_INIT
			SH1106_Clear();
			SH1106_WriteCommand(SH1106_DISPLAY_ON);
		#endif
	#endif
}

// Send command to the display
void SH1106_WriteCommand(const uint8_t Command) {
	
	#if SH1106_USE_I2C
		I2C_Start(SH1106_ADDRESS_WRITE);
		I2C_Write(SH1106_COMMAND_BYTE);
		I2C_Write(Command);
		I2C_Stop();
	#endif
	
	#if SH1106_USE_SPI
		SH1106_CHIP_SELECT;
		SH1106_DC_COMMAND;
		Spi_1(Command);
		SH1106_CHIP_DESELECT;
	#endif
}

// Send data to the display
void SH1106_WriteData(const uint8_t Data) {
	
	#if SH1106_USE_I2C
		I2C_Start(SH1106_ADDRESS_WRITE);
		I2C_Write(SH1106_DATA_BYTE);
		I2C_Write(Data);
		I2C_Stop();
	#endif
	
	#if SH1106_USE_SPI
		SH1106_CHIP_SELECT;
		SH1106_DC_DATA;
		Spi_1(Data);
		SH1106_CHIP_DESELECT;
	#endif
}

// Set contrast
void SH1106_ContrastSet(const uint8_t Value) {
	SH1106_WriteCommand(SH1106_CONTRAST);
	SH1106_WriteCommand(Value);
}

// Clear display - set Pattern = 0 to clear
void SH1106_Clear(const uint8_t Pattern) {
	for(uint8_t Page=0; Page<8; Page++) {
		SH1106_CursorPageSet(Page);
		SH1106_CursorXSet(0);
		
		#if SH1106_USE_I2C
			I2C_Start(SH1106_ADDRESS_WRITE);
			I2C_Write(SH1106_DATA_BYTE);
			for(uint8_t i = 0; i < SH1106_DISPLAY_SIZE_X; i++) {
				I2C_Write(Pattern);
			}
			I2C_Stop();
		#endif
		
		#if SH1106_USE_SPI
			SH1106_CHIP_SELECT;
			SH1106_DC_DATA;
			Spi_Repeat(Pattern, SH1106_DISPLAY_SIZE_X);
			SH1106_CHIP_DESELECT;
		#endif
	}
	
	SH1106_CursorXSet(0);
	SH1106_CursorPageSet(0);
}

// Light all pixels
void SH1106_Fill(void) {
	SH1106_Clear(0xFF);
}

// Draw chessboard
void SH1106_Chessboard(void) {
	
	// Loop 8 pages
	for(uint8_t Page = 0; Page < SH1106_PAGE_COUNT; Page++) {
		SH1106_CursorPageSet(Page);
		SH1106_CursorXSet(0);
		
		// Loop 128 columns
		#if SH1106_USE_I2C
			I2C_Start(SH1106_ADDRESS_WRITE);
			I2C_Write(SH1106_DATA_BYTE);
			for(uint8_t Column = 0; Column < SH1106_DISPLAY_SIZE_X / 2; Column++) {
				I2C_Write(0b10101010);
				I2C_Write(0b01010101);
			}
			I2C_Stop();
		#endif
		
		#if SH1106_USE_SPI
			SH1106_CHIP_SELECT;
			SH1106_DC_DATA;
			for(uint8_t Column = 0; Column < SH1106_DISPLAY_SIZE_X / 2; Column++) {
				Spi_2(0b10101010, 0b01010101);
			}
			SH1106_CHIP_DESELECT;
		#endif
	}
}

// ========================================
// Cursor setting
// ========================================

// Odczytanie pozycji X
uint8_t SH1106_CursorXGet(void) {
	return SH1106_CursorX;
}

// Ustawienie pozycji X
void SH1106_CursorXSet(uint8_t PosX) {
	
	// Sanity check
	SH1106_CursorX = PosX < SH1106_DISPLAY_SIZE_X ? PosX : 0;
	
	// Set in accordande to display x offset
	#if SH1106_USE_I2C
		I2C_Start(SH1106_ADDRESS_WRITE);
		I2C_Write(SH1106_COMMAND_BYTE);
		I2C_Write(SH1106_COLUMN_LOW((SH1106_CursorX + SH1106_OFFSET_X) & 0x0F));
		I2C_Write(SH1106_COMMAND_BYTE);
		I2C_Write(SH1106_COLUMN_HIGH(((SH1106_CursorX + SH1106_OFFSET_X) & 0xF0) >> 4));
		I2C_Stop();
	#endif
	
	#if SH1106_USE_SPI
		SH1106_CHIP_SELECT;
		SH1106_DC_COMMAND;
		Spi_2(SH1106_COLUMN_LOW((SH1106_CursorX + SH1106_OFFSET_X) & 0x0F), SH1106_COLUMN_HIGH(((SH1106_CursorX + SH1106_OFFSET_X) & 0xF0) >> 4));
		SH1106_CHIP_DESELECT;
	#endif
}

// Get actual selected page
uint8_t SH1106_CursorPageGet(void) {
	return SH1106_CursorP;
}

// Set page to write to
void SH1106_CursorPageSet(uint8_t Page) {
	SH1106_CursorP = Page;
	SH1106_WriteCommand(SH1106_PAGE(SH1106_CursorP));
}

// ========================================
// Read-Modify-Write Mode
// ========================================

// This is supported only in I2C mode and not for all displays! We've got some SH1106 displays that don't support this feature!

#if SH1106_USE_RMW
void SH1106_RmwStart(void) {
	I2C_Start(SH1106_ADDRESS_WRITE);
	I2C_Write(SH1106_COMMAND_BYTE);
	I2C_Write(SH1106_READ_MODIFY_WRITE);
	I2C_Write(SH1106_CoDATA_BYTE);
	I2C_Stop();
}

void SH1106_RmwExecute(uint8_t Byte) {
	uint8_t Buffer;
	
	I2C_Start(SH1106_ADDRESS_READ);
	I2C_Read();		// Dummy read
	Buffer = I2C_Read();
	I2C_Stop();
	
	if(SH1106_Color) {
		Buffer |= Byte;
	}
	else {
		Buffer &= ~Byte;
	}
		SH1106_WriteData(Buffer);
	
	SH1106_CursorX = (SH1106_CursorX == (SH1106_DISPLAY_SIZE_X-1) ? 0 : SH1106_CursorX + 1);
}

void SH1106_RmwEnd() {
	SH1106_WriteCommand(SH1106_END);
	SH1106_CursorXSet(SH1106_CursorX);
}
#endif

// ========================================
// Colors (black & white)
// ========================================

// 0 - black
// 1 - white

void SH1106_ColorSet(uint8_t Color) {
	SH1106_Color = Color;
}

uint8_t SH1106_ColorGet(void) {
	return SH1106_Color;
}

// ========================================
// Drawing
// ========================================

// Single pixel
void SH1106_DrawPixel(uint8_t x, uint8_t y) {
	uint8_t Page = y / SH1106_PAGE_HEIGHT;
	SH1106_CursorPageSet(Page);
	SH1106_CursorXSet(x);
	
	#if SH1106_USE_RMW
		SH1106_RmwStart();
		SH1106_RmwExecute(1 << (y % SH1106_PAGE_HEIGHT));
		SH1106_RmwEnd();
	#else
		SH1106_WriteData(SH1106_Color << (y % SH1106_PAGE_HEIGHT));
	#endif
}

// Horizontal line, thickness is 1 pixel
// Begin at x0, y0 and draw right
void SH1106_DrawLineHorizontal(uint8_t x0, uint8_t y0, uint8_t Length) {
	
	// Calculate y0 to page number and set cursor
	uint8_t Page = y0 / SH1106_PAGE_HEIGHT;
	SH1106_CursorPageSet(Page);
	SH1106_CursorXSet(x0);
	
	#if SH1106_USE_I2C
		#if SH1106_USE_RMW
			uint8_t Pattern = (1 << (y0 % SH1106_PAGE_HEIGHT));
			SH1106_RmwStart();
			while(Length--) {
				SH1106_RmwExecute(Pattern);
			}
			SH1106_RmwEnd();
		#else
			uint8_t Pattern = (SH1106_Color << (y0 % SH1106_PAGE_HEIGHT));
			I2C_Start(SH1106_ADDRESS_WRITE);
			I2C_Write(SH1106_DATA_BYTE);
			while(Length--) {
				I2C_Write(Pattern);
			}
			I2C_Stop();
		#endif
	#endif
	
	#if SH1106_USE_SPI
		uint8_t Pattern = (SH1106_Color << (y0 % SH1106_PAGE_HEIGHT));
		SH1106_CHIP_SELECT;
		SH1106_DC_DATA;
		Spi_Repeat(Pattern, Length);
		SH1106_CHIP_DESELECT;
	#endif
}

// Verical line, thickness is 1 pixel
// Begin at x0, y0 and draw bottom
void SH1106_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length) {
	
	#if SH1106_USE_RMW
		while(Length--) {
			SH1106_DrawPixel(x0, y0++);
		}
	#else
		uint8_t PageStart			=	y0 / SH1106_PAGE_HEIGHT;
		uint8_t PageEnd				=	(y0+Length) / SH1106_PAGE_HEIGHT;
		uint8_t PagePatternStart	=	0xFF << (y0 % SH1106_PAGE_HEIGHT);
		uint8_t PagePatternEnd		=	~(0xFF << ((y0+Length) % SH1106_PAGE_HEIGHT));
		
		if(PageStart == PageEnd) {
			// Tha line fits to single page (<= 8 pixels)
			SH1106_CursorXSet(x0);
			SH1106_CursorPageSet(PageStart);
			SH1106_WriteData(SH1106_Color ? PagePatternStart & PagePatternEnd : 0);
		}
		else {
			// The line doesn;t fit in single page
			// Draw biginning of the line
			SH1106_CursorXSet(x0);
			SH1106_CursorPageSet(PageStart);
			SH1106_WriteData(SH1106_Color ? PagePatternStart : 0);
			
			// Draw enging of the line
			if(PagePatternEnd) {
				SH1106_CursorXSet(x0);
				SH1106_CursorPageSet(PageEnd);
				SH1106_WriteData(SH1106_Color ? PagePatternEnd : 0);
			}
			
			// Draw middle part of the line, if there's need to
			while(PageEnd - PageStart >= 2) {
				SH1106_CursorXSet(x0);
				SH1106_CursorPageSet(++PageStart);
				SH1106_WriteData(SH1106_Color ? 0xFF : 0);
			}
		}
	#endif
}

// Draw line at any angle with Bresenham's algorithm
void SH1106_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	
	if(x0 == x1) {
		if(y0 > y1) {
			uint8_t temp = y0;
			y0 = y1;
			y1 = temp;
		}
		SH1106_DrawLineVertical(x0, y0, y1-y0+1);
		return;
	}
	
	if(y0 == y1) {
		if(x0 > x1) {
			uint8_t temp = x0;
			x0 = x1;
			x1 = temp;
		}
		SH1106_DrawLineHorizontal(x0, y0, x1-x0+1);
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
		SH1106_DrawPixel(x0, y0);
		if ((x0 == x1) && (y0 == y1)) return;
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
void SH1106_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	SH1106_DrawLineVertical(x0, y0, y1-y0+1);
	SH1106_DrawLineVertical(x1, y0, y1-y0+1);
	SH1106_DrawLineHorizontal(x0+1, y0, x1-x0-1);
	SH1106_DrawLineHorizontal(x0+1, y1, x1-x0-1);
}

// Rectangle with fill
void SH1106_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	// This is very similar to SH1106_DrawLineVertical
	uint8_t PageStart			=	y0 / SH1106_PAGE_HEIGHT;
	uint8_t PageEnd				=	(y1+1) / SH1106_PAGE_HEIGHT;
	uint8_t PagePatternStart	=	0xFF << (y0 % SH1106_PAGE_HEIGHT);
	uint8_t PagePatternEnd		=	~(0xFF << ((y1+1) % SH1106_PAGE_HEIGHT));
	
	if(PageStart == PageEnd) {
		SH1106_CursorXSet(x0);
		SH1106_CursorPageSet(PageStart);
		
		#if SH1106_USE_I2C
			#if SH1106_USE_RMW
				SH1106_RmwStart();
				for(uint8_t i=x0; i<=x1; i++) {
					SH1106_RmwExecute(PagePatternStart & PagePatternEnd);
				}
				SH1106_RmwEnd();
			#else
				I2C_Start(SH1106_ADDRESS_WRITE);
				I2C_Write(SH1106_DATA_BYTE);
				for(uint8_t i=x0; i<=x1; i++) {
					I2C_Write(PagePatternStart & PagePatternEnd);
				}
				I2C_Stop();
			#endif
		#endif
		
		#if SH1106_USE_SPI
			SH1106_CHIP_SELECT;
			SH1106_DC_DATA;
			Spi_Repeat(PagePatternStart & PagePatternEnd, x1-x0+1);
			SH1106_CHIP_DESELECT;
		#endif
	}
	else {
		SH1106_CursorXSet(x0);
		SH1106_CursorPageSet(PageStart);
		
		#if SH1106_USE_I2C
			#if SH1106_USE_RMW
				SH1106_RmwStart();
				for(uint8_t i=x0; i<=x1; i++) {
					SH1106_RmwExecute(PagePatternStart);
				}
				SH1106_RmwEnd();
			#else
				I2C_Start(SH1106_ADDRESS_WRITE);
				I2C_Write(SH1106_DATA_BYTE);
				for(uint8_t i=x0; i<=x1; i++) {
					I2C_Write(PagePatternStart);
				}
				I2C_Stop();
			#endif
		#endif
		
		#if SH1106_USE_SPI
			SH1106_CHIP_SELECT;
			SH1106_DC_DATA;
			Spi_Repeat(PagePatternStart, x1-x0+1);
			SH1106_CHIP_DESELECT;
		#endif
		
		if(PagePatternEnd) {
			SH1106_CursorXSet(x0);
			SH1106_CursorPageSet(PageEnd);
			
			#if SH1106_USE_I2C
				#if SH1106_USE_RMW
					SH1106_RmwStart();
					for(uint8_t i=x0; i<=x1; i++) {
						SH1106_RmwExecute(PagePatternEnd);
					}
					SH1106_RmwEnd();
				#else
					I2C_Start(SH1106_ADDRESS_WRITE);
					I2C_Write(SH1106_DATA_BYTE);
					for(uint8_t i=x0; i<=x1; i++) {
						I2C_Write(PagePatternEnd);
					}
					I2C_Stop();
				#endif
			#endif
			
			#if SH1106_USE_SPI
				SH1106_CHIP_SELECT;
				SH1106_DC_DATA;
				Spi_Repeat(PagePatternEnd, x1-x0+1);
				SH1106_CHIP_DESELECT;
			#endif
		}
		
		while(PageEnd - PageStart >= 2) {
			SH1106_CursorXSet(x0);
			SH1106_CursorPageSet(++PageStart);
			
			#if SH1106_USE_I2C
				#if SH1106_USE_RMW
					SH1106_RmwStart();
					for(uint8_t i=x0; i<=x1; i++) {
						SH1106_RmwExecute(0xFF);
					}
					SH1106_RmwEnd();
				#else
					I2C_Start(SH1106_ADDRESS_WRITE);
					I2C_Write(SH1106_DATA_BYTE);
					for(uint8_t i=x0; i<=x1; i++) {
						I2C_Write(0xFF);
					}
					I2C_Stop();
				#endif
			#endif
			
			#if SH1106_USE_SPI
				SH1106_CHIP_SELECT;
				SH1106_DC_DATA;
				Spi_Repeat(0xFF, x1-x0+1);
				SH1106_CHIP_DESELECT;
			#endif
		}
	}
}

// Circle
void SH1106_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r) {
	int16_t d = 5 - 4*r;
	int16_t x = 0;
	int16_t y = r;
	int16_t deltaA = (-2*r + 5) * 4;
	int16_t deltaB = 3*4;
	
	while (x <= y) {
		SH1106_DrawPixel(x0-x, y0-y);
		SH1106_DrawPixel(x0-x, y0+y);
		SH1106_DrawPixel(x0+x, y0-y);
		SH1106_DrawPixel(x0+x, y0+y);
		SH1106_DrawPixel(x0-y, y0-x);
		SH1106_DrawPixel(x0-y, y0+x);
		SH1106_DrawPixel(x0+y, y0-x);
		SH1106_DrawPixel(x0+y, y0+x);
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
// Bitmap
// ========================================

// Draw bitmap
void SH1106_Bitmap(const SH1106_Bitmap_t * Bitmap) {
	uint16_t Address;
	uint8_t Page = Bitmap->Height / SH1106_PAGE_HEIGHT - 1;
	
	uint8_t CursorX_Old = SH1106_CursorX;
	uint8_t CursorL_Old = SH1106_CursorP;
	
	do {
		Address = Page;
		
		#if SH1106_USE_I2C
			I2C_Start(SH1106_ADDRESS_WRITE);
			I2C_Write(SH1106_DATA_BYTE);
			for(uint8_t i = 0; i < Bitmap->Width; i++) {
				I2C_Write(SH1106_Color ? Bitmap->Array[Address] : ~Bitmap->Array[Address]);
				Address = Address + Bitmap->Height / SH1106_PAGE_HEIGHT;
			}
			I2C_Stop();
		#endif
			
		#if SH1106_USE_SPI
			SH1106_CHIP_SELECT;
			SH1106_DC_DATA;
			for(uint8_t i = 0; i < Bitmap->Width; i++) {
				Spi_1(SH1106_Color ? Bitmap->Array[Address] : ~Bitmap->Array[Address]);
				Address = Address + Bitmap->Height / SH1106_PAGE_HEIGHT;
			}
			SH1106_CHIP_DESELECT;
		#endif
		
		// If this was lat page
		if(Page == 0) {
			// It was the last page
			
			// Set curson at the begining of the bitmap
			if(Bitmap->Height / SH1106_PAGE_HEIGHT > 1) {
				SH1106_CursorPageSet(CursorL_Old);
			}
			
			// Set curson at the end of the bitmap
			SH1106_CursorX = CursorX_Old + Bitmap->Width;
			if(SH1106_CursorX >= SH1106_DISPLAY_SIZE_X) {
				SH1106_CursorX = SH1106_CursorX - SH1106_DISPLAY_SIZE_X;
			}
		}
		else {
			// It was not the last page
			
			// Set cursor back at the beginnign of the page
			SH1106_CursorXSet(CursorX_Old);
			
			// Move curson on page below
			SH1106_CursorPageSet(SH1106_CursorP + 1);
		}
	} while(Page--);
}

// ========================================
// Text
// ========================================

// Get actual font
const SH1106_FontDef_t * SH1106_FontGet(void) {
	return SH1106_Font;
}

// Set font
void SH1106_FontSet(const SH1106_FontDef_t * Font) {
	SH1106_Font = Font;
}
// Print single character
void SH1106_PrintChar(uint8_t Char) {
	
	// Check if the character is supported by the font
	if(Char < SH1106_Font->FirstChar) Char = SH1106_Font->LastChar;
	if(Char > SH1106_Font->LastChar) Char = SH1106_Font->LastChar;
	
	// Calculate character offset, because font table doesn't have to befin with 0x00 character
	Char = Char - SH1106_Font->FirstChar;
	
	// Find width of the character and its position is bitmap table
	uint8_t Width;
	uint8_t Height = SH1106_Font->Height;
	uint16_t Address;
	if(SH1106_Font->Width > 0) {
		Width = SH1106_Font->Width;
		Address = Char * Width * Height;
	}
	else {
		Width = SH1106_Font->Descriptors[Char].Width;
		Address = SH1106_Font->Descriptors[Char].Offset;
	}
	
	// If Address is null and width = 0 then print last charachter from table (badchar)
	if((Address == 0) && (Width == 0)) {
		Char = SH1106_Font->LastChar - SH1106_Font->FirstChar;
		Address = SH1106_Font->Descriptors[Char].Offset;
		Width = SH1106_Font->Descriptors[Char].Width;
	}
	
	// Update cursor position
	uint8_t CursorX_Old = SH1106_CursorX;
	uint8_t CursorL_Old = SH1106_CursorP;
	uint16_t Address_Old = Address;
	
	// Loop iterator
	uint8_t Linia = Height - 1;
	
	// Print all bytes of all pages
	do {
		
		Address = Address + Linia;
		
		// Print part of the charater that is proper for this page
			#if SH1106_USE_I2C
				I2C_Start(SH1106_ADDRESS_WRITE);
				I2C_Write(SH1106_DATA_BYTE);
				
				// Char
				for(uint8_t i=0; i<Width; i++) {
					I2C_Write(SH1106_Color ? SH1106_Font->Bitmaps[Address] : ~SH1106_Font->Bitmaps[Address]);
					Address = Address + Height;
				}
				
				// Spacing
				for(uint8_t i = SH1106_Font->Spacing; i; i--) {
					I2C_Write(SH1106_Color ? 0x00 : 0xFF);
				}
				I2C_Stop();
			#endif
			
			#if SH1106_USE_SPI
				SH1106_CHIP_SELECT;
				SH1106_DC_DATA;
				
				// Char
				for(uint8_t i=0; i<Width; i++) {
					Spi_1(SH1106_Color ? SH1106_Font->Bitmaps[Address] : ~SH1106_Font->Bitmaps[Address]);
					Address = Address + Height;
				}
				Address = Address + Height;
				
				// Spacing
				for(uint8_t i = SH1106_Font->Spacing; i; i--) {
					Spi_1(SH1106_Color ? 0x00 : 0xFF);
				}
				
				SH1106_CHIP_DESELECT;
			#endif
		
		// CzyIf this was the last line
		if(Linia == 0) {
			
			if(Height > 1) {
				SH1106_CursorPageSet(CursorL_Old);
			}
			
			SH1106_CursorX = CursorX_Old + Width + SH1106_Font->Spacing;
			if(SH1106_CursorX >= SH1106_DISPLAY_SIZE_X) {
				SH1106_CursorX = SH1106_CursorX - SH1106_DISPLAY_SIZE_X;
			}
		}
		else {
			// It was not the last line
			SH1106_CursorXSet(CursorX_Old);
			SH1106_CursorPageSet(SH1106_CursorP + 1);
			Address = Address_Old;
		}
	} while(Linia--);
}

// Calculate text width
uint16_t SH1106_TextWidth(const char * Text) {
	uint16_t Width = 0;
	uint16_t Offset = SH1106_Font->FirstChar;
	
	// Check if the font has characters with fixed width
	if(SH1106_Font->Width) {
		
		// Count number of characters
		while(*Text++) Width++;
		
		// Spacing after every character
		Width = Width + SH1106_Font->Spacing;
		
		// Multiply by width of single character
		Width = Width * (SH1106_Font->Width);
	}
	else {
		// Font with variable character width
		while(*Text) {
			Width += SH1106_Font->Descriptors[(*Text) - Offset].Width + SH1106_Font->Spacing;			
			Text++;
		}
	}
	
	return Width;
}

// Print text. Remember to set font first!
void SH1106_Text(const char * Text, SH1106_align_t Align) {
	
	// Set cursor position to match text widht and align
	uint16_t Width;
	switch(Align) {
		
		case SH1106_AlignLeft:
			SH1106_CursorXSet(0);
			break;
		
		case SH1106_AlignRight:
			Width = SH1106_TextWidth(Text);
			SH1106_CursorXSet(SH1106_DISPLAY_SIZE_X - Width);
			break;
		
		case SH1106_AlignCenter:
			Width = SH1106_TextWidth(Text);
			SH1106_CursorXSet(SH1106_DISPLAY_SIZE_X/2 - Width/2);
			break;
		
		default:
			break;
	}
	
	// Print text
	while(*Text) SH1106_PrintChar(*Text++);
}

// ========================================
// Testing
// ========================================

// Draw angled line made of 8 segments
void SH1106_Slash(void) {
	
	#if SH1106_USE_I2C
		uint8_t Slash = 0b10000000;
		while(Slash) {
			SH1106_WriteData(Slash);
			Slash = Slash >> 1;
		}
	#endif
	
	#if SH1106_USE_SPI
		const uint8_t Slash[8] = {
			0b10000000,
			0b01000000,
			0b00100000,
			0b00010000,
			0b00001000,
			0b00000100,
			0b00000010,
			0b00000001,
		};
		SH1106_CHIP_SELECT;
		SH1106_DC_DATA;
		Spi_Write(Slash, sizeof(Slash));
		SH1106_CHIP_DESELECT;
	#endif
}



#endif
