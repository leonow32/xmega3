#ifndef DISPLAY_SSD1309_DEFINES_H_
#define DISPLAY_SSD1309_DEFINES_H_

// ========================================
// Basic constants
// ========================================

#define		SSD1309_DISPLAY_SIZE_X			128
#define		SSD1309_DISPLAY_SIZE_Y			64
#define		SSD1309_PAGE_HEIGHT				8
#define		SSD1309_PAGE_COUNT				8
#define		SSD1309_OFFSET_X					2			// Horizontal offset - change this if the image doesn't appear on the center of the screen

// ========================================
// Display operation codes
// ========================================

// Polecenia o d³ugoœc 1 bajta s¹ zrealizowane jako definicje, które nale¿y wywo³aæ poprzez SSD1309_WriteCommand()
#define		SSD1309_COLUMN_LOW(Nibble)		(0x00 | (Nibble))			// 01, m³odsze 4 bity pozycji X
#define		SSD1309_COLUMN_HIGH(Nibble)		(0x10 | (Nibble))			// 02, starsze 4 bity pozycji X
#define		SSD1309_PUMP_VOLTAGE(Value)		(0x30 | (Value))			// 03, napiêcie przetwornicy, domyœlne 10, zakres od 0x00..0x03
#define		SSD1309_START_LINE(Line)			(0x40 | (Line))				// 04, offset pionowy, wiêkszanie powoduje przesuwanie w górê, zakres 0..63
#define		SSD1309_CONTRAST					0x81						// 05, kontrast nale¿y podaæ w kolejnym bajcie (0...255)
#define		SSD1309_REMAP(ADC)				(0xA0 | (ADC))				// 06, 1 wyœwietla praiwd³owo, 0 lustrzane odbicie
#define		SSD1309_ENTRIE_DISPLAY_ON(On)	(0xA4 | (On))				// 07, 1 ca³y wyœwietlacz bia³y, 0 normalna praca
#define		SSD1309_NORMAL_REVERSE(Select)	(0xA6 | (Select))			// 08, 1 negatyw, 0 pozytyw
#define		SSD1309_MULTIPLEX_RATIO			0xA8						// 09, wartoœæ w kolejnym bajcie
#define		SSD1309_DCDC_ON_OFF				0xAD						// 10, wartoœæ w kolejnym bajcie
#define		SSD1309_DISPLAY_ON_OFF(Select)	(0xAE | (Select))			// 11, 1 wyœwietlacz w³¹czony, 0 wy³¹czony
#define		SSD1309_DISPLAY_ON				0xAF						// 11, to samo co wy¿ej, ale ju¿ z wpisanym argumentem
#define		SSD1309_DISPLAY_OFF				0xAE						// 11, to samo co wy¿ej, ale ju¿ z wpisanym argumentem
#define		SSD1309_PAGE(Page)				(0xB0 | (Page))				// 12, numer linii licz¹c od góry
#define		SSD1309_SCAN_DIRECTION(Value)	(0xC0 | (Value))			// 13, 1 skanowanie od COM63 do COM0, 0 od COM0 do COM63
#define		SSD1309_DISPLAY_OFFSET			0xD3						// 14, argument w kolejnym bajcie, zakres 0..63
#define		SSD1309_CLOCK_DIV_FREQ			0xD5						// 15, argument w kolejnym bajcie, czytaæ datasheet
#define		SSD1309_CHARGE_PERIOD			0xD9						// 16, argument w kolejnym bajcie, czytaæ datasheet
#define		SSD1309_COMMON_PADS_HW_CONFIG	0xDA						// 17, argument w kolejnym bajcie, czytaæ datasheet
#define		SSD1309_VCOM_DESELECT_LEVEL		0xDB						// 18, argument w kolejnym bajcie, czytaæ datasheet
#define		SSD1309_READ_MODIFY_WRITE		0xE0						// 19, umo¿liwia odczytanie danych z wyœwietlacza
#define		SSD1309_END						0xEE						// 20, koñczy operacjê w trybie read-modify-write
#define		SSD1309_NOP						0xE3						// 21
#define		SSD1309_CHARGE_PUMP				0x8D						// polecenie, któego nie ma w datasheecie

// Komendy steruj¹ce I2C - decyduj¹ czy nastêpny przes³any bajt to dane do wyœwietlenia czy polecenie
#if SSD1309_USE_I2C
	#define SSD1309_COMMAND_BYTE				0x80
	#define SSD1309_DATA_BYTE				0x40
	#define SSD1309_CoDATA_BYTE				0xC0
#endif

// ========================================
// Text and fonts
// ========================================

enum SSD1309_align_t {
	SSD1309_AlignNone,
	SSD1309_AlignLeft,
	SSD1309_AlignRight,
	SSD1309_AlignCenter
};

struct SSD1309_CharDef_t {
	uint8_t		Width;						// Character width
	uint16_t	Offset;						// Address in characters bitmap array
};

// Struktura definicji czcionki
struct SSD1309_FontDef_t {
	uint8_t Height;							// Character height in lines of 8 pixels
	uint8_t Width;							// Common width of characters, if character width is not constant then place 0
	uint8_t Spacing;						// Character spacing
	uint8_t FirstChar;						// First character in bitmap array
	uint8_t LastChar;						// Last character in bitmap array
	const SSD1309_CharDef_t * Descriptors;	// Pointer to table with width od each character, set to null if width is the same for all characters
	const uint8_t * Bitmaps;				// Bitmap array
};

// ========================================
// Bitmaps
// ========================================

// Bitmap definition
struct SSD1309_Bitmap_t {
	const uint8_t Height;					// Height in pixels
	const uint8_t Width;					// Width in pixels
	const uint8_t * Array;					// Pointer to bitmap array
};

#endif /* DISPLAY_SSD1309_DEFINES_H_ */