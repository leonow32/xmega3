// Wersja 2.17

#if COMPONENT_UART_SINGLE

#include "uart_single.h"

// Bufor programowy
volatile UART_Buffer_t UART_ProgBuf;

// Inicjalizacja zgodnie z konfiguracj? w pliku configS
void Uart_Init(void) {
	
	// Konfiguracja dla ATtinyXX14/16/17/18 - port podstawowy
	#if UART0_PORTB_23 && (HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17)
		PORTMUX.CTRLB	&= ~PORTMUX_USART0_ALTERNATE_gc;
		PORTB.PIN3CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w??czony rezystor pull-up
		PORTB.PIN2CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w??czony rezystor pull-up
							PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy??czony bufor wej?ciowy
		VPORTB.OUT		|=	PIN2_bm;											// Pin Tx jako wyj?cie
		VPORTB.DIR		|=	PIN2_bm;											// Pin Tx jako wyj?cie
	
	// Konfiguracja dla ATtinyXX12/14/16/17/18 - port UART0 alternatywny
	#elif UART0_PORTA_12 && (HW_CPU_ATtinyXX12 || HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17)
		PORTMUX.CTRLB	|=	PORTMUX_USART0_ALTERNATE_gc;
		PORTA.PIN2CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w??czony rezystor pull-up
		PORTA.PIN1CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w??czony rezystor pull-up
							PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy??czony bufor wej?ciowy
		VPORTA.OUT		|=	PIN1_bm;											// Pin Tx jako wyj?cie
		VPORTA.DIR		|=	PIN1_bm;											// Pin Tx jako wyj?cie
	
	// Konfiguracja dla ATtinyXX24/26/27 - port UART0 podstawowy
	#elif UART0_PORTB_23 && (HW_CPU_ATtinyXX24 || HW_CPU_ATtinyXX26 || HW_CPU_ATtinyXX27)
		PORTMUX.USARTROUTEA	|=	PORTMUX_USART0_DEFAULT_gc;
		PORTB.PIN3CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w??czony rezystor pull-up
		PORTB.PIN2CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w??czony rezystor pull-up
							PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy??czony bufor wej?ciowy
		VPORTB.OUT		|=	PIN2_bm;											// Pin Tx jako wyj?cie
		VPORTB.DIR		|=	PIN2_bm;											// Pin Tx jako wyj?cie
	
	// Konfiguracja dla ATtinyXX24/26/27 - port UART0 alternatywny
	#elif UART0_PORTA_12 && (HW_CPU_ATtinyXX24 || HW_CPU_ATtinyXX26 || HW_CPU_ATtinyXX27)
		PORTMUX.USARTROUTEA	|=	PORTMUX_USART0_ALT1_gc;
		PORTA.PIN2CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w??czony rezystor pull-up
		PORTA.PIN1CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w??czony rezystor pull-up
							PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy??czony bufor wej?ciowy
		VPORTA.OUT		|=	PIN1_bm;											// Pin Tx jako wyj?cie
		VPORTA.DIR		|=	PIN1_bm;											// Pin Tx jako wyj?cie
	
	// Konfiguracja dla ATtinyXX24/26/27 - port UART1 podstawowy
	#elif UART1_PORTA_12 && (HW_CPU_ATtinyXX24 || HW_CPU_ATtinyXX26 || HW_CPU_ATtinyXX27)
		PORTMUX.USARTROUTEA	|=	PORTMUX_USART1_DEFAULT_gc;
		PORTA.PIN2CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w??czony rezystor pull-up
		PORTA.PIN1CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w??czony rezystor pull-up
							PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy??czony bufor wej?ciowy
		VPORTA.OUT		|=	PIN1_bm;											// Pin Tx jako wyj?cie
		VPORTA.DIR		|=	PIN1_bm;											// Pin Tx jako wyj?cie
	
	// Konfiguracja dla ATtinyXX24/26/27 - port UART1 alternatywny
	#elif UART1_PORTC_21 && (HW_CPU_ATtinyXX24 || HW_CPU_ATtinyXX26 || HW_CPU_ATtinyXX27)
		PORTMUX.USARTROUTEA	|=	PORTMUX_USART1_ALT1_gc;
		PORTC.PIN1CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w??czony rezystor pull-up
		PORTC.PIN2CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w??czony rezystor pull-up
							PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy??czony bufor wej?ciowy
		VPORTC.OUT		|=	PIN2_bm;											// Pin Tx jako wyj?cie
		VPORTC.DIR		|=	PIN2_bm;											// Pin Tx jako wyj?cie
	
	// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
	#elif UART1_PORTC_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		&= ~PORTMUX_USART1_gm;
		PORTC.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w??czony rezystor pull-up
		PORTC.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w??czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy??czony bufor wej?ciowy
		VPORTC.OUT				|=	PIN0_bm;									// Pin Tx jako wyj?cie
		VPORTC.DIR				|=	PIN0_bm;									// Pin Tx jako wyj?cie
	
	// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
	#elif UART1_PORTC_45 && (HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		|=	PORTMUX_USART1_ALT1_gc;
		PORTC.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w??czony rezystor pull-up
		PORTC.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w??czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy??czony bufor wej?ciowy
		VPORTC.OUT				|=	PIN4_bm;									// Pin Tx jako wyj?cie
		VPORTC.DIR				|=	PIN4_bm;									// Pin Tx jako wyj?cie
	
	// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
	#elif UART2_PORTF_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		&= ~PORTMUX_USART2_gm;
		PORTF.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w??czony rezystor pull-up
		PORTF.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w??czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy??czony bufor wej?ciowy
		VPORTF.OUT				|=	PIN0_bm;									// Pin Tx jako wyj?cie
		VPORTF.DIR				|=	PIN0_bm;									// Pin Tx jako wyj?cie
	
	// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
	#elif UART2_PORTF_45 && (HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		|=	PORTMUX_USART2_ALT1_gc;
		PORTF.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w??czony rezystor pull-up
		PORTF.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w??czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy??czony bufor wej?ciowy
		VPORTF.OUT				|=	PIN4_bm;									// Pin Tx jako wyj?cie
		VPORTF.DIR				|=	PIN4_bm;									// Pin Tx jako wyj?cie
	
	// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
	#elif UART3_PORTB_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		&= ~PORTMUX_USART3_gm;
		PORTB.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w??czony rezystor pull-up
		PORTB.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w??czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy??czony bufor wej?ciowy
		VPORTB.OUT				|=	PIN0_bm;									// Pin Tx jako wyj?cie
		VPORTB.DIR				|=	PIN0_bm;									// Pin Tx jako wyj?cie
	
	// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
	#elif UART3_PORTB_45 && (HW_CPU_ATmegaXX09)
		PORTMUX.USARTROUTEA		|=	PORTMUX_USART3_ALT1_gc;
		PORTB.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w??czony rezystor pull-up
		PORTB.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w??czony rezystor pull-up
									PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy??czony bufor wej?ciowy
		VPORTB.OUT				|=	PIN4_bm;									// Pin Tx jako wyj?cie
		VPORTB.DIR				|=	PIN4_bm;									// Pin Tx jako wyj?cie
	
	#else
		#error "Missing config for UART"
	#endif
	
	USARTX.BAUD					=	uint16_t((F_CPU * 4) / UART_BAUD);			// Baud rate
	
	USARTX.CTRLA				=	USART_RXCIE_bm |							// Receive Complete Interrupt Enable
									USART_TXCIE_bm |							// Transmit Complete Interrupt Enable
								  //USART_DREIE_bm |							// Data Register Empty Interrupt Enable
								  //USART_RXSIE_bm |							// Receiver Start Frame Interrupt Enable
								  //USART_LBME_bm |								// Loop-back Mode Enable
								  //USART_ABEIE_bm |							// Auto-baud Error Interrupt Enable
									0;
	
	USARTX.CTRLB				=	USART_RXEN_bm |								// Receiver Enable
									USART_TXEN_bm |								// Transmitter Enable
									USART_SFDEN_bm |							// Start Frame Detection Enable
								  //USART_ODME_bm |								// Open Drain Mode Enable
									USART_RXMODE_NORMAL_gc ;					// Receiver Mode
								  //USART_MPCM_bp;								// Multi-Processor Communication Mode
	
	USARTX.CTRLC				=	USART_CMODE_ASYNCHRONOUS_gc |				// USART Communication Mode
									USART_PMODE_DISABLED_gc |					// Parity Mode
									USART_SBMODE_1BIT_gc |						// Stop Bit Mode
									USART_CHSIZE_8BIT_gc ;						// Character Size
	
	#if UART_DEBUG_RUN
		USARTX.DBGCTRL			=	USART_DBGRUN_bm;							// Ma dzia?a? podczas breakpoint?w
	#endif	
}


// ====================
// Wysy?anie przez UART
// ====================


// Wysy?anie 1 bajtu danych
void Uart_Write(uint8_t Data) {
	
	// Ustawienie flagi zaj?to?ci transmitera
	USARTX.TXPLCTRL = UART_TX_BUSY;
	
	// Procedura zapisu danych do bufora sprz?towego lub programowego
	USARTX.STATUS		=	USART_TXCIF_bm;										// Kasowanie flagi ko?ca nadawania
	
	while(UART_ProgBuf.TxBufferCnt == UART_TX_BUFFER_LENGTH) {					// Sprawdzenie czy bufor programowy pusty lub czekanie a? b?dzie wolne miejsce
		#if UART_BREAK_ON_BUFFER_FULL
			asm volatile("break");												// Zatrzymanie je?li bufor przepe?niony
		#endif
	}
	
	cli();																		// Wy??czenie przerwa?, aby nie dopu?ci? do sytuacji, kiedy TxBuffer by?by jednocze?nie modyfikowany w przerwaniu
	UART_ProgBuf.TxBufferCnt++;													// Zwi?kszenie licznika znak?w w buforze nadawczym
	UART_ProgBuf.TxBuffer[UART_ProgBuf.TxBufferHead] = Data;					// Wpisanie znaku do bufora na pocz?tek kolejki FIFO
	
	if(++UART_ProgBuf.TxBufferHead == UART_TX_BUFFER_LENGTH) {					// Zapis ++TxBufferHead oszcz?dza pami?? o 4B
		UART_ProgBuf.TxBufferHead = 0;											// Przekre?cenie si? bufora pier?cieniowego
	}
	
	USARTX.CTRLA	=	USART_DREIE_bm |										// W??czenie przerwa? od DRE...
						USART_RXCIE_bm |										// ...a RX...
						USART_TXCIE_bm;											// ...oraz TX ju? wcze?niej by?o w??czone
	sei();																		// Glabalne w??czenie przerwa?
}


// Przerwanie UART0 w celu wysy?ania danych - po zwolnieniu 1 bajtu w buforze sprz?towym
ISR(USARTX_DRE_vect) {
	if(UART_ProgBuf.TxBufferCnt) {												// Je?eli w buforze programowym jest co? do wys?ania
		
		USARTX.STATUS	=	USART_TXCIF_bm;										// Kasowanie flagi ko?ca nadawania
		UART_ProgBuf.TxBufferCnt--;												// Zmniejszenie liczby znak?w w buforze nadawczym
		USARTX.TXDATAL = UART_ProgBuf.TxBuffer[UART_ProgBuf.TxBufferTail];		// Wysy?anie znaku z ko?ca kolejki FIFO
		
		#if UART_CLEAR_BYTE_AFTER_READ											// W celach debugowych
			UART_ProgBuf.TxBuffer[UART_ProgBuf.TxBufferTail] = 0;				// Czyszczenie znaku w buforze programowym, kt?ry zosta? skopiowany do bufora sprz?towego
		#endif
		
		if(++UART_ProgBuf.TxBufferTail == UART_TX_BUFFER_LENGTH) {				// Umieszczenie ++ tutaj oszcz?dza 4 bajty	
			UART_ProgBuf.TxBufferTail = 0;										// Przekr?cenie si? bufora pier?cieniowego
		}
	} 
	else {																		// Bufor programowy pusty, koniec transmisji (ale bajty w buforze sprz?towym ca?y czas s? jeszcze wysy?ane!)
		USARTX.CTRLA		=	USART_RXCIE_bm |								// W??czenie przerwa? od DRE...
								USART_TXCIE_bm;									// ...a RX oraz TX ju? wcze?niej by?o w??czone
	}
}


// Ca?kowite opr??nienie bufora sprz?towego i zako?czenie transmisji
ISR(USARTX_TXC_vect) {
	
	// Kasowanie flagi przerwania
	USARTX.STATUS	=	USART_TXCIF_bm;
	
	// Je?eli jest u?ywana blokada u?pienia
	#if UART_USE_UCOSMOS_SLEEP
		OS_SLEEP_ENABLE;														// Zwolnienie blokady u?pienia
	#endif
	
	// Czyszczenie flagi zaj?to?ci transmitera
	USARTX.TXPLCTRL = 0;
}


// ====================
// Odbi?r danych z UART
// ====================


// Funkcja pobieraj?ca jeden znak z wybranego portu
// Po odczytani znak z bufora programowego jest usuwany i automatycznie jest zwalniane miejsce na odbi?r kolejnego znaku
uint8_t Uart_Read(USART_t * Port) {
	
	uint8_t Data;
	if(UART_ProgBuf.RxBufferCnt) {												// Je?eli jest co? w buforze
		
		UART_ProgBuf.RxBufferCnt--;												// Zmniejszenie liczby znak?w w buforze, bo zaraz odczytamy jeden z nich
		
		// Je?eli jest u?ywana blokada u?pienia
		#if UART_USE_UCOSMOS_SLEEP
			if(UART_ProgBuf.RxBufferCnt == 0) {									// Je?eli bufor za chwil? b?dzie pusty
				OS_SLEEP_ENABLE;												// Zwolnienie blokady u?pienia
			}
		#endif
		
		Data = UART_ProgBuf.RxBuffer[UART_ProgBuf.RxBufferTail];				// Odczytanie ogona bufora						
		
		#if UART_CLEAR_BYTE_AFTER_READ											// Tylko w celach debugowych
			UART_ProgBuf.RxBuffer[UART_ProgBuf.RxBufferTail] = 0;				// Czyszczenie bajtu w buforze po jego odczycie
		#endif
		
		if(++UART_ProgBuf.RxBufferTail == UART_RX_BUFFER_LENGTH) {
			UART_ProgBuf.RxBufferTail = 0;										// Inkrementacja ogona i kontrola przepe?nienia, zapis ++ w tej lini oszcz?dza 2B ni? gdyby ++ by?o w kolejnej linii
		}
		
		return Data;
	} 
	else {																		// Je?eli bufor jest pusty
		return 0;
	}
}


// Przerwanie od RXC w celu skopiowanie znaku odebranego przez UART do bufora programowego
ISR(USARTX_RXC_vect) {
	
	// Je?eli jest u?ywana blokada u?pienia
	#if UART_USE_UCOSMOS_SLEEP
		if(UART_ProgBuf.RxBufferCnt == 0) {										// Je?eli bufor wcze?niej by? pusty
			OS_SLEEP_DISABLE;													// Wy??czenie trybu u?pienia do czasu odebrania wszystkich znak?w z bufora
		}
	#endif
	
	if(UART_ProgBuf.RxBufferCnt < UART_RX_BUFFER_LENGTH) {						// Kontrola wolnego miejsca w buforze
		UART_ProgBuf.RxBufferCnt++;
		UART_ProgBuf.RxBuffer[UART_ProgBuf.RxBufferHead] = USARTX.RXDATAL;
		if(++UART_ProgBuf.RxBufferHead == UART_RX_BUFFER_LENGTH) {				// Zapis ++RxBufferHead oszcz?dza pami?? o 2B
			UART_ProgBuf.RxBufferHead = 0;										// Przepe?nienie indeksu head
		}
	} 
	else {																		// Przepe?nienie bufora
		#if UART_BREAK_ON_BUFFER_FULL								
			asm volatile("break");												// Zatrzymanie je?li bufor przepe?niony
		#endif
		void(USARTX.RXDATAL);													// Odczytanie by wyzerowa? flag? przerwania
	}	
}


// Odczyt liczby znak?w gotowych do odczyty z bufora programowego
uint8_t Uart_ReceivedCnt(USART_t * Port) {
	return  UART_ProgBuf.RxBufferCnt;
}


// ==================
// Funkcje pomocnicze
// ==================


// Czyszczenie bufora programowego Rx
void Uart_RxBufferFlush(volatile UART_Buffer_t * ProgBuf) {
	
	cli();
	for(uint8_t i=0; i<UART_RX_BUFFER_LENGTH; i++) {
		UART_ProgBuf.RxBuffer[i] = 0;
	}
	
	UART_ProgBuf.RxBufferHead	=	0;
	UART_ProgBuf.RxBufferTail	=	0;
	UART_ProgBuf.RxBufferCnt	=	0;
	sei();
}


// TODO: Wyci?? to
void Uart_RxBufferFlush(USART_t * Port) {
	Uart_RxBufferFlush(&UART_ProgBuf);
}


// Czyszczenie bufora programowego Tx
void Uart_TxBufferFlush(volatile UART_Buffer_t * ProgBuf) {
	
	cli();
	for(uint8_t i=0; i<UART_TX_BUFFER_LENGTH; i++) {
		UART_ProgBuf.TxBuffer[i] = 0;
	}
	
	UART_ProgBuf.TxBufferHead	=	0;
	UART_ProgBuf.TxBufferTail	=	0;
	UART_ProgBuf.TxBufferCnt	=	0;
	sei();
}


// TODO: Wyci?? to
void Uart_TxBufferFlush(USART_t * Port) {
	Uart_TxBufferFlush(&UART_ProgBuf);
}


// Czekanie a? transmisja dobiegnie ko?ca (przydatne przed wej?ciem w stan u?pienia) - wersja dla wskazanego UART
void Uart_WaitForTxComplete(USART_t * Port) {
	while(USARTX.TXPLCTRL);
}


#endif
