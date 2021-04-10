#ifndef UART_MONITOR_CONFIG_H_
#define UART_MONITOR_CONFIG_H_

// ========================================
// Template
// ========================================

#if PRODUCT_TEMPLATE
	#define UART_MONITOR_PERIPHERAL		USART1			// UART instance
	#define UART_MONITOR_READ_PERIOD	500				// Time in ms to periodically check UART buffer
	#define UART_MONITOR_CONFIG_DONE
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if PRODUCT_AVRIOT
	#define UART_MONITOR_PERIPHERAL		USART1			// UART instance
	#define UART_MONITOR_READ_PERIOD	500				// Time in ms to periodically check UART buffer
	#define UART_MONITOR_CONFIG_DONE
#endif

// ========================================
// Dev Board Curiosity ATtiny1627
// ========================================

#if PRODUCT_CURIOSITY_T1627
	#define UART_MONITOR_PERIPHERAL		USART1			// UART instance
	#define UART_MONITOR_READ_PERIOD	500				// Time in ms to periodically check UART buffer
	#define UART_MONITOR_CONFIG_DONE
#endif

// ========================================
// Error handling
// ========================================

#ifndef UART_MONITOR_CONFIG_DONE
	#error "Missing config"
#endif

#endif /* UART_MONITOR_CONFIG_H_ */