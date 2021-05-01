#ifndef UART_MONITOR_H_
#define UART_MONITOR_H_
#if COMPONENT_UART_MONITOR

// ========================================
// Includes
// ========================================

#include	<avr/io.h>
#include	"../config/config.h"
#include	"uart_monitor_config.h"

#if COMPONENT_CONSOLE
	#include	"../console/console.h"
#else
	#error		"This module requires CONSOLE component"
#endif

#if COMPONENT_PRINT
	#include	"../print/print.h"
#else
	#error		"This module requires PRINT component"
#endif

#if COMPONENT_UART_MULTI
	#include	"../uart/uart_multi.h"
#else
	#error		"This module requires UART_MULTI component"
#endif

#if COMPONENT_UCOSMOS
	#include	"../uCosmos/uCosmos.h"
#else
	#error		"This module requires UCOSMOS component"
#endif


// ========================================
// Functions
// ========================================

void UartMonitor_Init(void);
task_t UartMonitor_Task(runmode_t RunMode);
void UartMonitor_CmdSend(uint8_t argc, uint8_t * argv[]);

#endif
#endif /* UART_MONITOR_H_ */
