/*
OPIS
		-	Wyœwietlacz SSD1351 z interfejsem SPI
UWAGI
		-	Dodaæ zabezpieczenie przed wyœwietleniem znaku, który wychdozi poza ekran
		-	Coœ nie dzia³a przy SSD1351_DrawRectangle przy parametrach granicznych
		-	Komendy sterownika
		-	Bitmapy kolorowe
	
CHANGELOG
0.15	+	uint16_t SSD1351_ColorRGB332toRGB565(uint8_t Color332);
0.14	*	Usuniêcie Spi_0 ze wszystkich funkcji
0.13	+	void SSD1351_BitmapRGB565(const BitmapXF90_t * Bitmap);
0.12	+	void SSD1351_CursorSet(uint8_t x, uint8_t y);
		*	Zamiana struktury przechowuj¹cej dane aktualnej czcionki na wskaŸnik do struktury czcionki, oszczêdnoœæ 354B + 7B RAM
		+	void SSD1351_ContrastSet(const uint8_t Value)
		+	static const uint8_t SSD1351_InitSequence[]
		*	Optymalizacja funkcji SSD1351_Init(), oszczêdnoœæ 146B
0.11	+	uint16_t SSD1351_ColorRGB888toRGB565(uint8_t R, uint8_t G, uint8_t B);
0.10	+	Nowa czcionka fontXF90_Sans16B_PL
		+	Nowa czcionka fontXF90_Sans24_PL
0.09	+	Obs³uga bitmap monochromatycznych
		+	void SSD1351_BitmapMono(const uint8_t * Bitmap, const uint8_t WidthPixels, const uint8_t HeightPixels);
0.08	*	Obs³uga poslkich znaków
		*	Funckje do wyœwietlania napisów i wyrównywania ich
0.07	+	Nowa czcionka FontXF90_Sans16_PL
0.06	*	Modyfikacja funkcji SSD1351_PrintChar(), by obs³ugiwa³a znaki o ró¿nych szerokoœciach i wysokoœciach
0.05	*	Nowy format czcionek XF90, aby lepiej zoptymalizowaæ zu¿ycie pamiêci i szybkoœæ generowania napisów
0.04	+	uint16_t SSD1351_ColorNameToRGB565(uint8_t ColorName);
0.03	+	void SSD1351_ActiveAreaXSet(uint8_t x1, uint8_t x2);
		+	void SSD1351_ActiveAreaYSet(uint8_t y1, uint8_t y2);
		+	uint8_t SSD1351_CursorXGet(void);
		+	void SSD1351_CursorXSet(uint8_t PosX);
		+	uint8_t SSD1351_CursorYGet(void);
		+	void SSD1351_CursorYSet(uint8_t PosY);
		+	uint16_t SSD1351_ColorFrontGet(void);
		+	void SSD1351_ColorFrontSet(uint16_t ColorRGB565);
		+	void SSD1351_ColorFrontSet(uint8_t R, uint8_t G, uint8_t B);
		+	uint16_t SSD1351_ColorBackGet(void);
		+	void SSD1351_ColorBackSet(uint16_t ColorRGB565);
		+	void SSD1351_ColorBackSet(uint8_t R, uint8_t G, uint8_t B);
		+	void SSD1351_DrawPixel(uint8_t x, uint8_t y);
		+	void SSD1351_DrawLineHorizontal(uint8_t x0, uint8_t y0, uint8_t Length);
		+	void SSD1351_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length);
		+	void SSD1351_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
		+	void SSD1351_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
		+	void SSD1351_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
		+	void SSD1351_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r)
		+	SSD1351_PrintChar() dla czcionek o sta³ej szerokoœci 8 pikseli
		+	Font/font_Dos8x8.h
		+	Font/font_Dos16x8.h
		+	Definicje kolorów 4-bitowych
0.02	+	void SSD1351_CursorPosxSet(uint8_t PosX);
		+	void SSD1351_CursorPosySet(uint8_t PosY);
		+	void SSD1351_Clear();
0.01	*	Pierwsze wydanie, adaptacja biblioteki SD1106

HARDWARE
		-	I2C
*/

#ifndef DISPLAY_SSD1351_H_
#define DISPLAY_SSD1351_H_
#if COMPONENT_DISPLAY_SSD1351

// ========================================
// Includes
// ========================================

#include	<avr/io.h>
#include	<util/delay.h>
#include	"display_ssd1351_defines.h"
#include	"display_ssd1351_config.h"

#if COMPONENT_SPI_MASTER
	#include	"../spi_master/spi_master.h"
#else
	#error		"This module requires SPI_MASTER component"
#endif

#if SSD1351_FONT_CONSOLE8x8
	#include	"font/console8x6.h"
#endif

#if SSD1351_FONT_DOS8x8
	#include	"font/dos8x8.h"
#endif

#if SSD1351_FONT_DOS16x8
	#include	"font/dos16x8.h"
#endif

#if SSD1351_FONT_SANS16_PL
	#include	"font/sans16_PL.h"
#endif

#if SSD1351_FONT_SANS16B_PL
	#include	"font/sans16B_PL.h"
#endif

#if SSD1351_FONT_SANS24_PL
	#include	"font/sans24_PL.h"
#endif

#if SSD1351_BITMAP_TEST_PATTERN
	#include	"bitmap/test_pattern.h"
#endif

#if SSD1351_BITMAP_EXTRONIC_LOGO
	#include	"bitmap/extronic_logo.h"
#endif

#if SSD1351_BITMAP_EXTRONIC_LOGO_RGB565
	#include	"bitmap/extronic_logo_rgb565.h"
#endif

// ========================================
// Basic functions
// ========================================

void		SSD1351_Init(void);
void		SSD1351_WriteCommand(const uint8_t Command);
void		SSD1351_WriteData(const uint8_t Data);
void		SSD1351_WriteRamEnable(void);
void		SSD1351_ContrastSet(const uint8_t Value);
void		SSD1351_Clear(void);
void		SSD1351_Chessboard(void);

// ========================================
// Cursor and active area
// ========================================

void		SSD1351_CursorSet(uint8_t x, uint8_t y);
uint8_t		SSD1351_CursorXGet(void);
void		SSD1351_CursorXSet(uint8_t x);
uint8_t		SSD1351_CursorYGet(void);
void		SSD1351_CursorYSet(uint8_t y);
void		SSD1351_ActiveAreaSet(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);
void		SSD1351_ActiveAreaXSet(uint8_t x1, uint8_t x2);
void		SSD1351_ActiveAreaYSet(uint8_t y1, uint8_t y2);

// ========================================
// Colors
// ========================================

uint16_t	SSD1351_ColorFrontGet(void);
void		SSD1351_ColorFrontSet(uint16_t ColorRGB565);
void		SSD1351_ColorFrontSet(uint8_t R, uint8_t G, uint8_t B);
uint16_t	SSD1351_ColorBackGet(void);
void		SSD1351_ColorBackSet(uint16_t ColorRGB565);
void		SSD1351_ColorBackSet(uint8_t R, uint8_t G, uint8_t B);
uint16_t	SSD1351_ColorNameToRGB565(uint8_t ColorName);
uint16_t	SSD1351_ColorRGB888toRGB565(uint8_t R, uint8_t G, uint8_t B);
uint16_t	SSD1351_ColorRGB332toRGB565(uint8_t Color332);

// ========================================
// Drawing
// ========================================

void		SSD1351_DrawPixel(uint8_t x, uint8_t y);
void		SSD1351_DrawLineHorizontal(uint8_t x0, uint8_t y0, uint8_t Length);
void		SSD1351_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length);
void		SSD1351_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void		SSD1351_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void		SSD1351_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void		SSD1351_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r);

// ========================================
// BBitmaps
// ========================================

void		SSD1351_Bitmap(const SSD1351_Bitmap_t * Bitmap);
void		SSD1351_BitmapMono(const SSD1351_Bitmap_t * Bitmap);
void		SSD1351_BitmapRGB565(const SSD1351_Bitmap_t * Bitmap);
void		SSD1351_BitmapRGB332(const SSD1351_Bitmap_t * Bitmap);

// ========================================
// Text
// ========================================

const SSD1351_FontDef_t * SSD1351_FontGet(void);
void		SSD1351_FontSet(const SSD1351_FontDef_t * Font);
uint8_t		SSD1351_TextWidthGet(const char * Text);
void		SSD1351_PrintChar(uint8_t Char, uint8_t Negative = 0);
void		SSD1351_Text(const char * Text, uint8_t Align = 0, uint8_t Negative = 0);

#endif /* DISPLAY_SSD1351_H_ */
#endif
