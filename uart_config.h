// Wersja 2.16

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#include	"general_config.h"


#if B_AVRIOT

	// Wyb�r, kt�re porty UART maj� by� u�ywane
	#define		UART0_USE					0
	#define		UART1_USE					1
	#define		UART2_USE					1

	#if UART0_USE
		#define	UART0_PORTA_01				1
		#define UART0_PORTA_45				0
	#endif

	#if UART1_USE
		#define	UART1_PORTC_01				1
	#endif

	#if UART2_USE
		#define	UART2_PORTF_01				1
		#define	UART2_PORTF_45				0
	#endif

	// Domy�lny port
	#define		UART_DEFAULT_PORT			USART2
	#define		UART_DEFAUL_PORT_BACKUP		USART2
 
	// Przerwanie z priorytetem (ustawi� tu port do konsoli systemowej)
	#define		UART_CONSOLE_INT			USART2_DRE_vect_num

	// Konfiguracja
	#define		UART_CLEAR_BYTE_AFTER_READ	0				// W celach debugowych, czy�ci bajty z TxBuffer i RxBuffer po ich wys�aniu/odebraniu
	#define		UART_BREAK_ON_BUFFER_FULL	0				// W celach debugowych, zatrzymuje program je�li bufor zostaje zape�niony
	#define		UART_DEBUG_RUN				1				// W celach debugorych, UART dzia�a podczas breakpoint�w

	// Tryb u�pienia je�eli jest wykorzystywany AVR uCosmos
	#define		UART_USE_UCOSMOS_SLEEP		0

	// Pr�dko�� transmisji
	#define		UART0_BAUD					57600			// Not used	
	#define		UART1_BAUD					57600			// Connector
	#define		UART2_BAUD					57600			// Debug

	// Bufory (max 254)
	#define		UART_TX_BUFFER_LENGTH		255
	#define		UART_RX_BUFFER_LENGTH		128
#endif




#if TEMPLATE
 
	#if HW_CPU_ATtinyXX12
		#define	UART0_USE					1
		#define	UART0_PORTA_12				1
	#endif

	#if HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17
		#define	UART0_USE					1
		#define	UART0_PORTA_12				1
		#define	UART0_PORTB_23				0
	#endif
 
	#if HW_CPU_ATmegaXX08_28pin
		#define	UART0_USE					1
		#define	UART1_USE					1
		#define	UART2_USE					1

		#if UART0_USE
			#define	UART0_PORTA_01			1
			#define	UART0_PORTA_45			0
		#endif

		#if UART1_USE
			#define	UART1_PORTC_01			1
		#endif

		#if UART2_USE
			#define	UART2_PORTF_01			1
		#endif
	#endif

	#if HW_CPU_ATmegaXX08_32pin
		#define	UART0_USE					0
		#define	UART1_USE					1
		#define	UART2_USE					1

		#if UART0_USE
			#define	UART0_PORTA_01			1
			#define	UART0_PORTA_45			0
		#endif

		#if UART1_USE
			#define	UART1_PORTC_01			1
		#endif

		#if UART2_USE
			#define	UART2_PORTF_01			1
			#define	UART2_PORTF_45			0
		#endif
	#endif

	#if HW_CPU_ATmegaXX09 && B_RPM_v005
		#define		UART0_USE				1
		#define		UART1_USE				1
		#define		UART2_USE				1
		#define		UART3_USE				1

		#if UART0_USE
			#define	UART0_PORTA_01			1
			#define	UART0_PORTA_45			0
		#endif

		#if UART1_USE
			#define	UART1_PORTC_01			1
			#define	UART1_PORTC_45			0
		#endif

		#if UART2_USE
			#define	UART2_PORTF_01			0
			#define	UART2_PORTF_45			1
		#endif

		#if UART3_USE
			#define	UART3_PORTB_01			1
			#define	UART3_PORTB_45			0
		#endif
	#endif

	// Domy�lny port
	#define		UART_DEFAULT_PORT			USART2
	#define		UART_DEFAUL_PORT_BACKUP		USART2

	// Przerwanie z priorytetem (ustawi� tu port do konsoli systemowej)
	#define		UART_CONSOLE_INT			USART2_DRE_vect_num

	// Konfiguracja
	#define		UART_CLEAR_BYTE_AFTER_READ	0				// W celach debugowych, czy�ci bajty z TxBuffer i RxBuffer po ich wys�aniu/odebraniu
	#define		UART_BREAK_ON_BUFFER_FULL	0				// W celach debugowych, zatrzymuje program je�li bufor zostaje zape�niony
	#define		UART_DEBUG_RUN				1				// W celach debugorych, UART dzia�a podczas breakpoint�w

	// Tryb u�pienia je�eli jest wykorzystywany AVR uCosmos
	#define		UART_USE_UCOSMOS_SLEEP		0

	// Pr�dko�� transmisji
	#define		UART0_BAUD					57600			// Not used
	#define		UART1_BAUD					57600			// Connector
	#define		UART2_BAUD					57600			// Debug
	#define		UART3_BAUD					57600			// Other

	// Bufory (max 254)
	#define		UART_TX_BUFFER_LENGTH		255
	#define		UART_RX_BUFFER_LENGTH		128
#endif



#endif /* UART_CONFIG_H_ */