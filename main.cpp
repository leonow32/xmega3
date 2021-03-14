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
	
	sei();
	
	// ========================================
	// Internal Software Init
	// ========================================
	
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
	
	Uart_Write("\r\n=== START ===\r\n");
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
	
	while(1) {
		TaskScheduler();
	}
}

