/*
UWAGI I POMYS£Y
		*	Obecny sposób implementacji uœpienia w AVR uCosmos zabrania wejœcia w tryb uœpienia IDLE je¿eli w buforze odbiorczym s¹ jakieœ dane do odczytania.
			Nastêpuje wtedy kolejuny obieg Schedulera. W przypadku je¿eli s¹ jakieœ dane w buforze nadawczym to mo¿na wejœæ w tryb uœpienia IDLE, poniewa¿ przerwanie
			od DRE bêdzie wybudza³o procesor. W przysz³oœci dodaæ obs³ugê trybów STANDBY I POWER DOWN
		*	Dodaæ funkcjê do zmieny baud rate
		*	Dodaæ auto baud
		-	Wybudzanie z trybu uœpienia STANDBY:
			20MHz	-	38400
			16MHz	-	38400
			10MHz	-	38400
			5MHz	-	38400
			2MHz	-	19200 (wybudzanie dzia³a na 38400, ale s¹ b³êdy synchronizacji)
			1MHz	-	9600 (wybudzanie dzia³a na 19200, ale s¹ b³êdy synchronizacji)


CHANGELOG
3.0.0	+	Utworzenie wersji signle i multi
2.18	-	Optymalizacja uart_config.h
2.17	+	Dodanie funkcji CRC kontrolnego
2.16	+	Dodanie funkcji XOR Kontrolny
		+	void Uart_Resend(USART_t * Port);
2.15	+	Wyœwietlanie liczb dziesiêtnych ze znakiem
			void Uart_WriteDec(int32_t Value, USART_t * Port);
2.14	+	Prosta optymalizacja poprzez dodanie funkcji void Uart__WriteNibble(uint8_t Nibble, USART_t * Port), oszczêdnoœæ 6B
2.13	*	Dodanie resetu watchdoga w pêtli w funkcji Uart_Dump()
2.12	+	Dodano funkcje do w³¹czania i wy³¹czanie odbiornika w celu oszczêdzania energii
		+	void Uart_RxDisable(USART_t * Port = &UART_DEFAULT_PORT); - automatyczne wy³¹czanie nadajnika pozwala zaoszczêdziæ pr¹c ok 5uA @ 5V
		+	void Uart_RxEnable(USART_t * Port = &UART_DEFAULT_PORT);
2.11	+	Implementacja przerwanie TXC - wyzwalanego po zakoñczeniu transmisji
		+	Poprawienie funkcji Uart_WaitForTxComplete()
		+	Automatyczne w³¹czanie transmitera w Uart_Write() i wy³¹czanie w przerwaniu TXC, kiedy nic nie jest nadawane
2.10	+	Analiza b³êdu Uart_Disable() - po wy³¹czeniu nadajnika, pin Tx zostaje automatycznie ustawiony jako wejœcie i przed
			kolejnym w³¹czeniem nadajnika powinien byæ ustawiony ponownie jako wyjœcie. Jednak wpisanie 1 do odpowiedniego
			rejestru DIR pozostawa³o bez efektu. Pomog³a zamiana kolejnoœci - najpierw w³¹czanie nadajnika, potem ustawienie Tx
			jako wyjœcie. Potencjalnie b³¹d w procesorze. Wymaga dok³adniejszej weryfikacji.
2.09	*	B³ad w funkcji Uart_Disable()
2.08	+	void Uart_Disable(USART_t * Port);
		+	void UART_Enable(USART_t * Port);
2.07	+	void Uart_RxBufferFlush(USART_t * Port);
		+	void Uart_TxBufferFlush(USART_t * Port);
2.06	+	Kontynuacja prac przy przerabianiu biblioteki na 4 porty
2.05	+	Kontynuacja prac przy przerabianiu biblioteki na 4 porty
2.04	*	Kontynuacja prac przy przerabianiu biblioteki na 4 porty
2.03	*	Przerabianie biblioteki w celu obs³ugi 4 UARTów z ATmegaXX09
2.02	-	Usuniêcie funkcjonalnoœci CTS/RTS
		+	void Uart_WriteHexString(const uint8_t * String, const uint16_t Length, const uint8_t Separator = 0, const uint8_t BytesInRow = 0);
		+	void Uart_Dump(const uint8_t * String, uint16_t Length, uint16_t AddressStartValue = 0);
2.01	+	void Uart_WriteBin(uint8_t Data, const uint8_t Separator)
2.00	*	Rozpoczêcie pracy nad wersj¹ do ATmega4809
1.20	+	Dodanie pliku uart_config.h z konfiguracj¹ wszystkich parametrów
1.19	-	funkcja Uart_WriteProgmem(const char * text) stosowana na poprzednich architekturach AVR nie ma sensu na XMEGA3 ze wzglêdu na
			jednolite adresowanie pamiêci Flash i RAM
		*	Uart_WriteTxt(const char * text) zmienione naUart_Write(const char * text) dla wygody
1.18	+	#define UART_CLEAR_BYTE_AFTER_READ -  czyœci bajty z TxBuffer i RxBuffer po ich wys³aniu/odebraniu
		+	#define UART_BREAK_ON_BUFFER_FULL - zatrzymuje program jeœli bufor zostaje zape³niony
1.17	*	Naprawienie dziwnego b³êdu w Uart_Write(). Przy sprawdzaniu warunku if(USART0.STATUS & USART_DREIF_bm) zdarza³y siê b³êdy przy
			BAUD_RATE=9600 i F_CPU=20000000. Przy innych czêstotliwoœciach b³êdy zdarza³y siê sporadycznie, na tyle rzadko, ¿e nie zosta³y zauwa¿one
			wczeœniej. B³¹d polega³ na wycinaniu znaku przy wysu³aniu ci¹gu. Zamiast "012345" procesor wysy³a³ "01245". Do buforwa programowego trafia³y
			cyfry 245, a do sprzêtowego 013, przy czym 3 by³o nadpisywane przez obs³ugê przerwania, pobieraj¹c¹ kolejn¹ cyfrê z bufora sprzêtpowego.
			Zmieniono warunek if(USART0.STATUS & USART_DREIF_bm) na if(USART0.CTRLA & USART_DREIE_bm). W stanie spoczynkowym przerwanie DRE jest wy³¹czone.
			W³¹czenie nastêpuje w trakcie wysy³ania pierwszego bajtu, a wy³¹czenie jest w obs³udze przerwania DRE, jeœli bufor sprzêtowy jest opró¿niony.
		+	void Uart_WaitForTxComplete(void);	
1.16	*	Naprawienie b³êdu w Uart_Write() pojawiaj¹cego siê przy du¿ej czêstotliwoœci F_CPU i ma³ej BAUD_RATE - nadajnik wtedy wycina³ niektóre znaki
		+	void Uart_TxBufferFlush(void);
1.15	*	Poprawienie b³êdu z argumentem domyœlnym Separator w Uart_WriteHex()
1.14	+	Dodanie obs³ugi portów wirtualnych
1.13	*	Zmiany wszystkich funkcji wyœwietlaj¹cych HEX. Teraz mo¿na zdecydowaæ jaki znak jest separatorem, a wczeœniej
			by³a dostêpna tylko spacja lub wcale. 
			void Uart_WriteHex(uint8_t Data, uint8_t Separator = 0)
			void Uart_WriteHex(uint16_t Data, uint8_t Separator = 0)
			void Uart_WriteHex(uint32_t Data, uint8_t Separator = 0)
		+	dodanie bitu SFDEN w rejestrze CTRLB w celu wybudzania procka w trybiu uœpienia STANDBY
1.12	+	Pull-up na pinie RX, aby nie wisia³ w powietrzy, kiedy nadajnik nie jest pod³¹czony
1.11	+	UartWriteHEX obs³uguje teraz liczby 8, 16 i 32 bitowe
1.10	*	Zmiana starndarnu nazewnictwa funkcji na format Biblioteka_FunkcjaFunkcja()
		+	Dodanie flagi gotowoœci Tx przy obs³udze CTS_RTS, bo bez tego nie by³o pewnoœci czy w 
			buforze sprzêtowym s¹ jeszcze jakieœ dane czy nie, w efekcie kolejnoœæ bajtów 
			potrafi³a siê pomieszaæ, podczas jednoczesnego nadawania i odczytywania
1.06	+	void UartWaitForTxComplete(void);
		+	Definicje do sterowania pinem RTS
1.05	+	Obs³uga CTS/RTS
1.04	*	Zmian void UartWriteTxt(char * text) na void UartWriteTxt(const char * text)
			¿eby nie pokazywa³o warningów o konwersji typów
1.03	+	UartRxBufferFlush()
		+	UartTxBufferFlush()
		
HARDWARE
		-	Portmux
		-	UART
		-	przerwania
*/

#ifndef UART_MULTI_H_
#define UART_MULTI_H_

#if COMPONENT_UART_MULTI

#include		<avr/io.h>
#include		<avr/interrupt.h>
#include		<string.h>
#include		<util/delay.h>
#include		"uart_multi_config.h"

#if COMPONENT_UCOSMOS && UART_USE_UCOSMOS_SLEEP
	#include	"../uCosmos/uCosmos.h"
#endif

// Definicje statusów
// Zapisywanie w rejestrze TXPLCTRL, który s³u¿y do IR, ale nie wykorzystujemy tej mo¿liwoœci
#define UART_TX_BUSY		uint8_t(0b00000001)

// Definicja struktury bufora pieœcieniowego, u¿ywanego przez wszystkie UARTy
struct UART_Buffer_t {
	uint8_t		RxBuffer[UART_RX_BUFFER_LENGTH];
	uint8_t		RxBufferHead;
	uint8_t		RxBufferTail;
	uint8_t		RxBufferCnt;
	uint8_t		TxBuffer[UART_TX_BUFFER_LENGTH];
	uint8_t		TxBufferHead;
	uint8_t		TxBufferTail;
	uint8_t		TxBufferCnt;
};

// Funkcje podstawowe
void		Uart_Init();
void		Uart_Write(uint8_t Data, USART_t * Port = &UART_DEFAULT_PORT);
uint8_t		Uart_Read(USART_t * Port = &UART_DEFAULT_PORT);
uint8_t		Uart_ReceivedCnt(USART_t * Port = &UART_DEFAULT_PORT);

// Funckje specyficzne dla poszczególnych instacji
#if UART0_USE
	void	Uart0_Write(uint8_t Data);
	uint8_t	Uart0_Read(void);
	uint8_t	Uart0_ReceivedCnt(void);
#endif

#if UART1_USE
	void	Uart1_Write(uint8_t Data);
	uint8_t	Uart1_Read(void);
	uint8_t	Uart1_ReceivedCnt(void);
#endif

#if UART2_USE
	void	Uart2_Write(uint8_t Data);
	uint8_t	Uart2_Read(void);
	uint8_t	Uart2_ReceivedCnt(void);
#endif

#if UART3_USE
	void	Uart3_Write(uint8_t Data);
	uint8_t	Uart3_Read(void);
	uint8_t	Uart3_ReceivedCnt(void);
#endif

// Funkcje pomocnicze
void		Uart_RxBufferFlush(volatile UART_Buffer_t * ProgBuf);
void		Uart_RxBufferFlush(USART_t * Port);
void		Uart_TxBufferFlush(volatile UART_Buffer_t * ProgBuf);
void		Uart_TxBufferFlush(USART_t * Port);
void		Uart_WaitForTxComplete(USART_t * Port);
void		Uart_WaitForTxComplete(void);

// Wycofane, definicje dla kompatybilnoœci wstecznej
#define		Uart_WriteProgmem(x)	Uart_Write(x)
#define		Uart_WriteTxt(x)		Uart_Write(x)

// Kontrola b³êdów
#if COMPONENT_UART_SINGLE && COMPONENT_UART_MULTI
	#error "Can't use COMPONENT_UART_SINGLE and COMPONENT_UART_MULTI at the same time"
#endif

#endif

#endif /* UART_MULTI_H_ */
