/*
DESCRIPTION
		-	Display with SSD1309 driver
		
TODO
		-	None
		
PERFORMANCE TEST
		-	SPI mode, clock frequency 10 MHz
			-	Clear	1024 us, 976 FPS
			-	Fill	1024 us, 976 FPS
			-	Chess	1824 us, 548 FPS
			-	Pixel	11 us, 90909 FPS
			I2C mode without RMW, frequency 400 kHz
			-	Clear	24 ms, 41 FPS
			-	Fill	24 ms, 41 FPS
			-	Chess	24 ms, 41 FPS
			-	Pixel	250 us, 4000 FPS
			I2C mode without RMW, frequency 1 MHz
			-	Clear	11.5 ms, 87 FPS
			-	Fill	11,5 ms, 87 FPS
			-	Chess	11 ms, 90 FPS
			-	Pixel	122 us, 8196 FPS
		
REQUIREMENTS
		-	COMPONENT_I2C_MASTER or COMPONENT_SPI_MASTER
*/

#ifndef DISPLAY_SSD1309_H_
#define DISPLAY_SSD1309_H_
#if COMPONENT_DISPLAY_SSD1309

#include	<avr/io.h>
#include	<util/delay.h>
#include	"display_ssd1309_config.h"
#include	"display_ssd1309_defines.h"

#if SSD1309_USE_SPI
	#if COMPONENT_SPI_MASTER
		#include	"../spi_master/spi_master.h"
	#else
		#error		"This module requires COMPONENT_SPI_MASTER"
	#endif
#endif

#if SSD1309_USE_I2C
	#if COMPONENT_I2C_MASTER
		#include	"../i2c_master/i2c_master.h"
	#else
		#error		"This module requires COMPONENT_I2C_MASTER"
	#endif
#endif

// Fonts
#include	"font/console8x6.h"
#include	"font/dos8x8.h"
#include	"font/dos16x8.h"
#include	"font/sans8.h"
#include	"font/sans16.h"
#include	"font/sans16B.h"
#include	"font/sans16_PL.h"
#include	"font/sans16B_PL.h"
#include	"font/sans24.h"
#include	"font/sans24B.h"
#include	"font/sans24_PL.h"
#include	"font/sans24B_PL.h"

// Bitmaps
#include	"bitmap/extronic_logo.h"

// ========================================
// Basic functions
// ========================================

void		SSD1309_Init(void);
void		SSD1309_WriteCommand(const uint8_t Command);
void		SSD1309_WriteData(const uint8_t Data);
void		SSD1309_ContrastSet(const uint8_t Value);
void		SSD1309_Clear(const uint8_t Pattern = 0);
void		SSD1309_Fill(void);
void		SSD1309_Chessboard(void);

// ========================================
// Cursor setting
// ========================================

uint8_t		SSD1309_CursorXGet(void);
void		SSD1309_CursorXSet(uint8_t PosX);
uint8_t		SSD1309_CursorPageGet(void);
void		SSD1309_CursorPageSet(uint8_t Page);

// ========================================
// Colors (black & white)
// ========================================

void		SSD1309_ColorSet(uint8_t Color);
uint8_t		SSD1309_ColorGet(void);

// ========================================
// Drawing
// ========================================

void		SSD1309_DrawPixel(uint8_t x, uint8_t y);
void		SSD1309_DrawLineHorizontal(uint8_t x0, uint8_t y0, uint8_t Length);
void		SSD1309_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length);
void		SSD1309_DrawLine(uint8_t x0, uint8_t y0, uint8_t x, uint8_t y);
void		SSD1309_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void		SSD1309_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void		SSD1309_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r);

// ========================================
// Bitmap
// ========================================

void		SSD1309_Bitmap(const SSD1309_Bitmap_t * Bitmap);

// ========================================
// Text
// ========================================

const SSD1309_FontDef_t * SSD1309_FontGet(void);
void		SSD1309_FontSet(const SSD1309_FontDef_t * Font);
uint16_t	SSD1309_TextWidth(const char * Text);
void		SSD1309_PrintChar(uint8_t Char);
void		SSD1309_Text(const char * Text, SSD1309_align_t Align = SSD1309_AlignNone);

// ========================================
// Testing
// ========================================

void		SSD1309_Slash(void);

#endif /* DISPLAY_SSD1309_H_ */
#endif
