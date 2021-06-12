#ifndef DISPLAY_SSD1681_DEFINES_H_
#define DISPLAY_SSD1681_DEFINES_H_

// ========================================
// Basic constants
// ========================================

#define		SSD1681_DISPLAY_SIZE_X				uint8_t(200)
#define		SSD1681_DISPLAY_SIZE_Y				uint8_t(200)
#define		SSD1681_PAGE_HEIGHT					uint8_t(8)
#define		SSD1681_PAGE_COUNT					uint8_t(25)		// Page is a horizontal rectangle of 8x200 pixels and each byte corresponds to 8 pixels in vertical

// ========================================
// Display operation codes
// ========================================

#define		SSD1681_DRIVER_OUTPUT_CONTROL					uint8_t(0x01)
#define		SSD1681_BOOSTER_SOFT_START_CONTROL				uint8_t(0x0C)
#define		SSD1681_GATE_SCAN_START_POSITION				uint8_t(0x0F)
#define		SSD1681_DEEP_SLEEP_MODE							uint8_t(0x10)
#define		SSD1681_DATA_ENTRY_MODE_SETTING					uint8_t(0x11)
#define		SSD1681_SW_RESET								uint8_t(0x12)
#define		SSD1681_TEMPERATURE_SENSOR_CONTROL				uint8_t(0x1A)
#define		SSD1681_MASTER_ACTIVATION						uint8_t(0x20)
#define		SSD1681_DISPLAY_UPDATE_CONTROL_1				uint8_t(0x21)
#define		SSD1681_DISPLAY_UPDATE_CONTROL_2				uint8_t(0x22)
#define		SSD1681_WRITE_RAM								uint8_t(0x24)
#define		SSD1681_WRITE_VCOM_REGISTER						uint8_t(0x2C)
#define		SSD1681_WRITE_LUT_REGISTER						uint8_t(0x32)
#define		SSD1681_SET_DUMMY_LINE_PERIOD					uint8_t(0x3A)		// Not described in datasheet
#define		SSD1681_SET_GATE_TIME							uint8_t(0x3B)		// Not described in datasheet
#define		SSD1681_BORDER_WAVEFORM_CONTROL					uint8_t(0x3C)
#define		SSD1681_SET_RAM_X_ADDRESS_START_END_POSITION	uint8_t(0x44)
#define		SSD1681_SET_RAM_Y_ADDRESS_START_END_POSITION	uint8_t(0x45)
#define		SSD1681_SET_RAM_X_ADDRESS_COUNTER				uint8_t(0x4E)
#define		SSD1681_SET_RAM_Y_ADDRESS_COUNTER				uint8_t(0x4F)
#define		SSD1681_TERMINATE_FRAME_READ_WRITE				uint8_t(0xFF)		// Not described in datasheet

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
