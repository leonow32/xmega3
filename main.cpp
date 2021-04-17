// ========================================
// AVR GCC Includes
// ========================================

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// ========================================
// Internal Hardware Includes
// ========================================

#if COMPONENT_CLOCK
	#include	"clock/clock.h"
#endif

#if COMPONENT_EEPROM
	#include	"eeprom/eeprom.h"
#endif

#if COMPONENT_I2C_MASTER
	#include	"i2c_master/i2c_master.h"
#endif

#if COMPONENT_PERIPHERALS
	#include	"peripherals/peripherals.h"
#endif

#if COMPONENT_SPI_MASTER
	#include	"spi_master/spi_master.h"
#endif

#if COMPONENT_UART_SINGLE
	#include	"uart/uart_single.h"
#elif COMPONENT_UART_MULTI
	#include	"uart/uart_multi.h"
#endif

// ========================================
// External Hardware Includes
// ========================================

#if COMPONENT_MCP9808
	#include	"mcp9808/mcp9808.h"
#endif

#if COMPONENT_MEM25
	#include	"mem25/mem25.h"
#endif

// ========================================
// Software includes
// ========================================

#if COMPONENT_CONSOLE
	#include	"console/console.h"
#endif

#if COMPONENT_PRINT
	#include	"print/print.h"
#endif

#if COMPONENT_UART_MONITOR
	#include	"uart_monitor/uart_monitor.h"
#endif

#if COMPONENT_UCOSMOS
	#include	"uCosmos/uCosmos.h"
#endif

// Main
int main(void) {
	
	// ========================================
	// Internal Hardware init
	// ========================================
	
	#if COMPONENT_CLOCK
		Clock_Init();
	#endif
	
	#if COMPONENT_EEPROM
		EEPROM_Init();
	#endif
	
	#if COMPONENT_I2C_MASTER
		I2C_Init();
	#endif
	
	#if COMPONENT_PERIPHERALS
		Peripherals_Init();
	#endif
	
	#if COMPONENT_SPI_MASTER
		Spi_Init();
	#endif
	
	#if COMPONENT_UART_MULTI || COMPONENT_UART_SINGLE
		Uart_Init();
	#endif
	
	// ========================================
	// Internal Software Init
	// ========================================
	
	#if COMPONENT_UCOSMOS
		Os_Init();
	#endif
	
	#if COMPONENT_CONSOLE
		Console_Init();
	#endif
	
	// ========================================
	// External Hardware init
	// ========================================
	
	#if COMPONENT_MCP9808
		MCP9808_Init();
	#endif
	
	#if COMPONENT_MEM25
		Mem25_Init();
	#endif
	
	// ========================================
	// Software init
	// ========================================
	
	#if PRODUCT_AVRIOT && PERIPHERALS_USE_DEMO_TASKS
		TaskAddMs(Peripherals_TaskRed,		1000);
		TaskAddMs(Peripherals_TaskYellow,	1100);
		TaskAddMs(Peripherals_TaskGreen,	1200);
		TaskAddMs(Peripherals_TaskBlue,		1300);
	#endif
	
	#if PRODUCT_XNANO && PERIPHERALS_USE_DEMO_TASKS
		TaskAddMs(Peripherals_TaskYellow,	1000);
	#endif
	
	#if PRODUCT_CURIOSITY_M4809 && PERIPHERALS_USE_DEMO_TASKS
		TaskAddMs(Peripherals_TaskYellow,	1000);
	#endif
	
	#if PRODUCT_CURIOSITY_T1627 && PERIPHERALS_USE_DEMO_TASKS
		TaskAddMs(Peripherals_TaskYellow,	1000);
	#endif
	
	#if PRODUCT_CURIOSITY_T3217 && PERIPHERALS_USE_DEMO_TASKS
		TaskAddMs(Peripherals_TaskYellow,	1000);
	#endif
	
	#if COMPONENT_UART_MONITOR
		UartMonitor_Init();
	#endif
	
	// ========================================
	// Main loop
	// ========================================
	
	while(1) {
		TaskScheduler();
	}
}

