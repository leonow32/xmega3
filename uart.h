/*
UWAGI I POMYS�Y
		*	Obecny spos�b implementacji u�pienia w AVR uCosmos zabrania wej�cia w tryb u�pienia IDLE je�eli w buforze odbiorczym s� jakie� dane do odczytania.
			Nast�puje wtedy kolejuny obieg Schedulera. W przypadku je�eli s� jakie� dane w buforze nadawczym to mo�na wej�� w tryb u�pienia IDLE, poniewa� przerwanie
			od DRE b�dzie wybudza�o procesor. W przysz�o�ci doda� obs�ug� tryb�w STANDBY I POWER DOWN
		*	Doda� funkcj� do zmieny baud rate
		*	Doda� auto baud
		-	Wybudzanie z trybu u�pienia STANDBY:
			20MHz	-	38400
			16MHz	-	38400
			10MHz	-	38400
			5MHz	-	38400
			2MHz	-	19200 (wybudzanie dzia�a na 38400, ale s� b��dy synchronizacji)
			1MHz	-	9600 (wybudzanie dzia�a na 19200, ale s� b��dy synchronizacji)


CHANGELOG
2.17	+	Dodanie funkcji CRC kontrolnego
2.16	+	Dodanie funkcji XOR Kontrolny
		+	void Uart_Resend(USART_t * Port);
2.15	+	Wy�wietlanie liczb dziesi�tnych ze znakiem
			void Uart_WriteDec(int32_t Value, USART_t * Port);
2.14	+	Prosta optymalizacja poprzez dodanie funkcji void Uart__WriteNibble(uint8_t Nibble, USART_t * Port), oszcz�dno�� 6B
2.13	*	Dodanie resetu watchdoga w p�tli w funkcji Uart_Dump()
2.12	+	Dodano funkcje do w��czania i wy��czanie odbiornika w celu oszcz�dzania energii
		+	void Uart_RxDisable(USART_t * Port = &UART_DEFAULT_PORT); - automatyczne wy��czanie nadajnika pozwala zaoszcz�dzi� pr�c ok 5uA @ 5V
		+	void Uart_RxEnable(USART_t * Port = &UART_DEFAULT_PORT);
2.11	+	Implementacja przerwanie TXC - wyzwalanego po zako�czeniu transmisji
		+	Poprawienie funkcji Uart_WaitForTxComplete()
		+	Automatyczne w��czanie transmitera w Uart_Write() i wy��czanie w przerwaniu TXC, kiedy nic nie jest nadawane
2.10	+	Analiza b��du Uart_Disable() - po wy��czeniu nadajnika, pin Tx zostaje automatycznie ustawiony jako wej�cie i przed
			kolejnym w��czeniem nadajnika powinien by� ustawiony ponownie jako wyj�cie. Jednak wpisanie 1 do odpowiedniego
			rejestru DIR pozostawa�o bez efektu. Pomog�a zamiana kolejno�ci - najpierw w��czanie nadajnika, potem ustawienie Tx
			jako wyj�cie. Potencjalnie b��d w procesorze. Wymaga dok�adniejszej weryfikacji.
2.09	*	B�ad w funkcji Uart_Disable()
2.08	+	void Uart_Disable(USART_t * Port);
		+	void UART_Enable(USART_t * Port);
2.07	+	void Uart_RxBufferFlush(USART_t * Port);
		+	void Uart_TxBufferFlush(USART_t * Port);
2.06	+	Kontynuacja prac przy przerabianiu biblioteki na 4 porty
2.05	+	Kontynuacja prac przy przerabianiu biblioteki na 4 porty
2.04	*	Kontynuacja prac przy przerabianiu biblioteki na 4 porty
2.03	*	Przerabianie biblioteki w celu obs�ugi 4 UART�w z ATmegaXX09
2.02	-	Usuni�cie funkcjonalno�ci CTS/RTS
		+	void Uart_WriteHexString(const uint8_t * String, const uint16_t Length, const uint8_t Separator = 0, const uint8_t BytesInRow = 0);
		+	void Uart_Dump(const uint8_t * String, uint16_t Length, uint16_t AddressStartValue = 0);
2.01	+	void Uart_WriteBin(uint8_t Data, const uint8_t Separator)
2.00	*	Rozpocz�cie pracy nad wersj� do ATmega4809
1.20	+	Dodanie pliku uart_config.h z konfiguracj� wszystkich parametr�w
1.19	-	funkcja Uart_WriteProgmem(const char * text) stosowana na poprzednich architekturach AVR nie ma sensu na XMEGA3 ze wzgl�du na
			jednolite adresowanie pami�ci Flash i RAM
		*	Uart_WriteTxt(const char * text) zmienione naUart_Write(const char * text) dla wygody
1.18	+	#define UART_CLEAR_BYTE_AFTER_READ -  czy�ci bajty z TxBuffer i RxBuffer po ich wys�aniu/odebraniu
		+	#define UART_BREAK_ON_BUFFER_FULL - zatrzymuje program je�li bufor zostaje zape�niony
1.17	*	Naprawienie dziwnego b��du w Uart_Write(). Przy sprawdzaniu warunku if(USART0.STATUS & USART_DREIF_bm) zdarza�y si� b��dy przy
			BAUD_RATE=9600 i F_CPU=20000000. Przy innych cz�stotliwo�ciach b��dy zdarza�y si� sporadycznie, na tyle rzadko, �e nie zosta�y zauwa�one
			wcze�niej. B��d polega� na wycinaniu znaku przy wysu�aniu ci�gu. Zamiast "012345" procesor wysy�a� "01245". Do buforwa programowego trafia�y
			cyfry 245, a do sprz�towego 013, przy czym 3 by�o nadpisywane przez obs�ug� przerwania, pobieraj�c� kolejn� cyfr� z bufora sprz�tpowego.
			Zmieniono warunek if(USART0.STATUS & USART_DREIF_bm) na if(USART0.CTRLA & USART_DREIE_bm). W stanie spoczynkowym przerwanie DRE jest wy��czone.
			W��czenie nast�puje w trakcie wysy�ania pierwszego bajtu, a wy��czenie jest w obs�udze przerwania DRE, je�li bufor sprz�towy jest opr�niony.
		+	void Uart_WaitForTxComplete(void);	
1.16	*	Naprawienie b��du w Uart_Write() pojawiaj�cego si� przy du�ej cz�stotliwo�ci F_CPU i ma�ej BAUD_RATE - nadajnik wtedy wycina� niekt�re znaki
		+	void Uart_TxBufferFlush(void);
1.15	*	Poprawienie b��du z argumentem domy�lnym Separator w Uart_WriteHex()
1.14	+	Dodanie obs�ugi port�w wirtualnych
1.13	*	Zmiany wszystkich funkcji wy�wietlaj�cych HEX. Teraz mo�na zdecydowa� jaki znak jest separatorem, a wcze�niej
			by�a dost�pna tylko spacja lub wcale. 
			void Uart_WriteHex(uint8_t Data, uint8_t Separator = 0)
			void Uart_WriteHex(uint16_t Data, uint8_t Separator = 0)
			void Uart_WriteHex(uint32_t Data, uint8_t Separator = 0)
		+	dodanie bitu SFDEN w rejestrze CTRLB w celu wybudzania procka w trybiu u�pienia STANDBY
1.12	+	Pull-up na pinie RX, aby nie wisia� w powietrzy, kiedy nadajnik nie jest pod��czony
1.11	+	UartWriteHEX obs�uguje teraz liczby 8, 16 i 32 bitowe
1.10	*	Zmiana starndarnu nazewnictwa funkcji na format Biblioteka_FunkcjaFunkcja()
		+	Dodanie flagi gotowo�ci Tx przy obs�udze CTS_RTS, bo bez tego nie by�o pewno�ci czy w 
			buforze sprz�towym s� jeszcze jakie� dane czy nie, w efekcie kolejno�� bajt�w 
			potrafi�a si� pomiesza�, podczas jednoczesnego nadawania i odczytywania
1.06	+	void UartWaitForTxComplete(void);
		+	Definicje do sterowania pinem RTS
1.05	+	Obs�uga CTS/RTS
1.04	*	Zmian void UartWriteTxt(char * text) na void UartWriteTxt(const char * text)
			�eby nie pokazywa�o warning�w o konwersji typ�w
1.03	+	UartRxBufferFlush()
		+	UartTxBufferFlush()
		
HARDWARE
		-	Portmux
		-	UART
		-	przerwania
*/

#ifndef UART_H_
#define UART_H_

#include	<avr/io.h>
#include	<avr/interrupt.h>
#include	<string.h>
#include	<util/delay.h>
#include	"uart_config.h"

#if C_UCOSMOS && UART_USE_UCOSMOS_SLEEP
 #include	"uCosmos.h"
#endif



// Definicja struktury bufora pie�cieniowego, u�ywanego przez wszystkie UARTy
struct UART_Buffer_t {
	uint8_t		RxBuffer[UART_RX_BUFFER_LENGTH];
	uint8_t		RxBufferHead;
	uint8_t		RxBufferTail;
	uint8_t		RxBufferCnt;
	uint8_t		TxBuffer[UART_TX_BUFFER_LENGTH];
	uint8_t		TxBufferHead;
	uint8_t		TxBufferTail;
	uint8_t		TxBufferCnt;
	uint16_t	TxBufferCRC;
};

extern USART_t * UART_PortOverride;

// Inicjalizacja
void		Uart_Init();
void		Uart_TxDisable(USART_t * Port = &UART_DEFAULT_PORT);
void		Uart_TxEnable(USART_t * Port = &UART_DEFAULT_PORT);
void		Uart_RxDisable(USART_t * Port = &UART_DEFAULT_PORT);
void		Uart_RxEnable(USART_t * Port = &UART_DEFAULT_PORT);

// Zapisywanie
void		Uart_Write(uint8_t Data, USART_t * Port = &UART_DEFAULT_PORT);
void		Uart_Write(const char * Text, USART_t * Port = &UART_DEFAULT_PORT);
void		Uart_WriteNL(USART_t * Port = &UART_DEFAULT_PORT);
void		Uart_WriteDec(uint32_t Value, USART_t * Port = &UART_DEFAULT_PORT);
void		Uart_WriteDecSigned(int8_t Value, USART_t * Port = &UART_DEFAULT_PORT);
void		Uart_WriteDecSigned(int32_t Value, USART_t * Port = &UART_DEFAULT_PORT);
void		Uart_WriteBin(uint8_t Data, const uint8_t Separator = 0, USART_t * Port = &UART_DEFAULT_PORT);
void		Uart_WriteHex(const uint8_t Data, const uint8_t Separator = 0, USART_t * Port = &UART_DEFAULT_PORT);
void		Uart_WriteHex(const uint16_t Data, const uint8_t Separator = 0, USART_t * Port = &UART_DEFAULT_PORT);
void		Uart_WriteHex(const uint32_t Data, const uint8_t Separator = 0, USART_t * Port = &UART_DEFAULT_PORT);
void		Uart_WriteHexString(const uint8_t * String, const uint16_t Length, const uint8_t Separator = 0, const uint8_t BytesInRow = 0, USART_t * Port = &UART_DEFAULT_PORT);
void		Uart_Dump(const uint8_t * String, uint16_t Length, uint16_t AddressStartValue = 0, USART_t * Port = &UART_DEFAULT_PORT);
void		Uart_Resend(USART_t * Port);

// Odczytywanie
uint8_t		Uart_Read(USART_t * Port = &UART_DEFAULT_PORT);
uint8_t		Uart_ReceivedCnt(USART_t * Port = &UART_DEFAULT_PORT);

// Funkcje pomocnicze
void		Uart_RxBufferFlush(volatile UART_Buffer_t * ProgBuf);
void		Uart_RxBufferFlush(USART_t * Port);
void		Uart_TxBufferFlush(volatile UART_Buffer_t * ProgBuf);
void		Uart_TxBufferFlush(USART_t * Port);
void		Uart_WaitForTxComplete(USART_t * Port);		
void		Uart_WaitForTxComplete(void);

// CRC kontrolne
void		Uart_TxCrcClear(USART_t * Port);
uint16_t	Uart_TxCrcGet(USART_t * Port);

// Wycofane, definicje dla kompatybilno�ci wstecznej
#define		Uart_WriteProgmem(x)	Uart_Write(x)
#define		Uart_WriteTxt(x)		Uart_Write(x)

#endif /* UART_H_ */
