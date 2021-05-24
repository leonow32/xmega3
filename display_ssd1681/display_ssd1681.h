/*
DESCRIPTION
		-	Display SSD1681 with SPI interface
		
HARDWARE
		-	SPI
*/

#ifndef DISPLAY_SSD1681_H_
#define DISPLAY_SSD1681_H_
#if COMPONENT_DISPLAY_SSD1681

// ========================================
// Includes
// ========================================

// DEBUG
#include "../print/print.h"

#include	<avr/io.h>
#include	<util/delay.h>
#include	"display_ssd1681_defines.h"
#include	"display_ssd1681_config.h"

#if COMPONENT_SPI_MASTER
	#include	"../spi_master/spi_master.h"
#else
	#error		"This module requires SPI_MASTER component"
#endif

// #if SSD1681_FONT_CONSOLE8x6
// 	#include	"font/console8x6.h"
// #endif
// 
// #if SSD1681_FONT_DOS8x8
// 	#include	"font/dos8x8.h"
// #endif
// 
// #if SSD1681_FONT_DOS16x8
// 	#include	"font/dos16x8.h"
// #endif
// 
// #if SSD1681_FONT_SANS16_PL
// 	#include	"font/sans16_PL.h"
// #endif
// 
// #if SSD1681_FONT_SANS16B_PL
// 	#include	"font/sans16B_PL.h"
// #endif
// 
// #if SSD1681_FONT_SANS24_PL
// 	#include	"font/sans24_PL.h"
// #endif
// 
// #if SSD1681_BITMAP_ARROW
// 	#include	"bitmap/arrow.h"
// #endif
// 
// #if SSD1681_BITMAP_EXTRONIC_LOGO_MONO
// 	#include	"bitmap/extronic_logo_mono.h"
// #endif
// 
// #if SSD1681_BITMAP_EXTRONIC_LOGO_RGB565
// 	#include	"bitmap/extronic_logo_rgb565.h"
// #endif
// 
// #if SSD1681_BITMAP_ME_AND_MY_GIRLFRIEND
// 	#include	"bitmap/me_and_my_girlfriend.h"
// #endif
// 
// #if SSD1681_BITMAP_CASSINI_RGB332
// 	#include	"bitmap/cassini_rgb332.h"
// #endif
// 
// #if SSD1681_BITMAP_CASSINI_RGB565
// 	#include	"bitmap/cassini_rgb565.h"
// #endif

// ========================================
// Global variables
// ========================================

extern uint8_t SSD1681_CursorP;
extern uint8_t SSD1681_CursorP_Max;
extern uint8_t SSD1681_CursorY;
extern uint8_t SSD1681_CursorY_Max;

// ========================================
// Basic functions
// ========================================

void		SSD1681_Init(void);
void		SSD1681_WaitUntilReady(void);
//void		SSD1681_WriteCommand(const uint8_t Command);
//void		SSD1681_WriteData(const uint8_t Data);
//void		SSD1681_WriteLUT(const uint8_t * LUT);
void		SSD1681_Refresh(void);
// void		SSD1681_WriteRamEnable(void);
// void		SSD1681_ContrastSet(const uint8_t Value);
void		SSD1681_Clear(void);
void		SSD1681_Fill(void);
void		SSD1681_Chessboard(void);

// ========================================
// Cursor and active area
// ========================================

void		SSD1681_CursorSet(uint8_t p, uint8_t y);
uint8_t		SSD1681_CursorPageGet(void);
void		SSD1681_CursorPageSet(uint8_t Page);
uint8_t		SSD1681_CursorYGet(void);
void		SSD1681_CursorYSet(uint8_t y);
void		SSD1681_ActiveAreaSet(uint8_t p0, uint8_t y0, uint8_t p1, uint8_t y1);
void		SSD1681_ActiveAreaPageSet(uint8_t p0, uint8_t p1);
void		SSD1681_ActiveAreaYSet(uint8_t y0, uint8_t y1);

// ========================================
// Colors
// ========================================

SSD1681_Color_t SSD1681_ColorGet(void);
void		SSD1681_ColorSet(SSD1681_Color_t Color);

// ========================================
// Drawing
// ========================================

// void		SSD1681_DrawPixel(uint8_t x, uint8_t y);
// void		SSD1681_DrawLineHorizontal(uint8_t x0, uint8_t y0, uint8_t Length);
// void		SSD1681_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length);
// void		SSD1681_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
// void		SSD1681_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
// void		SSD1681_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
// void		SSD1681_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r);

// ========================================
// Bitmaps
// ========================================

// void		SSD1681_Bitmap(const SSD1681_Bitmap_t * Bitmap);
// void		SSD1681_BitmapMono(const SSD1681_Bitmap_t * Bitmap);
// void		SSD1681_BitmapRGB565(const SSD1681_Bitmap_t * Bitmap);
// void		SSD1681_BitmapRGB332(const SSD1681_Bitmap_t * Bitmap);

// ========================================
// Text
// ========================================

// const SSD1681_FontDef_t * SSD1681_FontGet(void);
// void		SSD1681_FontSet(const SSD1681_FontDef_t * Font);
// uint8_t		SSD1681_TextWidthGet(const char * Text);
// void		SSD1681_PrintChar(uint8_t Char);
// void		SSD1681_Text(const char * Text, uint8_t Align = 0);

// ========================================
// Test
// ========================================

void SSD1681_Bytes(uint8_t Pattern, uint16_t Times);

#endif /* DISPLAY_SSD1681_H_ */
#endif
