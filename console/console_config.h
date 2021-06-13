// Version 0.01

#ifndef CONSOLE_CONFIG_H_
#define CONSOLE_CONFIG_H_

// ========================================
// Template
// ========================================

#if PRODUCT_TEMPLATE
	#define CONSOLE_COMMAND_LENGTH				250
	#define CONSOLE_MAX_ARGUMENTS				10
	#define CONSOLE_USE_HELP					1
	#define CONSOLE_USE_CTRL_Z					1
	#define CONSOLE_USE_COMMAND_ALL				1
	#define CONSOLE_USE_DEMO_COMMANDS			1
	#define CONSOLE_INPUT_STREAM				Uart_Read
	#define CONSOLE_INPUT_RECEIVED_CNT			Uart_ReceivedCnt
	#define CONSOLE_CONFIG_DONE
#endif

// ========================================
// Demo Display SH1106
// ========================================

#if PRODUCT_SH1106
	#define CONSOLE_COMMAND_LENGTH				250
	#define CONSOLE_MAX_ARGUMENTS				10
	#define CONSOLE_USE_HELP					1
	#define CONSOLE_USE_CTRL_Z					1
	#define CONSOLE_USE_COMMAND_ALL				1
	#define CONSOLE_USE_DEMO_COMMANDS			0
	#define CONSOLE_INPUT_STREAM				Uart_Read
	#define CONSOLE_INPUT_RECEIVED_CNT			Uart_ReceivedCnt
	#define CONSOLE_CONFIG_DONE
#endif

// ========================================
// Demo Display SSD1309
// ========================================

#if PRODUCT_SSD1309
	#define CONSOLE_COMMAND_LENGTH				250
	#define CONSOLE_MAX_ARGUMENTS				10
	#define CONSOLE_USE_HELP					1
	#define CONSOLE_USE_CTRL_Z					1
	#define CONSOLE_USE_COMMAND_ALL				1
	#define CONSOLE_USE_DEMO_COMMANDS			0
	#define CONSOLE_INPUT_STREAM				Uart_Read
	#define CONSOLE_INPUT_RECEIVED_CNT			Uart_ReceivedCnt
	#define CONSOLE_CONFIG_DONE
#endif

// ========================================
// Demo Display SSD1351
// ========================================

#if PRODUCT_SSD1351
	#define CONSOLE_COMMAND_LENGTH				250
	#define CONSOLE_MAX_ARGUMENTS				10
	#define CONSOLE_USE_HELP					1
	#define CONSOLE_USE_CTRL_Z					1
	#define CONSOLE_USE_COMMAND_ALL				1
	#define CONSOLE_USE_DEMO_COMMANDS			0
	#define CONSOLE_INPUT_STREAM				Uart_Read
	#define CONSOLE_INPUT_RECEIVED_CNT			Uart_ReceivedCnt
	#define CONSOLE_CONFIG_DONE
#endif

// ========================================
// Demo Display SSD1681
// ========================================

#if PRODUCT_SSD1681
	#define CONSOLE_COMMAND_LENGTH				250
	#define CONSOLE_MAX_ARGUMENTS				10
	#define CONSOLE_USE_HELP					1
	#define CONSOLE_USE_CTRL_Z					1
	#define CONSOLE_USE_COMMAND_ALL				1
	#define CONSOLE_USE_DEMO_COMMANDS			0
	#define CONSOLE_INPUT_STREAM				Uart_Read
	#define CONSOLE_INPUT_RECEIVED_CNT			Uart_ReceivedCnt
	#define CONSOLE_CONFIG_DONE
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if PRODUCT_AVRIOT
	#define CONSOLE_COMMAND_LENGTH				250
	#define CONSOLE_MAX_ARGUMENTS				10
	#define CONSOLE_USE_HELP					1
	#define CONSOLE_USE_CTRL_Z					1
	#define CONSOLE_USE_COMMAND_ALL				1
	#define CONSOLE_USE_DEMO_COMMANDS			1
	#define CONSOLE_CONFIG_DONE
	
	#if COMPONENT_UART_SINGLE
		#define CONSOLE_INPUT_STREAM			Uart_Read
		#define CONSOLE_INPUT_RECEIVED_CNT		Uart_ReceivedCnt
	#elif COMPONENT_UART_MULTI
		#define CONSOLE_INPUT_STREAM			Uart2_Read
		#define CONSOLE_INPUT_RECEIVED_CNT		Uart2_ReceivedCnt
	#endif
#endif

// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if PRODUCT_CURIOSITY_M4809
	#define CONSOLE_COMMAND_LENGTH				250
	#define CONSOLE_MAX_ARGUMENTS				10
	#define CONSOLE_USE_HELP					1
	#define CONSOLE_USE_CTRL_Z					1
	#define CONSOLE_USE_COMMAND_ALL				1
	#define CONSOLE_USE_DEMO_COMMANDS			1
	#define CONSOLE_CONFIG_DONE
	
	#if COMPONENT_UART_SINGLE
		#define CONSOLE_INPUT_STREAM			Uart_Read
		#define CONSOLE_INPUT_RECEIVED_CNT		Uart_ReceivedCnt
	#elif COMPONENT_UART_MULTI
		#define CONSOLE_INPUT_STREAM			Uart3_Read
		#define CONSOLE_INPUT_RECEIVED_CNT		Uart3_ReceivedCnt
	#endif
#endif

// ========================================
// Dev Board Curiosity ATtiny3217
// ========================================

#if PRODUCT_CURIOSITY_T1627
	#define CONSOLE_COMMAND_LENGTH				250
	#define CONSOLE_MAX_ARGUMENTS				10
	#define CONSOLE_USE_HELP					1
	#define CONSOLE_USE_CTRL_Z					1
	#define CONSOLE_USE_COMMAND_ALL				1
	#define CONSOLE_USE_DEMO_COMMANDS			1
	#define CONSOLE_CONFIG_DONE
	
	#if COMPONENT_UART_SINGLE
		#define CONSOLE_INPUT_STREAM			Uart_Read
		#define CONSOLE_INPUT_RECEIVED_CNT		Uart_ReceivedCnt
	#elif COMPONENT_UART_MULTI
		#define CONSOLE_INPUT_STREAM			Uart0_Read
		#define CONSOLE_INPUT_RECEIVED_CNT		Uart0_ReceivedCnt
	#endif
#endif

// ========================================
// Dev Board Curiosity ATtiny3217
// ========================================

#if PRODUCT_CURIOSITY_T3217
	#define CONSOLE_COMMAND_LENGTH				250
	#define CONSOLE_MAX_ARGUMENTS				10
	#define CONSOLE_USE_HELP					1
	#define CONSOLE_USE_CTRL_Z					1
	#define CONSOLE_USE_COMMAND_ALL				1
	#define CONSOLE_USE_DEMO_COMMANDS			1
	#define CONSOLE_INPUT_STREAM				Uart_Read
	#define CONSOLE_INPUT_RECEIVED_CNT			Uart_ReceivedCnt
	#define CONSOLE_CONFIG_DONE
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if PRODUCT_XNANO
	#define CONSOLE_COMMAND_LENGTH				250
	#define CONSOLE_MAX_ARGUMENTS				10
	#define CONSOLE_USE_HELP					1
	#define CONSOLE_USE_CTRL_Z					1
	#define CONSOLE_USE_COMMAND_ALL				1
	#define CONSOLE_USE_DEMO_COMMANDS			1
	#define CONSOLE_INPUT_STREAM				Uart_Read
	#define CONSOLE_INPUT_RECEIVED_CNT			Uart_ReceivedCnt
	#define CONSOLE_CONFIG_DONE
#endif

// ========================================
// GameBox4809
// ========================================

#if PRODUCT_GAMEBOX4809
	#define CONSOLE_COMMAND_LENGTH				250
	#define CONSOLE_MAX_ARGUMENTS				10
	#define CONSOLE_USE_HELP					1
	#define CONSOLE_USE_CTRL_Z					1
	#define CONSOLE_USE_COMMAND_ALL				1
	#define CONSOLE_USE_DEMO_COMMANDS			0
	#define CONSOLE_INPUT_STREAM				Uart_Read
	#define CONSOLE_INPUT_RECEIVED_CNT			Uart_ReceivedCnt
	#define CONSOLE_CONFIG_DONE
#endif

// ========================================
// Error handling
// ========================================

#ifndef CONSOLE_CONFIG_DONE
	#error "Missing config"
#endif


#endif /* CONSOLE_CONFIG_H_ */