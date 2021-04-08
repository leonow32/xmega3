// Wersja 3.0.0

#if COMPONENT_UART_MULTI

#include "uart_multi.h"

// ========================================
// Prototypes of static functions
// ========================================


static void Uart_InterruptRx(USART_t * Port, volatile UART_Buffer_t * Buffer);
static void Uart_InterruptTx(USART_t * Port);
static void Uart_InterruptDre(USART_t * Port, UART_Buffer_t * Buffer);


// ========================================
// Stuff dedicated for UART0
// ========================================


#if UART0_USE
	
	// Buffer
	UART_Buffer_t UART0_ProgBuf;
	
	// Send data via UART instance
	void Uart0_Write(uint8_t Data) {
		Uart_Write(Data, &USART0);
	}
	
	// Get char from UART instance
	uint8_t Uart0_Read(void) {
		return Uart_Read(&USART0);
	}
	
	// Get count of bytes in software buffer waiting to be read
	uint8_t Uart0_ReceivedCnt(void) {
		return Uart_ReceivedCnt(&USART0);
	};
	
	// Przerwanie UART0 w celu wysy³ania danych - po zwolnieniu 1 bajtu w buforze sprzêtowym
	ISR(USART0_DRE_vect) {
		Uart_InterruptDre(&USART0, &UART0_ProgBuf);
	}
	
	// Interrupt when transmit buffer empty
	ISR(USART0_TXC_vect) {
		Uart_InterruptTx(&USART0);
	}
	
	// Interrupt when a byte received to copy it from hardware buffer to software buffer
	ISR(USART0_RXC_vect) {
		Uart_InterruptRx(&USART0, &UART0_ProgBuf);
	}
	
	// Configure GPIO
	static void Uart0_InitPins(void) {
		
		// Konfiguracja dla ATtinyXX14/16/17/18 - port podstawowy
		#if UART0_PORTB_23 && (HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17)
			PORTMUX.CTRLB	&= ~PORTMUX_USART0_ALTERNATE_gc;
			PORTB.PIN3CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w³¹czony rezystor pull-up
			PORTB.PIN2CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w³¹czony rezystor pull-up
								PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy³¹czony bufor wejœciowy
			VPORTB.OUT		|=	PIN2_bm;											// Pin Tx jako wyjœcie
			VPORTB.DIR		|=	PIN2_bm;											// Pin Tx jako wyjœcie
		
		// Konfiguracja dla ATtinyXX12/14/16/17/18 - port alternatywny
		#elif UART0_PORTA_12 && (HW_CPU_ATtinyXX12 || HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17)
			PORTMUX.CTRLB	|=	PORTMUX_USART0_ALTERNATE_gc;
			PORTA.PIN2CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w³¹czony rezystor pull-up
			PORTA.PIN1CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w³¹czony rezystor pull-up
								PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy³¹czony bufor wejœciowy
			VPORTA.OUT		|=	PIN1_bm;											// Pin Tx jako wyjœcie
			VPORTA.DIR		|=	PIN1_bm;											// Pin Tx jako wyjœcie
		
		// Konfiguracja dla ATtinyXX24/26/27 - port podstawowy
		#elif UART0_PORTB_23 && (HW_CPU_ATtinyXX24 || HW_CPU_ATtinyXX26 || HW_CPU_ATtinyXX27)
			PORTMUX.USARTROUTEA	|=	PORTMUX_USART0_DEFAULT_gc;
			PORTB.PIN3CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w³¹czony rezystor pull-up
			PORTB.PIN2CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w³¹czony rezystor pull-up
								PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy³¹czony bufor wejœciowy
			VPORTB.OUT		|=	PIN2_bm;											// Pin Tx jako wyjœcie
			VPORTB.DIR		|=	PIN2_bm;											// Pin Tx jako wyjœcie
		
		// Konfiguracja dla ATtinyXX24/26/27 - port alternatywny
		#elif UART0_PORTA_12 && (HW_CPU_ATtinyXX24 || HW_CPU_ATtinyXX26 || HW_CPU_ATtinyXX27)
			PORTMUX.USARTROUTEA	|=	PORTMUX_USART0_ALT1_gc;
			PORTA.PIN2CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w³¹czony rezystor pull-up
			PORTA.PIN1CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w³¹czony rezystor pull-up
								PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy³¹czony bufor wejœciowy
			VPORTA.OUT		|=	PIN1_bm;											// Pin Tx jako wyjœcie
			VPORTA.DIR		|=	PIN1_bm;											// Pin Tx jako wyjœcie
		
		// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
		#elif UART0_PORTA_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
			PORTMUX.USARTROUTEA		&= ~PORTMUX_USART0_gm;
			PORTA.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
			PORTA.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
			VPORTA.OUT				|=	PIN0_bm;									// Pin Tx jako wyjœcie
			VPORTA.DIR				|=	PIN0_bm;									// Pin Tx jako wyjœcie
		
		// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
		#elif UART0_PORTA_45 && (HW_CPU_ATmegaXX09)
			PORTMUX.USARTROUTEA		|=	PORTMUX_USART0_ALT1_gc;
			PORTA.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
			PORTA.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
			VPORTA.OUT				|=	PIN4_bm;									// Pin Tx jako wyjœcie
			VPORTA.DIR				|=	PIN4_bm;									// Pin Tx jako wyjœcie
		
		#else
			#error "Missing config for UART"
		#endif
	}
	
#endif

// ========================================
// Stuff dedicated for UART1
// ========================================

#if UART1_USE
	
	// Buffer
	UART_Buffer_t UART1_ProgBuf;
	
	// Send data via UART instance
	void Uart1_Write(uint8_t Data) {
		Uart_Write(Data, &USART1);
	}
	
	// Get char from UART instance
	uint8_t Uart1_Read(void) {
		return Uart_Read(&USART1);
	}
	
	// Get count of bytes in software buffer waiting to be read
	uint8_t Uart1_ReceivedCnt(void) {
		return Uart_ReceivedCnt(&USART1);
	};
	
	// Przerwanie UART1 w celu wysy³ania danych - po zwolnieniu 1 bajtu w buforze sprzêtowym
	ISR(USART1_DRE_vect) {
		Uart_InterruptDre(&USART1, &UART1_ProgBuf);
	}
	
	// Interrupt when transmit buffer empty
	ISR(USART1_TXC_vect) {
		Uart_InterruptTx(&USART1);
	}
	
	// Interrupt when a byte received to copy it from hardware buffer to software buffer
	ISR(USART1_RXC_vect) {
		Uart_InterruptRx(&USART1, &UART1_ProgBuf);
	}
	
	// Configure GPIO
	static void Uart1__InitPins(void) {
		// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
		#if UART1_PORTC_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
			PORTMUX.USARTROUTEA		&= ~PORTMUX_USART1_gm;
			PORTC.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
			PORTC.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
			VPORTC.OUT				|=	PIN0_bm;									// Pin Tx jako wyjœcie
			VPORTC.DIR				|=	PIN0_bm;									// Pin Tx jako wyjœcie
		
		// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
		#elif UART1_PORTC_45 && (HW_CPU_ATmegaXX09)
			PORTMUX.USARTROUTEA		|=	PORTMUX_USART1_ALT1_gc;
			PORTC.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
			PORTC.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
			VPORTC.OUT				|=	PIN4_bm;									// Pin Tx jako wyjœcie
			VPORTC.DIR				|=	PIN4_bm;									// Pin Tx jako wyjœcie
		
		// Konfiguracja dla ATtinyXX24/26/27 - port podstawowy
		#elif UART1_PORTA_12 && (HW_CPU_ATtinyXX24 || HW_CPU_ATtinyXX26 || HW_CPU_ATtinyXX27)
			PORTMUX.USARTROUTEA	|=	PORTMUX_USART1_DEFAULT_gc;
			PORTA.PIN2CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w³¹czony rezystor pull-up
			PORTA.PIN1CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w³¹czony rezystor pull-up
								PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy³¹czony bufor wejœciowy
			VPORTA.OUT		|=	PIN1_bm;											// Pin Tx jako wyjœcie
			VPORTA.DIR		|=	PIN1_bm;											// Pin Tx jako wyjœcie
		
		// Konfiguracja dla ATtinyXX24/26/27 - port alternatywny
		#elif UART1_PORTC_21 && (HW_CPU_ATtinyXX24 || HW_CPU_ATtinyXX26 || HW_CPU_ATtinyXX27)
			PORTMUX.USARTROUTEA	|=	PORTMUX_USART1_ALT1_gc;
			PORTC.PIN1CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w³¹czony rezystor pull-up
			PORTC.PIN2CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w³¹czony rezystor pull-up
								PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy³¹czony bufor wejœciowy
			VPORTC.OUT		|=	PIN2_bm;											// Pin Tx jako wyjœcie
			VPORTC.DIR		|=	PIN2_bm;											// Pin Tx jako wyjœcie
		
		#else
			#error "Missing config for UART"
		#endif
	}
#endif

// ========================================
// Stuff dedicated for UART2
// ========================================

#if UART2_USE
	
	// Buffer
	UART_Buffer_t UART2_ProgBuf;
	
	// Send data via UART instance
	void Uart2_Write(uint8_t Data) {
		Uart_Write(Data, &USART2);
	}
	
	// Get char from UART instance
	uint8_t Uart2_Read(void) {
		return Uart_Read(&USART2);
	}
	
	// Get count of bytes in software buffer waiting to be read
	uint8_t Uart2_ReceivedCnt(void) {
		return Uart_ReceivedCnt(&USART2);
	};
	
	// Przerwanie UART2 w celu wysy³ania danych - po zwolnieniu 1 bajtu w buforze sprzêtowym
	ISR(USART2_DRE_vect) {
		Uart_InterruptDre(&USART2, &UART2_ProgBuf);
	}
	
	// Interrupt when transmit buffer empty
	ISR(USART2_TXC_vect) {
		Uart_InterruptTx(&USART2);
	}
	
	// Interrupt when a byte received to copy it from hardware buffer to software buffer
	ISR(USART2_RXC_vect) {
		Uart_InterruptRx(&USART2, &UART2_ProgBuf);
	}
	
	// Configure GPIO
	static void Uart2_InitPins(void) {
		
		// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
		#if UART2_PORTF_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
			PORTMUX.USARTROUTEA		&= ~PORTMUX_USART2_gm;
			PORTF.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
			PORTF.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
			VPORTF.OUT				|=	PIN0_bm;									// Pin Tx jako wyjœcie
			VPORTF.DIR				|=	PIN0_bm;									// Pin Tx jako wyjœcie
		
		// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
		#elif UART2_PORTF_45 && (HW_CPU_ATmegaXX09)
			PORTMUX.USARTROUTEA		|=	PORTMUX_USART2_ALT1_gc;
			PORTF.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
			PORTF.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
			VPORTF.OUT				|=	PIN4_bm;									// Pin Tx jako wyjœcie
			VPORTF.DIR				|=	PIN4_bm;									// Pin Tx jako wyjœcie
		
		#else
			#error "Missing config for UART"
		#endif
	}
	
#endif

// ========================================
// Stuff dedicated for UART3
// ========================================
	
#if UART3_USE
	
	// Buffer
	UART_Buffer_t UART3_ProgBuf;
	
	// Send data via UART instance
	void Uart3_Write(uint8_t Data) {
		Uart_Write(Data, &USART3);
	}
	
	// Get char from UART instance
	uint8_t Uart3_Read(void) {
		return Uart_Read(&USART3);
	}
	
	// Get count of bytes in software buffer waiting to be read
	uint8_t Uart3_ReceivedCnt(void) {
		return Uart_ReceivedCnt(&USART3);
	};
	
	// Przerwanie UART3 w celu wysy³ania danych - po zwolnieniu 1 bajtu w buforze sprzêtowym
	ISR(USART3_DRE_vect) {
		Uart_InterruptDre(&USART3, &UART3_ProgBuf);
	}
	
	// Interrupt when transmit buffer empty
	ISR(USART3_TXC_vect) {
		Uart_InterruptTx(&USART3);
	}
	
	// Interrupt when a byte received to copy it from hardware buffer to software buffer
	ISR(USART3_RXC_vect) {
		Uart_InterruptRx(&USART3, &UART3_ProgBuf);
	}
	
	// Configure GPIO
	static void Uart3_InitPins(void) {
		
		// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
		#if UART3_PORTB_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
			PORTMUX.USARTROUTEA		&= ~PORTMUX_USART3_gm;
			PORTB.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
			PORTB.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
			VPORTB.OUT				|=	PIN0_bm;									// Pin Tx jako wyjœcie
			VPORTB.DIR				|=	PIN0_bm;									// Pin Tx jako wyjœcie
		
		// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
		#elif UART3_PORTB_45 && (HW_CPU_ATmegaXX09)
			PORTMUX.USARTROUTEA		|=	PORTMUX_USART3_ALT1_gc;
			PORTB.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w³¹czony rezystor pull-up
			PORTB.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w³¹czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy³¹czony bufor wejœciowy
			VPORTB.OUT				|=	PIN4_bm;									// Pin Tx jako wyjœcie
			VPORTB.DIR				|=	PIN4_bm;									// Pin Tx jako wyjœcie
		
		#else
			#error "Missing config for UART"
		#endif
	}
#endif


// ========================================
// Funkcje pomocnicze
// ========================================


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
	
	//return &UART2_ProgBuf;
	// TODO: Posprz¹taæ to
// 	#if B_MIFARE_v002 || B_LOCK_v001 || BOARD_XNANO
// 		return &UART0_ProgBuf;
// 	#else
// 		return &UART2_ProgBuf;
// 	#endif
	//while(1);
	asm volatile("break");
	return NULL;
}


// Inicjalizacja sprzêtowego peryferium wskazanego wskaŸnikiem (u¿ywane tylko przez Uart_Init();
// - Port		-	WskaŸnik do portu
// - Baud		-	Baudrate ju¿ po przeliczeniu, ta wartoœæ jest wpisywana wprost do jesteru USARTx.BAUD
static void Uart__InitUsartPeripheral(USART_t * Port, UART_Buffer_t * Buffer, uint16_t Baud) {
	
	Port->BAUD			=	Baud;												// Baud rate
	
	Port->CTRLA			=	USART_RXCIE_bm |									// Receive Complete Interrupt Enable
							USART_TXCIE_bm |									// Transmit Complete Interrupt Enable
						//	USART_DREIE_bm |									// Data Register Empty Interrupt Enable
						//	USART_RXSIE_bm |									// Receiver Start Frame Interrupt Enable
						//	USART_LBME_bm |										// Loop-back Mode Enable
						//	USART_ABEIE_bm |									// Auto-baud Error Interrupt Enable
							0;
	
	Port->CTRLB			=	USART_RXEN_bm |										// Receiver Enable
							USART_TXEN_bm |										// Transmitter Enable
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


// Inicjalizacja zgodnie z konfiguracj¹ w pliku config
void Uart_Init() {
		
	// Konfiguracja UART0
	#if UART0_USE
		Uart0_InitPins();
		Uart__InitUsartPeripheral(&USART0, &UART0_ProgBuf, uint16_t((F_CPU * 4) / (UART0_BAUD)));
	#endif
	
	// Konfiguracja UART1
	#if UART1_USE
		Uart1__InitPins();
		Uart__InitUsartPeripheral(&USART1, &UART1_ProgBuf, uint16_t((F_CPU * 4) / (UART1_BAUD)));
	#endif
	
	// Konfiguracja UART2
	#if UART2_USE
		Uart2_InitPins();
		Uart__InitUsartPeripheral(&USART2, &UART2_ProgBuf, uint16_t((F_CPU * 4) / (UART2_BAUD)));
	#endif
	
	// Konfiguracja UART3
	#if UART3_USE
		Uart3_InitPins();
		Uart__InitUsartPeripheral(&USART3, &UART3_ProgBuf, uint16_t((F_CPU * 4) / (UART3_BAUD)));
	#endif
}


// ====================
// Wysy³anie przez UART
// ====================


// Wysy³anie 1 bajtu danych
void Uart_Write(uint8_t Data, USART_t * Port) {
	
	// Ustawienie flagi zajêtoœci transmitera
	Port->TXPLCTRL = UART_TX_BUSY;
	
	// WskaŸnik do bufora pierœcieniowego
	volatile UART_Buffer_t * Buffer = Uart__GetProgBuffer(Port);
	
	// Procedura zapisu danych do bufora sprzêtowego lub programowego
	Port->STATUS		=	USART_TXCIF_bm;									// Kasowanie flagi koñca nadawania
	
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
}


// Funkcja obs³uguj¹ca przerwania od zwolnienia siê miejsca w buforze
static void Uart_InterruptDre(USART_t * Port, UART_Buffer_t * Buffer) {
	
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


// Funkcja obs³uguj¹ca przerwanie od zakoñczenia transmisji
static void Uart_InterruptTx(USART_t * Port) {
	
	// Kasowanie flagi przerwania
	Port->STATUS	=	USART_TXCIF_bm;
	
	// Wy³¹czenie transmitera
	//Port->CTRLB		&= ~USART_TXEN_bm;
	
	// Je¿eli jest u¿ywana blokada uœpienia
	#if UART_USE_UCOSMOS_SLEEP
		OS_SLEEP_ENABLE;														// Zwolnienie blokady uœpienia
	#endif
	
	// Czyszczenie flagi zajêtoœci transmitera
	Port->TXPLCTRL = 0;
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
static void Uart_InterruptRx(USART_t * Port, volatile UART_Buffer_t * Buffer) {
	
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


// Odczyt liczby znaków gotowych do odczyty z bufora programowego
uint8_t Uart_ReceivedCnt(USART_t * Port) {
	return  Uart__GetProgBuffer(Port)->RxBufferCnt;
}


// ========================================
// Funkcje pomocnicze
// ========================================


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
	sei();
}


// Czyszczenie bufora programowego Rx - wersja z podawaniem nazwy portu przez argument
void Uart_TxBufferFlush(USART_t * Port) {
	Uart_WaitForTxComplete(Port);
	Uart_TxBufferFlush(Uart__GetProgBuffer(Port));
}


// Czekanie a¿ transmisja dobiegnie koñca (przydatne przed wejœciem w stan uœpienia) - wersja dla wskazanego UART
void Uart_WaitForTxComplete(USART_t * Port) {
	while(Port->TXPLCTRL);
}


// Czekanie a¿ tranmisja dobiegnie koñca - wersja dla wszystkich u¿ywanych UARTów
void Uart_WaitForTxComplete(void) {
	
	#if UART0_USE
		Uart_WaitForTxComplete(&USART0);
	#endif
	
	#if UART1_USE
		Uart_WaitForTxComplete(&USART1);
	#endif
	
	#if UART2_USE
		Uart_WaitForTxComplete(&USART2);
	#endif
	
	#if UART3_USE
		Uart_WaitForTxComplete(&USART3);
	#endif
}

#endif
