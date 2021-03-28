// Wersja 1.01

#ifndef CLOCK_CONFIG_H_
#define CLOCK_CONFIG_H_

// ========================================
// Template
// ========================================

#if P_TEMPLATE
	#define CLOCK_PRESCALER				1
	#define CLOCK_CLKOUT_ENABLE			0			// Clock output on CLKOUT pin
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if P_AVRIOT
	#define CLOCK_PRESCALER				1
	#define CLOCK_CLKOUT_ENABLE			0			// Clock output on CLKOUT pin
#endif

// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if P_CURIO4809
	#define CLOCK_PRESCALER				1
	#define CLOCK_CLKOUT_ENABLE			0			// Clock output on CLKOUT pin
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if P_XNANO
	#define CLOCK_PRESCALER				1
	#define CLOCK_CLKOUT_ENABLE			0			// Clock output on CLKOUT pin
#endif


#endif /* CLOCK_CONFIG_H_ */