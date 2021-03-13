// Wersja 1.01

#include "clock.h"
#include "clock_config.h"

void Clock_Init(void) {
	
	// Je¿eli sygna³ zegarowy ma byæ dostêpny na pinie CLKOUT
	#if CLOCK_CLKOUT_ENABLE
		
		#if   HW_CPU_ATtinyXX12
			#error "CLKOUT not supported on ATtinyXX12"

		#elif HW_CPU_ATtinyXX14
			#error "CLKOUT not supported on ATtinyXX14"

		#elif HW_CPU_ATtinyXX16
			VPORTB.OUT					|=	PIN5_bm;	
				
		#elif HW_CPU_ATtinyXX17
			VPORTB.OUT					|=	PIN5_bm;

		#elif HW_CPU_ATmegaXX08_28pin
			VPORTA.OUT					|=	PIN7_bm;

		#elif HW_CPU_ATmegaXX08_32pin
			VPORTA.OUT					|=	PIN7_bm;

		#elif HW_CPU_ATmegaXX09
			VPORTA.OUT					|=	PIN7_bm;

		#else
			#error "CPU not supported by clock.cpp"
		#endif	

		CPU_CCP						=	CCP_IOREG_gc;					// Odblokowanie chronionych rejestrow
		CLKCTRL.MCLKCTRLA			=	CLKCTRL_CLKOUT_bm |				// Wyjscie zegara na pinie CLKOUT
										CLKCTRL_CLKSEL_OSC20M_gc;		// Wybór generatora RC 16MHz/20MHz	
		
	#else
		CPU_CCP						=	CCP_IOREG_gc;					// Odblokowanie chronionych rejestrow
		CLKCTRL.MCLKCTRLA			=	CLKCTRL_CLKSEL_OSC20M_gc;		// Wybór generatora RC 16MHz/20MHz	
	#endif

	
	// Ustawienie preskalera
	CPU_CCP						=	CCP_IOREG_gc;						// Odblokowanie chronionych rejestrow							
	#if CLOCK_PRESCALER	  == 1
		CLKCTRL.MCLKCTRLB		=	0;	
	#elif CLOCK_PRESCALER == 2
		CLKCTRL.MCLKCTRLB		=	CLKCTRL_PDIV_2X_gc |
									CLKCTRL_PEN_bm;
	#elif CLOCK_PRESCALER == 4
		CLKCTRL.MCLKCTRLB		=	CLKCTRL_PDIV_4X_gc |
									CLKCTRL_PEN_bm;
	#elif CLOCK_PRESCALER == 6
		CLKCTRL.MCLKCTRLB		=	CLKCTRL_PDIV_6X_gc |
									CLKCTRL_PEN_bm;
	#elif CLOCK_PRESCALER == 8
		CLKCTRL.MCLKCTRLB		=	CLKCTRL_PDIV_8X_gc |
									CLKCTRL_PEN_bm;
	#elif CLOCK_PRESCALER == 10
		CLKCTRL.MCLKCTRLB		=	CLKCTRL_PDIV_10X_gc |
									CLKCTRL_PEN_bm;
	#elif CLOCK_PRESCALER == 12
		CLKCTRL.MCLKCTRLB		=	CLKCTRL_PDIV_12X_gc |
									CLKCTRL_PEN_bm;
	#elif CLOCK_PRESCALER == 16
		CLKCTRL.MCLKCTRLB		=	CLKCTRL_PDIV_16X_gc |
									CLKCTRL_PEN_bm;
	#elif CLOCK_PRESCALER == 24
		CLKCTRL.MCLKCTRLB		=	CLKCTRL_PDIV_24X_gc |
									CLKCTRL_PEN_bm;
	#elif CLOCK_PRESCALER == 32
		CLKCTRL.MCLKCTRLB		=	CLKCTRL_PDIV_32X_gc |
									CLKCTRL_PEN_bm;
	#elif CLOCK_PRESCALER == 48
		CLKCTRL.MCLKCTRLB		=	CLKCTRL_PDIV_48X_gc |
									CLKCTRL_PEN_bm;
	#elif CLOCK_PRESCALER == 64
		CLKCTRL.MCLKCTRLB		=	CLKCTRL_PDIV_64X_gc |
									CLKCTRL_PEN_bm;
	#else
		#error "Clock prescaler not set correctly"
	#endif
}