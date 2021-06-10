#ifndef DISPLAY_SSD1681_CONFIG_H_
#define DISPLAY_SSD1681_CONFIG_H_

// ========================================
// Template
// ========================================

#if TEMPLATE
	
#endif

// ========================================
// Demo Display SSD1681
// ========================================

#if PRODUCT_SSD1681
	
	// Pinout
	#define		SSD1681_CHIP_SELECT_INIT				VPORTC.DIR |=  PIN3_bm
	#define		SSD1681_CHIP_SELECT						VPORTC.OUT &= ~PIN3_bm
	#define		SSD1681_CHIP_DESELECT					VPORTC.OUT |=  PIN3_bm
	#define		SSD1681_DC_INIT							VPORTD.DIR |=  PIN4_bm
	#define		SSD1681_DC_DATA							VPORTD.OUT |=  PIN4_bm
	#define		SSD1681_DC_COMMAND						VPORTD.OUT &= ~PIN4_bm
	#define		SSD1681_BUSY_INIT						VPORTD.DIR &= ~PIN6_bm
	#define		SSD1681_BUSY_READ						(VPORTD.IN & PIN6_bm)
	
	// Config
	#define		SSD1681_CLEAR_AFERT_INIT				1
	#define		SSD1681_USE_TRI_COLOR_DISPLAY			0
	#define		SSD1681_USE_REFRESH_FULL				1
	#define		SSD1681_USE_REFRESH_PARTIAL				0
	#define		SSD1681_USE_DEMO_COMMANDS				1
	
	// Fonts
	#define		SSD1681_DEFAULT_FONT					SSD1681_FontDos16x8
	#define		SSD1681_FONT_CONSOLE8x6					0						// 480 B
	#define		SSD1681_FONT_DOS8x8						1						// 2048 B
	#define		SSD1681_FONT_DOS16x8					1						// 4096 B
	#define		SSD1681_FONT_SANS16_PL					0						// 1282 B
	#define		SSD1681_FONT_SANS16B_PL					0						// 1506 B
	#define		SSD1681_FONT_SANS24_PL					0						// 2958 B
	
	// Bitmaps
	#define		SSD1681_BITMAP_EXTRONIC_LOGO			1						// 1024 B
	
	#define		SSD1681_CONFIG_DONE
	
#endif

// ========================================
// Error handling
// ========================================

#ifndef SSD1681_CONFIG_DONE
	#error "Missing config"
#endif

#if SSD1681_USE_REFRESH_FULL && SSD1681_USE_REFRESH_PARTIAL
	#error "Can't use SSD1681_USE_REFRESH_FULL and SSD1681_USE_REFRESH_PARTIAL at the same time"
#endif

#endif /* DISPLAY_SSD1681_CONFIG_H_ */ 