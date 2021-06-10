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

enum SSD1681_align_t {
	SSD1681_AlignNone,
	SSD1681_AlignLeft,
	SSD1681_AlignRight,
	SSD1681_AlignCenter
};

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
	const uint8_t * Array;						// Pointer to bitmap array
};

// ========================================
// Miscellaneous
// ========================================

#define SSD1681_COMMAND						uint8_t(1)
#define SSD1681_DATA						uint8_t(0)
#define SSD1681_LUT_LENGTH					uint8_t(30)

#endif /* DISPLAY_SSD1681_DEFINES_H_ */
