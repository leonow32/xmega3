#ifndef UART_MONITOR_CONFIG_H_
#define UART_MONITOR_CONFIG_H_

// ========================================
// Template
// ========================================

#if TEMPLATE
	#define UART_MONITOR_PERIPHERAL		USART1			// UART instance
	#define UART_MONITOR_READ_PERIOD	500				// Time in ms to periodically check UART buffer
	#define UART_MONITOR_CONFIG_DONE
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if P_AVRIOT
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