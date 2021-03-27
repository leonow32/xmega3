// Wersja 3.0.0

#ifndef UART_SINGLE_CONFIG_H_
#define UART_SINGLE_CONFIG_H_

#include "../config/config.h"

// ========================================
// Template
// ========================================

#if P_TEMPLATE
	
	#if HW_CPU_ATtinyXX12
		#define	UART0_PORTA_12				1
	#endif
	
	#if HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17
		#define	UART0_PORTA_12				1
		#define	UART0_PORTB_23				0
	#endif
	
	#if HW_CPU_ATmegaXX08_28pin
		#define	UART0_PORTA_01				1
		#define	UART0_PORTA_45				0
		#define	UART1_PORTC_01				0
		#define	UART2_PORTF_01				0
	#endif
	
	#if HW_CPU_ATmegaXX08_32pin
		#define	UART0_PORTA_01				1
		#define	UART0_PORTA_45				0
		#define	UART1_PORTC_01				0
		#define	UART2_PORTF_01				0
		#define	UART2_PORTF_45				0
	#endif
	
	#if HW_CPU_ATmegaXX09
		#define	UART0_PORTA_01				1
		#define	UART0_PORTA_45				0
		#define	UART1_PORTC_01				0
		#define	UART1_PORTC_45				0
		#define	UART2_PORTF_01				0
		#define	UART2_PORTF_45				0
		#define	UART3_PORTB_01				0
		#define	UART3_PORTB_45				0
	#endif
	
	// Baud rate
	#define		UART_BAUD					115200
	
	// Konfiguracja
	#define		UART_CLEAR_BYTE_AFTER_READ	0				// W celach debugowych, czyœci bajty z TxBuffer i RxBuffer po ich wys³aniu/odebraniu
	#define		UART_BREAK_ON_BUFFER_FULL	0				// W celach debugowych, zatrzymuje program jeœli bufor zostaje zape³niony
	#define		UART_DEBUG_RUN				1				// W celach debugorych, UART dzia³a podczas breakpointów
	
	// Tryb uœpienia je¿eli jest wykorzystywany AVR uCosmos
	#define		UART_USE_UCOSMOS_SLEEP		0
	
	// Bufory (max 254)
	#define		UART_TX_BUFFER_LENGTH		255
	#define		UART_RX_BUFFER_LENGTH		128
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if P_AVRIOT
	
	#if HW_CPU_ATmegaXX08_32pin
		#define	UART0_PORTA_01				0
		#define	UART0_PORTA_45				0
		#define	UART1_PORTC_01				1		// Connector
		#define	UART2_PORTF_01				0		// Debug
		#define	UART2_PORTF_45				0
	#endif
	
	// Baud rate
	#define		UART_BAUD					115200
	
	// Konfiguracja
	#define		UART_CLEAR_BYTE_AFTER_READ	0				// W celach debugowych, czyœci bajty z TxBuffer i RxBuffer po ich wys³aniu/odebraniu
	#define		UART_BREAK_ON_BUFFER_FULL	0				// W celach debugowych, zatrzymuje program jeœli bufor zostaje zape³niony
	#define		UART_DEBUG_RUN				1				// W celach debugorych, UART dzia³a podczas breakpointów
	
	// Tryb uœpienia je¿eli jest wykorzystywany AVR uCosmos
	#define		UART_USE_UCOSMOS_SLEEP		0
	
	// Bufory (max 254)
	#define		UART_TX_BUFFER_LENGTH		255
	#define		UART_RX_BUFFER_LENGTH		128
#endif

// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if P_CURIO4809
	
	#if HW_CPU_ATmegaXX09
		#define	UART0_PORTA_01				0
		#define	UART0_PORTA_45				0
		#define	UART1_PORTC_01				0
		#define	UART1_PORTC_45				0
		#define	UART2_PORTF_01				0
		#define	UART2_PORTF_45				0
		#define	UART3_PORTB_01				1
		#define	UART3_PORTB_45				0
	#endif
	
	// Baud rate
	#define		UART_BAUD					115200
	
	// Konfiguracja
	#define		UART_CLEAR_BYTE_AFTER_READ	0				// W celach debugowych, czyœci bajty z TxBuffer i RxBuffer po ich wys³aniu/odebraniu
	#define		UART_BREAK_ON_BUFFER_FULL	0				// W celach debugowych, zatrzymuje program jeœli bufor zostaje zape³niony
	#define		UART_DEBUG_RUN				1				// W celach debugorych, UART dzia³a podczas breakpointów
	
	// Tryb uœpienia je¿eli jest wykorzystywany AVR uCosmos
	#define		UART_USE_UCOSMOS_SLEEP		0
	
	// Bufory (max 254)
	#define		UART_TX_BUFFER_LENGTH		255
	#define		UART_RX_BUFFER_LENGTH		128
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if P_XNANO
	
	#if HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17
		#define	UART0_PORTA_12				0
		#define	UART0_PORTB_23				1
	#endif
	
	// Baud rate
	#define		UART_BAUD					115200
	
	// Konfiguracja
	#define		UART_CLEAR_BYTE_AFTER_READ	0				// W celach debugowych, czyœci bajty z TxBuffer i RxBuffer po ich wys³aniu/odebraniu
	#define		UART_BREAK_ON_BUFFER_FULL	0				// W celach debugowych, zatrzymuje program jeœli bufor zostaje zape³niony
	#define		UART_DEBUG_RUN				1				// W celach debugorych, UART dzia³a podczas breakpointów
	
	// Tryb uœpienia je¿eli jest wykorzystywany AVR uCosmos
	#define		UART_USE_UCOSMOS_SLEEP		0
	
	// Bufory (max 254)
	#define		UART_TX_BUFFER_LENGTH		255
	#define		UART_RX_BUFFER_LENGTH		128
#endif

// ========================================
// Common
// ========================================

// Definicje uogólniaj¹ce
#if UART0_PORTA_01
	#define USARTX				USART0
	#define USARTX_DRE_vect		USART0_DRE_vect
	#define USARTX_TXC_vect		USART0_TXC_vect
	#define USARTX_RXC_vect		USART0_RXC_vect
#elif UART0_PORTA_12
	#define USARTX				USART0
	#define USARTX_DRE_vect		USART0_DRE_vect
	#define USARTX_TXC_vect		USART0_TXC_vect
	#define USARTX_RXC_vect		USART0_RXC_vect
#elif UART0_PORTA_45
	#define USARTX				USART0
	#define USARTX_DRE_vect		USART0_DRE_vect
	#define USARTX_TXC_vect		USART0_TXC_vect
	#define USARTX_RXC_vect		USART0_RXC_vect
#elif UART0_PORTB_23
	#define USARTX				USART0
	#define USARTX_DRE_vect		USART0_DRE_vect
	#define USARTX_TXC_vect		USART0_TXC_vect
	#define USARTX_RXC_vect		USART0_RXC_vect
#elif UART1_PORTC_01
	#define USARTX				USART1
	#define USARTX_DRE_vect		USART1_DRE_vect
	#define USARTX_TXC_vect		USART1_TXC_vect
	#define USARTX_RXC_vect		USART1_RXC_vect
#elif UART1_PORTC_45
	#define USARTX				USART1
	#define USARTX_DRE_vect		USART1_DRE_vect
	#define USARTX_TXC_vect		USART1_TXC_vect
	#define USARTX_RXC_vect		USART1_RXC_vect
#elif UART2_PORTF_01
	#define USARTX				USART2
	#define USARTX_DRE_vect		USART2_DRE_vect
	#define USARTX_TXC_vect		USART2_TXC_vect
	#define USARTX_RXC_vect		USART2_RXC_vect
#elif UART2_PORTF_45
	#define USARTX				USART2
	#define USARTX_DRE_vect		USART2_DRE_vect
	#define USARTX_TXC_vect		USART2_TXC_vect
	#define USARTX_RXC_vect		USART2_RXC_vect
#elif UART3_PORTB_01
	#define USARTX				USART3
	#define USARTX_DRE_vect		USART3_DRE_vect
	#define USARTX_TXC_vect		USART3_TXC_vect
	#define USARTX_RXC_vect		USART3_RXC_vect
#elif UART3_PORTB_45
	#define USARTX				USART3
	#define USARTX_DRE_vect		USART3_DRE_vect
	#define USARTX_TXC_vect		USART3_TXC_vect
	#define USARTX_RXC_vect		USART3_RXC_vect
#else
	#error "No UART instance selected"
#endif

#endif /* UART_SINGLE_CONFIG_H_ */