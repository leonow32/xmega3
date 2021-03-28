// ========================================
// AVR GCC Includes
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

#if C_EEPROM
	#include	"eeprom/eeprom.h"
#endif

#if C_I2C_MASTER
	#include	"i2c_master/i2c_master.h"
#endif

#if C_PERIPHERALS
	#include	"peripherals/peripherals.h"
#endif

#if C_UART_SINGLE
	#include	"uart/uart_single.h"
#elif C_UART_MULTI
	#include	"uart/uart_multi.h"
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

#if C_PRINT
	#include	"print/print.h"
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
	
	#if C_EEPROM
		EEPROM_Init();
	#endif
	
	#if C_I2C_MASTER
		I2C_Init();
	#endif
	
	#if C_PERIPHERALS
		Peripherals_Init();
	#endif
	
	#if C_UART_MULTI || C_UART_SINGLE
		Uart_Init();
	#endif
	
	// ========================================
	// Internal Software Init
	// ========================================
	
	#if C_UCOSMOS
		Os_Init();
	#endif
	
	#if C_CONSOLE
		Console_Init();
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
	#if P_AVRIOT && PERIPHERALS_USE_DEMO_TASKS
		TaskAddMs(Peripherals_TaskRed,		1000);
		TaskAddMs(Peripherals_TaskYellow,	1100);
		TaskAddMs(Peripherals_TaskGreen,	1200);
		TaskAddMs(Peripherals_TaskBlue,		1300);
	#endif
	
	#if P_XNANO && PERIPHERALS_USE_DEMO_TASKS
		TaskAddMs(Peripherals_TaskYellow,	1000);
	#endif
	
	#if P_CURIO4809 && PERIPHERALS_USE_DEMO_TASKS
		TaskAddMs(Peripherals_TaskYellow,	1000);
	#endif
	
	// ========================================
	// Main loop
	// ========================================
	
	while(1) {
		TaskScheduler();
	}
}

