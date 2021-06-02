#ifndef DISPLAY_SSD1309_CONFIG_H_
#define DISPLAY_SSD1309_CONFIG_H_

// ========================================
// Template
// ========================================

#if TEMPLATE
	
	// Interface selection
	#define		SSD1309_USE_I2C					1
	#define		SSD1309_USE_SPI					0
	
	// Config
	#define		SSD1309_USE_RMW					1	// read-modify-write for I2C interface only, takes about 6 times longer than without RMW
	#define		SSD1309_USE_DEMO_COMMANDS		1
	#define		SSD1309_CLEAR_AFERT_INIT			1
	#define		SSD1309_DEFAULT_CONTRAST			128
	
	// Addess on I2C bus
	#if SSD1309_USE_I2C
		#define		SSD1309_ADDRESS_READ			0x79
		#define		SSD1309_ADDRESS_WRITE		0x78
	#endif
	
	// Pinout for SPI
	#if SSD1309_USE_SPI
		#define		SSD1309_CHIP_SELECT_INIT		VPORTC.DIR |=  PIN4_bm
		#define		SSD1309_CHIP_SELECT			VPORTC.OUT &= ~PIN4_bm
		#define		SSD1309_CHIP_DESELECT		VPORTC.OUT |=  PIN4_bm
		#define		SSD1309_DC_INIT				VPORTC.DIR |=  PIN5_bm
		#define		SSD1309_DC_DATA				VPORTC.OUT |=  PIN5_bm
		#define		SSD1309_DC_COMMAND			VPORTC.OUT &= ~PIN5_bm
	#endif
	
	// Fonts
	#define		SSD1309_DEFAULT_FONT				SSD1309_FontDos16x8
	#define		SSD1309_FONT_CONSOLE8x6			1						// 480 B
	#define		SSD1309_FONT_DOS8x8				1						// 2048 B
	#define		SSD1309_FONT_DOS16x8				1						// 4096 B
	#define		SSD1309_FONT_SANS8				1						// 
	#define		SSD1309_FONT_SANS16				1						// 1194 B
	#define		SSD1309_FONT_SANS16_PL			1						// 
	#define		SSD1309_FONT_SANS16B				1						// 1380 B
	#define		SSD1309_FONT_SANS16B_PL			1						// 
	#define		SSD1309_FONT_SANS24				1						// 2658 B
	#define		SSD1309_FONT_SANS24_PL			1						// 
	#define		SSD1309_FONT_SANS24B				1						// 2937 B
	#define		SSD1309_FONT_SANS24B_PL			1						// 
	
	// Bitmaps
	#define		SSD1309_BITMAP_EXTRONIC_LOGO		1						// 1024 B
	
#endif

// ========================================
// Demo Display SSD1309
// ========================================

#if PRODUCT_SSD1309
	
	// Interface selection
	#define		SSD1309_USE_I2C					1
	#define		SSD1309_USE_SPI					0
	
	// Config
	#define		SSD1309_USE_RMW					0	// read-modify-write for I2C interface only, takes about 6 times longer than without RMW
	#define		SSD1309_USE_DEMO_COMMANDS		1
	#define		SSD1309_CLEAR_AFERT_INIT			0
	#define		SSD1309_DEFAULT_CONTRAST			0xCF
	
	// Addess on I2C bus
	#if SSD1309_USE_I2C
		#define		SSD1309_ADDRESS_READ			0x79
		#define		SSD1309_ADDRESS_WRITE		0x78
	#endif
	
	// Pinout for SPI
	#if SSD1309_USE_SPI
		#define		SSD1309_CHIP_SELECT_INIT		VPORTC.DIR |=  PIN4_bm
		#define		SSD1309_CHIP_SELECT			VPORTC.OUT &= ~PIN4_bm
		#define		SSD1309_CHIP_DESELECT		VPORTC.OUT |=  PIN4_bm
		#define		SSD1309_DC_INIT				VPORTC.DIR |=  PIN5_bm
		#define		SSD1309_DC_DATA				VPORTC.OUT |=  PIN5_bm
		#define		SSD1309_DC_COMMAND			VPORTC.OUT &= ~PIN5_bm
	#endif
	
	// Fonts
	#define		SSD1309_DEFAULT_FONT				SSD1309_FontDos16x8
	#define		SSD1309_FONT_CONSOLE8x6			1						// 480 B
	#define		SSD1309_FONT_DOS8x8				1						// 2048 B
	#define		SSD1309_FONT_DOS16x8			1						// 4096 B
	#define		SSD1309_FONT_SANS8				1						// 
	#define		SSD1309_FONT_SANS16				1						// 1194 B
	#define		SSD1309_FONT_SANS16_PL			0						// 
	#define		SSD1309_FONT_SANS16B			1							// 1380 B
	#define		SSD1309_FONT_SANS16B_PL			0						// 
	#define		SSD1309_FONT_SANS24				1						// 2658 B
	#define		SSD1309_FONT_SANS24_PL			0						// 
	#define		SSD1309_FONT_SANS24B			1						// 2937 B
	#define		SSD1309_FONT_SANS24B_PL			0						// 
	
	// Bitmaps
	#define		SSD1309_BITMAP_EXTRONIC_LOGO		1						// 1024 B
	
#endif

// Error handling
#if SSD1309_USE_I2C && SSD1309_USE_SPI
	#error "SSD1309 - Can't use I2C and SPI at the same time"
#endif

#if SSD1309_USE_SPI && SSD1309_USE_RMW
	#error "SSD1309 - Usage of RMW possible only in I2C mode, but selected SPI mode"
#endif

#endif /* DISPLAY_SSD1309_CONFIG_H_ */