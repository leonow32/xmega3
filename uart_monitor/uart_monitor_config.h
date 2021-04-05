#ifndef UART_MONITOR_CONFIG_H_
#define UART_MONITOR_CONFIG_H_

#if P_AVRIOT
	#define UART_MONITOR_PERIPHERAL		USART1			// UART instance
	#define UART_MONITOR_READ_PERIOD	500				// Time in ms to periodically check UART buffer
#endif



#endif /* UART_MONITOR_CONFIG_H_ */