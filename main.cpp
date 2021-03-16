// ========================================
// AVR_GCC Includes
// ========================================

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// ========================================
// Internal Hardware Includes
// ========================================

#if C_CLOCK
	#include	"clock/clock.h"
#endif

#if C_PERIPHERALS
	#include	"peripherals/peripherals.h"
#endif

#if C_UART_SINGLE
	#include	"uart/uart_single.h"
#elif C_UART_MULTI
	#include	"uart/uart_multi.h"
#else
	#error		"This module requires UART component"
#endif

// ========================================
// External Hardware Includes
// ========================================


// ========================================
// Software includes
// ========================================

#if C_CONSOLE
	#include	"console/console.h"
#endif

#if C_UCOSMOS
	#include	"uCosmos/uCosmos.h"
#endif

#if C_PRINT
	#include	"print/print.h"
#endif


// Main
int main(void) {

	// ========================================
	// Internal Hardware init
	// ========================================

	#if C_CLOCK
		Clock_Init();
	#endif

	#if C_PERIPHERALS
		Peripherals_Init();
	#endif

	#if C_UART_MULTI || C_UART_SINGLE
		Uart_Init();
	#endif
	
	// Przerwania
	CPUINT.CTRLA |=	CPUINT_LVL0RR_bm;			// Algorytm round-robin dla przerwañ o tym samym priorytecie
	sei();
	
	// ========================================
	// Internal Software Init
	// ========================================
	
	#if C_PRINT
		
	#endif
	
	#if C_UCOSMOS
		Os_Init();
		Os_ConsoleInit();
	#endif

	// ========================================
	// External Hardware init
	// ========================================
	
	
	
	// ========================================
	// Software init
	// ========================================
	
	Print("\r\n=== START ===\r\n");
	Os_ResetSourceShow(RSTCTRL.RSTFR);
	Os_ResetSourceClear();
	
	// Peripherals demo tasks
	#if B_AVRIOT && PERIPHERALS_USE_DEMO_TASKS
		TaskAddMs(Peripherals_TaskRed,		1000);
		TaskAddMs(Peripherals_TaskYellow,	1100);
		TaskAddMs(Peripherals_TaskGreen,	1200);
		TaskAddMs(Peripherals_TaskBlue,		1300);
	#endif
	
	#if B_XNANO && PERIPHERALS_USE_DEMO_TASKS
		TaskAddMs(Peripherals_TaskYellow,	1000);
	#endif
	
	
	// ========================================
	// Main loop
	// ========================================
	
// 	while(1) {
// 		Uart_Write("0123456789");
// 		_delay_ms(1000);
// 	}
	
// 	while(1) {
// 		uint8_t Received = Uart_ReceivedCnt();
// 		if(Received > 10) {
// 			Uart_Write(Uart_Read());
// 		}
// 	}
	
	while(1) {
		TaskScheduler();
	}
}

