/*
OPIS
		-	Wy�wietlacz SH1106 z interfejsem I2C/SPI
UWAGI
		-	Zapisywanie w trubie RMW (Read-Mofidy-Write) zajmuje ponad 6x wi�cej czasu ni� w trybie normalnym
	
PERFORMANCE TEST
		-	SPI mode, clock frequency 10 MHz
			-	Clear	1024 us, 976 FPS
			-	Fill	1024 us, 976 FPS
			-	Chess	1824 us, 548 FPS
			-	Pixel	11 us, 90909 FPS
			
CHANGELOG
1.01	*	Usuni�cie Spi_0() ze wszystkich funkcji
1.00	*	Zako�czenie prac nad podstawow� wersj� biblioteki SH1106
0.23	+	SH1106_InitPort() aby m�c zainicjalizowa� pin steruj�cy SPI wszystkich uk�ad�w pod��czonym pod jeden port SPI,
			a dopiero p�niej inicjalizowa� sterownik wy�wietlacza
0.22	+	Czcionki Sans z polskimi znakami
0.21	+	Obs�uga interfejsu SPI
		!	Poprawienie b��du w SH1106_DrawLineVertical() i SH1106_DrawRectangleFill() gdzie w przypadku d�ugo�ci linii b�d�cych 
			wielokrotno�ci� 8 kasowany by� jeden bajt na stronie poni�ej ko�ca linii
		*	Optymalizacja funkcji SH1106_DrawRectangleFill() by dzia�a�a szybciej
0.20	*	Zmieniono pliki czcionek na cpp i h, a definicje struktur fontR_info_t i fontR_def_t przeniesiono do pliku fontR_typedef
		+	Poprawienie i optymalizacja funkcji Bitmap, dodanie trybu RMW
		*	void SH1106_Bitmap(const uint8_t * Bitmap, const uint8_t Pages, const uint8_t Pixels, SH1106_rmw_t RmwMode = RmwNone);
0.19	+	void SH1106_Bitmap(const uint8_t * Bitmap, const uint8_t Length, const uint8_t Height);
0.18	*	Wydzielenie tablicy bitmap wszystkich czcionek do progmem
0.17	+	Nowa czcionka FontDos8x8
		+	Konfiguracja wydzielona do pliku display_sh1106_config.h
		+	Definicja SH1106_USE_RMW pozwalaj�ca zrezygnowa� z RMW je�li nie ma takiej potrzeby
0.16	+	Nowa czcionka FontDos16x8
		*	Poprawienie b��du w SH1106_PrintChar(), bo nie epokazywa�o dobrze znak�w o sta�ej szeroko�ci i wysoko�ci wi�kszej ni� 1 linia
		+	Dodanie Spacing do struktury _fontR_definition, aby ustali� odst�p mi�dzy znakami dla r�nych czcionek
		*	Modyfikacja SH1106_PrintChar() i SH1106_TextWidth() aby uwzgl�dnia� zmienny odst�p mi�dzy znakami
0.15	*	Pliki czcionek przeniesione do katalogu Font
		+	void SH1106_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r, SH1106_rmw_t RmwMode);
		+	void SH1106_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, SH1106_rmw_t RmwMode);
		+	void SH1106_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, SH1106_rmw_t RmwMode);
		*	Moyfikacja funkcji tekstowych, �eby obs�ugiwa�y RMW
		*	void SH1106_PrintChar(uint8_t Char, uint8_t Negative = 0, SH1106_rmw_t RmwMode = RmwNone);
		*	void SH1106_Text(const char * Text, SH1106_align_t Align = AlignNone, uint8_t Negative = 0, SH1106_rmw_t RmwMode = RmwNone);
0.14	+	void SH1106_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length, SH1106_rmw_t RmwMode = RmwNone);
		+	void SH1106_DrawLine(uint8_t x0, uint8_t y0, uint8_t x, uint8_t y, SH1106_rmw_t RmwMode = RmwNone);
		-	Niepotrzebne funkcje do inicjalizacji
0.13	+	Obs�uga read modify write przez I2C
			void SH1106_RmwStart(void);
			void SH1106_RmwExe(uint8_t Byte, SH1106_rmw_t Mode);
			void SH1106_RmwEnd()
		+	void SH1106_DrawPixel(uint8_t x, uint8_t y, SH1106_rmw_t RmwMode = RmwNone);
		+	void SH1106_DrawLineHorizontal(uint8_t x, uint8_t y, uint8_t Length, SH1106_rmw_t RmwMode = RmwNone);
		+	static const uint8_t SH1106_InitSequence[]
		*	Optymalizacja - odchudzenie programu o 464B
0.12	*	Modyfikacja w celu zgodno�ci z wy�wietlaczem 1,3" i 0,9"
		+	#define SH1106_OFFSET_X 2, bo jak si� okazuje inny wy�wietlacz tego samego typu ma offset w matrycy i obraz jest przesuni�ty
0.11	+	void SH1106_DrawLineHorizontal(uint8_t X, uint8_t Y, uint8_t Length);
0.10	*	Analiza sekwencji inicjalizacyjnej, w niekt�rych przypadkach trzeba wstawi� Twi_Write(SH1106_COMMAND_BYTE) pomi�dzy bajtami, np 
			przy ustawianiu kontrastu
0.09	*	Poprawienie b��du w SH1106_CursorLineSet przez kt�ry rozdzielczo�� wy�wietlacza by�a ograniczona do 128x56
		+	Dodatkowe definicje i opisy komend
0.08	+	void SH1106_DrawPixel(uint8_t X, uint8_t Y);
		+	void SH1106_ContrastSet(uint8_t Value);
		+	void SH1106_OffsetComsSet(uint8_t Value);
		+	void SH1106_CommonPadsHardware(bool Alternative);
		*	B��d w konfiguracji wy�wietlacza - w rezultacie rozdzielczo�� zosta�a zmniejszona do 128x56
0.07	+	Wy�wietlanie tekstu w negatywie
		+	void SH1106_Text(const char * Text, Align_t Align = None, uint8_t Negative = 0);
		+	uint16_t SH1106_TextWidth(const char * Text);
0.06	*	Zako�czenie prac nad funkcj� wy�wietlaqj�c� znaki o r�nej wysoko�ci i szeroko�ci
		+	fontR_definition_t SH1106_Font; jako zmienna globalna do przechowywania nazwy u�ywanej czcionki
0.05	*	Rozbudowa funkcji SH1106_PrintCharUniversal by obs�ugiwa�a czcionki o r�nych wysoko�ciach i szeroko�ciach
0.04	*	Rozbudowa funkcji do czcionek
		*	Budowa uniwersalnego formatu czcionki
		*	Poprawienie b��du w funkcji ustawiaj�cej pozycj� kursora
0.03	*	Uporz�dkowanie podstawowych funkcji
0.02	*	Dalszy rozw�j
0.01	*	Pierwsze wydanie

HARDWARE
		-	I2C
*/

#ifndef DISPLAY_SH1106_H_
#define DISPLAY_SH1106_H_
#if COMPONENT_DISPLAY_SH1106

#include	<avr/io.h>
#include	<util/delay.h>
#include	"display_sh1106_config.h"
#include	"display_sh1106_defines.h"
//#include	"FontR/fontR_typedef.h"

#if SH1106_USE_SPI 
	#if COMPONENT_SPI_MASTER
		#include	"../spi_master/spi_master.h"
	#else
		#error		"This module requires SPI_MASTER component"
	#endif
#endif

#if SH1106_USE_I2C
	#if COMPONENT_I2C_MASTER
		#include	"../i2c_master/i2c_master.h"
	#else
		#error		"This module requires I2C_MASTER component"
	#endif
#endif

#if SH1106_FONT_CONSOLE8x6
	#include	"font/console8x6.h"
#endif

#if SH1106_FONT_DOS8x8
	#include	"font/dos8x8.h"
#endif

#if SH1106_FONT_DOS16x8
	#include	"font/dos16x8.h"
#endif

#if SH1106_FONT_SANS8
	#include	"font/sans8.h"
#endif

#if SH1106_FONT_SANS16
	#include	"font/sans16.h"
#endif

#if SH1106_FONT_SANS16B
	#include	"font/sans16B.h"
#endif

#if SH1106_FONT_SANS16_PL
	#include	"font/sans16_PL.h"
#endif

#if SH1106_FONT_SANS16B_PL
	#include	"font/sans16B_PL.h"
#endif

#if SH1106_FONT_SANS24
	#include	"font/sans24.h"
#endif

#if SH1106_FONT_SANS24B
	#include	"font/sans24B.h"
#endif

#if SH1106_FONT_SANS24_PL
	#include	"font/sans24_PL.h"
#endif

#if SH1106_FONT_SANS24B_PL
	#include	"font/sans24B_PL.h"
#endif

#if SH1106_BITMAP_EXTRONIC_LOGO
	#include	"bitmap/extronic_logo.h"
#endif


// ========================================
// Basic functions
// ========================================

void		SH1106_Init(void);
void		SH1106_WriteCommand(const uint8_t Command);
void		SH1106_WriteData(const uint8_t Data);
void		SH1106_ContrastSet(const uint8_t Value);
void		SH1106_Clear(const uint8_t Pattern = 0);					// Ustawienie Pattern innego ni� domy�lny pozwala zape�ni� wy�wietlacz wzorem
void		SH1106_BackgroundGray(void);

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
void		SH1106_RmwStart(void);
void		SH1106_RmwExe(uint8_t Byte, SH1106_rmw_t Mode);
void		SH1106_RmwEnd();
#endif

// ========================================
// Drawing
// ========================================

#if SH1106_USE_RMW
void		SH1106_DrawPixel(uint8_t x, uint8_t y, SH1106_rmw_t RmwMode = SH1106_RmwNone);
void		SH1106_DrawLineHorizontal(uint8_t x0, uint8_t y0, uint8_t Length, SH1106_rmw_t RmwMode = SH1106_RmwNone);
void		SH1106_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length, SH1106_rmw_t RmwMode = SH1106_RmwNone);
void		SH1106_DrawLine(uint8_t x0, uint8_t y0, uint8_t x, uint8_t y, SH1106_rmw_t RmwMode = SH1106_RmwNone);
void		SH1106_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, SH1106_rmw_t RmwMode = SH1106_RmwNone);
void		SH1106_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, SH1106_rmw_t RmwMode = SH1106_RmwNone);
void		SH1106_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r, SH1106_rmw_t RmwMode = SH1106_RmwNone);
void		SH1106_Bitmap(const uint8_t * Bitmap, const uint8_t Pages, const uint8_t Pixels, SH1106_rmw_t RmwMode = SH1106_RmwNone);
#else
void		SH1106_DrawPixel(uint8_t x, uint8_t y);
void		SH1106_DrawLineHorizontal(uint8_t x0, uint8_t y0, uint8_t Length);
void		SH1106_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length);
void		SH1106_DrawLine(uint8_t x0, uint8_t y0, uint8_t x, uint8_t y);
void		SH1106_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void		SH1106_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void		SH1106_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r);
void		SH1106_Bitmap(const SH1106_Bitmap_t * Bitmap);
#endif

// ========================================
// Text
// ========================================

const SH1106_FontDef_t * SH1106_FontGet(void);
void SH1106_FontSet(const SH1106_FontDef_t * Font);
// uint16_t	SH1106_TextWidth(const char * Text);
// #if SH1106_USE_RMW
// void		SH1106_PrintChar(uint8_t Char, uint8_t Negative = 0, SH1106_rmw_t RmwMode = SH1106_RmwNone);
// void		SH1106_Text(const char * Text, SH1106_align_t Align = SH1106_AlignNone, uint8_t Negative = 0, SH1106_rmw_t RmwMode = SH1106_RmwNone);
// #else
void		SH1106_PrintChar(uint8_t Char, uint8_t Negative = 0);
void		SH1106_Text(const char * Text, SH1106_align_t Align = SH1106_AlignNone, uint8_t Negative = 0);
//#endif

// ========================================
// Testing
// ========================================

void		SH1106_Slash(void);
void		SH1106_Chessboard(void);
void		SH1106_Fill(void);

#endif /* DISPLAY_SH1106_H_ */
#endif
