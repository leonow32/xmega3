/*
OPIS
		-	Wyœwietlacz SH1106 z interfejsem I2C/SPI
UWAGI
		-	Zapisywanie w trubie RMW (Read-Mofidy-Write) zajmuje ponad 6x wiêcej czasu ni¿ w trybie normalnym
	
CHANGELOG
1.01	*	Usuniêcie Spi_0() ze wszystkich funkcji
1.00	*	Zakoñczenie prac nad podstawow¹ wersj¹ biblioteki SH1106
0.23	+	SH1106_InitPort() aby móc zainicjalizowaæ pin steruj¹cy SPI wszystkich uk³adów pod³¹czonym pod jeden port SPI,
			a dopiero póŸniej inicjalizowaæ sterownik wyœwietlacza
0.22	+	Czcionki Sans z polskimi znakami
0.21	+	Obs³uga interfejsu SPI
		!	Poprawienie b³êdu w SH1106_DrawLineVertical() i SH1106_DrawRectangleFill() gdzie w przypadku d³ugoœci linii bêd¹cych 
			wielokrotnoœci¹ 8 kasowany by³ jeden bajt na stronie poni¿ej koñca linii
		*	Optymalizacja funkcji SH1106_DrawRectangleFill() by dzia³a³a szybciej
0.20	*	Zmieniono pliki czcionek na cpp i h, a definicje struktur fontR_info_t i fontR_def_t przeniesiono do pliku fontR_typedef
		+	Poprawienie i optymalizacja funkcji Bitmap, dodanie trybu RMW
		*	void SH1106_Bitmap(const uint8_t * Bitmap, const uint8_t Pages, const uint8_t Pixels, SH1106_rmw_t RmwMode = RmwNone);
0.19	+	void SH1106_Bitmap(const uint8_t * Bitmap, const uint8_t Length, const uint8_t Height);
0.18	*	Wydzielenie tablicy bitmap wszystkich czcionek do progmem
0.17	+	Nowa czcionka FontDos8x8
		+	Konfiguracja wydzielona do pliku display_sh1106_config.h
		+	Definicja SH1106_USE_RMW pozwalaj¹ca zrezygnowaæ z RMW jeœli nie ma takiej potrzeby
0.16	+	Nowa czcionka FontDos16x8
		*	Poprawienie b³êdu w SH1106_PrintChar(), bo nie epokazywa³o dobrze znaków o sta³ej szerokoœci i wysokoœci wiêkszej ni¿ 1 linia
		+	Dodanie Spacing do struktury _fontR_definition, aby ustaliæ odstêp miêdzy znakami dla ró¿nych czcionek
		*	Modyfikacja SH1106_PrintChar() i SH1106_TextWidth() aby uwzglêdniaæ zmienny odstêp miêdzy znakami
0.15	*	Pliki czcionek przeniesione do katalogu Font
		+	void SH1106_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r, SH1106_rmw_t RmwMode);
		+	void SH1106_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, SH1106_rmw_t RmwMode);
		+	void SH1106_DrawRectangleFill(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, SH1106_rmw_t RmwMode);
		*	Moyfikacja funkcji tekstowych, ¿eby obs³ugiwa³y RMW
		*	void SH1106_PrintChar(uint8_t Char, uint8_t Negative = 0, SH1106_rmw_t RmwMode = RmwNone);
		*	void SH1106_Text(const char * Text, SH1106_align_t Align = AlignNone, uint8_t Negative = 0, SH1106_rmw_t RmwMode = RmwNone);
0.14	+	void SH1106_DrawLineVertical(uint8_t x0, uint8_t y0, uint8_t Length, SH1106_rmw_t RmwMode = RmwNone);
		+	void SH1106_DrawLine(uint8_t x0, uint8_t y0, uint8_t x, uint8_t y, SH1106_rmw_t RmwMode = RmwNone);
		-	Niepotrzebne funkcje do inicjalizacji
0.13	+	Obs³uga read modify write przez I2C
			void SH1106_RmwStart(void);
			void SH1106_RmwExe(uint8_t Byte, SH1106_rmw_t Mode);
			void SH1106_RmwEnd()
		+	void SH1106_DrawPixel(uint8_t x, uint8_t y, SH1106_rmw_t RmwMode = RmwNone);
		+	void SH1106_DrawLineHorizontal(uint8_t x, uint8_t y, uint8_t Length, SH1106_rmw_t RmwMode = RmwNone);
		+	static const uint8_t SH1106_InitSequence[]
		*	Optymalizacja - odchudzenie programu o 464B
0.12	*	Modyfikacja w celu zgodnoœci z wyœwietlaczem 1,3" i 0,9"
		+	#define SH1106_OFFSET_X 2, bo jak siê okazuje inny wyœwietlacz tego samego typu ma offset w matrycy i obraz jest przesuniêty
0.11	+	void SH1106_DrawLineHorizontal(uint8_t X, uint8_t Y, uint8_t Length);
0.10	*	Analiza sekwencji inicjalizacyjnej, w niektórych przypadkach trzeba wstawiæ Twi_Write(SH1106_COMMAND_BYTE) pomiêdzy bajtami, np 
			przy ustawianiu kontrastu
0.09	*	Poprawienie b³êdu w SH1106_CursorLineSet przez który rozdzielczoœæ wyœwietlacza by³a ograniczona do 128x56
		+	Dodatkowe definicje i opisy komend
0.08	+	void SH1106_DrawPixel(uint8_t X, uint8_t Y);
		+	void SH1106_ContrastSet(uint8_t Value);
		+	void SH1106_OffsetComsSet(uint8_t Value);
		+	void SH1106_CommonPadsHardware(bool Alternative);
		*	B³¹d w konfiguracji wyœwietlacza - w rezultacie rozdzielczoœæ zosta³a zmniejszona do 128x56
0.07	+	Wyœwietlanie tekstu w negatywie
		+	void SH1106_Text(const char * Text, Align_t Align = None, uint8_t Negative = 0);
		+	uint16_t SH1106_TextWidth(const char * Text);
0.06	*	Zakoñczenie prac nad funkcj¹ wyœwietlaqj¹c¹ znaki o ró¿nej wysokoœci i szerokoœci
		+	fontR_definition_t SH1106_Font; jako zmienna globalna do przechowywania nazwy u¿ywanej czcionki
0.05	*	Rozbudowa funkcji SH1106_PrintCharUniversal by obs³ugiwa³a czcionki o ró¿nych wysokoœciach i szerokoœciach
0.04	*	Rozbudowa funkcji do czcionek
		*	Budowa uniwersalnego formatu czcionki
		*	Poprawienie b³êdu w funkcji ustawiaj¹cej pozycjê kursora
0.03	*	Uporz¹dkowanie podstawowych funkcji
0.02	*	Dalszy rozwój
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

// Typy abstrakcyjne
enum SH1106_align_t {
	SH1106_AlignNone, 
	SH1106_AlignLeft,
	SH1106_AlignRight, 
	SH1106_AlignCenter
};

#if SH1106_USE_RMW
enum SH1106_rmw_t {
	SH1106_RmwNone,
	SH1106_RmwAdd,
	SH1106_RmwSub,
	SH1106_RmwInv
};
#endif

// Komendy steruj¹ce I2C - decyduj¹ czy nastêpny przes³any bajt to dane do wyœwietlenia czy polecenie
#if SH1106_USE_I2C
#define		SH1106_COMMAND_BYTE				0x80
#define		SH1106_DATA_BYTE				0x40
#define		SH1106_CoDATA_BYTE				0xC0
#endif

// Polecenia o d³ugoœc 1 bajta s¹ zrealizowane jako definicje, które nale¿y wywo³aæ poprzez SH1106_WriteCommand()
#define		SH1106_COLUMN_LOW(Nibble)		(0x00 | (Nibble))			// 01, m³odsze 4 bity pozycji X
#define		SH1106_COLUMN_HIGH(Nibble)		(0x10 | (Nibble))			// 02, starsze 4 bity pozycji X
#define		SH1106_PUMP_VOLTAGE(Value)		(0x30 | (Value))			// 03, napiêcie przetwornicy, domyœlne 10, zakres od 0x00..0x03
#define		SH1106_START_LINE(Line)			(0x40 | (Line))				// 04, offset pionowy, wiêkszanie powoduje przesuwanie w górê, zakres 0..63
#define		SH1106_CONTRAST					0x81						// 05, kontrast nale¿y podaæ w kolejnym bajcie (0...255)
#define		SH1106_REMAP(ADC)				(0xA0 | (ADC))				// 06, 1 wyœwietla praiwd³owo, 0 lustrzane odbicie
#define		SH1106_ENTRIE_DISPLAY_ON(On)	(0xA4 | (On))				// 07, 1 ca³y wyœwietlacz bia³y, 0 normalna praca
#define		SH1106_NORMAL_REVERSE(Select)	(0xA6 | (Select))			// 08, 1 negatyw, 0 pozytyw
#define		SH1106_MULTIPLEX_RATIO			0xA8						// 09, wartoœæ w kolejnym bajcie
#define		SH1106_DCDC_ON_OFF				0xAD						// 10, wartoœæ w kolejnym bajcie
#define		SH1106_DISPLAY_ON_OFF(Select)	(0xAE | (Select))			// 11, 1 wyœwietlacz w³¹czony, 0 wy³¹czony
#define		SH1106_DISPLAY_ON				0xAF						// 11, to samo co wy¿ej, ale ju¿ z wpisanym argumentem
#define		SH1106_DISPLAY_OFF				0xAE						// 11, to samo co wy¿ej, ale ju¿ z wpisanym argumentem
#define		SH1106_PAGE(Page)				(0xB0 | (Page))				// 12, numer linii licz¹c od góry
#define		SH1106_SCAN_DIRECTION(Value)	(0xC0 | (Value))			// 13, 1 skanowanie od COM63 do COM0, 0 od COM0 do COM63
#define		SH1106_DISPLAY_OFFSET			0xD3						// 14, argument w kolejnym bajcie, zakres 0..63
#define		SH1106_CLOCK_DIV_FREQ			0xD5						// 15, argument w kolejnym bajcie, czytaæ datasheet
#define		SH1106_CHARGE_PERIOD			0xD9						// 16, argument w kolejnym bajcie, czytaæ datasheet
#define		SH1106_COMMON_PADS_HW_CONFIG	0xDA						// 17, argument w kolejnym bajcie, czytaæ datasheet
#define		SH1106_VCOM_DESELECT_LEVEL		0xDB						// 18, argument w kolejnym bajcie, czytaæ datasheet
#define		SH1106_READ_MODIFY_WRITE		0xE0						// 19, nie wiadomo co to robi
#define		SH1106_END						0xEE						// 20, nie wiadomo co to robi
#define		SH1106_NOP						0xE3						// 21
#define		SH1106_CHARGE_PUMP				0x8D						// polecenie, któego nie ma w datasheecie


// Funkcje elementarne
void		SH1106_Init(void);
void		SH1106_WriteCommand(const uint8_t Command);
void		SH1106_WriteData(const uint8_t Data);
void		SH1106_ContrastSet(const uint8_t Value);
void		SH1106_Clear(const uint8_t Pattern = 0);					// Ustawienie Pattern innego ni¿ domyœlny pozwala zape³niæ wyœwietlacz wzorem
void		SH1106_BackgroundGray(void);

// Ustawianie kursora
uint8_t		SH1106_CursorPosxGet(void);
void		SH1106_CursorPosxSet(uint8_t PosX);
uint8_t		SH1106_CursorPageGet(void);
void		SH1106_CursorPageSet(uint8_t Page);

// Obs³uga trybu Read-Modify_Write
#if SH1106_USE_RMW
void		SH1106_RmwStart(void);
void		SH1106_RmwExe(uint8_t Byte, SH1106_rmw_t Mode);
void		SH1106_RmwEnd();
#endif

// Podstawowe funkcje geometryczne i rysowanie bitmap
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
void		SH1106_Bitmap(const uint8_t * Bitmap, const uint8_t Pages, const uint8_t Pixels);
#endif

// Napisy
// fontR_def_t	SH1106_FontGet(void);
// void		SH1106_FontSet(fontR_def_t Font);
// uint16_t	SH1106_TextWidth(const char * Text);
// #if SH1106_USE_RMW
// void		SH1106_PrintChar(uint8_t Char, uint8_t Negative = 0, SH1106_rmw_t RmwMode = SH1106_RmwNone);
// void		SH1106_Text(const char * Text, SH1106_align_t Align = SH1106_AlignNone, uint8_t Negative = 0, SH1106_rmw_t RmwMode = SH1106_RmwNone);
// #else
// void		SH1106_PrintChar(uint8_t Char, uint8_t Negative = 0);
// void		SH1106_Text(const char * Text, SH1106_align_t Align = SH1106_AlignNone, uint8_t Negative = 0);
//#endif

// Testowe
void		SH1106_DrawSlash(void);

#endif /* DISPLAY_SH1106_H_ */
#endif
