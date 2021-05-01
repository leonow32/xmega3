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

	// Piny steruj¹ca CS dla SPI
	#define		SSD1351_CS_PORT					VPORTA.OUT
	#define		SSD1351_CS_DIR					VPORTA.DIR
	#define		SSD1351_CS_PIN					PIN0_bm
	#define		SSD1351_DC_PORT					VPORTD.OUT
	#define		SSD1351_DC_DIR					VPORTD.DIR
	#define		SSD1351_DC_PIN					PIN7_bm

	// Definicje
	#define		SSD1351_DISPLAY_SIZE_X			128
	#define		SSD1351_DISPLAY_SIZE_Y			128

	// Czcionki
	//#include	"FontXF90/fontXF90_Console8x6.h"
	// #include	"FontXF90/fontXF90_Dos8x8.h"
	// #include	"FontXF90/fontXF90_Dos16x8.h"
	// #include	"FontR/fontR_Sans8.h"
	//#include	"FontR/fontR_Sans16.h"
	//#include	"FontXF90/fontXF90_Sans16_PL.h"
	// #include	"FontR/fontR_Sans16B.h"
	// #include	"FontXF90/fontXF90_Sans16B_PL.h"
	// #include	"FontR/fontR_Sans24.h"

	//#include	"FontXF90/fontXF90_Sans24_PL.h"

	// #include	"FontR/fontR_Sans24B.h"
	// #include	"FontR/fontR_Sans24B_PL.h"

	// Bitmapy
	//#include	"BitmapXF90/bitmapXF90_ExtronicLogo.h"
	// #include	"BitmapXF90/bitmapXF90_TestPattern.h"
	//#include	"BitmapXF90/bitmapXF90_Cassini565.h"
	//#include	"BitmapXF90/bitmapXF90_Cassini332.h"
	//#include	"BitmapXF90/bitmapXF90_Pluszaki.h"
	
	#define		SSD1351_CONFIG_DONE
	
#endif

// ========================================
// Error handling
// ========================================

#ifndef SSD1351_CONFIG_DONE
	#error "Missing config"
#endif

#endif /* DISPLAY_SSD1351_CONFIG_H_ */ 