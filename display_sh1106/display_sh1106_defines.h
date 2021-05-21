#ifndef DISPLAY_SH1106_DEFINES_H_
#define DISPLAY_SH1106_DEFINES_H_

// ========================================
// Basic constants
// ========================================

#define		SH1106_DISPLAY_SIZE_X			128
#define		SH1106_DISPLAY_SIZE_Y			64
#define		SH1106_PAGE_HEIGHT				8
#define		SH1106_PAGE_COUNT				8
#define		SH1106_OFFSET_X					2			// Offset poziomy - ustawi� je�li matryca OLED jest przesuni�ta wgl�dem wsp�rz�dnych sterownika

// ========================================
// Display operation codes
// ========================================

// Polecenia o d�ugo�c 1 bajta s� zrealizowane jako definicje, kt�re nale�y wywo�a� poprzez SH1106_WriteCommand()
#define		SH1106_COLUMN_LOW(Nibble)		(0x00 | (Nibble))			// 01, m�odsze 4 bity pozycji X
#define		SH1106_COLUMN_HIGH(Nibble)		(0x10 | (Nibble))			// 02, starsze 4 bity pozycji X
#define		SH1106_PUMP_VOLTAGE(Value)		(0x30 | (Value))			// 03, napi�cie przetwornicy, domy�lne 10, zakres od 0x00..0x03
#define		SH1106_START_LINE(Line)			(0x40 | (Line))				// 04, offset pionowy, wi�kszanie powoduje przesuwanie w g�r�, zakres 0..63
#define		SH1106_CONTRAST					0x81						// 05, kontrast nale�y poda� w kolejnym bajcie (0...255)
#define		SH1106_REMAP(ADC)				(0xA0 | (ADC))				// 06, 1 wy�wietla praiwd�owo, 0 lustrzane odbicie
#define		SH1106_ENTRIE_DISPLAY_ON(On)	(0xA4 | (On))				// 07, 1 ca�y wy�wietlacz bia�y, 0 normalna praca
#define		SH1106_NORMAL_REVERSE(Select)	(0xA6 | (Select))			// 08, 1 negatyw, 0 pozytyw
#define		SH1106_MULTIPLEX_RATIO			0xA8						// 09, warto�� w kolejnym bajcie
#define		SH1106_DCDC_ON_OFF				0xAD						// 10, warto�� w kolejnym bajcie
#define		SH1106_DISPLAY_ON_OFF(Select)	(0xAE | (Select))			// 11, 1 wy�wietlacz w��czony, 0 wy��czony
#define		SH1106_DISPLAY_ON				0xAF						// 11, to samo co wy�ej, ale ju� z wpisanym argumentem
#define		SH1106_DISPLAY_OFF				0xAE						// 11, to samo co wy�ej, ale ju� z wpisanym argumentem
#define		SH1106_PAGE(Page)				(0xB0 | (Page))				// 12, numer linii licz�c od g�ry
#define		SH1106_SCAN_DIRECTION(Value)	(0xC0 | (Value))			// 13, 1 skanowanie od COM63 do COM0, 0 od COM0 do COM63
#define		SH1106_DISPLAY_OFFSET			0xD3						// 14, argument w kolejnym bajcie, zakres 0..63
#define		SH1106_CLOCK_DIV_FREQ			0xD5						// 15, argument w kolejnym bajcie, czyta� datasheet
#define		SH1106_CHARGE_PERIOD			0xD9						// 16, argument w kolejnym bajcie, czyta� datasheet
#define		SH1106_COMMON_PADS_HW_CONFIG	0xDA						// 17, argument w kolejnym bajcie, czyta� datasheet
#define		SH1106_VCOM_DESELECT_LEVEL		0xDB						// 18, argument w kolejnym bajcie, czyta� datasheet
#define		SH1106_READ_MODIFY_WRITE		0xE0						// 19, umo�liwia odczytanie danych z wy�wietlacza
#define		SH1106_END						0xEE						// 20, ko�czy operacj� w trybie read-modify-write
#define		SH1106_NOP						0xE3						// 21
#define		SH1106_CHARGE_PUMP				0x8D						// polecenie, kt�ego nie ma w datasheecie

// Komendy steruj�ce I2C - decyduj� czy nast�pny przes�any bajt to dane do wy�wietlenia czy polecenie
#if SH1106_USE_I2C
	#define SH1106_COMMAND_BYTE				0x80
	#define SH1106_DATA_BYTE				0x40
	#define SH1106_CoDATA_BYTE				0xC0
#endif

// ========================================
// Text and fonts
// ========================================

enum SH1106_align_t {
	SH1106_AlignNone,
	SH1106_AlignLeft,
	SH1106_AlignRight,
	SH1106_AlignCenter
};

// Struktura d�ugo�ci i offset�w znak�w w tabeli bitmap
struct SH1106_CharDef_t {
	uint8_t		Width;						// Szeroko�� znaku w pikselach
	uint16_t	Offset;						// Adres w tablicy bitmap
};

// Struktura definicji czcionki
struct SH1106_FontDef_t {
	uint8_t Height;							// Wysoko�� zanku w liniach po 8 pixeli
	uint8_t Width;							// Je�eli czcionka ma sta�� szeroko��, je�li nie to =0
	uint8_t Spacing;						// Odst�p mi�dzy znakami
	uint8_t FirstChar;						// Pierwszy znak, jaki znajduje si� w tablicy Bitmaps
	uint8_t LastChar;						// Ostatni znak, jaki znajduje si� w tablicy Bitmaps
	const SH1106_CharDef_t * Descriptors;		// Tablica szeroko�ci i offset�w, je�li Width jest ustalone to wstawi� NULL
	const uint8_t * Bitmaps;				// Tablica znak�w
};

// ========================================
// Bitmaps
// ========================================

// Bitmap definition
struct SH1106_Bitmap_t {
	const uint8_t Height;						// Height in pixels
	const uint8_t Width;						// Width in pixels
	const uint8_t * Array;						// Pointer to bitmap array
};

// ========================================
// Other stuff
// ========================================




#endif /* DISPLAY_SH1106_DEFINES_H_ */