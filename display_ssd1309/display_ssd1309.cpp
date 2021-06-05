#if COMPONENT_DISPLAY_SSD1309

#include	"display_ssd1309.h"

// ========================================
// Global variables
// ========================================

static uint8_t SSD1309_CursorP = 0;
static uint8_t SSD1309_CursorX = 0;
static uint8_t SSD1309_Color	= 1;		// White
static const SSD1309_FontDef_t * SSD1309_Font = &SSD1309_DEFAULT_FONT;

// Display config for init function
static const uint8_t SSD1309_InitSequence[] = {
	SSD1309_DISPLAY_OFF,					// Display OFF
	
	SSD1309_CLOCK_DIV_FREQ,					// Display clock divide
	0x80,
	
	SSD1309_MULTIPLEX_RATIO,				// Multiplex ratio
	SSD1309_DISPLAY_SIZE_Y - 1,				// 1/64 duty
	
	SSD1309_DISPLAY_OFFSET,					// Display offset
	0x00,									// No offset
	
	SSD1309_START_LINE(0),					// Start line
	
	SSD1309_CHARGE_PUMP,					// Charge pump 0x8d
	0x14,
	
	SSD1309_MEMORY_MODE,
	0x00,
	
	SSD1309_REMAP(1),						// Remap
	
	SSD1309_COMSCANDEC,
	
	SSD1309_COMMON_PADS_HW_CONFIG,			// Com pins
	0x12,
	
	SSD1309_CONTRAST,						// Set contrast
	SSD1309_DEFAULT_CONTRAST,				// Contrast DATA
	
	SSD1309_CHARGE_PERIOD,					// Precharge period
	0xF1,
	
	SSD1309_VCOM_DESELECT_LEVEL,			// VCOM deselect
	0x40,
	
	SSD1309_ENTRIE_DISPLAY_ON(0),			// Display ON
	
	SSD1309_NORMAL_REVERSE(0),				// Normal display
	
	SSD1309_DEACTIVATE_SCROLL,
	
	#if SSD1309_CLEAR_AFERT_INIT == 0
 		SSD1309_DISPLAY_ON,					// Display ON
 	#endif
};

// Initialization
void SSD1309_Init(void) {
	
	// If you have problem with initialization, add RC circuit to RESET pin
	// 100n capacitor between RESET and GND
	// 100k resistor between RESET and VCC
	
	#if SSD1309_USE_I2C
		for(uint8_t i=0; i<sizeof(SSD1309_InitSequence); i++) {
			SSD1309_WriteCommand(SSD1309_InitSequence[i]);
		}
		
		#if SSD1309_CLEAR_AFERT_INIT
			SSD1309_Clear();
			SSD1309_WriteCommand(SSD1309_DISPLAY_ON);
		#endif
	#endif
	
	#if SSD1309_USE_SPI
		SSD1309_CHIP_SELECT_INIT;
		SSD1309_DC_INIT;
		
		SSD1309_CHIP_SELECT;
		SSD1309_DC_COMMAND;
		Spi_Write(SSD1309_InitSequence, sizeof(SSD1309_InitSequence));
		SSD1309_CHIP_DESELECT;
		
		#if SSD1309_CLEAR_AFERT_INIT
			SSD1309_Clear();
			SSD1309_WriteCommand(SSD1309_DISPLAY_ON);
		#endif
	#endif
}

// Send command to the display
void SSD1309_WriteCommand(const uint8_t Command) {
	
	#if SSD1309_USE_I2C
		I2C_Start(SSD1309_ADDRESS_WRITE);
		I2C_Write(SSD1309_COMMAND_BYTE);
		I2C_Write(Command);
		I2C_Stop();
	#endif
	
	#if SSD1309_USE_SPI
		SSD1309_CHIP_SELECT;
		SSD1309_DC_COMMAND;
		Spi_1(Command);
		SSD1309_CHIP_DESELECT;
	#endif
}

// Send data to the display
void SSD1309_WriteData(const uint8_t Data) {
	
	#if SSD1309_USE_I2C
		I2C_Start(SSD1309_ADDRESS_WRITE);
		I2C_Write(SSD1309_DATA_BYTE);
		I2C_Write(Data);
		I2C_Stop();
	#endif
	
	#if SSD1309_USE_SPI
		SSD1309_CHIP_SELECT;
		SSD1309_DC_DATA;
		Spi_1(Data);
		SSD1309_CHIP_DESELECT;
	#endif
}

// Set contrast
void SSD1309_ContrastSet(const uint8_t Value) {
	SSD1309_WriteCommand(SSD1309_CONTRAST);
	SSD1309_WriteCommand(Value);
}

// Clear display - set Pattern = 0 to clear
void SSD1309_Clear(const uint8_t Pattern) {
	for(uint8_t Page=0; Page<8; Page++) {
		SSD1309_CursorSet(0, Page);
		
		#if SSD1309_USE_I2C
			I2C_Start(SSD1309_ADDRESS_WRITE);
			I2C_Write(SSD1309_DATA_BYTE);
			for(uint8_t i = 0; i < SSD1309_DISPLAY_SIZE_X; i++) {
				I2C_Write(Pattern);
			}
			I2C_Stop();
		#endif
		
		#if SSD1309_USE_SPI
			SSD1309_CHIP_SELECT;
			SSD1309_DC_DATA;
			Spi_Repeat(Pattern, SSD1309_DISPLAY_SIZE_X);
			SSD1309_CHIP_DESELECT;
		#endif
	}
	
	SSD1309_CursorSet(0, 0);
}

// Light all pixels
void SSD1309_Fill(void) {
	SSD1309_Clear(0xFF);
}

// Draw chessboard
void SSD1309_Chessboard(void) {
	
	// Loop 8 pages
	for(uint8_t Page = 0; Page < SSD1309_PAGE_COUNT; Page++) {
		SSD1309_CursorSet(0, Page);
		
		// Loop 128 columns
		#if SSD1309_USE_I2C
			I2C_Start(SSD1309_ADDRESS_WRITE);
			I2C_Write(SSD1309_DATA_BYTE);
			for(uint8_t Column = 0; Column < SSD1309_DISPLAY_SIZE_X / 2; Column++) {
				I2C_Write(0b10101010);
				I2C_Write(0b01010101);
			}
			I2C_Stop();
		#endif
		
		#if SSD1309_USE_SPI
			SSD1309_CHIP_SELECT;
			SSD1309_DC_DATA;
			for(uint8_t Column = 0; Column < SSD1309_DISPLAY_SIZE_X / 2; Column++) {
				Spi_2(0b10101010, 0b01010101);
			}
			SSD1309_CHIP_DESELECT;
		#endif
	}
}

// ========================================
// Cursor setting
// ========================================


void SSD1309_CursorSet(uint8_t x, uint8_t p) {
	SSD1309_CursorPageSet(p);
	SSD1309_CursorXSet(x);
}

// Odczytanie pozycji X
uint8_t SSD1309_CursorXGet(void) {
	return SSD1309_CursorX;
}

// Ustawienie pozycji X
void SSD1309_CursorXSet(uint8_t PosX) {
	
	// Sanity check
	SSD1309_CursorX = PosX < SSD1309_DISPLAY_SIZE_X ? PosX : 0;
	
	// Set in accordande to display x offset
	#if SSD1309_USE_I2C
		I2C_Start(SSD1309_ADDRESS_WRITE);
		I2C_Write(SSD1309_COMMAND_BYTE);
		I2C_Write(SSD1309_COLUMN_LOW((SSD1309_CursorX + SSD1309_OFFSET_X) & 0x0F));
		I2C_Write(SSD1309_COMMAND_BYTE);
		I2C_Write(SSD1309_COLUMN_HIGH(((SSD1309_CursorX + SSD1309_OFFSET_X) & 0xF0) >> 4));
		I2C_Stop();
	#endif
	
	#if SSD1309_USE_SPI
		SSD1309_CHIP_SELECT;
		SSD1309_DC_COMMAND;
		Spi_2(SSD1309_COLUMN_LOW((SSD1309_CursorX + SSD1309_OFFSET_X) & 0x0F), SSD1309_COLUMN_HIGH(((SSD1309_CursorX + SSD1309_OFFSET_X) & 0xF0) >> 4));
		SSD1309_CHIP_DESELECT;
	#endif
}

// Get actual selected page
uint8_t SSD1309_CursorPageGet(void) {
	return SSD1309_CursorP;
}

// Set page to write to
void SSD1309_CursorPageSet(uint8_t Page) {
	SSD1309_CursorP = Page;
	SSD1309_WriteCommand(SSD1309_PAGE(SSD1309_CursorP));
}

// ========================================
// Colors (black & white)
// ========================================

// 0 - black
// 1 - white

void SSD1309_ColorSet(uint8_t Color) {
	SSD1309_Color = Color;
}

uint8_t SSD1309_ColorGet(void) {
	return SSD1309_Color;
}

// ========================================
// Drawing
// ========================================

// Single pixel
void SSD1309_DrawPixel(uint8_t x, uint8_t y) {
	uint8_t Page = y / SSD1309_PAGE_HEIGHT;
	SSD1309_CursorSet(x, Page);
	SSD1309_WriteData(SSD1309_Color << (y % SSD1309_PAGE_HEIGHT));
}

// Horizontal line, thickness is 1 pixel
// Begin at x0, y0 and draw right
void SSD1309_DrawLineHorizontal(uint8_t x0, uint8_t y0, uint8_t Length) {
	
	// Calculate y0 to page number and set cursor
	uint8_t Page = y0 / SSD1309_PAGE_HEIGHT;
	SSD1309_CursorSet(x0, Page);
	
	#if SSD1309_USE_I2C
		uint8_t Pattern = (SSD1309_Color << (y0 % SSD1309_PAGE_HEIGHT));
		I2C_Start(SSD1309_ADDRESS_WRITE);
		I2C_Write(SSD1309_DATA_BYTE);
		while(Length--) {
			I2C_Write(Pattern);
		}
		I2C_Stop();
	#endif
	
	#if SSD1309_USE_SPI
		uint8_t Pattern = (SSD1309_Color << (y0 % SSD1309_PAGE_HEIGHT));
		SSD1309_CHIP_SELECT;
		SSD1309_DC_DATA;
		Spi_Repeat(Pattern, Length);
		SSD1309_CHIP_DESELECT;
	#endif
}

// Verical line, thickness is 1 pixel
// Begin at x0, y0 and draw bottom
void SSD1309_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length) {
	
	uint8_t PageStart			=	y0 / SSD1309_PAGE_HEIGHT;
	uint8_t PageEnd				=	(y0+Length) / SSD1309_PAGE_HEIGHT;
	uint8_t PagePatternStart	=	0xFF << (y0 % SSD1309_PAGE_HEIGHT);
	uint8_t PagePatternEnd		=	~(0xFF << ((y0+Length) % SSD1309_PAGE_HEIGHT));
		
	if(PageStart == PageEnd) {
		// Tha line fits to single page (<= 8 pixels)
		SSD1309_CursorSet(x0, PageStart);
		SSD1309_WriteData(PagePatternStart & PagePatternEnd);
	}
	else {
		// The line doesn;t fit in single page
		// Draw biginning of the line
		SSD1309_CursorSet(x0, PageStart);
		SSD1309_WriteData(PagePatternStart);
			
		// Draw enging of the line
		if(PagePatternEnd) {
			SSD1309_CursorSet(x0, PageEnd);
			SSD1309_WriteData(PagePatternEnd);
		}
			
		// Draw middle part of the line, if there's need to
		while(PageEnd - PageStart >= 2) {
			SSD1309_CursorSet(x0, ++PageStart);
			SSD1309_WriteData(0xFF);
		}
	}
}

// Draw line at any angle with Bresenham's algorithm
void SSD1309_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	
	if(x0 == x1) {
		if(y0 > y1) {
			uint8_t temp = y0;
			y0 = y1;
			y1 = temp;
		}
		SSD1309_DrawLineVertical(x0, y0, y1-y0+1);
		return;
	}
	
	if(y0 == y1) {
		if(x0 > x1) {
			uint8_t temp = x0;
			x0 = x1;
			x1 = temp;
		}
		SSD1309_DrawLineHorizontal(x0, y0, x1-x0+1);
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
		SSD1309_DrawPixel(x0, y0);
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
void SSD1309_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	SSD1309_DrawLineVertical(x0, y0, y1-y0+1);
	SSD1309_DrawLineVertical(x1, y0, y1-y0+1);
	SSD1309_DrawLineHorizontal(x0+1, y0, x1-x0-1);
	SSD1309_DrawLineHorizontal(x0+1, y1, x1-x0-1);
}

// Rectangle with fill
void SSD1309_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	// This is very similar to SSD1309_DrawLineVertical
	uint8_t PageStart			=	y0 / SSD1309_PAGE_HEIGHT;
	uint8_t PageEnd				=	(y1+1) / SSD1309_PAGE_HEIGHT;
	uint8_t PagePatternStart	=	0xFF << (y0 % SSD1309_PAGE_HEIGHT);
	uint8_t PagePatternEnd		=	~(0xFF << ((y1+1) % SSD1309_PAGE_HEIGHT));
	
	if(PageStart == PageEnd) {
		SSD1309_CursorSet(x0, PageStart);
		
		#if SSD1309_USE_I2C
			I2C_Start(SSD1309_ADDRESS_WRITE);
			I2C_Write(SSD1309_DATA_BYTE);
			for(uint8_t i=x0; i<=x1; i++) {
				I2C_Write(PagePatternStart & PagePatternEnd);
			}
			I2C_Stop();
		#endif
		
		#if SSD1309_USE_SPI
			SSD1309_CHIP_SELECT;
			SSD1309_DC_DATA;
			Spi_Repeat(PagePatternStart & PagePatternEnd, x1-x0+1);
			SSD1309_CHIP_DESELECT;
		#endif
	}
	else {
		SSD1309_CursorSet(x0, PageStart);
		
		#if SSD1309_USE_I2C
			I2C_Start(SSD1309_ADDRESS_WRITE);
			I2C_Write(SSD1309_DATA_BYTE);
			for(uint8_t i=x0; i<=x1; i++) {
				I2C_Write(PagePatternStart);
			}
			I2C_Stop();
		#endif
		
		#if SSD1309_USE_SPI
			SSD1309_CHIP_SELECT;
			SSD1309_DC_DATA;
			Spi_Repeat(PagePatternStart, x1-x0+1);
			SSD1309_CHIP_DESELECT;
		#endif
		
		if(PagePatternEnd) {
			SSD1309_CursorSet(x0, PageEnd);
			
			#if SSD1309_USE_I2C
				I2C_Start(SSD1309_ADDRESS_WRITE);
				I2C_Write(SSD1309_DATA_BYTE);
				for(uint8_t i=x0; i<=x1; i++) {
					I2C_Write(PagePatternEnd);
				}
				I2C_Stop();
			#endif
			
			#if SSD1309_USE_SPI
				SSD1309_CHIP_SELECT;
				SSD1309_DC_DATA;
				Spi_Repeat(PagePatternEnd, x1-x0+1);
				SSD1309_CHIP_DESELECT;
			#endif
		}
		
		while(PageEnd - PageStart >= 2) {
			SSD1309_CursorSet(x0, ++PageStart);
			
			#if SSD1309_USE_I2C
				I2C_Start(SSD1309_ADDRESS_WRITE);
				I2C_Write(SSD1309_DATA_BYTE);
				for(uint8_t i=x0; i<=x1; i++) {
					I2C_Write(0xFF);
				}
				I2C_Stop();
			#endif
			
			#if SSD1309_USE_SPI
				SSD1309_CHIP_SELECT;
				SSD1309_DC_DATA;
				Spi_Repeat(0xFF, x1-x0+1);
				SSD1309_CHIP_DESELECT;
			#endif
		}
	}
}

// Circle
void SSD1309_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r) {
	int16_t d = 5 - 4*r;
	int16_t x = 0;
	int16_t y = r;
	int16_t deltaA = (-2*r + 5) * 4;
	int16_t deltaB = 3*4;
	
	while (x <= y) {
		SSD1309_DrawPixel(x0-x, y0-y);
		SSD1309_DrawPixel(x0-x, y0+y);
		SSD1309_DrawPixel(x0+x, y0-y);
		SSD1309_DrawPixel(x0+x, y0+y);
		SSD1309_DrawPixel(x0-y, y0-x);
		SSD1309_DrawPixel(x0-y, y0+x);
		SSD1309_DrawPixel(x0+y, y0-x);
		SSD1309_DrawPixel(x0+y, y0+x);
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
void SSD1309_Bitmap(const SSD1309_Bitmap_t * Bitmap) {
	uint16_t Address;
	uint8_t Page = Bitmap->Height / SSD1309_PAGE_HEIGHT - 1;
	
	uint8_t CursorX_Old = SSD1309_CursorX;
	uint8_t CursorL_Old = SSD1309_CursorP;
	
	do {
		Address = Page;
		
		#if SSD1309_USE_I2C
			I2C_Start(SSD1309_ADDRESS_WRITE);
			I2C_Write(SSD1309_DATA_BYTE);
			for(uint8_t i = 0; i < Bitmap->Width; i++) {
				I2C_Write(SSD1309_Color ? Bitmap->Array[Address] : ~Bitmap->Array[Address]);
				Address = Address + Bitmap->Height / SSD1309_PAGE_HEIGHT;
			}
			I2C_Stop();
		#endif
			
		#if SSD1309_USE_SPI
			SSD1309_CHIP_SELECT;
			SSD1309_DC_DATA;
			for(uint8_t i = 0; i < Bitmap->Width; i++) {
				Spi_1(SSD1309_Color ? Bitmap->Array[Address] : ~Bitmap->Array[Address]);
				Address = Address + Bitmap->Height / SSD1309_PAGE_HEIGHT;
			}
			SSD1309_CHIP_DESELECT;
		#endif
		
		// If this was lat page
		if(Page == 0) {
			// It was the last page
			
			// Set curson at the begining of the bitmap
			if(Bitmap->Height / SSD1309_PAGE_HEIGHT > 1) {
				SSD1309_CursorPageSet(CursorL_Old);
			}
			
			// Set curson at the end of the bitmap
			SSD1309_CursorX = CursorX_Old + Bitmap->Width;
			if(SSD1309_CursorX >= SSD1309_DISPLAY_SIZE_X) {
				SSD1309_CursorX = SSD1309_CursorX - SSD1309_DISPLAY_SIZE_X;
			}
		}
		else {
			// It was not the last page
			SSD1309_CursorSet(CursorX_Old, SSD1309_CursorP + 1);
		}
	} while(Page--);
}

// ========================================
// Text
// ========================================

// Get actual font
const SSD1309_FontDef_t * SSD1309_FontGet(void) {
	return SSD1309_Font;
}

// Set font
void SSD1309_FontSet(const SSD1309_FontDef_t * Font) {
	SSD1309_Font = Font;
}
// Print single character
void SSD1309_PrintChar(uint8_t Char) {
	
	// Check if the character is supported by the font
	if(Char < SSD1309_Font->FirstChar) Char = SSD1309_Font->LastChar;
	if(Char > SSD1309_Font->LastChar) Char = SSD1309_Font->LastChar;
	
	// Calculate character offset, because font table doesn't have to befin with 0x00 character
	Char = Char - SSD1309_Font->FirstChar;
	
	// Find width of the character and its position is bitmap table
	uint8_t Width;
	uint8_t Height = SSD1309_Font->Height;
	uint16_t Address;
	if(SSD1309_Font->Width > 0) {
		Width = SSD1309_Font->Width;
		Address = Char * Width * Height;
	}
	else {
		Width = SSD1309_Font->Descriptors[Char].Width;
		Address = SSD1309_Font->Descriptors[Char].Offset;
	}
	
	// If Address is null and width = 0 then print last charachter from table (badchar)
	if((Address == 0) && (Width == 0)) {
		Char = SSD1309_Font->LastChar - SSD1309_Font->FirstChar;
		Address = SSD1309_Font->Descriptors[Char].Offset;
		Width = SSD1309_Font->Descriptors[Char].Width;
	}
	
	// Update cursor position
	uint8_t CursorX_Old = SSD1309_CursorX;
	uint8_t CursorL_Old = SSD1309_CursorP;
	uint16_t Address_Old = Address;
	
	// Loop iterator
	uint8_t Linia = Height - 1;
	
	// Print all bytes of all pages
	do {
		
		Address = Address + Linia;
		
		// Print part of the charater that is proper for this page
			#if SSD1309_USE_I2C
				I2C_Start(SSD1309_ADDRESS_WRITE);
				I2C_Write(SSD1309_DATA_BYTE);
				
				// Char
				for(uint8_t i=0; i<Width; i++) {
					I2C_Write(SSD1309_Color ? SSD1309_Font->Bitmaps[Address] : ~SSD1309_Font->Bitmaps[Address]);
					Address = Address + Height;
				}
				
				// Spacing
				for(uint8_t i = SSD1309_Font->Spacing; i; i--) {
					I2C_Write(SSD1309_Color ? 0x00 : 0xFF);
				}
				I2C_Stop();
			#endif
			
			#if SSD1309_USE_SPI
				SSD1309_CHIP_SELECT;
				SSD1309_DC_DATA;
				
				// Char
				for(uint8_t i=0; i<Width; i++) {
					Spi_1(SSD1309_Color ? SSD1309_Font->Bitmaps[Address] : ~SSD1309_Font->Bitmaps[Address]);
					Address = Address + Height;
				}
				Address = Address + Height;
				
				// Spacing
				for(uint8_t i = SSD1309_Font->Spacing; i; i--) {
					Spi_1(SSD1309_Color ? 0x00 : 0xFF);
				}
				
				SSD1309_CHIP_DESELECT;
			#endif
		
		// CzyIf this was the last line
		if(Linia == 0) {
			
			if(Height > 1) {
				SSD1309_CursorPageSet(CursorL_Old);
			}
			
			SSD1309_CursorX = CursorX_Old + Width + SSD1309_Font->Spacing;
			if(SSD1309_CursorX >= SSD1309_DISPLAY_SIZE_X) {
				SSD1309_CursorX = SSD1309_CursorX - SSD1309_DISPLAY_SIZE_X;
			}
		}
		else {
			// It was not the last line
			SSD1309_CursorSet(CursorX_Old, SSD1309_CursorP + 1);
			Address = Address_Old;
		}
	} while(Linia--);
}

// Calculate text width
uint16_t SSD1309_TextWidth(const char * Text) {
	uint16_t Width = 0;
	uint16_t Offset = SSD1309_Font->FirstChar;
	
	// Check if the font has characters with fixed width
	if(SSD1309_Font->Width) {
		
		// Count number of characters
		while(*Text++) Width++;
		
		// Spacing after every character
		Width = Width + SSD1309_Font->Spacing;
		
		// Multiply by width of single character
		Width = Width * (SSD1309_Font->Width);
	}
	else {
		// Font with variable character width
		while(*Text) {
			Width += SSD1309_Font->Descriptors[(*Text) - Offset].Width + SSD1309_Font->Spacing;			
			Text++;
		}
	}
	
	return Width;
}

// Print text. Remember to set font first!
void SSD1309_Text(const char * Text, SSD1309_align_t Align) {
	
	// Set cursor position to match text widht and align
	uint16_t Width;
	switch(Align) {
		
		case SSD1309_AlignLeft:
			SSD1309_CursorXSet(0);
			break;
		
		case SSD1309_AlignRight:
			Width = SSD1309_TextWidth(Text);
			SSD1309_CursorXSet(SSD1309_DISPLAY_SIZE_X - Width);
			break;
		
		case SSD1309_AlignCenter:
			Width = SSD1309_TextWidth(Text);
			SSD1309_CursorXSet(SSD1309_DISPLAY_SIZE_X/2 - Width/2);
			break;
		
		default:
			break;
	}
	
	// Print text
	while(*Text) SSD1309_PrintChar(*Text++);
}

// ========================================
// Testing
// ========================================

// Draw angled line made of 8 segments
void SSD1309_Slash(void) {
	
	#if SSD1309_USE_I2C
		uint8_t Slash = 0b10000000;
		while(Slash) {
			SSD1309_WriteData(Slash);
			Slash = Slash >> 1;
		}
	#endif
	
	#if SSD1309_USE_SPI
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
		SSD1309_CHIP_SELECT;
		SSD1309_DC_DATA;
		Spi_Write(Slash, sizeof(Slash));
		SSD1309_CHIP_DESELECT;
	#endif
}



#endif
