#ifndef DISPLAY_SSD1351_DEFINES_H_
#define DISPLAY_SSD1351_DEFINES_H_

// ========================================
// Basic constants
// ========================================

#define		SSD1351_DISPLAY_SIZE_X				128
#define		SSD1351_DISPLAY_SIZE_Y				128

// ========================================
// Display operation codes
// ========================================

#define		SSD1351_COLUMN_RANGE				0x15						// 01 specifies the range in which the cursor can increment
#define		SSD1351_ROW_RANGE					0x75						// 02 specifies the range in which the cursor can increment
#define		SSD1351_RAM_WRITE					0x5C						// 03
#define		SSD1351_RAM_READ					0x5D						// 04 reading from the display doesn't work in SPI mode
#define		SSD1351_REMAP_COLOR_DEPTH			0xA0						// 05
#define		SSD1351_SET_DISPLAY_START_LINE		0xA1						// 06 set vertical scroll by RAM from 0~127. [reset=00h]
#define		SSD1351_SET_DISPLAY_OFFSET			0xA2						// 07 set vertical scroll by Row from 0-127. [reset=60h]
#define		SSD1351_SET_DISPLAY_MODE_OFF		0xA4						// 08a
#define		SSD1351_SET_DISPLAY_MODE_ON			0xA5						// 08b
#define		SSD1351_SET_DISPLAY_MODE_RESET		0xA6						// 08c
#define		SSD1351_SET_DISPLAY_MODE_INVERT		0xA7						// 08d
#define		SSD1351_FUNCTION_SELECTION			0xAB						// 09,
#define		SSD1351_NOP							0xAD						// 10
#define		SSD1351_SLEEP_MODE_ON				0xAE						// 11a
#define		SSD1351_SLEEP_MODE_OFF				0xAF						// 11b
#define		SSD1351_NOP2						0xB0						// 12
#define		SSD1351_SET_RESET_PRECHARGE			0xB1						// 13
#define		SSD1351_DISPLAY_ENHANCEMENT			0xB2						// 14
#define		SSD1351_CLOCK_DIVIDER_OSC_FREQ		0xB3						// 15
#define		SSD1351_SET_SEGMENT_LOW_VOLTAGE		0xB4						// 16
#define		SSD1351_SET_GPIO					0xB5						// 17
#define		SSD1351_SET_SECOND_PRECHARGE		0xB6						// 18
#define		SSD1351_LOOKUP_TABLE				0xB8						// 19
#define		SSD1351_USE_BUILTIN_LINEAR_LUT		0xB9						// 20
#define		SSD1351_SET_PRECHARGE_VOLTAGE		0xBB						// 21
#define		SSD1351_SET_VCOMH_VOLTAGE			0xBE						// 22
#define		SSD1351_SET_CONTRAST				0xC1						// 23
#define		SSD1351_MASTER_CONTRAST_CURRENT		0xC7						// 24
#define		SSD1351_SET_MUX_RATIO				0xCA						// 25
#define		SSD1351_NOP3						0xD1						// 26
#define		SSD1351_NOP4						0xE3						// 27
#define		SSD1351_SET_LOCK_COMMAND			0xFD						// 28
#define		SSD1351_HORIZONTAL_SCROLL			0x96						// 29
#define		SSD1351_STOP_MOVING					0x9E						// 30
#define		SSD1351_START_MOVING				0x9F						// 31

// ========================================
// Color definitions
// ========================================

// RGB565 palette								0bRRRRRGGGGGGBBBBB
#define		SSD1351_COLOR_BLACK_ID				0
#define		SSD1351_COLOR_BLACK_RGB565			0b0000000000000000
#define		SSD1351_COLOR_RED_ID				1
#define		SSD1351_COLOR_RED_RGB565			0b1111100000000000
#define		SSD1351_COLOR_GREEN_ID				2
#define		SSD1351_COLOR_GREEN_RGB565			0b0000011111100000
#define		SSD1351_COLOR_YELLOW_ID				3
#define		SSD1351_COLOR_YELLOW_RGB565			0b1111111111100000
#define		SSD1351_COLOR_BLUE_ID				4
#define		SSD1351_COLOR_BLUE_RGB565			0b0000000000011111
#define		SSD1351_COLOR_MAGENTA_ID			5
#define		SSD1351_COLOR_MAGENTA_RGB565		0b1111100000011111
#define		SSD1351_COLOR_CYAN_ID				6
#define		SSD1351_COLOR_CYAN_RGB565			0b0000011111111111
#define		SSD1351_COLOR_WHITE_ID				7
#define		SSD1351_COLOR_WHITE_RGB565			0b1111111111111111
#define		SSD1351_COLOR_GRAY_ID				8
#define		SSD1351_COLOR_GRAY_RGB565			0b1000010000010000
#define		SSD1351_COLOR_LIGHTRED_ID			9
#define		SSD1351_COLOR_LIGHTRED_RGB565		0b1111110000010000
#define		SSD1351_COLOR_LIGHTGREEN_ID			10
#define		SSD1351_COLOR_LIGHTGREEN_RGB565		0b1000011111110000
#define		SSD1351_COLOR_LIGHTYELLOW_ID		11
#define		SSD1351_COLOR_LIGHTYELLOW_RGB565	0b1111111111110000
#define		SSD1351_COLOR_LIGHTBLUE_ID			12
#define		SSD1351_COLOR_LIGHTBLUE_RGB565		0b1000010000011111
#define		SSD1351_COLOR_LIGHTMAGENTA_ID		13
#define		SSD1351_COLOR_LIGHTMAGENTA_RGB565	0b1111110000011111
#define		SSD1351_COLOR_LIGHTCYAN_ID			14
#define		SSD1351_COLOR_LIGHTCYAN_RGB565		0b1000011111111111
#define		SSD1351_COLOR_LIGHTGRAY_ID			15
#define		SSD1351_COLOR_LIGHTGRAY_RGB565		0b1100011000011000

// ========================================
// Text and fonts
// ========================================

#define		SSD1351_HALIGN_NONE					0x00
#define		SSD1351_HALIGN_LEFT					0x01
#define		SSD1351_HALIGN_CENTER				0x02
#define		SSD1351_HALIGN_RIGHT				0x03
#define		SSD1351_VALIGN_NONE					0x00
#define		SSD1351_VALIGN_TOP					0x10
#define		SSD1351_VALIGN_CENTER				0x20
#define		SSD1351_VALIGN_BOTTOM				0x30

// Character definition
struct SSD1351_CharDef_t {
	uint8_t		Width;							// Width of character in pixels
	uint16_t	Offset;							// Address in bitmap array
};

// Font definition
struct SSD1351_FontDef_t {
	uint8_t Height;								// Height of character in pixels
	uint8_t Width;								// Width of character if constant for all characters, if variable width then type 0
	uint8_t Spacing;							// Space between characters
	uint8_t FirstChar;							// ASCII code of first character in bitmap array
	uint8_t LastChar;							// ASCII code of last character in bitmap array
	const SSD1351_CharDef_t * Descriptors;		// Pointer to array of character definitions if Width!=0, if width is constant for all characters then pass NULL
	const uint8_t * Bitmaps;					// Pointer to bitmaps array
};

// Enum to select one of possible color modes
enum SSD1351_Color_t {
	SSD1351_ColorMono,							// 1 byte = 8 pixels
	SSD1351_ColorRGB332,						// 1 pixel = 1 byte,  0bRRRGGGBB
	SSD1351_ColorRGB565							// 1 pixel = 2 bytes, 0bRRRRRGGGGGGBBBBB
};

// Bitmap definition
struct SSD1351_Bitmap_t {
	const uint8_t Height;						// Height in pixels
	const uint8_t Width;						// 
	const SSD1351_Color_t ColorDepth;			// 
	const uint8_t * Bitmaps;					// 
};


#endif /* DISPLAY_SSD1351_DEFINES_H_ */
