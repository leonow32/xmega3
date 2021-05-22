#ifndef DISPLAY_SH1106_CONFIG_H_
#define DISPLAY_SH1106_CONFIG_H_

// ========================================
// Template
// ========================================

#if TEMPLATE
	
	// Interface selection
	#define		SH1106_USE_I2C					1
	#define		SH1106_USE_SPI					0
	
	// Config
	#define		SH1106_USE_RMW					1	// read-modify-write for I2C interface only
	#define		SH1106_USE_DEMO_COMMANDS		1
	#define		SH1106_CLEAR_AFERT_INIT			1
	#define		SH1106_DEFAULT_CONTRAST			255
	
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
	
	// Fonts
	#define		SH1106_DEFAULT_FONT				SH1106_FontDos16x8
	#define		SH1106_FONT_CONSOLE8x6			1						// 480 B
	#define		SH1106_FONT_DOS8x8				1						// 2048 B
	#define		SH1106_FONT_DOS16x8				1						// 4096 B
	#define		SH1106_FONT_SANS8				1						// 
	#define		SH1106_FONT_SANS16				1						// 1194 B
	#define		SH1106_FONT_SANS16_PL			1						// 
	#define		SH1106_FONT_SANS16B				1						// 1380 B
	#define		SH1106_FONT_SANS16B_PL			1						// 
	#define		SH1106_FONT_SANS24				1						// 2658 B
	#define		SH1106_FONT_SANS24_PL			1						// 
	#define		SH1106_FONT_SANS24B				1						// 2937 B
	#define		SH1106_FONT_SANS24B_PL			1						// 
	
	// Bitmaps
	#define		SH1106_BITMAP_EXTRONIC_LOGO		1						// 1024 B
	
#endif

// ========================================
// Demo Display SH1106
// ========================================

#if PRODUCT_SH1106
	
	// Interface selection
	#define		SH1106_USE_I2C					1
	#define		SH1106_USE_SPI					0
	
	// Config
	#define		SH1106_USE_RMW					1	// read-modify-write for I2C interface only
	#define		SH1106_USE_DEMO_COMMANDS		1
	#define		SH1106_CLEAR_AFERT_INIT			1
	#define		SH1106_DEFAULT_CONTRAST			255
	
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
	
	// Fonts
	#define		SH1106_DEFAULT_FONT				SH1106_FontDos16x8
	#define		SH1106_FONT_CONSOLE8x6			1						// 480 B
	#define		SH1106_FONT_DOS8x8				1						// 2048 B
	#define		SH1106_FONT_DOS16x8				1						// 4096 B
	#define		SH1106_FONT_SANS8				1						// 
	#define		SH1106_FONT_SANS16				1						// 1194 B
	#define		SH1106_FONT_SANS16_PL			1						// 
	#define		SH1106_FONT_SANS16B				1						// 1380 B
	#define		SH1106_FONT_SANS16B_PL			1						// 
	#define		SH1106_FONT_SANS24				1						// 2658 B
	#define		SH1106_FONT_SANS24_PL			1						// 
	#define		SH1106_FONT_SANS24B				1						// 2937 B
	#define		SH1106_FONT_SANS24B_PL			1						// 
	
	// Bitmaps
	#define		SH1106_BITMAP_EXTRONIC_LOGO		1						// 1024 B
	
#endif

// Error handling
#if SH1106_USE_I2C && SH1106_USE_SPI
	#error "SH1106 - Can't use I2C and SPI at the same time"
#endif

#if SH1106_USE_SPI && SH1106_USE_RMW
	#error "SH1106 - Usage of RMW possible only in I2C mode, but selected SPI mode"
#endif

#endif /* DISPLAY_SH1106_CONFIG_H_ */