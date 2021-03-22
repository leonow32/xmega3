// Version 0.01

#ifndef INTERPRETER_CONFIG_H_
#define INTERPRETER_CONFIG_H_

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
	#define INTERPRETER_COMMAND_LENGTH			250
	#define INTERPRETER_MAX_ARGUMENTS			10
	
	#define INTERPRETER_UART_INSTANCE			USART3
	
	#define INTERPRETER_USE_CTRL_Z				1
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if P_XNANO
	
#endif


#endif /* INTERPRETER_CONFIG_H_ */