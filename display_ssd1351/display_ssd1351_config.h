#ifndef DISPLAY_SSD1351_CONFIG_H_
#define DISPLAY_SSD1351_CONFIG_H_

// ========================================
// Template
// ========================================

#if TEMPLATE
	
	// Pinout
	#define		SSD1351_CHIP_SELECT_INIT				VPORTC.DIR	|=	PIN3_bm
	#define		SSD1351_CHIP_SELECT						VPORTC.OUT	&= ~PIN3_bm
	#define		SSD1351_CHIP_DESELECT					VPORTC.OUT	|=  PIN3_bm
	#define		SSD1351_DC_INIT							VPORTC.DIR |=  PIN4_bm
	#define		SSD1351_DC_DATA							VPORTC.OUT |=  PIN4_bm
	#define		SSD1351_DC_COMMAND						VPORTC.OUT &= ~PIN4_bm
	
	// Config
	#define		SSD1351_DEFAULT_CONTRAST				255
	#define		SSD1351_CLEAR_AFERT_INIT				1
	#define		SSD1351_USE_DEMO_COMMANDS				1
	
	// Fonts
	#define		SSD1351_DEFAULT_FONT					SSD1351_FontSans16_PL
	#define		SSD1351_FONT_CONSOLE8x6					1						// 480 B
	#define		SSD1351_FONT_DOS8x8						1						// 2048 B
	#define		SSD1351_FONT_DOS16x8					1						// 4096 B
	#define		SSD1351_FONT_SANS16_PL					1						// 1282 B
	#define		SSD1351_FONT_SANS16B_PL					1						// 1506 B
	#define		SSD1351_FONT_SANS24_PL					1						// 2958 B
	
	// Bitmaps
	#define		SSD1351_BITMAP_ARROW					0				// 3849 B
#endif

// ========================================
// Demo Display SSD1351
// ========================================

#if PRODUCT_SSD1351
	
	// Pinout
	#define		SSD1351_CHIP_SELECT_INIT				VPORTD.DIR	|=	PIN7_bm
	#define		SSD1351_CHIP_SELECT						VPORTD.OUT	&= ~PIN7_bm
	#define		SSD1351_CHIP_DESELECT					VPORTD.OUT	|=  PIN7_bm
	#define		SSD1351_DC_INIT							VPORTA.DIR |= PIN0_bm
	#define		SSD1351_DC_DATA							VPORTA.OUT |=  PIN0_bm
	#define		SSD1351_DC_COMMAND						VPORTA.OUT &= ~PIN0_bm
	
	// Config
	#define		SSD1351_DEFAULT_CONTRAST				255
	#define		SSD1351_CLEAR_AFERT_INIT				1
	#define		SSD1351_USE_DEMO_COMMANDS				1
	
	// Fonts
	#define		SSD1351_DEFAULT_FONT					SSD1351_FontSans16_PL
	#define		SSD1351_FONT_CONSOLE8x6					1						// 480 B
	#define		SSD1351_FONT_DOS8x8						1						// 2048 B
	#define		SSD1351_FONT_DOS16x8					1						// 4096 B
	#define		SSD1351_FONT_SANS16_PL					1						// 1282 B
	#define		SSD1351_FONT_SANS16B_PL					1						// 1506 B
	#define		SSD1351_FONT_SANS24_PL					1						// 2958 B
	
	// Bitmaps
	#define		SSD1351_BITMAP_ARROW					0						// 3200 B
	#define		SSD1351_BITMAP_EXTRONIC_LOGO_MONO		1						// 1024 B
	#define		SSD1351_BITMAP_EXTRONIC_LOGO_RGB565		0						// 11776 B
	#define		SSD1351_BITMAP_ME_AND_MY_GIRLFRIEND		0						// 32766 B
	#define		SSD1351_BITMAP_CASSINI_RGB332			0						// 16384 B
	#define		SSD1351_BITMAP_CASSINI_RGB565			0						// 32766 B
	
	#define		SSD1351_CONFIG_DONE
	
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if PRODUCT_AVRIOT
	
	// Pinout
	#define		SSD1351_CHIP_SELECT_INIT				VPORTD.DIR	|=	PIN7_bm
	#define		SSD1351_CHIP_SELECT						VPORTD.OUT	&= ~PIN7_bm
	#define		SSD1351_CHIP_DESELECT					VPORTD.OUT	|=  PIN7_bm
	#define		SSD1351_DC_INIT							VPORTA.DIR |= PIN0_bm
	#define		SSD1351_DC_DATA							VPORTA.OUT |=  PIN0_bm
	#define		SSD1351_DC_COMMAND						VPORTA.OUT &= ~PIN0_bm
	
	// Config
	#define		SSD1351_DEFAULT_CONTRAST				255
	#define		SSD1351_CLEAR_AFERT_INIT				1
	#define		SSD1351_USE_DEMO_COMMANDS				1
	
	// Fonts
	#define		SSD1351_DEFAULT_FONT					SSD1351_FontSans16_PL
	#define		SSD1351_FONT_CONSOLE8x6					1						// 480 B
	#define		SSD1351_FONT_DOS8x8						1						// 2048 B
	#define		SSD1351_FONT_DOS16x8					1						// 4096 B
	#define		SSD1351_FONT_SANS16_PL					1						// 1282 B
	#define		SSD1351_FONT_SANS16B_PL					1						// 1506 B
	#define		SSD1351_FONT_SANS24_PL					1						// 2958 B
	
	// Bitmaps
	#define		SSD1351_BITMAP_ARROW					0						// 3200 B
	#define		SSD1351_BITMAP_EXTRONIC_LOGO_MONO		1						// 1024 B
	#define		SSD1351_BITMAP_EXTRONIC_LOGO_RGB565		0						// 11776 B
	#define		SSD1351_BITMAP_ME_AND_MY_GIRLFRIEND		0						// 32766 B
	#define		SSD1351_BITMAP_CASSINI_RGB332			0						// 16384 B
	#define		SSD1351_BITMAP_CASSINI_RGB565			0						// 32766 B
	
	#define		SSD1351_CONFIG_DONE
	
#endif

// ========================================
// GameBox4809
// ========================================

#if PRODUCT_GAMEBOX4809
	
	// Pinout
	#define		SSD1351_CHIP_SELECT_INIT				VPORTC.DIR	|=	PIN3_bm
	#define		SSD1351_CHIP_SELECT						VPORTC.OUT	&= ~PIN3_bm
	#define		SSD1351_CHIP_DESELECT					VPORTC.OUT	|=  PIN3_bm
	#define		SSD1351_DC_INIT							VPORTC.DIR |=  PIN4_bm
	#define		SSD1351_DC_DATA							VPORTC.OUT |=  PIN4_bm
	#define		SSD1351_DC_COMMAND						VPORTC.OUT &= ~PIN4_bm
	
	// Config
	#define		SSD1351_DEFAULT_CONTRAST				255
	#define		SSD1351_CLEAR_AFERT_INIT				1
	#define		SSD1351_USE_DEMO_COMMANDS				1
	
	// Fonts
	#define		SSD1351_DEFAULT_FONT					SSD1351_FontSans16_PL
	#define		SSD1351_FONT_CONSOLE8x6					1						// 480 B
	#define		SSD1351_FONT_DOS8x8						1						// 2048 B
	#define		SSD1351_FONT_DOS16x8					1						// 4096 B
	#define		SSD1351_FONT_SANS16_PL					1						// 1282 B
	#define		SSD1351_FONT_SANS16B_PL					1						// 1506 B
	#define		SSD1351_FONT_SANS24_PL					1						// 2958 B
	
	// Bitmaps
	#define		SSD1351_BITMAP_ARROW					0						// 3200 B
	#define		SSD1351_BITMAP_EXTRONIC_LOGO_MONO		1						// 1024 B
	#define		SSD1351_BITMAP_EXTRONIC_LOGO_RGB565		0						// 11776 B
	#define		SSD1351_BITMAP_ME_AND_MY_GIRLFRIEND		0						// 32766 B
	#define		SSD1351_BITMAP_CASSINI_RGB332			0						// 16384 B
	#define		SSD1351_BITMAP_CASSINI_RGB565			0						// 32766 B
	
	#define		SSD1351_CONFIG_DONE
	
#endif

// ========================================
// Error handling
// ========================================

#ifndef SSD1351_CONFIG_DONE
	#error "Missing config"
#endif

#endif /* DISPLAY_SSD1351_CONFIG_H_ */ 