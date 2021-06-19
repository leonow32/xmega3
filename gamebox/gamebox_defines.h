#if COMPONENT_GAMEBOX
#ifndef GAMEBOX_DEFINES_H_
#define GAMEBOX_DEFINES_H_

// ========================================
// Keyboard
// ========================================

#define GB_KEY_MASK				0xF0
#define GB_KEY_ACTION			0x0F
#define GB_KEY_UP_MASK			0x10
#define GB_KEY_DOWN_MASK		0x20
#define GB_KEY_LEFT_MASK		0x30
#define GB_KEY_RIGHT_MASK		0x40
#define GB_KEY_OK_MASK			0x50
#define GB_KEY_ESCAPE_MASK		0x60
#define GB_KEY_A_MASK			0x70
#define GB_KEY_B_MASK			0x80
#define GB_KEY_PRESS_MASK		0x01
#define GB_KEY_LONG_MASK		0x02
#define GB_KEY_RELEASE_MASK		0x03

// Enum to select one of possible color modes
enum GB_KeyEvent_t {
	GB_None					= 0x00,
	GB_KeyUpPress			= GB_KEY_UP_MASK		| GB_KEY_PRESS_MASK,
	GB_KeyUpLong			= GB_KEY_UP_MASK		| GB_KEY_LONG_MASK,
	GB_KeyUpRelease			= GB_KEY_UP_MASK		| GB_KEY_RELEASE_MASK,
	GB_KeyDownPress			= GB_KEY_DOWN_MASK		| GB_KEY_PRESS_MASK,
	GB_KeyDownLong			= GB_KEY_DOWN_MASK		| GB_KEY_LONG_MASK,
	GB_KeyDownRelease		= GB_KEY_DOWN_MASK		| GB_KEY_RELEASE_MASK,
	GB_KeyLeftPress			= GB_KEY_LEFT_MASK		| GB_KEY_PRESS_MASK,
	GB_KeyLeftLong			= GB_KEY_LEFT_MASK		| GB_KEY_LONG_MASK,
	GB_KeyLeftRelease		= GB_KEY_LEFT_MASK		| GB_KEY_RELEASE_MASK,
	GB_KeyRightPress		= GB_KEY_RIGHT_MASK		| GB_KEY_PRESS_MASK,
	GB_KeyRightLong			= GB_KEY_RIGHT_MASK		| GB_KEY_LONG_MASK,
	GB_KeyRightRelease		= GB_KEY_RIGHT_MASK		| GB_KEY_RELEASE_MASK,
	GB_KeyOKPress			= GB_KEY_OK_MASK		| GB_KEY_PRESS_MASK,
	GB_KeyOKLong			= GB_KEY_OK_MASK		| GB_KEY_LONG_MASK,
	GB_KeyOKRelease			= GB_KEY_OK_MASK		| GB_KEY_RELEASE_MASK,
	GB_KeyEscapePress		= GB_KEY_ESCAPE_MASK	| GB_KEY_PRESS_MASK,
	GB_KeyEscapeLong		= GB_KEY_ESCAPE_MASK	| GB_KEY_LONG_MASK,
	GB_KeyEscapeRelease		= GB_KEY_ESCAPE_MASK	| GB_KEY_RELEASE_MASK,
	GB_KeyAPress			= GB_KEY_A_MASK			| GB_KEY_PRESS_MASK,
	GB_KeyALong				= GB_KEY_A_MASK			| GB_KEY_LONG_MASK,
	GB_KeyARelease			= GB_KEY_A_MASK			| GB_KEY_RELEASE_MASK,
	GB_KeyBPress			= GB_KEY_B_MASK			| GB_KEY_PRESS_MASK,
	GB_KeyBLong				= GB_KEY_B_MASK			| GB_KEY_LONG_MASK,
	GB_KeyBRelease			= GB_KEY_B_MASK			| GB_KEY_RELEASE_MASK,
};

// ========================================
// Display dependent macros
// ========================================

#define GB_Clear		SSD1351_Clear

#endif /* GAMEBOX_DEFINES_H_ */
#endif
