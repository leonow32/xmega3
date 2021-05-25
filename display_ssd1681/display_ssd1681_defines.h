#ifndef DISPLAY_SSD1681_DEFINES_H_
#define DISPLAY_SSD1681_DEFINES_H_

// ========================================
// Basic constants
// ========================================

#define		SSD1681_DISPLAY_SIZE_X				200
#define		SSD1681_DISPLAY_SIZE_Y				200
#define		SSD1681_PAGE_HEIGHT					8
#define		SSD1681_PAGE_COUNT					25		// Page is a horizontal rectangle of 8x200 pixels and each byte corresponds to 8 pixels in vertical

// ========================================
// Display operation codes
// ========================================

#define		DRIVER_OUTPUT_CONTROL					0x01
#define		BOOSTER_SOFT_START_CONTROL				0x0C
#define		GATE_SCAN_START_POSITION				0x0F
#define		DEEP_SLEEP_MODE							0x10
#define		DATA_ENTRY_MODE_SETTING					0x11
#define		SW_RESET								0x12
#define		TEMPERATURE_SENSOR_CONTROL				0x1A
#define		MASTER_ACTIVATION						0x20
#define		DISPLAY_UPDATE_CONTROL_1				0x21
#define		DISPLAY_UPDATE_CONTROL_2				0x22
#define		WRITE_RAM								0x24
#define		WRITE_VCOM_REGISTER						0x2C
#define		WRITE_LUT_REGISTER						0x32
#define		SET_DUMMY_LINE_PERIOD					0x3A		// tego nie ma w datasheet
#define		SET_GATE_TIME							0x3B		// tego nie ma w datasheet
#define		BORDER_WAVEFORM_CONTROL					0x3C
#define		SET_RAM_X_ADDRESS_START_END_POSITION	0x44
#define		SET_RAM_Y_ADDRESS_START_END_POSITION	0x45
#define		SET_RAM_X_ADDRESS_COUNTER				0x4E
#define		SET_RAM_Y_ADDRESS_COUNTER				0x4F
#define		TERMINATE_FRAME_READ_WRITE				0xFF		// tego nie ma w datasheet

// #define		SSD1681_COLUMN_RANGE				0x15						// 01 specifies the range in which the cursor can increment
// #define		SSD1681_ROW_RANGE					0x75						// 02 specifies the range in which the cursor can increment
// #define		SSD1681_RAM_WRITE					0x5C						// 03
// #define		SSD1681_RAM_READ					0x5D						// 04 reading from the display doesn't work in SPI mode
// #define		SSD1681_REMAP_COLOR_DEPTH			0xA0						// 05
// #define		SSD1681_SET_DISPLAY_START_LINE		0xA1						// 06 set vertical scroll by RAM from 0~127. [reset=00h]
// #define		SSD1681_SET_DISPLAY_OFFSET			0xA2						// 07 set vertical scroll by Row from 0-127. [reset=60h]
// #define		SSD1681_SET_DISPLAY_MODE_OFF		0xA4						// 08a
// #define		SSD1681_SET_DISPLAY_MODE_ON			0xA5						// 08b
// #define		SSD1681_SET_DISPLAY_MODE_RESET		0xA6						// 08c
// #define		SSD1681_SET_DISPLAY_MODE_INVERT		0xA7						// 08d
// #define		SSD1681_FUNCTION_SELECTION			0xAB						// 09,
// #define		SSD1681_NOP							0xAD						// 10
// #define		SSD1681_SLEEP_MODE_ON				0xAE						// 11a
// #define		SSD1681_SLEEP_MODE_OFF				0xAF						// 11b
// #define		SSD1681_NOP2						0xB0						// 12
// #define		SSD1681_SET_RESET_PRECHARGE			0xB1						// 13
// #define		SSD1681_DISPLAY_ENHANCEMENT			0xB2						// 14
// #define		SSD1681_CLOCK_DIVIDER_OSC_FREQ		0xB3						// 15
// #define		SSD1681_SET_SEGMENT_LOW_VOLTAGE		0xB4						// 16
// #define		SSD1681_SET_GPIO					0xB5						// 17
// #define		SSD1681_SET_SECOND_PRECHARGE		0xB6						// 18
// #define		SSD1681_LOOKUP_TABLE				0xB8						// 19
// #define		SSD1681_USE_BUILTIN_LINEAR_LUT		0xB9						// 20
// #define		SSD1681_SET_PRECHARGE_VOLTAGE		0xBB						// 21
// #define		SSD1681_SET_VCOMH_VOLTAGE			0xBE						// 22
// #define		SSD1681_SET_CONTRAST				0xC1						// 23
// #define		SSD1681_MASTER_CONTRAST_CURRENT		0xC7						// 24
// #define		SSD1681_SET_MUX_RATIO				0xCA						// 25
// #define		SSD1681_NOP3						0xD1						// 26
// #define		SSD1681_NOP4						0xE3						// 27
// #define		SSD1681_SET_LOCK_COMMAND			0xFD						// 28
// #define		SSD1681_HORIZONTAL_SCROLL			0x96						// 29
// #define		SSD1681_STOP_MOVING					0x9E						// 30
// #define		SSD1681_START_MOVING				0x9F						// 31

// ========================================
// Color definitions
// ========================================

// Enum to select one of possible color modes
enum SSD1681_Color_t {
	SSD1681_ColorBlack = 0,
	SSD1681_ColorWhite = 1,
	#if SSD1681_USE_TRI_COLOR_DISPLAY
		SSD1681_ColorRed = 2,
	#endif
};

// ========================================
// Text and fonts
// ========================================

#define		SSD1681_HALIGN_NONE					0x00
#define		SSD1681_HALIGN_LEFT					0x01
#define		SSD1681_HALIGN_CENTER				0x02
#define		SSD1681_HALIGN_RIGHT				0x03
#define		SSD1681_VALIGN_NONE					0x00
#define		SSD1681_VALIGN_TOP					0x10
#define		SSD1681_VALIGN_CENTER				0x20
#define		SSD1681_VALIGN_BOTTOM				0x30

// Character definition
struct SSD1681_CharDef_t {
	uint8_t		Width;							// Width of character in pixels
	uint16_t	Offset;							// Address in bitmap array
};

// Font definition
struct SSD1681_FontDef_t {
	uint8_t Height;								// Height of character in pixels
	uint8_t Width;								// Width of character if constant for all characters, if variable width then type 0
	uint8_t Spacing;							// Space between characters
	uint8_t FirstChar;							// ASCII code of first character in bitmap array
	uint8_t LastChar;							// ASCII code of last character in bitmap array
	const SSD1681_CharDef_t * Descriptors;		// Pointer to array of character definitions if Width!=0, if width is constant for all characters then pass NULL
	const uint8_t * Bitmaps;					// Pointer to bitmaps array
};

// ========================================
// Bitmaps
// ========================================

// Enum to select one of possible color modes
// enum SSD1681_Color_t {
// 	SSD1681_ColorMono,							// 1 byte = 8 pixels
// 	SSD1681_ColorRGB332,						// 1 pixel = 1 byte,  0bRRRGGGBB
// 	SSD1681_ColorRGB565							// 1 pixel = 2 bytes, 0bRRRRRGGGGGGBBBBB
// };

// Bitmap definition
struct SSD1681_Bitmap_t {
	const uint8_t Height;						// Height in pixels
	const uint8_t Width;						// Width in pixels
	const SSD1681_Color_t ColorDepth;			// Color depth
	const uint8_t * Bitmaps;					// Pointer to bitmap array
};

// ========================================
// Miscellaneous
// ========================================

#define SSD1681_COMMAND						uint8_t(1)
#define SSD1681_DATA						uint8_t(0)
#define SSD1681_LUT_LENGTH					uint8_t(30)

#endif /* DISPLAY_SSD1681_DEFINES_H_ */
