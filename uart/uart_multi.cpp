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
	
	// Przerwanie UART0 w celu wysy�ania danych - po zwolnieniu 1 bajtu w buforze sprz�towym
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
			PORTB.PIN3CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w��czony rezystor pull-up
			PORTB.PIN2CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w��czony rezystor pull-up
								PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy��czony bufor wej�ciowy
			VPORTB.OUT		|=	PIN2_bm;											// Pin Tx jako wyj�cie
			VPORTB.DIR		|=	PIN2_bm;											// Pin Tx jako wyj�cie
		
		// Konfiguracja dla ATtinyXX12/14/16/17/18 - port alternatywny
		#elif UART0_PORTA_12 && (HW_CPU_ATtinyXX12 || HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17)
			PORTMUX.CTRLB	|=	PORTMUX_USART0_ALTERNATE_gc;
			PORTA.PIN2CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w��czony rezystor pull-up
			PORTA.PIN1CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w��czony rezystor pull-up
								PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy��czony bufor wej�ciowy
			VPORTA.OUT		|=	PIN1_bm;											// Pin Tx jako wyj�cie
			VPORTA.DIR		|=	PIN1_bm;											// Pin Tx jako wyj�cie
		
		// Konfiguracja dla ATtinyXX24/26/27 - port podstawowy
		#elif UART0_PORTB_23 && (HW_CPU_ATtinyXX24 || HW_CPU_ATtinyXX26 || HW_CPU_ATtinyXX27)
			PORTMUX.USARTROUTEA	|=	PORTMUX_USART0_DEFAULT_gc;
			PORTB.PIN3CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w��czony rezystor pull-up
			PORTB.PIN2CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w��czony rezystor pull-up
								PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy��czony bufor wej�ciowy
			VPORTB.OUT		|=	PIN2_bm;											// Pin Tx jako wyj�cie
			VPORTB.DIR		|=	PIN2_bm;											// Pin Tx jako wyj�cie
		
		// Konfiguracja dla ATtinyXX24/26/27 - port alternatywny
		#elif UART0_PORTA_12 && (HW_CPU_ATtinyXX24 || HW_CPU_ATtinyXX26 || HW_CPU_ATtinyXX27)
			PORTMUX.USARTROUTEA	|=	PORTMUX_USART0_ALT1_gc;
			PORTA.PIN2CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w��czony rezystor pull-up
			PORTA.PIN1CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w��czony rezystor pull-up
								PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy��czony bufor wej�ciowy
			VPORTA.OUT		|=	PIN1_bm;											// Pin Tx jako wyj�cie
			VPORTA.DIR		|=	PIN1_bm;											// Pin Tx jako wyj�cie
		
		// Konfiguracja dla ATmegaXX08/XX09 - port podstawowy
		#elif UART0_PORTA_01 && (HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09)
			PORTMUX.USARTROUTEA		&= ~PORTMUX_USART0_gm;
			PORTA.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
			PORTA.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
			VPORTA.OUT				|=	PIN0_bm;									// Pin Tx jako wyj�cie
			VPORTA.DIR				|=	PIN0_bm;									// Pin Tx jako wyj�cie
		
		// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
		#elif UART0_PORTA_45 && (HW_CPU_ATmegaXX09)
			PORTMUX.USARTROUTEA		|=	PORTMUX_USART0_ALT1_gc;
			PORTA.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
			PORTA.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
			VPORTA.OUT				|=	PIN4_bm;									// Pin Tx jako wyj�cie
			VPORTA.DIR				|=	PIN4_bm;									// Pin Tx jako wyj�cie
		
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
	
	// Przerwanie UART1 w celu wysy�ania danych - po zwolnieniu 1 bajtu w buforze sprz�towym
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
			PORTC.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
			PORTC.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
			VPORTC.OUT				|=	PIN0_bm;									// Pin Tx jako wyj�cie
			VPORTC.DIR				|=	PIN0_bm;									// Pin Tx jako wyj�cie
		
		// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
		#elif UART1_PORTC_45 && (HW_CPU_ATmegaXX09)
			PORTMUX.USARTROUTEA		|=	PORTMUX_USART1_ALT1_gc;
			PORTC.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
			PORTC.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
			VPORTC.OUT				|=	PIN4_bm;									// Pin Tx jako wyj�cie
			VPORTC.DIR				|=	PIN4_bm;									// Pin Tx jako wyj�cie
		
		// Konfiguracja dla ATtinyXX24/26/27 - port podstawowy
		#elif UART1_PORTA_12 && (HW_CPU_ATtinyXX24 || HW_CPU_ATtinyXX26 || HW_CPU_ATtinyXX27)
			PORTMUX.USARTROUTEA	|=	PORTMUX_USART1_DEFAULT_gc;
			PORTA.PIN2CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w��czony rezystor pull-up
			PORTA.PIN1CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w��czony rezystor pull-up
								PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy��czony bufor wej�ciowy
			VPORTA.OUT		|=	PIN1_bm;											// Pin Tx jako wyj�cie
			VPORTA.DIR		|=	PIN1_bm;											// Pin Tx jako wyj�cie
		
		// Konfiguracja dla ATtinyXX24/26/27 - port alternatywny
		#elif UART1_PORTC_21 && (HW_CPU_ATtinyXX24 || HW_CPU_ATtinyXX26 || HW_CPU_ATtinyXX27)
			PORTMUX.USARTROUTEA	|=	PORTMUX_USART1_ALT1_gc;
			PORTC.PIN1CTRL	 =	PORT_PULLUPEN_bm;									// Pin Rx ma w��czony rezystor pull-up
			PORTC.PIN2CTRL	 =	PORT_PULLUPEN_bm |									// Pin Tx ma w��czony rezystor pull-up
								PORT_ISC_INPUT_DISABLE_gc;							// Pin Tx ma wy��czony bufor wej�ciowy
			VPORTC.OUT		|=	PIN2_bm;											// Pin Tx jako wyj�cie
			VPORTC.DIR		|=	PIN2_bm;											// Pin Tx jako wyj�cie
		
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
	
	// Przerwanie UART2 w celu wysy�ania danych - po zwolnieniu 1 bajtu w buforze sprz�towym
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
			PORTF.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
			PORTF.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
			VPORTF.OUT				|=	PIN0_bm;									// Pin Tx jako wyj�cie
			VPORTF.DIR				|=	PIN0_bm;									// Pin Tx jako wyj�cie
		
		// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
		#elif UART2_PORTF_45 && (HW_CPU_ATmegaXX09)
			PORTMUX.USARTROUTEA		|=	PORTMUX_USART2_ALT1_gc;
			PORTF.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
			PORTF.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
			VPORTF.OUT				|=	PIN4_bm;									// Pin Tx jako wyj�cie
			VPORTF.DIR				|=	PIN4_bm;									// Pin Tx jako wyj�cie
		
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
	
	// Przerwanie UART3 w celu wysy�ania danych - po zwolnieniu 1 bajtu w buforze sprz�towym
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
			PORTB.PIN1CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
			PORTB.PIN0CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
			VPORTB.OUT				|=	PIN0_bm;									// Pin Tx jako wyj�cie
			VPORTB.DIR				|=	PIN0_bm;									// Pin Tx jako wyj�cie
		
		// Konfiguracja dla ATmegaXX08/XX09 - port alternatywny
		#elif UART3_PORTB_45 && (HW_CPU_ATmegaXX09)
			PORTMUX.USARTROUTEA		|=	PORTMUX_USART3_ALT1_gc;
			PORTB.PIN5CTRL			 =	PORT_PULLUPEN_bm;							// Pin Rx ma w��czony rezystor pull-up
			PORTB.PIN4CTRL			 =	PORT_PULLUPEN_bm |							// Pin Tx ma w��czony rezystor pull-up
										PORT_ISC_INPUT_DISABLE_gc;					// Pin Tx ma wy��czony bufor wej�ciowy
			VPORTB.OUT				|=	PIN4_bm;									// Pin Tx jako wyj�cie
			VPORTB.DIR				|=	PIN4_bm;									// Pin Tx jako wyj�cie
		
		#else
			#error "Missing config for UART"
		#endif
	}
#endif


// ========================================
// Funkcje pomocnicze
// ========================================


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
	
	//return &UART2_ProgBuf;
	// TODO: Posprz�ta� to
// 	#if B_MIFARE_v002 || B_LOCK_v001 || BOARD_XNANO
// 		return &UART0_ProgBuf;
// 	#else
// 		return &UART2_ProgBuf;
// 	#endif
	//while(1);
	asm volatile("break");
	return NULL;
}


// Inicjalizacja sprz�towego peryferium wskazanego wska�nikiem (u�ywane tylko przez Uart_Init();
// - Port		-	Wska�nik do portu
// - Baud		-	Baudrate ju� po przeliczeniu, ta warto�� jest wpisywana wprost do jesteru USARTx.BAUD
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
		Port->DBGCTRL	=	USART_DBGRUN_bm;									// Ma dzia�a� podczas breakpoint�w
	#endif	
	
	// Czyszczenie bufora
	memset(Buffer, 0, sizeof(UART_Buffer_t));
}


// Inicjalizacja zgodnie z konfiguracj� w pliku config
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
// Wysy�anie przez UART
// ====================


// Wysy�anie 1 bajtu danych
void Uart_Write(uint8_t Data, USART_t * Port) {
	
	// Ustawienie flagi zaj�to�ci transmitera
	Port->TXPLCTRL = UART_TX_BUSY;
	
	// Wska�nik do bufora pier�cieniowego
	volatile UART_Buffer_t * Buffer = Uart__GetProgBuffer(Port);
	
	// Procedura zapisu danych do bufora sprz�towego lub programowego
	Port->STATUS		=	USART_TXCIF_bm;									// Kasowanie flagi ko�ca nadawania
	
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
}


// Funkcja obs�uguj�ca przerwania od zwolnienia si� miejsca w buforze
static void Uart_InterruptDre(USART_t * Port, UART_Buffer_t * Buffer) {
	
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


// Funkcja obs�uguj�ca przerwanie od zako�czenia transmisji
static void Uart_InterruptTx(USART_t * Port) {
	
	// Kasowanie flagi przerwania
	Port->STATUS	=	USART_TXCIF_bm;
	
	// Wy��czenie transmitera
	//Port->CTRLB		&= ~USART_TXEN_bm;
	
	// Je�eli jest u�ywana blokada u�pienia
	#if UART_USE_UCOSMOS_SLEEP
		OS_SLEEP_ENABLE;														// Zwolnienie blokady u�pienia
	#endif
	
	// Czyszczenie flagi zaj�to�ci transmitera
	Port->TXPLCTRL = 0;
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
static void Uart_InterruptRx(USART_t * Port, volatile UART_Buffer_t * Buffer) {
	
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


// Odczyt liczby znak�w gotowych do odczyty z bufora programowego
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


// Czekanie a� transmisja dobiegnie ko�ca (przydatne przed wej�ciem w stan u�pienia) - wersja dla wskazanego UART
void Uart_WaitForTxComplete(USART_t * Port) {
	while(Port->TXPLCTRL);
}


// Czekanie a� tranmisja dobiegnie ko�ca - wersja dla wszystkich u�ywanych UART�w
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
