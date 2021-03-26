// Version 0.01

#ifndef CONSOLE_CONFIG_H_
#define CONSOLE_CONFIG_H_

// ========================================
// Template
// ========================================

#if P_TEMPLATE
	
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if P_AVRIOT
	
#endif

// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if P_CURIO4809
	
	// Length of command buffer
	#define CONSOLE_COMMAND_LENGTH			250
	#define CONSOLE_MAX_ARGUMENTS			10
	
	#define CONSOLE_UART_INSTANCE			USART3
	
	#define CONSOLE_USE_CTRL_Z				1
	
	#define CONSOLE_USE_COMMAND_ALL			1
	#define CONSOLE_USE_DEMO_COMMANDS		1
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if P_XNANO
	
#endif


#endif /* CONSOLE_CONFIG_H_ */