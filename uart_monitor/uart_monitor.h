#ifndef UART_MONITOR_H_
#define UART_MONITOR_H_
#if C_UART_MONITOR

// ========================================
// Includes
// ========================================

#include	<avr/io.h>
#include	"../config/config.h"
#include	"uart_monitor_config.h"

#if C_CONSOLE
	#include	"../console/console.h"
#else
	#error		"This module requires CONSOLE component"
#endif

#if C_PRINT
	#include	"../print/print.h"
#else
	#error		"This module requires PRINT component"
#endif

#if C_UART_MULTI
	#include	"../uart/uart_multi.h"
#else
	#error		"This module requires UART_MULTI component"
#endif

#if C_UCOSMOS
	#include	"../uCosmos/uCosmos.h"
#else
	#error		"This module requires UCOSMOS component"
#endif


// ========================================
// Functions
// ========================================

void UartMonitor_Init(void);
task_t UartMonitor_Task(runmode_t RunMode);
void UartMonitor_CmdSendHex(uint8_t argc, uint8_t * argv[]);
void UartMonitor_CmdSendAscii(uint8_t argc, uint8_t * argv[]);
#endif
#endif /* UART_MONITOR_H_ */
