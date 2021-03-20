// Wersja 3.0.0

#ifndef UART_MULTI_CONFIG_H_
#define UART_MULTI_CONFIG_H_

#include "../config/config.h"

// ========================================
// Template
// ========================================

#if P_TEMPLATE
	
	#if HW_CPU_ATtinyXX12
		#define	UART0_USE					1
		#define	UART0_BAUD					115200			// Connected to...
		#define	UART0_PORTA_12				1
	#endif
	
	#if HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17
		#define	UART0_USE					1
		#define	UART0_BAUD					115200			// Connected to...
		#define	UART0_PORTA_12				1
		#define	UART0_PORTB_23				0
	#endif
	
	#if HW_CPU_ATmegaXX08_28pin
		#define	UART0_USE					1
		#define	UART1_USE					1
		#define	UART2_USE					1
	
		#if UART0_USE
			#define	UART0_BAUD				115200			// Connected to...
			#define	UART0_PORTA_01			1
			#define	UART0_PORTA_45			0
		#endif
	
		#if UART1_USE
			#define	UART1_BAUD				115200			// Connected to...
			#define	UART1_PORTC_01			1
		#endif
	
		#if UART2_USE
			#define	UART2_BAUD				115200			// Connected to...
			#define	UART2_PORTF_01			1
		#endif
	#endif
	
	#if HW_CPU_ATmegaXX08_32pin
		#define	UART0_USE					0
		#define	UART1_USE					1
		#define	UART2_USE					1
	
		#if UART0_USE
			#define	UART0_BAUD				115200			// Connected to...
			#define	UART0_PORTA_01			1
			#define	UART0_PORTA_45			0
		#endif
	
		#if UART1_USE
			#define	UART1_BAUD				115200			// Connected to...
			#define	UART1_PORTC_01			1
		#endif
	
		#if UART2_USE
			#define	UART2_BAUD				115200			// Connected to...
			#define	UART2_PORTF_01			1
			#define	UART2_PORTF_45			0
		#endif
	#endif
	
	#if HW_CPU_ATmegaXX09
		#define		UART0_USE				1
		#define		UART1_USE				1
		#define		UART2_USE				1
		#define		UART3_USE				1
	
		#if UART0_USE
			#define	UART0_BAUD				115200			// Connected to...
			#define	UART0_PORTA_01			1
			#define	UART0_PORTA_45			0
		#endif
	
		#if UART1_USE
			#define	UART1_BAUD				115200			// Connected to...
			#define	UART1_PORTC_01			1
			#define	UART1_PORTC_45			0
		#endif
	
		#if UART2_USE
			#define	UART2_BAUD				115200			// Connected to...
			#define	UART2_PORTF_01			0
			#define	UART2_PORTF_45			1
		#endif
	
		#if UART3_USE
			#define	UART3_BAUD				115200			// Connected to...
			#define	UART3_PORTB_01			1
			#define	UART3_PORTB_45			0
		#endif
	#endif
	
	// Domyœlny port
	#define		UART_DEFAULT_PORT			USART2
	
	// Przerwanie z priorytetem (ustawiæ tu port do konsoli systemowej)
	#define		UART_CONSOLE_INT			USART2_DRE_vect_num
	
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

#if B_AVRIOT
	
	// Które porty UART maj¹ byæ u¿ywane
	#define		UART0_USE					0
	#define		UART1_USE					1
	#define		UART2_USE					1
	
	#if UART0_USE
		#define	UART0_BAUD					0				// Not used	
		#define	UART0_PORTA_01				1
		#define UART0_PORTA_45				0
	#endif
	
	#if UART1_USE
		#define	UART1_BAUD					115200			// Connector
		#define	UART1_PORTC_01				1
	#endif
	
	#if UART2_USE
		#define	UART2_BAUD					115200			// Debug
		#define	UART2_PORTF_01				1
		#define	UART2_PORTF_45				0
	#endif
	
	// Domyœlny port
	#define		UART_DEFAULT_PORT			USART2
	
	// Przerwanie z priorytetem (ustawiæ tu port do konsoli systemowej)
	#define		UART_CONSOLE_INT			USART2_DRE_vect_num
	
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
	
	#define		UART0_USE				1
	#define		UART1_USE				1
	#define		UART2_USE				1
	#define		UART3_USE				1
	
	#if UART0_USE
		#define	UART0_BAUD				115200			// Connected to...
		#define	UART0_PORTA_01			1
		#define	UART0_PORTA_45			0
	#endif
	
	#if UART1_USE
		#define	UART1_BAUD				115200			// Connected to...
		#define	UART1_PORTC_01			1
		#define	UART1_PORTC_45			0
	#endif
	
	#if UART2_USE
		#define	UART2_BAUD				115200			// Connected to...
		#define	UART2_PORTF_01			1
		#define	UART2_PORTF_45			0
	#endif
	
	#if UART3_USE
		#define	UART3_BAUD				115200			// Debug port
		#define	UART3_PORTB_01			1
		#define	UART3_PORTB_45			0
	#endif
	
	// Domyœlny port
	#define		UART_DEFAULT_PORT			USART3
	
	// Przerwanie z priorytetem (ustawiæ tu port do konsoli systemowej)
	#define		UART_CONSOLE_INT			USART3_DRE_vect_num
	
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

#if B_XNANO
	#define	UART0_USE					1
	#define	UART0_BAUD					115200			// Connected to...
	#define	UART0_PORTA_12				1
	#define	UART0_PORTB_23				0
	
	// Domyœlny port
	#define		UART_DEFAULT_PORT			USART0
	
	// Przerwanie z priorytetem (ustawiæ tu port do konsoli systemowej)
	#define		UART_CONSOLE_INT			USART0_DRE_vect_num
	
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



#endif /* UART_MULTI_CONFIG_H_ */