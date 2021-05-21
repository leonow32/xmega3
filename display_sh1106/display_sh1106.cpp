#if COMPONENT_DISPLAY_SH1106

#include	"display_sh1106.h"

// Zmienne globalne
static uint8_t SH1106_CursorP = 0;
static uint8_t SH1106_CursorX = 0;
static uint8_t SH1106_Color	= 1;		// White
static const SH1106_FontDef_t * SH1106_Font = &SH1106_DEFAULT_FONT;

// Konfiguracja wyœwietlacza dla funkcji SH1106_Init()
static const uint8_t SH1106_InitSequence[] = {
	SH1106_DISPLAY_OFF,						// Display OFF
	SH1106_COLUMN_LOW(SH1106_OFFSET_X),		// Low Column
	SH1106_COLUMN_HIGH(0),					// High Column
	SH1106_PAGE(0),							// Strona
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

// Inicjalizacja
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

// Wys³anie komendy
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

// Wys³anie danych
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

// Ustawianie kontrastu
void SH1106_ContrastSet(const uint8_t Value) {
	SH1106_WriteCommand(SH1106_CONTRAST);
	SH1106_WriteCommand(Value);
}

// Czyszczenie wyœwietlacza
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

// Szachownica na ca³y wyœwietlacz
void SH1106_BackgroundGray(void) {
	for(uint8_t Page=0; Page<8; Page++) {
		SH1106_CursorPageSet(Page);
		SH1106_CursorXSet(0);
		
		#if SH1106_USE_I2C
			I2C_Start(SH1106_ADDRESS_WRITE);
			I2C_Write(SH1106_DATA_BYTE);
			for(uint8_t i = 0; i < (SH1106_DISPLAY_SIZE_X/2); i++) {
				I2C_Write(0b10101010);
				I2C_Write(0b01010101);
			}
			I2C_Stop();
		#endif
		
		#if SH1106_USE_SPI
			SH1106_CHIP_SELECT;
			SH1106_DC_DATA;
			for(uint8_t i=0; i < (SH1106_DISPLAY_SIZE_X/2); i++) {
				Spi_2(0b10101010, 0b01010101);
			}
			SH1106_CHIP_DESELECT;			
		#endif
	}
	
	SH1106_CursorXSet(0);
	SH1106_CursorPageSet(0);
}

// Pozycja kursora
//  - pozycja pozioma - zmienna Posx, zakres od 0 do 127
//  - pozycja pionowa - zmienna Line, zakres od 0 do 7, ka¿da strona to 8 pikseli

// Odczytanie pozycji X
uint8_t SH1106_CursorXGet(void) {
	return SH1106_CursorX;
}

// Ustawienie pozycji X
void SH1106_CursorXSet(uint8_t PosX) {
	
	// Kontrola
	SH1106_CursorX = PosX < SH1106_DISPLAY_SIZE_X ? PosX : 0;
	
	// Ustawianie z uwaglêdnieniem offsetu X wyœwietlacza
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

// Odczytanie aktualniej strony
uint8_t SH1106_CursorPageGet(void) {
	return SH1106_CursorP;
}

// Ustawienie pozycji strony
void SH1106_CursorPageSet(uint8_t Page) {
	SH1106_CursorP = Page;
	SH1106_WriteCommand(SH1106_PAGE(SH1106_CursorP));
}

// Funkcje trybu Read-Modify-Write tylko dla I2C, nieobs³ugiwane w SPI
// Wejœcie do trybu read-modify-write
void SH1106_RmwStart(void) {
	I2C_Start(SH1106_ADDRESS_WRITE);
	I2C_Write(SH1106_COMMAND_BYTE);
	I2C_Write(SH1106_READ_MODIFY_WRITE);
	I2C_Write(SH1106_CoDATA_BYTE);
	I2C_Stop();
}

// Operacja w trybie read-modify-write. W zaleznoœci od Mode mo¿na nadpisaæ piksele, wyczyœciæ lub zanegowaæ
void SH1106_RmwExecute(uint8_t Byte) {
	uint8_t Buffer;
	
	// Odczytanie do bufora
	I2C_Start(SH1106_ADDRESS_READ);
	I2C_Read();		// Dummy read
	Buffer = I2C_Read();
	I2C_Stop();
	
	// Wykonanie operacji
	if(SH1106_Color) {
		Buffer |= Byte;
	}
	else {
		Buffer &= ~Byte;
	}
	
	// Przes³anie z powrotem do pamiêci
	SH1106_WriteData(Buffer);
	
	// Zwiêkszenie pozycji kursora
	// Uwaga - sterownik ma rozdzielczoœæ 132 a wyœwietlacz ma 128
	SH1106_CursorX = (SH1106_CursorX == (SH1106_DISPLAY_SIZE_X-1) ? 0 : SH1106_CursorX + 1);
}

// Wyjœcie z trybu read-mofify-write
void SH1106_RmwEnd() {
	SH1106_WriteCommand(SH1106_END);
	SH1106_CursorXSet(SH1106_CursorX);
}

void SH1106_ColorSet(uint8_t Color) {
	SH1106_Color = Color;
}

uint8_t SH1106_ColorGet(void) {
	return SH1106_Color;
}

// Rysowanie piksela
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

// Linia pozioma
void SH1106_DrawLineHorizontal(uint8_t x0, uint8_t y0, uint8_t Length) {
	// Rysuje liniê poziom¹ od punktu (x0,y0) w prawo.
	
	// Przeliczenie wysokoœci na numer strony i ustawienie kursora
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

// Rysuje liniê pionow¹ od punktu (X,Y) w dó³.
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
			// Linia zawiera siê tylko w jednej stronie wyœwietlacza (<= 8 pikseli)
			SH1106_CursorXSet(x0);
			SH1106_CursorPageSet(PageStart);
			SH1106_WriteData(PagePatternStart & PagePatternEnd);
		}
		else {
			// Linia zawiera siê w wiêcej ni¿ jednej stronie wyœwietlacza
			// Rysowanie pocz¹tku linii
			SH1106_CursorXSet(x0);
			SH1106_CursorPageSet(PageStart);
			SH1106_WriteData(PagePatternStart);
			
			// Rysowanie koñca linii
			if(PagePatternEnd) {
				SH1106_CursorXSet(x0);
				SH1106_CursorPageSet(PageEnd);
				SH1106_WriteData(PagePatternEnd);
			}
			
			// Rysowanie œrodka linii jeœli jest, wykorzystywanie zmiennej LineStart do wskazywania aktualnej pozycji linii podczas rysowania
			while(PageEnd - PageStart >= 2) {
				SH1106_CursorXSet(x0);
				SH1106_CursorPageSet(++PageStart);
				SH1106_WriteData(0xFF);
			}
		}
	#endif
}

// Linia pod dowolnym k¹tem algorytmem Bresenhama
// Jeœli trzeba narysowaæ liniê pionow¹ lub poziom¹ to u¿ywaæ funkcji LineHorizontal lub LineVertica, bo dzia³aj¹ szybciej
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
	for (;;) {
		SH1106_DrawPixel(x0, y0);
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

//  Prostok¹t bez wype³nienia
void SH1106_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	SH1106_DrawLineVertical(x0, y0, y1-y0+1);
	SH1106_DrawLineVertical(x1, y0, y1-y0+1);
	SH1106_DrawLineHorizontal(x0+1, y0, x1-x0-1);
	SH1106_DrawLineHorizontal(x0+1, y1, x1-x0-1);
}

// Prostok¹t z wype³nieniem
void SH1106_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	// Funkcja jest podobna do SH1106_DrawLineVertical
	uint8_t PageStart			=	y0 / SH1106_PAGE_HEIGHT;
	uint8_t PageEnd				=	(y1+1) / SH1106_PAGE_HEIGHT;
	uint8_t PagePatternStart	=	0xFF << (y0 % SH1106_PAGE_HEIGHT);
	uint8_t PagePatternEnd		=	~(0xFF << ((y1+1) % SH1106_PAGE_HEIGHT));
	
	if(PageStart == PageEnd) {
		// Linia zawiera siê tylko w jednej stronie wyœwietlacza (<= 8 pikseli)
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
		// Prostok¹t zawiera siê w wiêcej ni¿ jednej stronie wyœwietlacza
		// Rysowanie górnej czêœci
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
		
		// Rysowanie dolnej czêœci jeœli jest
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
		
		// Rysowanie œrodkowej czêœci jeœli jest, wykorzystywanie zmiennej LineStart do wskazywania aktualnej pozycji linii podczas rysowania
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

// Okr¹g
void SH1106_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r) {
	// Uwaga - w niektóych przypadkach przy metodzie RmwInv mo¿e zostawiaæ kropki w miejscach ³¹czenia siê 1/8 czêsci okrêgu
	// ze wzglêdu na podwójne obliczanie tych punktów
	
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

// Rysowanie bitmapy
void SH1106_Bitmap(const SH1106_Bitmap_t * Bitmap) {
	uint16_t Address;
	//uint8_t Page = Pages - 1;
	uint8_t Page = Bitmap->Height / SH1106_PAGE_HEIGHT - 1;
	
	uint8_t CursorX_Old = SH1106_CursorX;
	uint8_t CursorL_Old = SH1106_CursorP;
	
	do {
		// Podcz¹tkowy offset adresu
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
		
		// Czy to by³a ostatnia strona
		if(Page == 0) {
			// To by³a ostatnia strona
			
			// Kursor strony ustawiamy tam gdzie by³ na pocz¹tku, jeœli znak by³ na wielu stronach
			if(Bitmap->Height / SH1106_PAGE_HEIGHT > 1) {
				SH1106_CursorPageSet(CursorL_Old);
			}
			
			// Kursor X ustawiamy na koniec znaku
			SH1106_CursorX = CursorX_Old + Bitmap->Width;
			if(SH1106_CursorX >= SH1106_DISPLAY_SIZE_X) {
				SH1106_CursorX = SH1106_CursorX - SH1106_DISPLAY_SIZE_X;
			}
		}
		else {
			// To nie by³a jeszcze ostatnia strona
			
			// Cofamy kursor na pocz¹tek
			SH1106_CursorXSet(CursorX_Old);
			
			// Przesuwamy kursor o jedn¹ stronê ni¿ej
			SH1106_CursorPageSet(SH1106_CursorP + 1);
		}
	} while(Page--);
}

// Odczytanie aktualnie ustawionej czcionki
const SH1106_FontDef_t * SH1106_FontGet(void) {
	return SH1106_Font;
}

// Ustawienie czcionki
void SH1106_FontSet(const SH1106_FontDef_t * Font) {
	SH1106_Font = Font;
}

// Wyœwietlanie znaku
void SH1106_PrintChar(uint8_t Char) {
	
	// Kontrola czy ¿¹dany znak znajduje siê w tablicy
	if(Char < SH1106_Font->FirstChar) Char = SH1106_Font->LastChar;
	if(Char > SH1106_Font->LastChar) Char = SH1106_Font->LastChar;
	
	// Offset znaku, bo tablica bitmap nie musi zawieraæ wszystkich znaków ASCII od zera
	Char = Char - SH1106_Font->FirstChar;
	
	// Okreœlenie szerokoœci znaku oraz jego po³o¿enia w tabeli bitmap
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
	
	// Je¿eli Addres = 0 i Szerokoœæ = 0 to znaczy, ¿e taki znak nie jest zdefiniowany, wiêc wyœwietlamy BadChar (ostatni znak z tabeli)
	if((Address == 0) && (Width == 0)) {
		Char = SH1106_Font->LastChar - SH1106_Font->FirstChar;
		Address = SH1106_Font->Descriptors[Char].Offset;
		Width = SH1106_Font->Descriptors[Char].Width;
	}
	
	// Aktualna pozycja kursora
	uint8_t CursorX_Old = SH1106_CursorX;
	uint8_t CursorL_Old = SH1106_CursorP;
	uint16_t Address_Old = Address;
	
	// Iterator pêtli wyœwietlaj¹cej wszystkie strony po kolei
	uint8_t Linia = Height - 1;
	
	// Wyœwietlamy po kolei wszystkie czêsci znaku w kolejnych stronach wyœwietlacza
	do {
		
		// Offset adresu dla znaków wielostronowych (wysokoœæ > 8 pikseli)
		Address = Address + Linia;
		
		// Wyœwietlanie czêœci znaku w³aœciwej dla tej strony
			#if SH1106_USE_I2C
				I2C_Start(SH1106_ADDRESS_WRITE);
				I2C_Write(SH1106_DATA_BYTE);
				
				// Znak
				for(uint8_t i=0; i<Width; i++) {
					I2C_Write(SH1106_Color ? SH1106_Font->Bitmaps[Address] : ~SH1106_Font->Bitmaps[Address]);
					Address = Address + Height;
				}
				
				// Odstêp miêdzy znakami
				for(uint8_t i = SH1106_Font->Spacing; i; i--) {
					I2C_Write(SH1106_Color ? 0x00 : 0xFF);
				}
				I2C_Stop();
			#endif
			
			#if SH1106_USE_SPI
				SH1106_CHIP_SELECT;
				SH1106_DC_DATA;
				
				// Znak
				for(uint8_t i=0; i<Width; i++) {
					Spi_1(SH1106_Color ? SH1106_Font->Bitmaps[Address] : ~SH1106_Font->Bitmaps[Address]);
					Address = Address + Height;
				}
				//Spi_1(Negative ? ~SH1106_Font.Bitmaps[Address] : SH1106_Font.Bitmaps[Address]);
				Address = Address + Height;
				
				// Odstêp miêdzy znakami
				for(uint8_t i = SH1106_Font->Spacing; i; i--) {
					Spi_1(SH1106_Color ? 0x00 : 0xFF);
				}
				
				SH1106_CHIP_DESELECT;
			#endif
		
		// Czy to by³a ostatnia strona
		if(Linia == 0) {
			// To by³a ostatnia strona
			
			// Kursor strony ustawiamy tam gdzie by³ na pocz¹tku, jeœli znak by³ na wielu stronach
			if(Height > 1) {
				SH1106_CursorPageSet(CursorL_Old);
			}
			
			// Kursor X ustawiamy na koniec znaku
			SH1106_CursorX = CursorX_Old + Width + SH1106_Font->Spacing;
			if(SH1106_CursorX >= SH1106_DISPLAY_SIZE_X) {
				SH1106_CursorX = SH1106_CursorX - SH1106_DISPLAY_SIZE_X;
			}
		}
		else {
			// To nie by³a jeszcze ostatnia strona
			
			// Cofamy kursor na pocz¹tek
			SH1106_CursorXSet(CursorX_Old);
			
			// Przesuwamy kursor o jedn¹ stronê ni¿ej
			SH1106_CursorPageSet(SH1106_CursorP + 1);
			
			// Cofamy licznik adresu
			Address = Address_Old;
		}
	} while(Linia--);		// Powtarzaj dopóki zosta³y jeszcze strony do wysweitlenia
}

// Wylicza d³ugoœæ napisu w pikselach w zale¿noœci od wybranej czcionki
uint16_t SH1106_TextWidth(const char * Text) {
	uint16_t Width = 0;
	uint16_t Offset = SH1106_Font->FirstChar;
	
	// Sprawdzenie czy czcionka ma sta³¹ szerokoœæ znaku
	if(SH1106_Font->Width) {
		// Czcionka o sta³ej szerokoœci znaków
		
		// Zliczanie iloœci znaków
		while(*Text++) Width++;
		
		// Odtsêp za ka¿dym znakiem
		Width = Width + SH1106_Font->Spacing;
		
		// Mno¿enie przez sta³¹ szerokoœæ znaku
		Width = Width * (SH1106_Font->Width);
	}
	else {
		// Czcionka o zmiennej szerokoœci znaków
		while(*Text) {
			Width += SH1106_Font->Descriptors[(*Text) - Offset].Width + SH1106_Font->Spacing;			
			Text++;
		}
	}
	
	return Width;
}

// Pisanie tekstu. Wczeœniej wybraæ czcionkê!
void SH1106_Text(const char * Text, SH1106_align_t Align) {
	
	// Ustawienie pozycji kursora w zale¿noœci od wyrównania tekstu
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
	
	// Wyœwietlenie tekstu
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

void SH1106_Fill(void) {
	SH1106_Clear(0xFF);
}

#endif
