// Wersja 2.17

#if C_UART_SINGLE

#include "uart_single.h"

// Bufor programowy
volatile UART_Buffer_t UART_ProgBuf;

// TODO: Wyci¹æ to
USART_t * UART_PortOverride = NULL;


// Inicjalizacja zgodnie z konfiguracj¹ w pliku configS
void Uart_Init(void) {
	
	// DEBUG
	PIN_A_INIT;
	PIN_B_INIT;
	
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
	
	USARTX.BAUD					=	uint16_t((F_CPU * 4) / UART_BAUD);			// Baud rate
	
	USARTX.CTRLA				=	USART_RXCIE_bm |							// Receive Complete Interrupt Enable
									USART_TXCIE_bm |							// Transmit Complete Interrupt Enable
								  //USART_DREIE_bm |							// Data Register Empty Interrupt Enable
								  //USART_RXSIE_bm |							// Receiver Start Frame Interrupt Enable
								  //USART_LBME_bm |								// Loop-back Mode Enable
								  //USART_ABEIE_bm |							// Auto-baud Error Interrupt Enable
									USART_RS485_OFF_gc;							// RS485 Mode

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
		USARTX.DBGCTRL			=	USART_DBGRUN_bm;							// Ma dzia³aæ podczas breakpointów
	#endif	
	
	// Czyszczenie bufora
	//memset(UART_ProgBuf, 0, sizeof(UART_ProgBuf));
	
	CPUINT.LVL1VEC				=	UART_CONSOLE_INT;							// Jeœli wrzucamy coœ do bufora UART w przerwaniu, 
																				// to przerwanie opró¿nienia bufora musi mieæ wiêkszy priortet, 
																				// bo inaczej w przypadku przepe³nienia bufora procesor siê zawiesi
}


// ====================
// Wysy³anie przez UART
// ====================


// Wysy³anie 1 bajtu danych
void Uart_Write(uint8_t Data, USART_t * Port) {
	
	// Ustawienie flagi zajêtoœci transmitera
	UART_ProgBuf.Status |= UART_TX_BUSY;
	
	// Procedura zapisu danych do bufora sprzêtowego lub programowego
	USARTX.STATUS		=	USART_TXCIF_bm;										// Kasowanie flagi koñca nadawania
	
	while(UART_ProgBuf.TxBufferCnt == UART_TX_BUFFER_LENGTH) {					// Sprawdzenie czy bufor programowy pusty lub czekanie a¿ bêdzie wolne miejsce
		#if UART_BREAK_ON_BUFFER_FULL
			asm volatile("break");												// Zatrzymanie jeœli bufor przepe³niony
		#endif
	}
		
	cli();																		// Wy³¹czenie przerwañ, aby nie dopuœciæ do sytuacji, kiedy TxBuffer by³by jednoczeœnie modyfikowany w przerwaniu
	UART_ProgBuf.TxBufferCnt++;													// Zwiêkszenie licznika znaków w buforze nadawczym
	UART_ProgBuf.TxBuffer[UART_ProgBuf.TxBufferHead] = Data;					// Wpisanie znaku do bufora na pocz¹tek kolejki FIFO
		
	if(++UART_ProgBuf.TxBufferHead == UART_TX_BUFFER_LENGTH) {					// Zapis ++TxBufferHead oszczêdza pamiêæ o 4B
		UART_ProgBuf.TxBufferHead = 0;											// Przekreœcenie siê bufora pierœcieniowego
	}
		
	USARTX.CTRLA	=	USART_DREIE_bm |										// W³¹czenie przerwañ od DRE...
						USART_RXCIE_bm |										// ...a RX...
						USART_TXCIE_bm;											// ...oraz TX ju¿ wczeœniej by³o w³¹czone
	sei();																		// Glabalne w³¹czenie przerwañ
}


// Przerwanie UART0 w celu wysy³ania danych - po zwolnieniu 1 bajtu w buforze sprzêtowym
ISR(USARTX_DRE_vect) {
	if(UART_ProgBuf.TxBufferCnt) {												// Je¿eli w buforze programowym jest coœ do wys³ania
		
		USARTX.STATUS	=	USART_TXCIF_bm;										// Kasowanie flagi koñca nadawania
		UART_ProgBuf.TxBufferCnt--;												// Zmniejszenie liczby znaków w buforze nadawczym
		USARTX.TXDATAL = UART_ProgBuf.TxBuffer[UART_ProgBuf.TxBufferTail];		// Wysy³anie znaku z koñca kolejki FIFO
		
		#if UART_CLEAR_BYTE_AFTER_READ											// W celach debugowych
			UART_ProgBuf.TxBuffer[UART_ProgBuf.TxBufferTail] = 0;				// Czyszczenie znaku w buforze programowym, który zosta³ skopiowany do bufora sprzêtowego
		#endif
		
		if(++UART_ProgBuf.TxBufferTail == UART_TX_BUFFER_LENGTH) {				// Umieszczenie ++ tutaj oszczêdza 4 bajty	
			UART_ProgBuf.TxBufferTail = 0;										// Przekrêcenie siê bufora pierœcieniowego
		}
	} 
	else {																		// Bufor programowy pusty, koniec transmisji (ale bajty w buforze sprzêtowym ca³y czas s¹ jeszcze wysy³ane!)
		USARTX.CTRLA		=	USART_RXCIE_bm |								// W³¹czenie przerwañ od DRE...
							USART_TXCIE_bm;										// ...a RX oraz TX ju¿ wczeœniej by³o w³¹czone
	}
}


// Ca³kowite opró¿nienie bufora sprzêtowego i zakoñczenie transmisji
ISR(USARTX_TXC_vect) {
	
	// Kasowanie flagi przerwania
	USARTX.STATUS	=	USART_TXCIF_bm;
	
	// Je¿eli jest u¿ywana blokada uœpienia
	#if UART_USE_UCOSMOS_SLEEP
		OS_SLEEP_ENABLE;														// Zwolnienie blokady uœpienia
	#endif
	
	// Czyszczenie flagi zajêtoœci transmitera
	UART_ProgBuf.Status &= ~UART_TX_BUSY;
}


// ================================================
// Funkcje wy¿szego poziomu do wysy³ania przez UART
// ================================================


// Zapis ci¹gu znaków
void Uart_Write(const char * Text, USART_t * Port) {
	while(*Text) Uart_Write(*Text++);
}


// Nowa linia
void Uart_WriteNL(USART_t * Port) {
	Uart_Write("\r\n");
}


// Liczba dziesiêtna bez znaku
void Uart_WriteDec(uint32_t Value, USART_t * Port) {
	if(Value==0) {
		Uart_Write('0');
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
		Uart_Write(cyfra[i]+48);
	}
}

// Liczba dziesiêtna ze znakiem
void Uart_WriteDecSigned(int8_t Value, USART_t * Port) {
	if(Value < 0) {
		Uart_Write('-');
		Value = -Value;
	}
	Uart_WriteDec(uint8_t(Value));
}

// Liczba dziesiêtna ze znakiem
void Uart_WriteDecSigned(int32_t Value, USART_t * Port) {
	if(Value < 0) {
		Uart_Write('-');
		Value = -Value;
	}
	Uart_WriteDec(uint32_t(Value));
}


// Zapis liczny binarnej
void Uart_WriteBin(uint8_t Data, const uint8_t Separator, USART_t * Port) {
	for(uint8_t BitMask = 0b10000000; BitMask; BitMask = BitMask >> 1) {
		Uart_Write(Data & BitMask ? '1' : '0');
	}
	if(Separator) Uart_Write(Separator);
}


void Uart__WriteNibble(uint8_t Nibble) {
	if(Nibble <= 9) Uart_Write(Nibble + '0');
	else Uart_Write(Nibble + 55);
}

// Liczba HEX 8-bitowa
void Uart_WriteHex(const uint8_t Data, const uint8_t Separator, USART_t * Port) {
	Uart__WriteNibble((Data & 0xF0) >> 4);
	Uart__WriteNibble((Data & 0x0F) >> 0);
	if(Separator) Uart_Write(Separator); 
}


// Liczba HEX 16-bitowa
void Uart_WriteHex(const uint16_t Data, const uint8_t Separator, USART_t * Port) {
	Uart_WriteHex(uint8_t((Data & 0xFF00) >> 8), 0);
	Uart_WriteHex(uint8_t((Data & 0x00FF)     ), Separator);
}


// Liczba HEX 32-bitowa
void Uart_WriteHex(const uint32_t Data, const uint8_t Separator, USART_t * Port) {
	Uart_WriteHex(uint8_t((Data & 0xFF000000) >> 24), 0);
	Uart_WriteHex(uint8_t((Data & 0x00FF0000) >> 16), 0);
	Uart_WriteHex(uint8_t((Data & 0x0000FF00) >> 8 ), 0);
	Uart_WriteHex(uint8_t((Data & 0x000000FF)      ), Separator);
}


// Ci¹g znaków prezentowany jako HEX
void Uart_WriteHexString(const uint8_t * String, const uint16_t Length, const uint8_t Separator, const uint8_t BytesInRow, USART_t * Port) {
	
	for(uint16_t i=0; i<Length; i++) {
		
		// Przejœcie do nowej linii (nie dotyczny pierwszego wyœwietlanego znaku)
		if((i%BytesInRow == 0) && i != 0) {
			Uart_WriteNL();
		}
		
		// Wyœwietlenie znaku
		Uart_WriteHex(*(String+i), Separator);
	}
}


// Ci¹g znaków prezentowany jako HEX, wraz z nag³ówkiem i adresowaniem
void Uart_Dump(const uint8_t * String, uint16_t Length, uint16_t AddressStartValue, USART_t * Port) {
	
	uint8_t * wskaznik		= (uint8_t *)String;
	uint16_t LengthForHex	= Length;
	uint16_t LengthForAscii	= Length;
	uint16_t i = 0;
	
	Uart_Write("       0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F");
	
	// Wyœwietlanie w pêtli po 16 znaków na ka¿d¹ liniê
	do {
		
		// Zejœcie do nowej linii
		Uart_WriteNL();
		
		// Wyœwietlenie adresu
		Uart_WriteHex(uint16_t(i + AddressStartValue), ':');
		Uart_Write(' ');
		
		// Wyœwietlenie HEX
		for(uint8_t h=0; h<=15; h++) {
			
			// Sprawdzanie czy nie zosta³y wyœwietlone ju¿ wszystkie znaki
			if(LengthForHex) {
				LengthForHex--;
				Uart_WriteHex(*(wskaznik+h), ' ');
			}
			else {
				// Wyœwietlanie trzech spacji, aby potem mo¿na by³o wyœwietliæ ASCII we w³aœciwym miejscu
				Uart_Write("   ");
			}
		}
		
		// Wyœwietlenie ASCII
		for(uint8_t h=0; h<=15; h++) {
			if((*(wskaznik+h) >= ' ') && (*(wskaznik+h) < 127)) {				// Omijanie znaków specjanych <32 i <127
				Uart_Write(*(wskaznik+h));
			} 
			else {
				Uart_Write(' ');
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
	} while(i <= Length-1 && i != 0);											// i != 0 zabezpiecza przed przekrêceniem sie licznika po 0xFFFF
}


// Ponowne wys³anie ca³ej zawartoœci bufora TX
// Aby ta operacja dzia³a³a prawid³owo, wczeœniej nale¿y wywo³aæ Uart_TxBufferFlush i d³ugoœæ wysy³anego
// ci¹gu znaków nie mo¿e przekroczyæ d³ugoœci bufora UART_TX_BUFFER_LENGTH
void Uart_Resend(USART_t * Port) {
	
	//volatile UART_Buffer_t * Buffer = Uart__GetProgBuffer(Port);
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
	
	UART_ProgBuf.TxBufferTail = 0;
	
	
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
	
	UART_ProgBuf.TxBufferCnt = UART_ProgBuf.TxBufferHead;

	// Je¿eli obecnie transmiter jest wy³¹czony, to go w³¹czamy
	/*
	if((Port->CTRLB & USART_TXEN_bm) == 0) {
		Uart_TxEnable(Port);

		// Je¿eli jest u¿ywana blokada uœpienia
		#if UART_USE_UCOSMOS_SLEEP
		OS_SLEEP_DISABLE;														// Ustawienie blokady uœpienia
		#endif
	}*/
	
	// Aktywowanie wysy³ania
	Port->CTRLA		=	USART_DREIE_bm |										// W³¹czenie przerwañ od DRE...
						USART_RXCIE_bm |										// ...a RX...
						USART_TXCIE_bm;											// ...oraz TX ju¿ wczeœniej by³o w³¹czone
	
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
	
	uint8_t Data;
	if(UART_ProgBuf.RxBufferCnt) {												// Je¿eli jest coœ w buforze
		
		UART_ProgBuf.RxBufferCnt--;												// Zmniejszenie liczby znaków w buforze, bo zaraz odczytamy jeden z nich
		
		// Je¿eli jest u¿ywana blokada uœpienia
		#if UART_USE_UCOSMOS_SLEEP
			if(UART_ProgBuf.RxBufferCnt == 0) {									// Je¿eli bufor za chwilê bêdzie pusty
				OS_SLEEP_ENABLE;												// Zwolnienie blokady uœpienia
			}
		#endif
		
		Data = UART_ProgBuf.RxBuffer[UART_ProgBuf.RxBufferTail];				// Odczytanie ogona bufora						
		
		#if UART_CLEAR_BYTE_AFTER_READ											// Tylko w celach debugowych
			UART_ProgBuf.RxBuffer[UART_ProgBuf.RxBufferTail] = 0;				// Czyszczenie bajtu w buforze po jego odczycie
		#endif
		
		if(++UART_ProgBuf.RxBufferTail == UART_RX_BUFFER_LENGTH) {
			UART_ProgBuf.RxBufferTail = 0;										// Inkrementacja ogona i kontrola przepe³nienia, zapis ++ w tej lini oszczêdza 2B ni¿ gdyby ++ by³o w kolejnej linii
		}
		
		return Data;
	} 
	else {																		// Je¿eli bufor jest pusty
		return 0;
	}
}


// Przerwanie od RXC w celu skopiowanie znaku odebranego przez UART do bufora programowego
ISR(USARTX_RXC_vect) {

	// Je¿eli jest u¿ywana blokada uœpienia
	#if UART_USE_UCOSMOS_SLEEP
		if(UART_ProgBuf.RxBufferCnt == 0) {										// Je¿eli bufor wczeœniej by³ pusty
			OS_SLEEP_DISABLE;													// Wy³¹czenie trybu uœpienia do czasu odebrania wszystkich znaków z bufora
		}
	#endif
	
	if(UART_ProgBuf.RxBufferCnt < UART_RX_BUFFER_LENGTH) {						// Kontrola wolnego miejsca w buforze
		UART_ProgBuf.RxBufferCnt++;
		UART_ProgBuf.RxBuffer[UART_ProgBuf.RxBufferHead] = USARTX.RXDATAL;
		if(++UART_ProgBuf.RxBufferHead == UART_RX_BUFFER_LENGTH) {				// Zapis ++RxBufferHead oszczêdza pamiêæ o 2B
			UART_ProgBuf.RxBufferHead = 0;										// Przepe³nienie indeksu head
		}
	} 
	else {																		// Przepe³nienie bufora
		#if UART_BREAK_ON_BUFFER_FULL								
			asm volatile("break");												// Zatrzymanie jeœli bufor przepe³niony
		#endif
		void(USARTX.RXDATAL);													// Odczytanie by wyzerowaæ flagê przerwania
	}	
}


// Odczyt liczby znaków gotowych do odczyty z bufora programowego
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


// TODO: Wyci¹æ to
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


// TODO: Wyci¹æ to
void Uart_TxBufferFlush(USART_t * Port) {
	Uart_TxBufferFlush(&UART_ProgBuf);
}


// Czekanie a¿ transmisja dobiegnie koñca (przydatne przed wejœciem w stan uœpienia) - wersja dla wskazanego UART
void Uart_WaitForTxComplete(USART_t * Port) {
	while(UART_ProgBuf.Status & UART_TX_BUSY);
}


#endif
