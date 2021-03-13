// Wersja 2.17

#include "uart_multi.h"


// Bufory programowe dla ka¿dego sprzêtowego portu
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


// Struktura umo¿liwiaj¹ca zignorowanie argumentu USART_t * Port wszystkich funkcji, je¿eli UART_PortOverride != NULL
USART_t * UART_PortOverride = NULL;


// ==================
// Funkcje pomocnicze
// ==================


// Funkcja zwracaj¹ca wskaŸnik do bufora programowego w³aœciwego dla podanego potru sprzêtowego
static volatile UART_Buffer_t * Uart__GetProgBuffer(USART_t * Port) {
	
	// Sprawdzanie, który bufor nale¿y zastosowaæ w zale¿noœci od wybranego portu
	// Porównujemy tu adres portu przekazany przez wskaŸnik z fizycznym adresem strutury USARTn
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
	// TODO: Posprz¹taæ to
	#if B_MIFARE_v002 || B_LOCK_v001 || B_XNANO
		return &UART0_ProgBuf;
	#else
		return &UART2_ProgBuf;
	#endif
	//while(1);
	//asm volatile("break");
	//return NULL;
}


// Inicjalizacja sprzêtowego peryferium wskazanego wskaŸnikiem (u¿ywane tylko przez Uart_Init();
// - Port		-	WskaŸnik do portu
// - Baud		-	Baudrate ju¿ po przeliczeniu, ta wartoœæ jest wpisywana wprost do jesteru USARTx.BAUD
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
		Port->DBGCTRL	=	USART_DBGRUN_bm;									// Ma dzia³aæ podczas breakpointów
	#endif	
	
	// Czyszczenie bufora
	memset(Buffer, 0, sizeof(UART_Buffer_t));
}


// Inicjalizacja pinu TX, który musi byæ ustawiony jako wyjœcie i ustawiony w stan 1
// Dodatkowo konfiguracja Portmux, jeœli wybrano port alternatywny
#if UART0_USE
static void Uart__InitPinsForUsart0(void) {
	
	// Konfiguracja dla ATtinyXX14/16/17/18 - port podstawowy
	#if UART0_PORTB_23 && (HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17)
		PORTMUX.CTRLB	&= ~PORTMUX_USART0_ALTERNATE_gc;
		PORTB.PIN3CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w³¹czony rezystor pull-up
		PORTB.PIN2CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w³¹czony rezystor pull-up
							PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy³¹czony bufor wejœciowy
		VPORTB.OUT		|=	PIN2_bm;											// Pin Tx jako wyjœcie
		VPORTB.DIR		|=	PIN2_bm;											// Pin Tx jako wyjœcie
		
		
	#endif

	// Konfiguracja dla ATtinyXX12/14/16/17/18 - port alternatywny
	#if UART0_PORTA_12 && (HW_CPU_ATtinyXX12 || HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17)
		PORTMUX.CTRLB	|=	PORTMUX_USART0_ALTERNATE_gc;
		PORTA.PIN2CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w³¹czony rezystor pull-up
		PORTA.PIN1CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w³¹czony rezystor pull-up
							PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy³¹czony bufor wejœciowy
		VPORTA.OUT		|=	PIN1_bm;											// Pin Tx jako wyjœcie
		VPORTA.DIR		|=	PIN1_bm;											// Pin Tx jako wyjœcie
		
		
	#endif

	// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
	#if UART0_PORTA_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		&= ~PORTMUX_USART0_gm;
		PORTA.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
		PORTA.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
		VPORTA.OUT				|=	PIN0_bm;									// Pin Tx jako wyjœcie
		VPORTA.DIR				|=	PIN0_bm;									// Pin Tx jako wyjœcie
	#endif

	// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
	#if UART0_PORTA_45 && (HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		|=	PORTMUX_USART0_ALT1_gc;
		PORTA.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
		PORTA.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
		VPORTA.OUT				|=	PIN4_bm;									// Pin Tx jako wyjœcie
		VPORTA.DIR				|=	PIN4_bm;									// Pin Tx jako wyjœcie
	#endif
}
#endif


// Inicjalizacja pinu TX, który musi byæ ustawiony jako wyjœcie i ustawiony w stan 1
// Dodatkowo konfiguracja Portmux, jeœli wybrano port alternatywny
#if UART1_USE
static void Uart__InitPinsForUsart1(void) {
	
	// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
	#if UART1_PORTC_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		&= ~PORTMUX_USART1_gm;
		PORTC.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
		PORTC.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
		VPORTC.OUT				|=	PIN0_bm;									// Pin Tx jako wyjœcie
		VPORTC.DIR				|=	PIN0_bm;									// Pin Tx jako wyjœcie
	#endif

	// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
	#if UART1_PORTC_45 && (HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		|=	PORTMUX_USART1_ALT1_gc;
		PORTC.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
		PORTC.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
		VPORTC.OUT				|=	PIN4_bm;									// Pin Tx jako wyjœcie
		VPORTC.DIR				|=	PIN4_bm;									// Pin Tx jako wyjœcie
	#endif
}
#endif


// Inicjalizacja pinu TX, który musi byæ ustawiony jako wyjœcie i ustawiony w stan 1
// Dodatkowo konfiguracja Portmux, jeœli wybrano port alternatywny
#if UART2_USE
static void Uart__InitPinsForUsart2(void) {

	// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
	#if UART2_PORTF_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		&= ~PORTMUX_USART2_gm;
		PORTF.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
		PORTF.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
		VPORTF.OUT				|=	PIN0_bm;									// Pin Tx jako wyjœcie
		VPORTF.DIR				|=	PIN0_bm;									// Pin Tx jako wyjœcie
	#endif

	// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
	#if UART2_PORTF_45 && (HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		|=	PORTMUX_USART2_ALT1_gc;
		PORTF.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
		PORTF.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
		VPORTF.OUT				|=	PIN4_bm;									// Pin Tx jako wyjœcie
		VPORTF.DIR				|=	PIN4_bm;									// Pin Tx jako wyjœcie
	#endif
}
#endif


// Inicjalizacja pinu TX, który musi byæ ustawiony jako wyjœcie i ustawiony w stan 1
// Dodatkowo konfiguracja Portmux, jeœli wybrano port alternatywny
#if UART3_USE
static void Uart__InitPinsForUsart3(void) {

	// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
	#if UART3_PORTB_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		&= ~PORTMUX_USART3_gm;
		PORTB.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
		PORTB.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
		VPORTB.OUT				|=	PIN0_bm;									// Pin Tx jako wyjœcie
		VPORTB.DIR				|=	PIN0_bm;									// Pin Tx jako wyjœcie
	#endif

	// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
	#if UART3_PORTB_45 && (HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		|=	PORTMUX_USART3_ALT1_gc;
		PORTB.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
		PORTB.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
		VPORTB.OUT				|=	PIN4_bm;									// Pin Tx jako wyjœcie
		VPORTB.DIR				|=	PIN4_bm;									// Pin Tx jako wyjœcie
	#endif
}
#endif


// Inicjalizacja zgodnie z konfiguracj¹ w pliku uart_config.h
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
	CPUINT.CTRLA	|=	CPUINT_LVL0RR_bm;										// Algorytm round-robin dla przerwañ o tym samym priorytecie
	CPUINT.LVL1VEC	=	UART_CONSOLE_INT;										// Jeœli wrzucamy coœ do bufora UART w przerwaniu, 
																				// to przerwanie opró¿nienia bufora musi mieæ wiêkszy priortet, 
																				// bo inaczej w przypadku przepe³nienia bufora procesor siê zawiesi
}


// Wy³¹czenie transmitera (domyœlnie po inicjalizacji jest w³¹czony)
void Uart_TxDisable(USART_t * Port) {
	cli();
	Port->CTRLB		&=	~USART_TXEN_bm;
	sei();
}


// W³¹czenie transmitera (domyœlnie po inicjalizacji jest w³¹czony)
void Uart_TxEnable(USART_t * Port) {
	cli();

	// W³¹czenie nadajnika
	Port->CTRLB		|=	USART_TXEN_bm;

	// Po wy³¹czeniu nadajnika UART pin Tx ustawiany jest automatycznie jako wejœcie i trzeba go ponownie skonfigurowaæ jako wyjœcie
	// UWAGA - chyba jest tu jakiœ problem z procesorem, bo jeœli ustawienie pinów bêdzie przez ponownym w³¹czeniem nadajnika,
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


// Wy³¹czenie odbiornika (domyœlnie po inicjalizacji jest w³¹czony)
void Uart_RxDisable(USART_t * Port) {
	Port->CTRLB		&=	~USART_RXEN_bm;
}


// W³¹czenie odbiornika (domyœlnie po inicjalizacji jest w³¹czony)
void Uart_RxEnable(USART_t * Port) {
	Port->CTRLB		|=	USART_RXEN_bm;
}



// ====================
// Wysy³anie przez UART
// ====================


// Wysy³anie 1 bajtu danych
void Uart_Write(uint8_t Data, USART_t * Port) {

// 	// Je¿eli za argument wstawiono !!
	if(UART_PortOverride != NULL) {
		Port = UART_PortOverride;
	}
	
	// Je¿eli obecnie transmiter jest wy³¹czony, to go w³¹czamy 
	if((Port->CTRLB & USART_TXEN_bm) == 0) {								
		Uart_TxEnable(Port);													

		// Je¿eli jest u¿ywana blokada uœpienia
		#if UART_USE_UCOSMOS_SLEEP
			OS_SLEEP_DISABLE;													// Ustawienie blokady uœpienia
		#endif
	}

	// WskaŸnik do bufora pierœcieniowego
	volatile UART_Buffer_t * Buffer = Uart__GetProgBuffer(Port);
	
	// Procedura zapisu danych do bufora sprzêtowego lub programowego
	Port->STATUS		=	USART_TXCIF_bm;										// Kasowanie flagi koñca nadawania
// 	if(!(Port->CTRLA & USART_DREIE_bm)) {										// Jeœli DRE jest w³¹czone to znaczy, ¿e mamy ju¿ rozpoczêt¹ transmisjê
// 		Port->TXDATAL	=	Data;												// Wpisanie danych do bufora nadawczego i rozpoczêcie transmisji
// 		Port->CTRLA		=	USART_DREIE_bm |									// W³¹czenie przerwañ od DRE...
// 							USART_RXCIE_bm |									// ...a RX...
// 							USART_TXCIE_bm;										// ...oraz TX ju¿ wczeœniej by³o w³¹czone
// 	} 
// 	else {																		// Bufor sprzêtowy pe³ny
		while(Buffer->TxBufferCnt == UART_TX_BUFFER_LENGTH) {					// Sprawdzenie czy bufor programowy pusty lub czekanie a¿ bêdzie wolne miejsce
			#if UART_BREAK_ON_BUFFER_FULL								
				asm volatile("break");											// Zatrzymanie jeœli bufor przepe³niony
			#endif
		}
		
		cli();																	// Wy³¹czenie przerwañ, aby nie dopuœciæ do sytuacji, kiedy TxBuffer by³by jednoczeœnie modyfikowany w przerwaniu
		Buffer->TxBufferCnt++;													// Zwiêkszenie licznika znaków w buforze nadawczym
		Buffer->TxBuffer[Buffer->TxBufferHead] = Data;							// Wpisanie znaku do bufora na pocz¹tek kolejki FIFO
		
		if(++Buffer->TxBufferHead == UART_TX_BUFFER_LENGTH) {					// Zapis ++TxBufferHead oszczêdza pamiêæ o 4B
			Buffer->TxBufferHead = 0;											// Przekreœcenie siê bufora pierœcieniowego
		}
		
		Port->CTRLA		=	USART_DREIE_bm |									// W³¹czenie przerwañ od DRE...
							USART_RXCIE_bm |									// ...a RX...
							USART_TXCIE_bm;										// ...oraz TX ju¿ wczeœniej by³o w³¹czone
		sei();																	// Glabalne w³¹czenie przerwañ
//	}
	
	// Aktualizacja CRC
	Data = Data ^ uint8_t(Buffer->TxBufferCRC);
	Data = Data ^ (Data << 4);
	Buffer->TxBufferCRC = (Buffer->TxBufferCRC >> 8) ^ (Data << 8) ^ (Data << 3) ^ (Data >> 4);
}


// Funkcja obs³uguj¹ca przerwania od zwolnienia siê miejsca w buforze
static void Uart__InterruptDre(USART_t * Port, UART_Buffer_t * Buffer) {
	
	//volatile UART_Buffer_t * Buffer = Uart__GetProgBuffer(Port);
	
	if(Buffer->TxBufferCnt) {													// Je¿eli w buforze programowym jest coœ do wys³ania
		
		Port->STATUS	=	USART_TXCIF_bm;										// Kasowanie flagi koñca nadawania
		Buffer->TxBufferCnt--;													// Zmniejszenie liczby znaków w buforze nadawczym
		Port->TXDATAL = Buffer->TxBuffer[Buffer->TxBufferTail];					// Wysy³anie znaku z koñca kolejki FIFO
		
		#if UART_CLEAR_BYTE_AFTER_READ											// W celach debugowych
			Buffer->TxBuffer[Buffer->TxBufferTail] = 0;							// Czyszczenie znaku w buforze programowym, który zosta³ skopiowany do bufora sprzêtowego
		#endif
		
		if(++Buffer->TxBufferTail == UART_TX_BUFFER_LENGTH) {					// Umieszczenie ++ tutaj oszczêdza 4 bajty	
			Buffer->TxBufferTail = 0;											// Przekrêcenie siê bufora pierœcieniowego
		}
	} 
	else {																		// Bufor programowy pusty, koniec transmisji (ale bajty w buforze sprzêtowym ca³y czas s¹ jeszcze wysy³ane!)
		Port->CTRLA		=	USART_RXCIE_bm |									// W³¹czenie przerwañ od DRE...
							USART_TXCIE_bm;										// ...a RX oraz TX ju¿ wczeœniej by³o w³¹czone
	}	
}


// Przerwanie UART0 w celu wysy³ania danych - po zwolnieniu 1 bajtu w buforze sprzêtowym
#if UART0_USE
ISR(USART0_DRE_vect) {
//	INT_ON;
	Uart__InterruptDre(&USART0, &UART0_ProgBuf);
//	INT_OFF;
}
#endif


// Przerwanie UART1 w celu wysy³ania danych - po zwolnieniu 1 bajtu w buforze sprzêtowym
#if UART1_USE
ISR(USART1_DRE_vect) {
	Uart__InterruptDre(&USART1, &UART1_ProgBuf);
}
#endif


// Przerwanie UART2 w celu wysy³ania danych - po zwolnieniu 1 bajtu w buforze sprzêtowym
#if UART2_USE
ISR(USART2_DRE_vect) {
	Uart__InterruptDre(&USART2, &UART2_ProgBuf);
}
#endif


// Przerwanie UART3 w celu wysy³ania danych - po zwolnieniu 1 bajtu w buforze sprzêtowym
#if UART3_USE
ISR(USART3_DRE_vect) {
	Uart__InterruptDre(&USART3, &UART3_ProgBuf);
}
#endif


// Funkcja obs³uguj¹ca przerwanie od zakoñczenia transmisji
static void Uart__InterruptTx(USART_t * Port) {

	// Kasowanie flagi przerwania
	Port->STATUS	=	USART_TXCIF_bm;

	// Wy³¹czenie transmitera
	Port->CTRLB		&= ~USART_TXEN_bm;

	// Je¿eli jest u¿ywana blokada uœpienia
	#if UART_USE_UCOSMOS_SLEEP
		OS_SLEEP_ENABLE;														// Zwolnienie blokady uœpienia
	#endif
}


// Ca³kowite opró¿nienie bufora sprzêtowego i zakoñczenie transmisji w USART 0
#if UART0_USE
ISR(USART0_TXC_vect) {
	Uart__InterruptTx(&USART0);
}
#endif


// Ca³kowite opró¿nienie bufora sprzêtowego i zakoñczenie transmisji w USART 1
#if UART1_USE
ISR(USART1_TXC_vect) {
	Uart__InterruptTx(&USART1);
}
#endif


// Ca³kowite opró¿nienie bufora sprzêtowego i zakoñczenie transmisji w USART 2
#if UART2_USE
ISR(USART2_TXC_vect) {
	Uart__InterruptTx(&USART2);
}
#endif


// Ca³kowite opró¿nienie bufora sprzêtowego i zakoñczenie transmisji w USART 3
#if UART3_USE
ISR(USART3_TXC_vect) {
	Uart__InterruptTx(&USART3);
}
#endif

// ================================================
// Funkcje wy¿szego poziomu do wysy³ania przez UART
// ================================================


// Zapis ci¹gu znaków
void Uart_Write(const char * Text, USART_t * Port) {
	while(*Text) Uart_Write(*Text++, Port);
}


// Nowa linia
void Uart_WriteNL(USART_t * Port) {
	Uart_Write("\r\n", Port);
}


// Liczba dziesiêtna bez znaku
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

// Liczba dziesiêtna ze znakiem
void Uart_WriteDecSigned(int8_t Value, USART_t * Port) {
	if(Value < 0) {
		Uart_Write('-', Port);
		Value = -Value;
	}
	Uart_WriteDec(uint8_t(Value), Port);
}

// Liczba dziesiêtna ze znakiem
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


// Ci¹g znaków prezentowany jako HEX
void Uart_WriteHexString(const uint8_t * String, const uint16_t Length, const uint8_t Separator, const uint8_t BytesInRow, USART_t * Port) {
	
	for(uint16_t i=0; i<Length; i++) {
		
		// Przejœcie do nowej linii (nie dotyczny pierwszego wyœwietlanego znaku)
		if((i%BytesInRow == 0) && i != 0) {
			Uart_WriteNL(Port);
		}

		// Wyœwietlenie znaku
		Uart_WriteHex(*(String+i), Separator, Port);
	}
}


// Ci¹g znaków prezentowany jako HEX, wraz z nag³ówkiem i adresowaniem
void Uart_Dump(const uint8_t * String, uint16_t Length, uint16_t AddressStartValue, USART_t * Port) {
	
	uint8_t * wskaznik		= (uint8_t *)String;
	uint16_t LengthForHex	= Length;
	uint16_t LengthForAscii	= Length;
	uint16_t i = 0;

	Uart_Write("       0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F", Port);

	// Wyœwietlanie w pêtli po 16 znaków na ka¿d¹ liniê
	do {
		
		// Zejœcie do nowej linii
		Uart_WriteNL(Port);

		// Wyœwietlenie adresu
		Uart_WriteHex(uint16_t(i + AddressStartValue), ':', Port);
		Uart_Write(' ', Port);

		// Wyœwietlenie HEX
		for(uint8_t h=0; h<=15; h++) {
			
			// Sprawdzanie czy nie zosta³y wyœwietlone ju¿ wszystkie znaki
			if(LengthForHex) {
				LengthForHex--;
				Uart_WriteHex(*(wskaznik+h), ' ', Port);
			}
			else {
				// Wyœwietlanie trzech spacji, aby potem mo¿na by³o wyœwietliæ ASCII we w³aœciwym miejscu
				Uart_Write("   ");
			}
		}
		
		// Wyœwietlenie ASCII
		for(uint8_t h=0; h<=15; h++) {
			if((*(wskaznik+h) >= ' ') && (*(wskaznik+h) < 127)) {				// Omijanie znaków specjanych <32 i <127
				Uart_Write(*(wskaznik+h), Port);
			} 
			else {
				Uart_Write(' ', Port);
			}
			
			if(--LengthForAscii == 0) {
				break;
			}
		}
		
		// Inkrementacja wskaŸników
		wskaznik += 16;
		i += 16;

		// Reset watchdoga
		asm volatile("wdr");
	} while(i <= Length-1 && i != 0);		// i != 0 zabezpiecza przed przekrêceniem sie licznika po 0xFFFF


}


// Ponowne wys³anie ca³ej zawartoœci bufora TX
// Aby ta operacja dzia³a³a prawid³owo, wczeœniej nale¿y wywo³aæ Uart_TxBufferFlush i d³ugoœæ wysy³anego
// ci¹gu znaków nie mo¿e przekroczyæ d³ugoœci bufora UART_TX_BUFFER_LENGTH
void Uart_Resend(USART_t * Port) {
	
	volatile UART_Buffer_t * Buffer = Uart__GetProgBuffer(Port);
// 	Uart_Write("\r\nHead: ");
// 	Uart_WriteDec(Buffer->TxBufferHead);
// 	Uart_Write("\r\nTail: ");
// 	Uart_WriteDec(Buffer->TxBufferTail);
// 	Uart_Write("\r\nCnt: ");
// 	Uart_WriteDec(Buffer->TxBufferCnt);
// 	Uart_WriteNL();
	
	// Wy³¹czenie przerwañ
	cli();
	
	// Zerowanie wskaŸnika tail
	
	Buffer->TxBufferTail = 0;
	
	
// 	Uart_Write("\r\nHead: ");
// 	Uart_WriteDec(Buffer->TxBufferHead);
// 	Uart_Write("\r\nTail: ");
// 	Uart_WriteDec(Buffer->TxBufferTail);
// 	Uart_Write("\r\nCnt: ");
// 	Uart_WriteDec(Buffer->TxBufferCnt);
// 	Uart_WriteNL();

	// Usuwanie ACK doklejonego na koñcu bufora
// 	if(Buffer->TxBuffer[Buffer->TxBufferHead - 1] == ACK) {
// 		Buffer->TxBuffer[--Buffer->TxBufferHead] = NUL;
// 	}
	
	Buffer->TxBufferCnt = Buffer->TxBufferHead;

	// Je¿eli obecnie transmiter jest wy³¹czony, to go w³¹czamy
	if((Port->CTRLB & USART_TXEN_bm) == 0) {
		Uart_TxEnable(Port);

		// Je¿eli jest u¿ywana blokada uœpienia
		#if UART_USE_UCOSMOS_SLEEP
		OS_SLEEP_DISABLE;													// Ustawienie blokady uœpienia
		#endif
	}
	
	// Aktywowanie wysy³ania
	Port->CTRLA		=	USART_DREIE_bm |									// W³¹czenie przerwañ od DRE...
						USART_RXCIE_bm |									// ...a RX...
						USART_TXCIE_bm;										// ...oraz TX ju¿ wczeœniej by³o w³¹czone
	
	// W³¹czenie przerwañ
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
// Odbiór danych z UART
// ====================


// Funkcja pobieraj¹ca jeden znak z wybranego portu
// Po odczytani znak z bufora programowego jest usuwany i automatycznie jest zwalniane miejsce na odbiór kolejnego znaku
uint8_t Uart_Read(USART_t * Port) {

	// WskaŸnik do bufora
	volatile UART_Buffer_t * Buffer = Uart__GetProgBuffer(Port);
		
	uint8_t Data;
	if(Buffer->RxBufferCnt) {													// Je¿eli jest coœ w buforze
		
		Buffer->RxBufferCnt--;													// Zmniejszenie liczby znaków w buforze, bo zaraz odczytamy jeden z nich

		// Je¿eli jest u¿ywana blokada uœpienia
		#if UART_USE_UCOSMOS_SLEEP
			if(Buffer->RxBufferCnt == 0) {										// Je¿eli bufor za chwilê bêdzie pusty
				OS_SLEEP_ENABLE;												// Zwolnienie blokady uœpienia
			}
		#endif

		Data = Buffer->RxBuffer[Buffer->RxBufferTail];							// Odczytanie ogona bufora						
		
		#if UART_CLEAR_BYTE_AFTER_READ											// Tylko w celach debugowych
			Buffer->RxBuffer[Buffer->RxBufferTail] = 0;							// Czyszczenie bajtu w buforze po jego odczycie
		#endif
		
		if(++Buffer->RxBufferTail == UART_RX_BUFFER_LENGTH) {
			Buffer->RxBufferTail = 0;											// Inkrementacja ogona i kontrola przepe³nienia, zapis ++ w tej lini oszczêdza 2B ni¿ gdyby ++ by³o w kolejnej linii
		}
		
		//Uart_Write(Data, Port);
		return Data;
	} 
	else {																		// Je¿eli bufor jest pusty
		return 0;
	}
}


// Przerwanie od odbiornu danych
static void Uart__InterruptRx(USART_t * Port, volatile UART_Buffer_t * Buffer) {
	
	// WskaŸnik do bufora portu UART, który zg³osi³ przerwanie
	//volatile UART_Buffer_t * Buffer = Uart__GetProgBuffer(Port);

	// Je¿eli jest u¿ywana blokada uœpienia
	#if UART_USE_UCOSMOS_SLEEP
		if(Buffer->RxBufferCnt == 0) {											// Je¿eli bufor wczeœniej by³ pusty
			OS_SLEEP_DISABLE;													// Wy³¹czenie trybu uœpienia do czasu odebrania wszystkich znaków z bufora
		}
	#endif
	
	if(Buffer->RxBufferCnt < UART_RX_BUFFER_LENGTH) {							// Kontrola wolnego miejsca w buforze
		Buffer->RxBufferCnt++;
		Buffer->RxBuffer[Buffer->RxBufferHead] = Port->RXDATAL;
		if(++Buffer->RxBufferHead == UART_RX_BUFFER_LENGTH) {					// Zapis ++RxBufferHead oszczêdza pamiêæ o 2B
			Buffer->RxBufferHead = 0;											// Przepe³nienie indeksu head
		}
	} 
	else {																		// Przepe³nienie bufora
		#if UART_BREAK_ON_BUFFER_FULL								
			asm volatile("break");												// Zatrzymanie jeœli bufor przepe³niony
		#endif
		(void)Port->RXDATAL;													// Odczytanie by wyzerowaæ flagê przerwania
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

// Odczyt liczby znaków gotowych do odczyty z bufora programowego
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


// Czekanie a¿ transmisja dobiegnie koñca (przydatne przed wejœciem w stan uœpienia) - wersja dla wskazanego UART
void Uart_WaitForTxComplete(USART_t * Port) {
	if(Uart__GetProgBuffer(Port)->TxBufferCnt == 0) {
		return;
	}
	while(Port->CTRLB & USART_TXEN_bm);
}


// Czekanie a¿ tranmisja dobiegnie koñca - wersja dla wszystkich u¿ywanych UARTów
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

