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
	
	#define		SSD1351_USE_DEMO_COMMANDS		1
	
	// Definicje
	#define		SSD1351_DISPLAY_SIZE_X			128
	#define		SSD1351_DISPLAY_SIZE_Y			128
	
	// Czcionki
	#include	"font/fontXF90_Console8x6.h"
	#include	"font/fontXF90_Dos8x8.h"
	#include	"font/fontXF90_Dos16x8.h"
	#include	"font/fontXF90_Sans16_PL.h"
	#include	"font/fontXF90_Sans16B_PL.h"
	#include	"font/fontXF90_Sans24_PL.h"
	
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