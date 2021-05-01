// Wersja 0.15

#if COMPONENT_DISPLAY_SSD1351

#include	"display_ssd1351.h"

// Zmienne globalne
static uint8_t SSD1351_CursorX			= 0;
static uint8_t SSD1351_CursorX_Max		= SSD1351_DISPLAY_SIZE_X - 1;
static uint8_t SSD1351_CursorY			= 0;
static uint8_t SSD1351_CursorY_Max		= SSD1351_DISPLAY_SIZE_Y - 1;

const static fontXF90_def_t * SSD1351_Font;
static uint8_t SSD1351_ColorFrontH		= 0xFF;		// Bia�y
static uint8_t SSD1351_ColorFrontL		= 0xFF;
static uint8_t SSD1351_ColorBackH		= 0x00;		// Czarny
static uint8_t SSD1351_ColorBackL		= 0x00;

// Konfiguracja wy�wietlacza dla funkcji SH1106_Init()
static const uint8_t SSD1351_InitSequence[] = {
	1,	SSD1351_SET_LOCK_COMMAND,
	0,	0x12,

	1,	SSD1351_SET_LOCK_COMMAND,			// Command lock
	0,	0xB1,								// Command A2,B1,B3,BB,BE,C1 accessible if in unlock state

	1,	SSD1351_SLEEP_MODE_ON,				// Display off

	1, SSD1351_SET_DISPLAY_MODE_OFF,		// Normal Display mode

	1, SSD1351_COLUMN_RANGE,				// Set column address
	0, 0x00,								// Column address start 00
	0, 0x7F,								// Column address end 95

	1, SSD1351_ROW_RANGE,					// Set row address
	0, 0x00,								// Row address start 00
	0, 0x7f,								// Row address end 63

	1, SSD1351_CLOCK_DIVIDER_OSC_FREQ,
	0, 0xF1,

	1, SSD1351_SET_MUX_RATIO,
	0, 0x7F,

	1, SSD1351_REMAP_COLOR_DEPTH,			// Set re-map & data format
	0, 0b01110101,							// Vertical address increment 0b01110101
											// bit 0 - 1: kursor od lewej do prawej, 1 od g�ry do do�u
											// bit 1 - lustrzane odbicie Y
											// bit 2 - zamiana kolor�w
											// bit 3 - nieu�ywany
											// bit 4 - lustrzane odbicie X
											// bit 5 - naprzemienne linie (nie u�ywa�)
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
	0, 0xFF,								// Oryginalnie 0xC8
	0, 0xFF,								// Oryginalnie 0x80
	0, 0xFF,								// Oryginalnie 0xC0

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

	1, SSD1351_SLEEP_MODE_OFF,				// Display on
};

// ===================
// Funckje elementarne
// ===================


// Inicjalizacja
void SSD1351_Init(void) {

	SSD1351_CS_PORT	|=	SSD1351_CS_PIN;
	SSD1351_CS_DIR	|=	SSD1351_CS_PIN;
	SSD1351_DC_DIR	|=	SSD1351_DC_PIN;

	const uint8_t * Index = SSD1351_InitSequence;
	const uint8_t * Limit = SSD1351_InitSequence + sizeof(SSD1351_InitSequence);

	SSD1351_CHIP_SELECT;

	// Przesy��nie tablicy SSD1351_InitSequence
	// Bajt nieparzysty ukre�la czy jak ustawi� pin steruj�cy DC (dane lub polecenie)
	// Bajt parzysty ma zosta� przes�any przez SPI
	while(Index != Limit) {
		if(*Index++) SSD1351_DC_COMMAND;
		else SSD1351_DC_DATA;
		Spi_1(*Index++);
	}
	
	SSD1351_CHIP_DESELECT;
}


// Wys�anie komendy
void SSD1351_WriteCommand(const uint8_t Command) {
	SSD1351_CHIP_SELECT;
	SSD1351_DC_COMMAND;
	Spi_1(Command);
	SSD1351_CHIP_DESELECT;
}


// Wys�anie danych
void SSD1351_WriteData(const uint8_t Data) {
	SSD1351_CHIP_SELECT;
	SSD1351_DC_DATA;
	Spi_1(Data);
	SSD1351_CHIP_DESELECT;
}


// Zezwolenie na wy�wietlanie otrzymanych danych
void SSD1351_WriteRamEnable(void) {
	SSD1351_CHIP_SELECT;
	SSD1351_DC_COMMAND;
	Spi_1(SSD1351_RAM_WRITE);
	SSD1351_CHIP_DESELECT;	
}


// Ustawianie kontrastu
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


// Czyszczenie wy�wietlacza
void SSD1351_Clear(void) {

	// Ustawienie obszaru aktywnego na ca�y wy�wietlacz
	SSD1351_ActiveAreaSet(0, SSD1351_DISPLAY_SIZE_X-1, 0, SSD1351_DISPLAY_SIZE_Y-1);
	
	// Zape�nienie pikselami o kolorze t�a
	SSD1351_CHIP_SELECT;
	Spi_Repeat(SSD1351_ColorBackH, SSD1351_ColorBackL, SSD1351_DISPLAY_SIZE_X * SSD1351_DISPLAY_SIZE_Y);
	SSD1351_CHIP_DESELECT;
}


// Szachownica na ca�y wy�wietlacz
void SSD1351_Chessboard(void) {

	// Zakres osi X od 0 do 127
	SSD1351_ActiveAreaXSet(0, SSD1351_DISPLAY_SIZE_X-1);

	// Zakres osi Y od 0 do 127
	for(uint8_t y=0; y<SSD1351_DISPLAY_SIZE_Y; y++) {
		SSD1351_ActiveAreaYSet(y, y);
		SSD1351_CHIP_SELECT;
		if(y & 0x01) {
			// Linie nieparzyste
			for(uint8_t x=0; x<(SSD1351_DISPLAY_SIZE_X/2); x++) {
				Spi_4(0xFF, 0xFF, 0x00, 0x00);
			}
		}
		else {
			// Linie parzyste
			for(uint8_t x=0; x<(SSD1351_DISPLAY_SIZE_X/2); x++) {
				Spi_4(0x00, 0x00, 0xFF, 0xFF);
			}
		}
		SSD1351_CHIP_DESELECT;
	}

	SSD1351_ActiveAreaSet(0, SSD1351_DISPLAY_SIZE_X-1, 0, SSD1351_DISPLAY_SIZE_Y-1);
}

// ===============
// Pozycja kursora
// ===============

// Ustawienie pozycji XY
void SSD1351_CursorSet(uint8_t x, uint8_t y) {
	SSD1351_CursorX = x < SSD1351_DISPLAY_SIZE_X ? x : SSD1351_DISPLAY_SIZE_X-1;
	SSD1351_CursorY = y < SSD1351_DISPLAY_SIZE_Y ? y : SSD1351_DISPLAY_SIZE_Y-1;
}

// Odczytanie pozycji X
uint8_t SSD1351_CursorXGet(void) {
	return SSD1351_CursorX;
}


// Ustawienie pozycji X
void SSD1351_CursorXSet(uint8_t x) {
 	SSD1351_CursorX = x < SSD1351_DISPLAY_SIZE_X ? x : SSD1351_DISPLAY_SIZE_X-1;
}


// Odczytanie pozycji Y
uint8_t SSD1351_CursorYGet(void) {
	return SSD1351_CursorY;
}


//Ustawienie pozycji Y
void SSD1351_CursorYSet(uint8_t y) {
 	SSD1351_CursorY = y < SSD1351_DISPLAY_SIZE_Y ? y : SSD1351_DISPLAY_SIZE_Y-1;
}


// Ustawianie aktywnego obszaru, by zape�ni� go pikselami
void SSD1351_ActiveAreaSet(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2) {
	
	// Kontrola
	SSD1351_CursorX			= x1 < SSD1351_DISPLAY_SIZE_X ? x1 : SSD1351_DISPLAY_SIZE_X-1;
	SSD1351_CursorX_Max		= x2 < SSD1351_DISPLAY_SIZE_X ? x2 : SSD1351_DISPLAY_SIZE_X-1;
	SSD1351_CursorY			= y1 < SSD1351_DISPLAY_SIZE_Y ? y1 : SSD1351_DISPLAY_SIZE_Y-1;
	SSD1351_CursorY_Max		= y2 < SSD1351_DISPLAY_SIZE_Y ? y2 : SSD1351_DISPLAY_SIZE_Y-1;

	// Przes�anie do wy�wietlacza
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


// Ustawianie aktywnego obszaru tylko w X, by zape�ni� go pikselami
void SSD1351_ActiveAreaXSet(uint8_t x1, uint8_t x2) {
	
	// Kontrola
	SSD1351_CursorX			= x1 < SSD1351_DISPLAY_SIZE_X ? x1 : SSD1351_DISPLAY_SIZE_X-1;
	SSD1351_CursorX_Max		= x2 < SSD1351_DISPLAY_SIZE_X ? x2 : SSD1351_DISPLAY_SIZE_X-1;

	// Przes�anie do wy�wietlacza
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


// Ustawianie aktywnego obszaru tylko w Y, by zape�ni� go pikselami
void SSD1351_ActiveAreaYSet(uint8_t y1, uint8_t y2) {
	
	// Kontrola
	SSD1351_CursorY			= y1 < SSD1351_DISPLAY_SIZE_Y ? y1 : SSD1351_DISPLAY_SIZE_Y-1;
	SSD1351_CursorY_Max		= y2 < SSD1351_DISPLAY_SIZE_Y ? y2 : SSD1351_DISPLAY_SIZE_Y-1;

	// Przes�anie do wy�wietlacza
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


// ===============
// Kolory
// ===============

// Pobranie koloru pierwszego planu
uint16_t SSD1351_ColorFrontGet(void) {
	return (uint16_t)SSD1351_ColorFrontH << 8 | SSD1351_ColorFrontL;
}


// Ustawienie koloru t�a poprzed podabie warto�ci RGB w formacie 565
void SSD1351_ColorFrontSet(uint16_t ColorRGB565) {
	SSD1351_ColorFrontH = (uint8_t)(ColorRGB565 >> 8);
	SSD1351_ColorFrontL = (uint8_t)(ColorRGB565 & 0x00FF);
}


// Ustawienie kolrou pierwszego planu poprzed podanie warto�ci RGB ka�dej osobno
void SSD1351_ColorFrontSet(uint8_t R, uint8_t G, uint8_t B) {
	
	// Skr�cenie warto�ci RGB do warto�ci obs�ugiwanych przez wy�wietlacz (RGB565)
	R = R & 0b11111000;
	G = G & 0b11111100;
	B = B & 0b11111000;

	// Sk�adanie zmiennej koloru
	SSD1351_ColorFrontH = R | (G >> 5);
	SSD1351_ColorFrontL = (G << 3) | (B >> 3);
}


// Pobranie koloru pierwszego planu
uint16_t SSD1351_ColorBackGet(void) {
	return (uint16_t)SSD1351_ColorBackH << 8 | SSD1351_ColorBackL;
}


// Ustawienie koloru t�a poprzed podabie warto�ci RGB w formacie 565
void SSD1351_ColorBackSet(uint16_t ColorRGB565) {
	SSD1351_ColorBackH = (uint8_t)(ColorRGB565 >> 8);
	SSD1351_ColorBackL = (uint8_t)(ColorRGB565 & 0x00FF);
}


// Ustawienie kolrou t�a poprzed podanie warto�ci RGB ka�dej osobno
void SSD1351_ColorBackSet(uint8_t R, uint8_t G, uint8_t B) {
	
	// Skr�cenie warto�ci RGB do warto�ci obs�ugiwanych przez wy�wietlacz (RGB565)
	R = R & 0b11111000;
	G = G & 0b11111100;
	B = B & 0b11111000;

	// Sk�adanie zmiennej koloru
	SSD1351_ColorBackH = R | (G >> 5);
	SSD1351_ColorBackL = (G << 3) | (B >> 3);
}

// Konwersja nazwy lub ID kolrou na warto�� RGB565
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


// Konwersja RGB888 na RGB565
uint16_t SSD1351_ColorRGB888toRGB565(uint8_t R, uint8_t G, uint8_t B) {
	
	// Skr�cenie warto�ci RGB do warto�ci obs�ugiwanych przez wy�wietlacz (RGB565)
	R = R & 0b11111000;
	G = G & 0b11111100;
	B = B & 0b11111000;

	// Sk�adanie zmiennej koloru
	uint8_t ColorH = R | (G >> 5);
	uint8_t ColorL = (G << 3) | (B >> 3);

	return ((uint16_t)ColorH << 8) | ColorL;
}


// Konwersja RGB
uint16_t SSD1351_ColorRGB332toRGB565(uint8_t Color332) {

	// Tabele konwersji palety
	const uint8_t b3to6lookup[8] = {0, 9, 18, 27, 36, 45, 54, 63};
	const uint8_t b3to5lookup[8] = {0, 4, 9, 13, 18, 22, 27, 31};
	const uint8_t b2to5lookup[4] = {0, 10, 21, 31};

	uint16_t red, green, blue;
	
	red = (Color332 & 0xe0) >> 5;		// rgb332 3 red bits now right justified
	red = (uint16_t)b3to5lookup[red];		// 3 bits converted to 5 bits
	red = red << 11;			// red bits now 5 MSB bits
	
	green = (Color332 & 0x1c) >> 2;		// rgb332 3 green bits now right justified
	green = (uint16_t)b3to6lookup[green];	// 3 bits converted to 6 bits
	green = green << 5;			// green bits now 6 "middle" bits
	
	blue = Color332 & 0x03;			// rgb332 2 blue bits are right justified
	blue = (uint16_t)b2to5lookup[blue];	// 2 bits converted to 5 bits, right justified
	
	return (uint16_t)(red | green | blue);
}


// ====================================
// Funkcje rysuj�ce figury geometryczne
// ====================================


// Rysowanie piksela
void SSD1351_DrawPixel(uint8_t x, uint8_t y) {
	SSD1351_ActiveAreaSet(x, x, y, y);
	SSD1351_CHIP_SELECT;
	Spi_2(SSD1351_ColorFrontH, SSD1351_ColorFrontL);
	SSD1351_CHIP_DESELECT;
}


// Linia pozioma
void SSD1351_DrawLineHorizontal(uint8_t x0, uint8_t y0, uint8_t Length) {
	// Rysuje lini� poziom� od punktu (x0,y0) w prawo.

	SSD1351_ActiveAreaSet(x0, x0 + Length - 1, y0, y0);
	SSD1351_CHIP_SELECT;
	Spi_Repeat(SSD1351_ColorFrontH, SSD1351_ColorFrontL, Length);
	SSD1351_CHIP_DESELECT;
}


// Linia pionowa
void SSD1351_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length) {
	// Rysuje lini� pionow� od punktu (X,Y) w d�.

	SSD1351_ActiveAreaSet(x0, x0, y0, y0 + Length - 1);
	SSD1351_CHIP_SELECT;
	Spi_Repeat(SSD1351_ColorFrontH, SSD1351_ColorFrontL, Length);
	SSD1351_CHIP_DESELECT;
}


// Linia pod dowolnym k�tem algorytmem Bresenhama
// Je�li trzeba narysowa� lini� pionow� lub poziom� to u�ywa� funkcji LineHorizontal lub LineVertica, bo dzia�aj� szybciej
void SSD1351_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {

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


//  Prostok�t bez wype�nienia
void SSD1351_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	SSD1351_DrawLineVertical(x0, y0, y1-y0+1);
	SSD1351_DrawLineVertical(x1, y0, y1-y0+1);
	SSD1351_DrawLineHorizontal(x0+1, y0, x1-x0-1);
	SSD1351_DrawLineHorizontal(x0+1, y1, x1-x0-1);
}
	

// Prostok�t z wype�nieniem
void SSD1351_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	for(uint8_t y=y0; y<=y1; y++) {
		SSD1351_DrawLineHorizontal(x0, y, y1-y0+1);
	}
}


// Okr�g
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

// =======
// Bitmapy
// =======

// Rysowanie bitmapy monochromatycznej
// Kolor pierwszego planu, kolor t�a, wsp�rz�dnie XY ustawi� przed wywo�aniem SSD1351_BitmapMono()
void SSD1351_BitmapMono(const BitmapXF90_t * Bitmap) {
	
	// Odczytanie rozmiaru bitmapy
	uint8_t WidthPixels = Bitmap->Width;
	uint8_t HeightPixels = Bitmap->Height;

	// Ustawienie obszaru roboczego
	SSD1351_ActiveAreaSet(SSD1351_CursorX, SSD1351_CursorX + WidthPixels - 1, SSD1351_CursorY, SSD1351_CursorY + HeightPixels - 1);

	// P�tla kolumn
	uint8_t Buffer = 0;
	uint16_t Address = 0;
	SSD1351_CHIP_SELECT;
	for(uint8_t ActualColumn = 0; ActualColumn < WidthPixels; ActualColumn++) {

		uint8_t ActualRow = HeightPixels;
		uint8_t BitMask = 0;

		// P�tla wierszy
		while(ActualRow--) {
			if(BitMask == 0) {
				BitMask = 0b10000000;
				//Buffer = Bitmap[Address++];
				Buffer = Bitmap->Bitmaps[Address++];
			}

			if(Buffer & BitMask) {
				// Kolor pierwszoplanowy
				Spi_2(SSD1351_ColorFrontH, SSD1351_ColorFrontL); 
			}
			else {
				// Kolor t�a
				Spi_2(SSD1351_ColorBackH, SSD1351_ColorBackL);
			}

			// Przesuni�cie maski bitowej
			BitMask = BitMask >> 1;
		}
	}
	SSD1351_CHIP_DESELECT;
}


// Rysowanie bitmapy kolorowej w RGB565
// Kolor pierwszego planu, kolor t�a, wsp�rz�dnie XY ustawi� przed wywo�aniem SSD1351_BitmapMono()
void SSD1351_BitmapRGB565(const BitmapXF90_t * Bitmap) {
	
	// Odczytanie rozmiaru bitmapy
	uint8_t WidthPixels = Bitmap->Width;
	uint8_t HeightPixels = Bitmap->Height;

	// Ustawienie obszaru roboczego
	SSD1351_ActiveAreaSet(SSD1351_CursorX, SSD1351_CursorX + WidthPixels - 1, SSD1351_CursorY, SSD1351_CursorY + HeightPixels - 1);

	// Rysowanie pikseli
	SSD1351_CHIP_SELECT;
	Spi_Write(Bitmap->Bitmaps, WidthPixels * HeightPixels * 2);
	SSD1351_CHIP_DESELECT;
}


// Rysowanie bitmapy kolorowej w RGB332
// Kolor pierwszego planu, kolor t�a, wsp�rz�dnie XY ustawi� przed wywo�aniem SSD1351_BitmapMono()
void SSD1351_BitmapRGB332(const BitmapXF90_t * Bitmap) {
	
	// Odczytanie rozmiaru bitmapy
	uint8_t WidthPixels = Bitmap->Width;
	uint8_t HeightPixels = Bitmap->Height;
	uint16_t Size = WidthPixels * HeightPixels;
	uint16_t Color565;
	const uint8_t * BitmapPointer = Bitmap->Bitmaps;

	// Ustawienie obszaru roboczego
	SSD1351_ActiveAreaSet(SSD1351_CursorX, SSD1351_CursorX + WidthPixels - 1, SSD1351_CursorY, SSD1351_CursorY + HeightPixels - 1);

	// Rysowanie pikseli
	SSD1351_CHIP_SELECT;
	while(Size--) {
		Color565 = SSD1351_ColorRGB332toRGB565(*BitmapPointer++);
		Spi_2(Color565 >> 8, Color565 & 0xFF);
	}
	SSD1351_CHIP_DESELECT;

}


// =================
// Czcionki i napisy
// =================


// Odczytanie aktualnie ustawionej czcionki
const fontXF90_def_t * SSD1351_FontGet(void) {
	return SSD1351_Font;
}


// Ustawienie czcionki
// U�ycie: SSD1351_FontSet(&FontXF90_NazwaCzcionki);  <- pami�ta� o &
void SSD1351_FontSet(const fontXF90_def_t * Font) {
	SSD1351_Font = Font;
}


// Wy�wietlanie znaku
// Zmienna Negative jest opcjonalna, warto�� inna ni� 0 powoduje negacj� koloru
void SSD1351_PrintChar(uint8_t Char, uint8_t Negative) {

	// Kontrola czy ��dany znak znajduje si� w tablicy
	if(Char < SSD1351_Font->FirstChar) Char = SSD1351_Font->LastChar;
	if(Char > SSD1351_Font->LastChar) Char = SSD1351_Font->LastChar;
	
	// Offset znaku, bo tablica bitmap nie musi zawiera� wszystkich znak�w ASCII od zera
	Char = Char - SSD1351_Font->FirstChar;
	
	// Okre�lenie szeroko�ci znaku oraz jego po�o�enia w tabeli bitmap
	uint8_t Width;
	uint8_t Height = SSD1351_Font->Height;
	uint8_t Spacing = SSD1351_Font->Spacing;
	uint16_t Address;
	if(SSD1351_Font->Width > 0) {
		// Dla czcionki o sta�ej szeroko�ci znaku
		Width = SSD1351_Font->Width;
		Address = Char * Width * (Height/8);
	}
	else {
		// Dla czcionki o zmiennej szeroko�ci znaku
		Width = SSD1351_Font->Descriptors[Char].Width;
		Address = SSD1351_Font->Descriptors[Char].Offset;
	}

	// Je�eli Addres = 0 i Szeroko�� = 0 to znaczy, �e taki znak nie jest zdefiniowany, wi�c wy�wietlamy BadChar (ostatni znak z tabeli)
	if((Address == 0) && (Width == 0)) {
		Char = SSD1351_Font->LastChar - SSD1351_Font->FirstChar;
		Address = SSD1351_Font->Descriptors[Char].Offset;
		Width = SSD1351_Font->Descriptors[Char].Width;
	}

	// Obszar roboczy
	SSD1351_ActiveAreaSet(SSD1351_CursorX, SSD1351_CursorX + Width + Spacing - 1, SSD1351_CursorY, SSD1351_CursorY + Height - 1);

	// Wysy�anie pikseli
	uint8_t Buffer = 0;
	SSD1351_CHIP_SELECT;
	
	// P�tla kolumn tylko dla znaku (spacing b�dzie w kolejnej p�tli)
	for(uint8_t ActualColumn = 0; ActualColumn < Width; ActualColumn++) {

		uint8_t ActualRow = Height;
		uint8_t BitMask = 0;

		// P�tla wierszy
		while(ActualRow--) {
			if(BitMask == 0) {
				BitMask = 0b10000000;
				Buffer = SSD1351_Font->Bitmaps[Address++];
			}

			if(Buffer & BitMask) {
				// Kolor pierwszoplanowy
				if(Negative) Spi_2(SSD1351_ColorBackH, SSD1351_ColorBackL);
				else Spi_2(SSD1351_ColorFrontH, SSD1351_ColorFrontL);
			}
			else {
				// Kolor t�a
				if(Negative) Spi_2(SSD1351_ColorFrontH, SSD1351_ColorFrontL);
				else Spi_2(SSD1351_ColorBackH, SSD1351_ColorBackL);
			}

			// Przesuni�cie maski bitowej
			BitMask = BitMask >> 1;
		}
	}

	// Spacing
	for(uint8_t Column = 0; Column < Spacing; Column++) {
		for(uint8_t i=0; i<Height; i++) {
			if(Negative) Spi_2(SSD1351_ColorFrontH, SSD1351_ColorFrontL);
			else Spi_2(SSD1351_ColorBackH, SSD1351_ColorBackL);
		}
	}

	// Koniec transmisji
	SSD1351_CHIP_DESELECT;

	// Ustawienie kursora na koniec znaku
	SSD1351_CursorX = SSD1351_CursorX + Width + Spacing;
	if(SSD1351_CursorX > SSD1351_DISPLAY_SIZE_X) {
		SSD1351_CursorX = SSD1351_CursorX - SSD1351_DISPLAY_SIZE_X;
	}
}


// Wylicza d�ugo�� napisu w pikselach w zale�no�ci od wybranej czcionki
uint8_t SSD1351_TextWidth(const char * Text) {
	uint8_t Width = 0;
	uint16_t Offset = SSD1351_Font->FirstChar;

	// Sprawdzenie czy czcionka ma sta�� szeroko�� znaku
	if(SSD1351_Font->Width) {
		// Czcionka o sta�ej szeroko�ci znak�w

		// Zliczanie ilo�ci znak�w
		while(*Text++) Width++;

		// Odts�p za ka�dym znakiem		(!! sprawdzi� to i poprawi� w SH1106)
		//Width = Width + SSD1351_Font.Spacing;

		// Mno�enie przez sta�� szeroko�� znaku
		Width = Width * (SSD1351_Font->Width + SSD1351_Font->Spacing);						
	}
	else {
		// Czcionka o zmiennej szeroko�ci znak�w
		while(*Text) {
			Width += SSD1351_Font->Descriptors[(*Text) - Offset].Width + SSD1351_Font->Spacing;			
			Text++;
		}
	}
	
	return Width;
}


// Pisanie tekstu. Wcze�niej wybra� czcionk�!
void SSD1351_Text(const char * Text, uint8_t Align, uint8_t Negative) {
	
	// Ustawienie pozycji kursora w zale�no�ci od wyr�wnania tekstu
	uint8_t Width = SSD1351_TextWidth(Text);
	uint8_t Height = SSD1351_Font->Height;

	// M�odszy nibble oznacza wyr�wnanie poziome
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

	// Starszy nibble oznacza wyr�wnanie pionowe
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

	// Wy�wietlenie tekstu
		while(*Text) SSD1351_PrintChar(*Text++, Negative);
}

#endif
