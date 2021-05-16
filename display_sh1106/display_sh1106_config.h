#ifndef DISPLAY_SH1106_CONFIG_H_
#define DISPLAY_SH1106_CONFIG_H_

// ========================================
// Template
// ========================================

#if TEMPLATE

#endif

// ========================================
// Demo Display SH1106
// ========================================

#if PRODUCT_SH1106
	
	#define SH1106_USE_DEMO_COMMANDS			1
	
	// Interface selection
	#define		SH1106_USE_I2C					0
	#define		SH1106_USE_SPI					1
	
	// Config
	#define		SH1106_DEFAULT_CONTRAST			255
	#define		SH1106_CLEAR_AFERT_INIT			1
	#define		SH1106_USE_DEMO_COMMANDS		1
	#define		SH1106_USE_RMW					0		// for I2C interface only
	
	// Addess on I2C bus
	#if SH1106_USE_I2C
		#define		SH1106_ADDRESS_READ			0x79
		#define		SH1106_ADDRESS_WRITE		0x78
	#endif
	
	// Pinout for SPI
	#if SH1106_USE_SPI
		#define		SH1106_CHIP_SELECT_INIT		VPORTC.DIR |=  PIN4_bm
		#define		SH1106_CHIP_SELECT			VPORTC.OUT &= ~PIN4_bm
		#define		SH1106_CHIP_DESELECT		VPORTC.OUT |=  PIN4_bm
		#define		SH1106_DC_INIT				VPORTC.DIR |=  PIN5_bm
		#define		SH1106_DC_DATA				VPORTC.OUT |=  PIN5_bm
		#define		SH1106_DC_COMMAND			VPORTC.OUT &= ~PIN5_bm
	#endif

	
	// Czcionki (znaki obr�cone o 90 stopni - wersja R)
	// #include	"FontR/fontR_Console8x6.h"
	// #include	"FontR/fontR_Dos8x8.h"
	// #include	"FontR/fontR_Dos16x8.h"
	// #include	"FontR/fontR_Sans8.h"
	// #include	"FontR/fontR_Sans16.h"
	// #include	"FontR/fontR_Sans16_PL.h"
	// #include	"FontR/fontR_Sans16B.h"
	// #include	"FontR/fontR_Sans16B_PL.h"
	// #include	"FontR/fontR_Sans24.h"
	// #include	"FontR/fontR_Sans24_PL.h"
	// #include	"FontR/fontR_Sans24B.h"
	// #include	"FontR/fontR_Sans24B_PL.h"
	
	// Bitmapy
	//#include	"Bitmap/bitmap_Testowy.h"
	//#include	"Bitmap/bitmap_ExtronicLogo.h"
	
	// Bitmaps
	#define		SH1106_BITMAP_EXTRONIC_LOGO	1						// 1024 B
	
	
#endif

// Komunikaty o b��dach
#if SH1106_USE_I2C && SH1106_USE_SPI
	#error "SH1106 - Can't use I2C and SPI at the same time"
#endif

#if SH1106_USE_SPI && SH1106_USE_RMW
	#error "SH1106 - Usage of RMW possible only in I2C mode, but selected SPI mode"
#endif

#endif /* DISPLAY_SH1106_CONFIG_H_ */