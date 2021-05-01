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
#include	"display_ssd1351_config.h"
#include	"font/fontXF90_typedef.h"
#include	"bitmap/bitmapXF90_typedef.h"

#if COMPONENT_SPI_MASTER
	#include	"../spi_master/spi_master.h"
#else
	#error		"This module requires SPI_MASTER component"
#endif



// Komendy steruj¹ce SPI - sterowanie pinem DC
#define		SSD1351_DC_DATA						SSD1351_DC_PORT |=  SSD1351_DC_PIN
#define		SSD1351_DC_COMMAND					SSD1351_DC_PORT &= ~SSD1351_DC_PIN
#define		SSD1351_CHIP_SELECT					SSD1351_CS_PORT &= ~SSD1351_CS_PIN
#define		SSD1351_CHIP_DESELECT				SSD1351_CS_PORT |=  SSD1351_CS_PIN

// !! 
// Polecenia o d³ugoœc 1 bajta s¹ zrealizowane jako definicje, które nale¿y wywo³aæ poprzez SSD1351_WriteCommand()
#define		SSD1351_COLUMN_RANGE				0x15						// 01, ustawia zakres w którym porusza siê kursor
#define		SSD1351_ROW_RANGE					0x75						// 02, ustawia zakres w którym porusza siê kursor
#define		SSD1351_RAM_WRITE					0x5C						// 03, Start zapisuj grafiki do RAM
#define		SSD1351_RAM_READ					0x5D						// 04, Odczytywanie z RAM (nie dzia³a poprzez SPI)
#define		SSD1351_REMAP_COLOR_DEPTH			0xA0						// 05, 
#define		SSD1351_SET_DISPLAY_START_LINE		0xA1						// 06, Set vertical scroll by RAM from 0~127. [reset=00h]
#define		SSD1351_SET_DISPLAY_OFFSET			0xA2						// 07, Set vertical scroll by Row from 0-127. [reset=60h]
#define		SSD1351_SET_DISPLAY_MODE_OFF		0xA4						// 08a
#define		SSD1351_SET_DISPLAY_MODE_ON			0xA5						// 08b
#define		SSD1351_SET_DISPLAY_MODE_RESET		0xA6						// 08c
#define		SSD1351_SET_DISPLAY_MODE_INVERT		0xA7						// 08d
#define		SSD1351_FUNCTION_SELECTION			0xAB						// 09,
#define		SSD1351_NOP							0xAD						// 10
#define		SSD1351_SLEEP_MODE_ON				0xAE						// 11a
#define		SSD1351_SLEEP_MODE_OFF				0xAF						// 11b
#define		SSD1351_NOP2						0xB0						// 12
#define		SSD1351_SET_RESET_PRECHARGE			0xB1						// 13
#define		SSD1351_DISPLAY_ENHANCEMENT			0xB2						// 14
#define		SSD1351_CLOCK_DIVIDER_OSC_FREQ		0xB3						// 15
#define		SSD1351_SET_SEGMENT_LOW_VOLTAGE		0xB4						// 16
#define		SSD1351_SET_GPIO					0xB5						// 17
#define		SSD1351_SET_SECOND_PRECHARGE		0xB6						// 18
#define		SSD1351_LOOKUP_TABLE				0xB8						// 19
#define		SSD1351_USE_BUILTIN_LINEAR_LUT		0xB9						// 20
#define		SSD1351_SET_PRECHARGE_VOLTAGE		0xBB						// 21
#define		SSD1351_SET_VCOMH_VOLTAGE			0xBE						// 22
#define		SSD1351_SET_CONTRAST				0xC1						// 23
#define		SSD1351_MASTER_CONTRAST_CURRENT		0xC7						// 24
#define		SSD1351_SET_MUX_RATIO				0xCA						// 25
#define		SSD1351_NOP3						0xD1						// 26
#define		SSD1351_NOP4						0xE3						// 27
#define		SSD1351_SET_LOCK_COMMAND			0xFD						// 28
#define		SSD1351_HORIZONTAL_SCROLL			0x96						// 29
#define		SSD1351_STOP_MOVING					0x9E						// 30
#define		SSD1351_START_MOVING				0x9F						// 31


// Definicje kolorów							0bRRRRRGGGGGGBBBBB
#define		SSD1351_COLOR_BLACK_ID				0
#define		SSD1351_COLOR_BLACK_RGB565			0b0000000000000000
#define		SSD1351_COLOR_RED_ID				1
#define		SSD1351_COLOR_RED_RGB565			0b1111100000000000
#define		SSD1351_COLOR_GREEN_ID				2
#define		SSD1351_COLOR_GREEN_RGB565			0b0000011111100000
#define		SSD1351_COLOR_YELLOW_ID				3
#define		SSD1351_COLOR_YELLOW_RGB565			0b1111111111100000
#define		SSD1351_COLOR_BLUE_ID				4
#define		SSD1351_COLOR_BLUE_RGB565			0b0000000000011111
#define		SSD1351_COLOR_MAGENTA_ID			5
#define		SSD1351_COLOR_MAGENTA_RGB565		0b1111100000011111
#define		SSD1351_COLOR_CYAN_ID				6
#define		SSD1351_COLOR_CYAN_RGB565			0b0000011111111111
#define		SSD1351_COLOR_WHITE_ID				7
#define		SSD1351_COLOR_WHITE_RGB565			0b1111111111111111
#define		SSD1351_COLOR_GRAY_ID				8
#define		SSD1351_COLOR_GRAY_RGB565			0b1000010000010000
#define		SSD1351_COLOR_LIGHTRED_ID			9
#define		SSD1351_COLOR_LIGHTRED_RGB565		0b1111110000010000
#define		SSD1351_COLOR_LIGHTGREEN_ID			10
#define		SSD1351_COLOR_LIGHTGREEN_RGB565		0b1000011111110000
#define		SSD1351_COLOR_LIGHTYELLOW_ID		11
#define		SSD1351_COLOR_LIGHTYELLOW_RGB565	0b1111111111110000
#define		SSD1351_COLOR_LIGHTBLUE_ID			12
#define		SSD1351_COLOR_LIGHTBLUE_RGB565		0b1000010000011111
#define		SSD1351_COLOR_LIGHTMAGENTA_ID		13
#define		SSD1351_COLOR_LIGHTMAGENTA_RGB565	0b1111110000011111
#define		SSD1351_COLOR_LIGHTCYAN_ID			14
#define		SSD1351_COLOR_LIGHTCYAN_RGB565		0b1000011111111111
#define		SSD1351_COLOR_LIGHTGRAY_ID			15
#define		SSD1351_COLOR_LIGHTGRAY_RGB565		0b1100011000011000

// Definicje wyrównania tekstu dla funkcji SSD1351_Text
#define		SSD1351_HALIGN_NONE					0x00
#define		SSD1351_HALIGN_LEFT					0x01
#define		SSD1351_HALIGN_CENTER				0x02
#define		SSD1351_HALIGN_RIGHT				0x03
#define		SSD1351_HALIGN_JUSTIFY				0x04
#define		SSD1351_VALIGN_NONE					0x00
#define		SSD1351_VALIGN_TOP					0x10
#define		SSD1351_VALIGN_CENTER				0x20
#define		SSD1351_VALIGN_BOTTOM				0x30

// Funkcje elementarne
void		SSD1351_Init(void);
void		SSD1351_WriteCommand(const uint8_t Command);
void		SSD1351_WriteData(const uint8_t Data);
void		SSD1351_WriteRamEnable(void);

void		SSD1351_ContrastSet(const uint8_t Value);
void		SSD1351_Clear(void);					// Ustawienie Pattern innego ni¿ domyœlny pozwala zape³niæ wyœwietlacz wzorem
void		SSD1351_Chessboard(void);

// Ustawianie kursora
void		SSD1351_CursorSet(uint8_t x, uint8_t y);
uint8_t		SSD1351_CursorXGet(void);
void		SSD1351_CursorXSet(uint8_t x);
uint8_t		SSD1351_CursorYGet(void);
void		SSD1351_CursorYSet(uint8_t y);

// Obszar roboczy
void		SSD1351_ActiveAreaSet(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);
void		SSD1351_ActiveAreaXSet(uint8_t x1, uint8_t x2);
void		SSD1351_ActiveAreaYSet(uint8_t y1, uint8_t y2);

// Kolory
uint16_t	SSD1351_ColorFrontGet(void);
void		SSD1351_ColorFrontSet(uint16_t ColorRGB565);
void		SSD1351_ColorFrontSet(uint8_t R, uint8_t G, uint8_t B);
uint16_t	SSD1351_ColorBackGet(void);
void		SSD1351_ColorBackSet(uint16_t ColorRGB565);
void		SSD1351_ColorBackSet(uint8_t R, uint8_t G, uint8_t B);
uint16_t	SSD1351_ColorNameToRGB565(uint8_t ColorName);
uint16_t	SSD1351_ColorRGB888toRGB565(uint8_t R, uint8_t G, uint8_t B);

uint16_t	SSD1351_ColorRGB332toRGB565(uint8_t Color332);
// Podstawowe funkcje geometryczne i rysowanie bitmap
void		SSD1351_DrawPixel(uint8_t x, uint8_t y);
void		SSD1351_DrawLineHorizontal(uint8_t x0, uint8_t y0, uint8_t Length);
void		SSD1351_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length);
void		SSD1351_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void		SSD1351_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void		SSD1351_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void		SSD1351_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r);

// Bitmapy
void		SSD1351_BitmapMono(const BitmapXF90_t * Bitmap);
void		SSD1351_BitmapRGB565(const BitmapXF90_t * Bitmap);
void		SSD1351_BitmapRGB332(const BitmapXF90_t * Bitmap);

// Napisy
const fontXF90_def_t * SSD1351_FontGet(void);
void		SSD1351_FontSet(const fontXF90_def_t * Font);
uint8_t		SSD1351_TextWidth(const char * Text);
void		SSD1351_PrintChar(uint8_t Char, uint8_t Negative = 0);
void		SSD1351_Text(const char * Text, uint8_t Align = 0, uint8_t Negative = 0);

#endif /* DISPLAY_SSD1351_H_ */
#endif
