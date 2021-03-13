// Wersja 2.17

#include "uart_multi.h"


// Bufory programowe dla ka�dego sprz�towego portu
#if UART0_USE
	UART_Buffer_t UART0_ProgBuf;
#endif

#if UART1_USE
	UART_Buffer_t UART1_ProgBuf;
#endif

#if UART2_USE
	UART_Buffer_t UART2_ProgBuf;
#endif
	
#if UART3_USE
	UART_Buffer_t UART3_ProgBuf;
#endif


// Struktura umo�liwiaj�ca zignorowanie argumentu USART_t * Port wszystkich funkcji, je�eli UART_PortOverride != NULL
USART_t * UART_PortOverride = NULL;


// ==================
// Funkcje pomocnicze
// ==================


// Funkcja zwracaj�ca wska�nik do bufora programowego w�a�ciwego dla podanego potru sprz�towego
static volatile UART_Buffer_t * Uart__GetProgBuffer(USART_t * Port) {
	
	// Sprawdzanie, kt�ry bufor nale�y zastosowa� w zale�no�ci od wybranego portu
	// Por�wnujemy tu adres portu przekazany przez wska�nik z fizycznym adresem strutury USARTn
	#if UART0_USE
		if(Port == &USART0) {
			return &UART0_ProgBuf;
		}
	#endif
	
	#if UART1_USE
		if(Port == &USART1) {
			return &UART1_ProgBuf;
		}
	#endif
	
	#if UART2_USE
		if(Port == &USART2) {
			return &UART2_ProgBuf;
		}
	#endif
	
	#if UART3_USE
		if(Port == &USART3) {
			return &UART3_ProgBuf;
		}
	#endif	
	
	Uart_Write("Uart__GetProgBuffer ");
	Uart_WriteHex((uint16_t)Port);
	asm volatile("wdr");
	_delay_ms(100);
	
	
	//return &UART2_ProgBuf;
	// TODO: Posprz�ta� to
	#if B_MIFARE_v002 || B_LOCK_v001 || B_XNANO
		return &UART0_ProgBuf;
	#else
		return &UART2_ProgBuf;
	#endif
	//while(1);
	//asm volatile("break");
	//return NULL;
}


// Inicjalizacja sprz�towego peryferium wskazanego wska�nikiem (u�ywane tylko przez Uart_Init();
// - Port		-	Wska�nik do portu
// - Baud		-	Baudrate ju� po przeliczeniu, ta warto�� jest wpisywana wprost do jesteru USARTx.BAUD
static void Uart__InitUsartPeripheral(USART_t * Port, UART_Buffer_t * Buffer, uint16_t Baud) {
	
	Port->BAUD			=	Baud;												// Baud rate
	
	Port->CTRLA			=	USART_RXCIE_bm |									// Receive Complete Interrupt Enable
							USART_TXCIE_bm |									// Transmit Complete Interrupt Enable
						  //USART_DREIE_bm |									// Data Register Empty Interrupt Enable
						  //USART_RXSIE_bm |									// Receiver Start Frame Interrupt Enable
						  //USART_LBME_bm |										// Loop-back Mode Enable
						  //USART_ABEIE_bm |									// Auto-baud Error Interrupt Enable
							USART_RS485_OFF_gc;									// RS485 Mode

	Port->CTRLB			=	USART_RXEN_bm |										// Receiver Enable
						  //USART_TXEN_bm |										// Transmitter Enable
							USART_SFDEN_bm |									// Start Frame Detection Enable
						  //USART_ODME_bm |										// Open Drain Mode Enable
							USART_RXMODE_NORMAL_gc ;							// Receiver Mode
						  //USART_MPCM_bp;										// Multi-Processor Communication Mode

	Port->CTRLC			=	USART_CMODE_ASYNCHRONOUS_gc |						// USART Communication Mode
							USART_PMODE_DISABLED_gc |							// Parity Mode
							USART_SBMODE_1BIT_gc |								// Stop Bit Mode
							USART_CHSIZE_8BIT_gc ;								// Character Size
	
	#if UART_DEBUG_RUN
		Port->DBGCTRL	=	USART_DBGRUN_bm;									// Ma dzia�a� podczas breakpoint�w
	#endif	
	
	// Czyszczenie bufora
	memset(Buffer, 0, sizeof(UART_Buffer_t));
}


// Inicjalizacja pinu TX, kt�ry musi by� ustawiony jako wyj�cie i ustawiony w stan 1
// Dodatkowo konfiguracja Portmux, je�li wybrano port alternatywny
#if UART0_USE
static void Uart__InitPinsForUsart0(void) {
	
	// Konfiguracja dla ATtinyXX14/16/17/18 - port podstawowy
	#if UART0_PORTB_23 && (HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17)
		PORTMUX.CTRLB	&= ~PORTMUX_USART0_ALTERNATE_gc;
		PORTB.PIN3CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w��czony rezystor pull-up
		PORTB.PIN2CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w��czony rezystor pull-up
							PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy��czony bufor wej�ciowy
		VPORTB.OUT		|=	PIN2_bm;											// Pin Tx jako wyj�cie
		VPORTB.DIR		|=	PIN2_bm;											// Pin Tx jako wyj�cie
		
		
	#endif

	// Konfiguracja dla ATtinyXX12/14/16/17/18 - port alternatywny
	#if UART0_PORTA_12 && (HW_CPU_ATtinyXX12 || HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17)
		PORTMUX.CTRLB	|=	PORTMUX_USART0_ALTERNATE_gc;
		PORTA.PIN2CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w��czony rezystor pull-up
		PORTA.PIN1CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w��czony rezystor pull-up
							PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy��czony bufor wej�ciowy
		VPORTA.OUT		|=	PIN1_bm;											// Pin Tx jako wyj�cie
		VPORTA.DIR		|=	PIN1_bm;											// Pin Tx jako wyj�cie
		
		
	#endif

	// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
	#if UART0_PORTA_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		&= ~PORTMUX_USART0_gm;
		PORTA.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
		PORTA.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
		VPORTA.OUT				|=	PIN0_bm;									// Pin Tx jako wyj�cie
		VPORTA.DIR				|=	PIN0_bm;									// Pin Tx jako wyj�cie
	#endif

	// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
	#if UART0_PORTA_45 && (HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		|=	PORTMUX_USART0_ALT1_gc;
		PORTA.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
		PORTA.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
		VPORTA.OUT				|=	PIN4_bm;									// Pin Tx jako wyj�cie
		VPORTA.DIR				|=	PIN4_bm;									// Pin Tx jako wyj�cie
	#endif
}
#endif


// Inicjalizacja pinu TX, kt�ry musi by� ustawiony jako wyj�cie i ustawiony w stan 1
// Dodatkowo konfiguracja Portmux, je�li wybrano port alternatywny
#if UART1_USE
static void Uart__InitPinsForUsart1(void) {
	
	// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
	#if UART1_PORTC_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		&= ~PORTMUX_USART1_gm;
		PORTC.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
		PORTC.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
		VPORTC.OUT				|=	PIN0_bm;									// Pin Tx jako wyj�cie
		VPORTC.DIR				|=	PIN0_bm;									// Pin Tx jako wyj�cie
	#endif

	// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
	#if UART1_PORTC_45 && (HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		|=	PORTMUX_USART1_ALT1_gc;
		PORTC.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
		PORTC.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
		VPORTC.OUT				|=	PIN4_bm;									// Pin Tx jako wyj�cie
		VPORTC.DIR				|=	PIN4_bm;									// Pin Tx jako wyj�cie
	#endif
}
#endif


// Inicjalizacja pinu TX, kt�ry musi by� ustawiony jako wyj�cie i ustawiony w stan 1
// Dodatkowo konfiguracja Portmux, je�li wybrano port alternatywny
#if UART2_USE
static void Uart__InitPinsForUsart2(void) {

	// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
	#if UART2_PORTF_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		&= ~PORTMUX_USART2_gm;
		PORTF.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
		PORTF.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
		VPORTF.OUT				|=	PIN0_bm;									// Pin Tx jako wyj�cie
		VPORTF.DIR				|=	PIN0_bm;									// Pin Tx jako wyj�cie
	#endif

	// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
	#if UART2_PORTF_45 && (HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		|=	PORTMUX_USART2_ALT1_gc;
		PORTF.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
		PORTF.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
		VPORTF.OUT				|=	PIN4_bm;									// Pin Tx jako wyj�cie
		VPORTF.DIR				|=	PIN4_bm;									// Pin Tx jako wyj�cie
	#endif
}
#endif


// Inicjalizacja pinu TX, kt�ry musi by� ustawiony jako wyj�cie i ustawiony w stan 1
// Dodatkowo konfiguracja Portmux, je�li wybrano port alternatywny
#if UART3_USE
static void Uart__InitPinsForUsart3(void) {

	// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
	#if UART3_PORTB_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		&= ~PORTMUX_USART3_gm;
		PORTB.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
		PORTB.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
		VPORTB.OUT				|=	PIN0_bm;									// Pin Tx jako wyj�cie
		VPORTB.DIR				|=	PIN0_bm;									// Pin Tx jako wyj�cie
	#endif

	// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
	#if UART3_PORTB_45 && (HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		|=	PORTMUX_USART3_ALT1_gc;
		PORTB.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
		PORTB.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
		VPORTB.OUT				|=	PIN4_bm;									// Pin Tx jako wyj�cie
		VPORTB.DIR				|=	PIN4_bm;									// Pin Tx jako wyj�cie
	#endif
}
#endif


// Inicjalizacja zgodnie z konfiguracj� w pliku uart_config.h
void Uart_Init() {
		
	// Konfiguracja UART0
	#if UART0_USE
		Uart__InitPinsForUsart0();
		Uart__InitUsartPeripheral(&USART0, &UART0_ProgBuf, uint16_t((F_CPU * 4) / (UART0_BAUD)));
	#endif
	
	// Konfiguracja UART1
	#if UART1_USE
		Uart__InitPinsForUsart1();
		Uart__InitUsartPeripheral(&USART1, &UART1_ProgBuf, uint16_t((F_CPU * 4) / (UART1_BAUD)));
	#endif
	
	// Konfiguracja UART2
	#if UART2_USE
		Uart__InitPinsForUsart2();
		Uart__InitUsartPeripheral(&USART2, &UART2_ProgBuf, uint16_t((F_CPU * 4) / (UART2_BAUD)));
	#endif
	
	// Konfiguracja UART3
	#if UART3_USE
		Uart__InitPinsForUsart3();
		Uart__InitUsartPeripheral(&USART3, &UART3_ProgBuf, uint16_t((F_CPU * 4) / (UART3_BAUD)));
	#endif
	
	// Przerwania
	CPUINT.CTRLA	|=	CPUINT_LVL0RR_bm;										// Algorytm round-robin dla przerwa� o tym samym priorytecie
	CPUINT.LVL1VEC	=	UART_CONSOLE_INT;										// Je�li wrzucamy co� do bufora UART w przerwaniu, 
																				// to przerwanie opr�nienia bufora musi mie� wi�kszy priortet, 
																				// bo inaczej w przypadku przepe�nienia bufora procesor si� zawiesi
}


// Wy��czenie transmitera (domy�lnie po inicjalizacji jest w��czony)
void Uart_TxDisable(USART_t * Port) {
	cli();
	Port->CTRLB		&=	~USART_TXEN_bm;
	sei();
}


// W��czenie transmitera (domy�lnie po inicjalizacji jest w��czony)
void Uart_TxEnable(USART_t * Port) {
	cli();

	// W��czenie nadajnika
	Port->CTRLB		|=	USART_TXEN_bm;

	// Po wy��czeniu nadajnika UART pin Tx ustawiany jest automatycznie jako wej�cie i trzeba go ponownie skonfigurowa� jako wyj�cie
	// UWAGA - chyba jest tu jaki� problem z procesorem, bo je�li ustawienie pin�w b�dzie przez ponownym w��czeniem nadajnika,
	// to wpisanie 1 do rejestru DIR nie daje efektu!?
	#if UART0_USE
		if(Port == &USART0) {
			Uart__InitPinsForUsart0();
		}
	#endif
	
	#if UART1_USE
		if(Port == &USART1) {
			Uart__InitPinsForUsart1();
		}
	#endif
	
	#if UART2_USE
		if(Port == &USART2) {
			Uart__InitPinsForUsart2();
		}
	#endif
	
	#if UART3_USE
		if(Port == &USART3) {
			Uart__InitPinsForUsart3();
		}
	#endif	

	sei();
}


// Wy��czenie odbiornika (domy�lnie po inicjalizacji jest w��czony)
void Uart_RxDisable(USART_t * Port) {
	Port->CTRLB		&=	~USART_RXEN_bm;
}


// W��czenie odbiornika (domy�lnie po inicjalizacji jest w��czony)
void Uart_RxEnable(USART_t * Port) {
	Port->CTRLB		|=	USART_RXEN_bm;
}



// ====================
// Wysy�anie przez UART
// ====================


// Wysy�anie 1 bajtu danych
void Uart_Write(uint8_t Data, USART_t * Port) {

// 	// Je�eli za argument wstawiono !!
	if(UART_PortOverride != NULL) {
		Port = UART_PortOverride;
	}
	
	// Je�eli obecnie transmiter jest wy��czony, to go w��czamy 
	if((Port->CTRLB & USART_TXEN_bm) == 0) {								
		Uart_TxEnable(Port);													

		// Je�eli jest u�ywana blokada u�pienia
		#if UART_USE_UCOSMOS_SLEEP
			OS_SLEEP_DISABLE;													// Ustawienie blokady u�pienia
		#endif
	}

	// Wska�nik do bufora pier�cieniowego
	volatile UART_Buffer_t * Buffer = Uart__GetProgBuffer(Port);
	
	// Procedura zapisu danych do bufora sprz�towego lub programowego
	Port->STATUS		=	USART_TXCIF_bm;										// Kasowanie flagi ko�ca nadawania
// 	if(!(Port->CTRLA & USART_DREIE_bm)) {										// Je�li DRE jest w��czone to znaczy, �e mamy ju� rozpocz�t� transmisj�
// 		Port->TXDATAL	=	Data;												// Wpisanie danych do bufora nadawczego i rozpocz�cie transmisji
// 		Port->CTRLA		=	USART_DREIE_bm |									// W��czenie przerwa� od DRE...
// 							USART_RXCIE_bm |									// ...a RX...
// 							USART_TXCIE_bm;										// ...oraz TX ju� wcze�niej by�o w��czone
// 	} 
// 	else {																		// Bufor sprz�towy pe�ny
		while(Buffer->TxBufferCnt == UART_TX_BUFFER_LENGTH) {					// Sprawdzenie czy bufor programowy pusty lub czekanie a� b�dzie wolne miejsce
			#if UART_BREAK_ON_BUFFER_FULL								
				asm volatile("break");											// Zatrzymanie je�li bufor przepe�niony
			#endif
		}
		
		cli();																	// Wy��czenie przerwa�, aby nie dopu�ci� do sytuacji, kiedy TxBuffer by�by jednocze�nie modyfikowany w przerwaniu
		Buffer->TxBufferCnt++;													// Zwi�kszenie licznika znak�w w buforze nadawczym
		Buffer->TxBuffer[Buffer->TxBufferHead] = Data;							// Wpisanie znaku do bufora na pocz�tek kolejki FIFO
		
		if(++Buffer->TxBufferHead == UART_TX_BUFFER_LENGTH) {					// Zapis ++TxBufferHead oszcz�dza pami�� o 4B
			Buffer->TxBufferHead = 0;											// Przekre�cenie si� bufora pier�cieniowego
		}
		
		Port->CTRLA		=	USART_DREIE_bm |									// W��czenie przerwa� od DRE...
							USART_RXCIE_bm |									// ...a RX...
							USART_TXCIE_bm;										// ...oraz TX ju� wcze�niej by�o w��czone
		sei();																	// Glabalne w��czenie przerwa�
//	}
	
	// Aktualizacja CRC
	Data = Data ^ uint8_t(Buffer->TxBufferCRC);
	Data = Data ^ (Data << 4);
	Buffer->TxBufferCRC = (Buffer->TxBufferCRC >> 8) ^ (Data << 8) ^ (Data << 3) ^ (Data >> 4);
}


// Funkcja obs�uguj�ca przerwania od zwolnienia si� miejsca w buforze
static void Uart__InterruptDre(USART_t * Port, UART_Buffer_t * Buffer) {
	
	//volatile UART_Buffer_t * Buffer = Uart__GetProgBuffer(Port);
	
	if(Buffer->TxBufferCnt) {													// Je�eli w buforze programowym jest co� do wys�ania
		
		Port->STATUS	=	USART_TXCIF_bm;										// Kasowanie flagi ko�ca nadawania
		Buffer->TxBufferCnt--;													// Zmniejszenie liczby znak�w w buforze nadawczym
		Port->TXDATAL = Buffer->TxBuffer[Buffer->TxBufferTail];					// Wysy�anie znaku z ko�ca kolejki FIFO
		
		#if UART_CLEAR_BYTE_AFTER_READ											// W celach debugowych
			Buffer->TxBuffer[Buffer->TxBufferTail] = 0;							// Czyszczenie znaku w buforze programowym, kt�ry zosta� skopiowany do bufora sprz�towego
		#endif
		
		if(++Buffer->TxBufferTail == UART_TX_BUFFER_LENGTH) {					// Umieszczenie ++ tutaj oszcz�dza 4 bajty	
			Buffer->TxBufferTail = 0;											// Przekr�cenie si� bufora pier�cieniowego
		}
	} 
	else {																		// Bufor programowy pusty, koniec transmisji (ale bajty w buforze sprz�towym ca�y czas s� jeszcze wysy�ane!)
		Port->CTRLA		=	USART_RXCIE_bm |									// W��czenie przerwa� od DRE...
							USART_TXCIE_bm;										// ...a RX oraz TX ju� wcze�niej by�o w��czone
	}	
}


// Przerwanie UART0 w celu wysy�ania danych - po zwolnieniu 1 bajtu w buforze sprz�towym
#if UART0_USE
ISR(USART0_DRE_vect) {
//	INT_ON;
	Uart__InterruptDre(&USART0, &UART0_ProgBuf);
//	INT_OFF;
}
#endif


// Przerwanie UART1 w celu wysy�ania danych - po zwolnieniu 1 bajtu w buforze sprz�towym
#if UART1_USE
ISR(USART1_DRE_vect) {
	Uart__InterruptDre(&USART1, &UART1_ProgBuf);
}
#endif


// Przerwanie UART2 w celu wysy�ania danych - po zwolnieniu 1 bajtu w buforze sprz�towym
#if UART2_USE
ISR(USART2_DRE_vect) {
	Uart__InterruptDre(&USART2, &UART2_ProgBuf);
}
#endif


// Przerwanie UART3 w celu wysy�ania danych - po zwolnieniu 1 bajtu w buforze sprz�towym
#if UART3_USE
ISR(USART3_DRE_vect) {
	Uart__InterruptDre(&USART3, &UART3_ProgBuf);
}
#endif


// Funkcja obs�uguj�ca przerwanie od zako�czenia transmisji
static void Uart__InterruptTx(USART_t * Port) {

	// Kasowanie flagi przerwania
	Port->STATUS	=	USART_TXCIF_bm;

	// Wy��czenie transmitera
	Port->CTRLB		&= ~USART_TXEN_bm;

	// Je�eli jest u�ywana blokada u�pienia
	#if UART_USE_UCOSMOS_SLEEP
		OS_SLEEP_ENABLE;														// Zwolnienie blokady u�pienia
	#endif
}


// Ca�kowite opr�nienie bufora sprz�towego i zako�czenie transmisji w USART 0
#if UART0_USE
ISR(USART0_TXC_vect) {
	Uart__InterruptTx(&USART0);
}
#endif


// Ca�kowite opr�nienie bufora sprz�towego i zako�czenie transmisji w USART 1
#if UART1_USE
ISR(USART1_TXC_vect) {
	Uart__InterruptTx(&USART1);
}
#endif


// Ca�kowite opr�nienie bufora sprz�towego i zako�czenie transmisji w USART 2
#if UART2_USE
ISR(USART2_TXC_vect) {
	Uart__InterruptTx(&USART2);
}
#endif


// Ca�kowite opr�nienie bufora sprz�towego i zako�czenie transmisji w USART 3
#if UART3_USE
ISR(USART3_TXC_vect) {
	Uart__InterruptTx(&USART3);
}
#endif

// ================================================
// Funkcje wy�szego poziomu do wysy�ania przez UART
// ================================================


// Zapis ci�gu znak�w
void Uart_Write(const char * Text, USART_t * Port) {
	while(*Text) Uart_Write(*Text++, Port);
}


// Nowa linia
void Uart_WriteNL(USART_t * Port) {
	Uart_Write("\r\n", Port);
}


// Liczba dziesi�tna bez znaku
void Uart_WriteDec(uint32_t Value, USART_t * Port) {
	if(Value==0) {
		Uart_Write('0', Port);
		return;
	}
	
	uint8_t cyfra[10];
	memset(cyfra, 0, sizeof(cyfra));
	int8_t i=0;
	
	while(Value) {
		cyfra[i] = (uint8_t)(Value%10);
		Value = Value / 10;
		++i;
	}
	
	while(i--) {
		Uart_Write(cyfra[i]+48, Port);
	}
}

// Liczba dziesi�tna ze znakiem
void Uart_WriteDecSigned(int8_t Value, USART_t * Port) {
	if(Value < 0) {
		Uart_Write('-', Port);
		Value = -Value;
	}
	Uart_WriteDec(uint8_t(Value), Port);
}

// Liczba dziesi�tna ze znakiem
void Uart_WriteDecSigned(int32_t Value, USART_t * Port) {
	if(Value < 0) {
		Uart_Write('-', Port);
		Value = -Value;
	}
	Uart_WriteDec(uint32_t(Value), Port);
}


// Zapis liczny binarnej
void Uart_WriteBin(uint8_t Data, const uint8_t Separator, USART_t * Port) {
	for(uint8_t BitMask = 0b10000000; BitMask; BitMask = BitMask >> 1) {
		Uart_Write(Data & BitMask ? '1' : '0', Port);
	}
	if(Separator) Uart_Write(Separator, Port);
}


void Uart__WriteNibble(uint8_t Nibble, USART_t * Port) {
	if(Nibble <= 9) Uart_Write(Nibble + '0', Port);
	else Uart_Write(Nibble + 55, Port);
}

// Liczba HEX 8-bitowa
void Uart_WriteHex(const uint8_t Data, const uint8_t Separator, USART_t * Port) {
	Uart__WriteNibble((Data & 0xF0) >> 4, Port);
	Uart__WriteNibble((Data & 0x0F) >> 0, Port);
	if(Separator) Uart_Write(Separator, Port); 
}


// Liczba HEX 16-bitowa
void Uart_WriteHex(const uint16_t Data, const uint8_t Separator, USART_t * Port) {
	Uart_WriteHex(uint8_t((Data & 0xFF00) >> 8), 0, Port);
	Uart_WriteHex(uint8_t((Data & 0x00FF)     ), Separator, Port);
}


// Liczba HEX 32-bitowa
void Uart_WriteHex(const uint32_t Data, const uint8_t Separator, USART_t * Port) {
	Uart_WriteHex(uint8_t((Data & 0xFF000000) >> 24), 0, Port);
	Uart_WriteHex(uint8_t((Data & 0x00FF0000) >> 16), 0, Port);
	Uart_WriteHex(uint8_t((Data & 0x0000FF00) >> 8 ), 0, Port);
	Uart_WriteHex(uint8_t((Data & 0x000000FF)      ), Separator, Port);
}


// Ci�g znak�w prezentowany jako HEX
void Uart_WriteHexString(const uint8_t * String, const uint16_t Length, const uint8_t Separator, const uint8_t BytesInRow, USART_t * Port) {
	
	for(uint16_t i=0; i<Length; i++) {
		
		// Przej�cie do nowej linii (nie dotyczny pierwszego wy�wietlanego znaku)
		if((i%BytesInRow == 0) && i != 0) {
			Uart_WriteNL(Port);
		}

		// Wy�wietlenie znaku
		Uart_WriteHex(*(String+i), Separator, Port);
	}
}


// Ci�g znak�w prezentowany jako HEX, wraz z nag��wkiem i adresowaniem
void Uart_Dump(const uint8_t * String, uint16_t Length, uint16_t AddressStartValue, USART_t * Port) {
	
	uint8_t * wskaznik		= (uint8_t *)String;
	uint16_t LengthForHex	= Length;
	uint16_t LengthForAscii	= Length;
	uint16_t i = 0;

	Uart_Write("       0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F", Port);

	// Wy�wietlanie w p�tli po 16 znak�w na ka�d� lini�
	do {
		
		// Zej�cie do nowej linii
		Uart_WriteNL(Port);

		// Wy�wietlenie adresu
		Uart_WriteHex(uint16_t(i + AddressStartValue), ':', Port);
		Uart_Write(' ', Port);

		// Wy�wietlenie HEX
		for(uint8_t h=0; h<=15; h++) {
			
			// Sprawdzanie czy nie zosta�y wy�wietlone ju� wszystkie znaki
			if(LengthForHex) {
				LengthForHex--;
				Uart_WriteHex(*(wskaznik+h), ' ', Port);
			}
			else {
				// Wy�wietlanie trzech spacji, aby potem mo�na by�o wy�wietli� ASCII we w�a�ciwym miejscu
				Uart_Write("   ");
			}
		}
		
		// Wy�wietlenie ASCII
		for(uint8_t h=0; h<=15; h++) {
			if((*(wskaznik+h) >= ' ') && (*(wskaznik+h) < 127)) {				// Omijanie znak�w specjanych <32 i <127
				Uart_Write(*(wskaznik+h), Port);
			} 
			else {
				Uart_Write(' ', Port);
			}
			
			if(--LengthForAscii == 0) {
				break;
			}
		}
		
		// Inkrementacja wska�nik�w
		wskaznik += 16;
		i += 16;

		// Reset watchdoga
		asm volatile("wdr");
	} while(i <= Length-1 && i != 0);		// i != 0 zabezpiecza przed przekr�ceniem sie licznika po 0xFFFF


}


// Ponowne wys�anie ca�ej zawarto�ci bufora TX
// Aby ta operacja dzia�a�a prawid�owo, wcze�niej nale�y wywo�a� Uart_TxBufferFlush i d�ugo�� wysy�anego
// ci�gu znak�w nie mo�e przekroczy� d�ugo�ci bufora UART_TX_BUFFER_LENGTH
void Uart_Resend(USART_t * Port) {
	
	volatile UART_Buffer_t * Buffer = Uart__GetProgBuffer(Port);
// 	Uart_Write("\r\nHead: ");
// 	Uart_WriteDec(Buffer->TxBufferHead);
// 	Uart_Write("\r\nTail: ");
// 	Uart_WriteDec(Buffer->TxBufferTail);
// 	Uart_Write("\r\nCnt: ");
// 	Uart_WriteDec(Buffer->TxBufferCnt);
// 	Uart_WriteNL();
	
	// Wy��czenie przerwa�
	cli();
	
	// Zerowanie wska�nika tail
	
	Buffer->TxBufferTail = 0;
	
	
// 	Uart_Write("\r\nHead: ");
// 	Uart_WriteDec(Buffer->TxBufferHead);
// 	Uart_Write("\r\nTail: ");
// 	Uart_WriteDec(Buffer->TxBufferTail);
// 	Uart_Write("\r\nCnt: ");
// 	Uart_WriteDec(Buffer->TxBufferCnt);
// 	Uart_WriteNL();

	// Usuwanie ACK doklejonego na ko�cu bufora
// 	if(Buffer->TxBuffer[Buffer->TxBufferHead - 1] == ACK) {
// 		Buffer->TxBuffer[--Buffer->TxBufferHead] = NUL;
// 	}
	
	Buffer->TxBufferCnt = Buffer->TxBufferHead;

	// Je�eli obecnie transmiter jest wy��czony, to go w��czamy
	if((Port->CTRLB & USART_TXEN_bm) == 0) {
		Uart_TxEnable(Port);

		// Je�eli jest u�ywana blokada u�pienia
		#if UART_USE_UCOSMOS_SLEEP
		OS_SLEEP_DISABLE;													// Ustawienie blokady u�pienia
		#endif
	}
	
	// Aktywowanie wysy�ania
	Port->CTRLA		=	USART_DREIE_bm |									// W��czenie przerwa� od DRE...
						USART_RXCIE_bm |									// ...a RX...
						USART_TXCIE_bm;										// ...oraz TX ju� wcze�niej by�o w��czone
	
	// W��czenie przerwa�
	sei();
	
	
	
	
	//Uart_Write('x', Port);
	
// 	Uart_Write("\r\nHead: ");
// 	Uart_WriteDec(Buffer->TxBufferHead);
// 	Uart_Write("\r\nTail: ");
// 	Uart_WriteDec(Buffer->TxBufferTail);
// 	Uart_Write("\r\nCnt: ");
// 	Uart_WriteDec(Buffer->TxBufferCnt);
// 	Uart_WriteNL();
	
//	Uart_Write((const char *)Buffer->TxBuffer);
}


// ====================
// Odbi�r danych z UART
// ====================


// Funkcja pobieraj�ca jeden znak z wybranego portu
// Po odczytani znak z bufora programowego jest usuwany i automatycznie jest zwalniane miejsce na odbi�r kolejnego znaku
uint8_t Uart_Read(USART_t * Port) {

	// Wska�nik do bufora
	volatile UART_Buffer_t * Buffer = Uart__GetProgBuffer(Port);
		
	uint8_t Data;
	if(Buffer->RxBufferCnt) {													// Je�eli jest co� w buforze
		
		Buffer->RxBufferCnt--;													// Zmniejszenie liczby znak�w w buforze, bo zaraz odczytamy jeden z nich

		// Je�eli jest u�ywana blokada u�pienia
		#if UART_USE_UCOSMOS_SLEEP
			if(Buffer->RxBufferCnt == 0) {										// Je�eli bufor za chwil� b�dzie pusty
				OS_SLEEP_ENABLE;												// Zwolnienie blokady u�pienia
			}
		#endif

		Data = Buffer->RxBuffer[Buffer->RxBufferTail];							// Odczytanie ogona bufora						
		
		#if UART_CLEAR_BYTE_AFTER_READ											// Tylko w celach debugowych
			Buffer->RxBuffer[Buffer->RxBufferTail] = 0;							// Czyszczenie bajtu w buforze po jego odczycie
		#endif
		
		if(++Buffer->RxBufferTail == UART_RX_BUFFER_LENGTH) {
			Buffer->RxBufferTail = 0;											// Inkrementacja ogona i kontrola przepe�nienia, zapis ++ w tej lini oszcz�dza 2B ni� gdyby ++ by�o w kolejnej linii
		}
		
		//Uart_Write(Data, Port);
		return Data;
	} 
	else {																		// Je�eli bufor jest pusty
		return 0;
	}
}


// Przerwanie od odbiornu danych
static void Uart__InterruptRx(USART_t * Port, volatile UART_Buffer_t * Buffer) {
	
	// Wska�nik do bufora portu UART, kt�ry zg�osi� przerwanie
	//volatile UART_Buffer_t * Buffer = Uart__GetProgBuffer(Port);

	// Je�eli jest u�ywana blokada u�pienia
	#if UART_USE_UCOSMOS_SLEEP
		if(Buffer->RxBufferCnt == 0) {											// Je�eli bufor wcze�niej by� pusty
			OS_SLEEP_DISABLE;													// Wy��czenie trybu u�pienia do czasu odebrania wszystkich znak�w z bufora
		}
	#endif
	
	if(Buffer->RxBufferCnt < UART_RX_BUFFER_LENGTH) {							// Kontrola wolnego miejsca w buforze
		Buffer->RxBufferCnt++;
		Buffer->RxBuffer[Buffer->RxBufferHead] = Port->RXDATAL;
		if(++Buffer->RxBufferHead == UART_RX_BUFFER_LENGTH) {					// Zapis ++RxBufferHead oszcz�dza pami�� o 2B
			Buffer->RxBufferHead = 0;											// Przepe�nienie indeksu head
		}
	} 
	else {																		// Przepe�nienie bufora
		#if UART_BREAK_ON_BUFFER_FULL								
			asm volatile("break");												// Zatrzymanie je�li bufor przepe�niony
		#endif
		(void)Port->RXDATAL;													// Odczytanie by wyzerowa� flag� przerwania
	}	
}

// Przerwanie od RXC w celu skopiowanie znaku odebranego przez UART do bufora programowego
#if UART0_USE
ISR(USART0_RXC_vect) {
//	INT_ON;
	Uart__InterruptRx(&USART0, &UART0_ProgBuf);
//	INT_OFF;
}
#endif


// Przerwanie od RXC w celu skopiowanie znaku odebranego przez UART do bufora programowego
#if UART1_USE
ISR(USART1_RXC_vect) {
	Uart__InterruptRx(&USART1, &UART1_ProgBuf);
}
#endif


// Przerwanie od RXC w celu skopiowanie znaku odebranego przez UART do bufora programowego
#if UART2_USE
ISR(USART2_RXC_vect) {
	Uart__InterruptRx(&USART2, &UART2_ProgBuf);
}
#endif


// Przerwanie od RXC w celu skopiowanie znaku odebranego przez UART do bufora programowego
#if UART3_USE
ISR(USART3_RXC_vect) {
	Uart__InterruptRx(&USART3, &UART3_ProgBuf);
}
#endif

// Odczyt liczby znak�w gotowych do odczyty z bufora programowego
uint8_t Uart_ReceivedCnt(USART_t * Port) {
	return  Uart__GetProgBuffer(Port)->RxBufferCnt;
// 	volatile UART_Buffer_t * Buffer = Uart__GetProgBuffer(Port);
// 	return Buffer->RxBufferCnt;
}


// ==================
// Funkcje pomocnicze
// ==================


// Czyszczenie bufora programowego Rx
void Uart_RxBufferFlush(volatile UART_Buffer_t * ProgBuf) {
	
	cli();
	for(uint8_t i=0; i<UART_RX_BUFFER_LENGTH; i++) {
		ProgBuf->RxBuffer[i] = 0;
	}
	
	ProgBuf->RxBufferHead	=	0;
	ProgBuf->RxBufferTail	=	0;
	ProgBuf->RxBufferCnt	=	0;
	sei();
}


// Czyszczenie bufora programowego Rx - wersja z podawaniem nazwy portu przez argument
void Uart_RxBufferFlush(USART_t * Port) {
	Uart_RxBufferFlush(Uart__GetProgBuffer(Port));
}


// Czyszczenie bufora programowego Tx
void Uart_TxBufferFlush(volatile UART_Buffer_t * ProgBuf) {
	
	cli();
	for(uint8_t i=0; i<UART_TX_BUFFER_LENGTH; i++) {
		ProgBuf->TxBuffer[i] = 0;
	}
	
	ProgBuf->TxBufferHead	=	0;
	ProgBuf->TxBufferTail	=	0;
	ProgBuf->TxBufferCnt	=	0;
	ProgBuf->TxBufferCRC	=	0x6363;
	sei();
}


// Czyszczenie bufora programowego Rx - wersja z podawaniem nazwy portu przez argument
void Uart_TxBufferFlush(USART_t * Port) {
	Uart_WaitForTxComplete(Port);
	Uart_TxBufferFlush(Uart__GetProgBuffer(Port));
}


// Czekanie a� transmisja dobiegnie ko�ca (przydatne przed wej�ciem w stan u�pienia) - wersja dla wskazanego UART
void Uart_WaitForTxComplete(USART_t * Port) {
	if(Uart__GetProgBuffer(Port)->TxBufferCnt == 0) {
		return;
	}
	while(Port->CTRLB & USART_TXEN_bm);
}


// Czekanie a� tranmisja dobiegnie ko�ca - wersja dla wszystkich u�ywanych UART�w
void Uart_WaitForTxComplete(void) {

	#if UART0_USE
		while(USART0.CTRLB & USART_TXEN_bm);
	#endif
	
	#if UART1_USE
		while(USART1.CTRLB & USART_TXEN_bm);
	#endif
	
	#if UART2_USE
		while(USART2.CTRLB & USART_TXEN_bm);
	#endif
	
	#if UART3_USE
		while(USART3.CTRLB & USART_TXEN_bm);
	#endif
}


// Zerowanie kontrolnego CRC
void Uart_TxCrcClear(USART_t * Port) {
	Uart__GetProgBuffer(Port)->TxBufferCRC = 0x6363;
}


// Odczytywanie kontrolnego CRC
uint16_t Uart_TxCrcGet(USART_t * Port) {
	return Uart__GetProgBuffer(Port)->TxBufferCRC;
}

