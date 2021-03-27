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
	#define CONSOLE_COMMAND_LENGTH				250
	#define CONSOLE_MAX_ARGUMENTS				10
	#define CONSOLE_USE_CTRL_Z					1
	#define CONSOLE_USE_COMMAND_ALL				1
	#define CONSOLE_USE_DEMO_COMMANDS			1
	
	#if C_UART_SINGLE
		#define CONSOLE_INPUT_STREAM			Uart_Read
		#define CONSOLE_INPUT_RECEIVED_CNT		Uart_ReceivedCnt
	#elif C_UART_MULTI
		#define CONSOLE_INPUT_STREAM			Uart3_Read
		#define CONSOLE_INPUT_RECEIVED_CNT		Uart3_ReceivedCnt
	#endif

#endif

// ========================================
// Dev Board XNANO
// ========================================

#if P_XNANO
	
#endif


#endif /* CONSOLE_CONFIG_H_ */