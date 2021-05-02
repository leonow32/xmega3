// Wersja 0.15

#ifndef DISPLAY_SSD1351_CONFIG_H_
#define DISPLAY_SSD1351_CONFIG_H_

// ========================================
// Template
// ========================================

#if TEMPLATE

#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if PRODUCT_AVRIOT
	
	// Pinout
	#define		SSD1351_CHIP_SELECT_INIT		VPORTD.DIR	|=	PIN7_bm
	#define		SSD1351_CHIP_SELECT				VPORTD.OUT	&= ~PIN7_bm
	#define		SSD1351_CHIP_DESELECT			VPORTD.OUT	|=  PIN7_bm
	#define		SSD1351_DC_INIT					VPORTA.DIR |= PIN0_bm
	#define		SSD1351_DC_DATA					VPORTA.OUT |=  PIN0_bm
	#define		SSD1351_DC_COMMAND				VPORTA.OUT &= ~PIN0_bm
	
	// Config
	#define		SSD1351_DEFAULT_CONTRAST		255
	
	// Fonts
	#define		SSD1351_DEFAULT_FONT			FontXF90_Dos8x8
	#define		SSD1351_FONT_CONSOLE8x8			1						// 497 B
	#define		SSD1351_FONT_DOS8x8				1						// 2065 B
	#define		SSD1351_FONT_DOS16x8			1						// 4113 B
	#define		SSD1351_FONT_SANS16_PL			1						// 1938 B
	#define		SSD1351_FONT_SANS16B_PL			1						// 2162 B
	#define		SSD1351_FONT_SANS24_PL			1						// 3614 B
	
	// Bitmapy
	//#include	"BitmapXF90/bitmapXF90_ExtronicLogo.h"
	// #include	"BitmapXF90/bitmapXF90_TestPattern.h"
	//#include	"BitmapXF90/bitmapXF90_Cassini565.h"
	//#include	"BitmapXF90/bitmapXF90_Cassini332.h"
	//#include	"BitmapXF90/bitmapXF90_Pluszaki.h"
	
	// Miscellaneous
	#define		SSD1351_USE_DEMO_COMMANDS		1
	
	#define		SSD1351_CONFIG_DONE
	
#endif

// ========================================
// Error handling
// ========================================

#ifndef SSD1351_CONFIG_DONE
	#error "Missing config"
#endif

#endif /* DISPLAY_SSD1351_CONFIG_H_ */ 