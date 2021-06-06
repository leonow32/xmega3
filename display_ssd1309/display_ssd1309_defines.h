#ifndef DISPLAY_SSD1309_DEFINES_H_
#define DISPLAY_SSD1309_DEFINES_H_

// ========================================
// Basic constants
// ========================================

#define		SSD1309_DISPLAY_SIZE_X			uint8_t(128)
#define		SSD1309_DISPLAY_SIZE_Y			uint8_t(64)
#define		SSD1309_PAGE_HEIGHT				uint8_t(8)
#define		SSD1309_PAGE_COUNT				uint8_t(8)

#define		SSD1309_COLOR_WHITE				uint8_t(1)
#define		SSD1309_COLOR_BLACK				uint8_t(0)

// ========================================
// Display operation codes
// ========================================

// Use SSD1309_WriteCommand(). If command uses an argument sent in the followin byte, use SSD1309_WriteCommand() too.
#define		SSD1309_COLUMN_LOW(Nibble)		uint8_t(0x00 | (Nibble))
#define		SSD1309_COLUMN_HIGH(Nibble)		uint8_t(0x10 | (Nibble))
#define		SSD1309_MEMORY_MODE				uint8_t(0x20)
#define		SSD1309_START_LINE(Line)		uint8_t(0x40 | (Line))
#define		SSD1309_CONTRAST				uint8_t(0x81)
#define		SSD1309_REMAP(ADC)				uint8_t(0xA0 | (ADC))
#define		SSD1309_ENTRIE_DISPLAY_ON(On)	uint8_t(0xA4 | (On))
#define		SSD1309_NORMAL_REVERSE(Select)	uint8_t(0xA6 | (Select))
#define		SSD1309_MULTIPLEX_RATIO			uint8_t(0xA8)
#define		SSD1309_DISPLAY_ON				uint8_t(0xAF)
#define		SSD1309_DISPLAY_OFF				uint8_t(0xAE)
#define		SSD1309_PAGE(Page)				uint8_t(0xB0 | (Page))
#define		SSD1309_DISPLAY_OFFSET			uint8_t(0xD3)
#define		SSD1309_CLOCK_DIV_FREQ			uint8_t(0xD5)
#define		SSD1309_CHARGE_PERIOD			uint8_t(0xD9)
#define		SSD1309_COMMON_PADS_HW_CONFIG	uint8_t(0xDA)
#define		SSD1309_VCOM_DESELECT_LEVEL		uint8_t(0xDB)
#define		SSD1309_CHARGE_PUMP				uint8_t(0x8D)
#define		SSD1309_COMSCANDEC				uint8_t(0xC8)
#define		SSD1309_DEACTIVATE_SCROLL		uint8_t(0x2E)

// Commands to control I2C data flow - this decides if the following byte is a command or data
#if SSD1309_USE_I2C
	#define SSD1309_COMMAND_BYTE			uint8_t(0x80)
	#define SSD1309_DATA_BYTE				uint8_t(0x40)
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