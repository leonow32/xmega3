// Version 1.0.0

#ifndef PRINT_CONFIG_H_
#define PRINT_CONFIG_H_

// ========================================
// Template
// ========================================

#if P_TEMPLATE
	
	// Whether to use one output stream at all times or whether it should be changeable
	#define PRINT_USE_STREAM_SINGLE					0
	#define PRINT_USE_STREAM_MULTI					1
	
	// Default output stream
	#define PRINT_DEFAULT_STREAM					Uart_Write
	
	// Use font formatting in console
	#define PRINT_USE_COLORS						1
	
	// Use demo commands
	#define PRINT_USE_DEMO_COMMANDS					1
	
	#define PRINT_CONFIG_DONE
	
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if P_AVRIOT
	
	// Whether to use one output stream at all times or whether it should be changeable
	#define PRINT_USE_STREAM_SINGLE					0
	#define PRINT_USE_STREAM_MULTI					1
	
	// Default output stream
	#define PRINT_DEFAULT_STREAM					Uart2_Write
	
	// Use font formatting in console
	#define PRINT_USE_COLORS						1
	
	// Use demo commands
	#define PRINT_USE_DEMO_COMMANDS					1
	
	#define PRINT_CONFIG_DONE
	
#endif

// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if P_CURIOSITY_M4809
	
	// Whether to use one output stream at all times or whether it should be changeable
	#define PRINT_USE_STREAM_SINGLE					0
	#define PRINT_USE_STREAM_MULTI					1
	
	// Default output stream
	#if C_UART_SINGLE
		#define PRINT_DEFAULT_STREAM				Uart_Write
	#elif C_UART_MULTI
		#define PRINT_DEFAULT_STREAM				Uart3_Write
	#endif
	
	// Use font formatting in console
	#define PRINT_USE_COLORS						1
	
	// Use demo commands
	#define PRINT_USE_DEMO_COMMANDS					1
	
	#define PRINT_CONFIG_DONE
	
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if P_XNANO
	
	// Whether to use one output stream at all times or whether it should be changeable
	#define PRINT_USE_STREAM_SINGLE					0
	#define PRINT_USE_STREAM_MULTI					1
	
	// Default output stream
	#define PRINT_DEFAULT_STREAM					Uart_Write
	
	// Use font formatting in console
	#define PRINT_USE_COLORS						1
	
	// Use demo commands
	#define PRINT_USE_DEMO_COMMANDS					1
	
	#define PRINT_CONFIG_DONE
	
#endif

// ========================================
// Error handling
// ========================================

#ifndef PRINT_CONFIG_DONE
	#error "Missing config"
#endif

#if PRINT_USE_STREAM_SINGLE && PRINT_USE_STREAM_MULTI
	#error "Can't use PRINT_USE_STREAM_SINGLE and PRINT_USE_STREAM_MULTI at the same time"
#endif


#endif /* PRINT_CONFIG_H_ */