#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// =========================
// Internal Hardware Icludes
// =========================

#if C_CLOCK
	#include "clock/clock.h"
#endif

#if C_PERIPHERALS
	#include "peripherals/peripherals.h"
#endif

#if C_UART
	#include "uart/uart.h"
#endif

// =========================
// External Hardware Icludes
// =========================


// =================
// Software includes
// =================

#if C_CONSOLE
	#include "console/console.h"
#endif

#if C_UCOSMOS
	#include "uCosmos/uCosmos.h"
#endif


// Main
int main(void) {

	// ======================
	// Internal Hardware init
	// ======================

	#if C_CLOCK
		Clock_Init();
	#endif

	#if C_PERIPHERALS
		Peripherals_Init();
	#endif

	#if C_UART
		Uart_Init();
	#endif
	
	sei();
	
	// ======================
	// Internal Software Init
	// ======================
	
	#if C_UCOSMOS
		Os_Init();
		Os_ConsoleInit();
	#endif

	// ======================
	// External Hardware init
	// ======================
	
	
	
	// =============
	// Software init
	// =============
	
	
	// =========
	// Main loop
	// =========
	
	
	Uart_Write("\r\n=== START ===\r\n", &USART2);
	Os_ResetSourceShow(RSTCTRL.RSTFR);
	Os_ResetSourceClear();
	
	// Peripherals demo tasks
	#if PERIPHERALS_USE_DEMO_TASKS
		TaskAddMs(Peripherals_TaskRed,		1000);
		TaskAddMs(Peripherals_TaskYellow,	1100);
		TaskAddMs(Peripherals_TaskGreen,	1200);
		TaskAddMs(Peripherals_TaskBlue,		1300);
	#endif
		
	while(1) {
		TaskScheduler();
	}
	
	while(1) {
		//PORTD.OUTSET = PIN0_bm;
		//_delay_ms(1000);
		//PORTD.OUTCLR = PIN0_bm;
		//_delay_ms(1000);

		//Uart_Write("Hello\r\n", &USART2);
		
		if(KEY_SW0_READ)					LED_BLUE_ON;
		else								LED_BLUE_OFF;
		
		if(KEY_SW1_READ)					LED_GREEN_ON;
		else								LED_GREEN_OFF;
		
		if(KEY_SW0_READ && KEY_SW1_READ)	LED_YELLOW_ON;
		else								LED_YELLOW_OFF;
		
		uint8_t ch;
		ch = Uart_Read();
		if(ch) {
			Uart_Write(ch);
		}

// 		if(Uart_Read()) {
// 			PORTD.OUTTGL = PIN0_bm;
// 		}
	}
}

