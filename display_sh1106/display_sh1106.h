/*
DESCRIPTION
		-	Display with SH1106 driver
		
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

#ifndef DISPLAY_SH1106_H_
#define DISPLAY_SH1106_H_
#if COMPONENT_DISPLAY_SH1106

#include	<avr/io.h>
#include	<util/delay.h>
#include	"display_sh1106_config.h"
#include	"display_sh1106_defines.h"

#if SH1106_USE_SPI
	#if COMPONENT_SPI_MASTER
		#include	"../spi_master/spi_master.h"
	#else
		#error		"This module requires COMPONENT_SPI_MASTER"
	#endif
#endif

#if SH1106_USE_I2C
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

void		SH1106_Init(void);
void		SH1106_WriteCommand(const uint8_t Command);
void		SH1106_WriteData(const uint8_t Data);
void		SH1106_ContrastSet(const uint8_t Value);
void		SH1106_Clear(const uint8_t Pattern = 0);
void		SH1106_Fill(void);
void		SH1106_Chessboard(void);

// ========================================
// Cursor setting
// ========================================

uint8_t		SH1106_CursorXGet(void);
void		SH1106_CursorXSet(uint8_t PosX);
uint8_t		SH1106_CursorPageGet(void);
void		SH1106_CursorPageSet(uint8_t Page);

// ========================================
// Read-Modify-Write Mode
// ========================================

#if SH1106_USE_RMW
	void	SH1106_RmwStart(void);
	void	SH1106_RmwExecute(uint8_t Byte);
	void	SH1106_RmwEnd();
#endif

// ========================================
// Colors (black & white)
// ========================================

void		SH1106_ColorSet(uint8_t Color);
uint8_t		SH1106_ColorGet(void);

// ========================================
// Drawing
// ========================================

void		SH1106_DrawPixel(uint8_t x, uint8_t y);
void		SH1106_DrawLineHorizontal(uint8_t x0, uint8_t y0, uint8_t Length);
void		SH1106_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length);
void		SH1106_DrawLine(uint8_t x0, uint8_t y0, uint8_t x, uint8_t y);
void		SH1106_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void		SH1106_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void		SH1106_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r);

// ========================================
// Bitmap
// ========================================

void		SH1106_Bitmap(const SH1106_Bitmap_t * Bitmap);

// ========================================
// Text
// ========================================

const SH1106_FontDef_t * SH1106_FontGet(void);
void		SH1106_FontSet(const SH1106_FontDef_t * Font);
uint16_t	SH1106_TextWidth(const char * Text);
void		SH1106_PrintChar(uint8_t Char);
void		SH1106_Text(const char * Text, SH1106_align_t Align = SH1106_AlignNone);

// ========================================
// Testing
// ========================================

void		SH1106_Slash(void);

#endif /* DISPLAY_SH1106_H_ */
#endif
