// Version 2.0.0

#ifndef CLOCK_CONFIG_H_
#define CLOCK_CONFIG_H_

// ========================================
// Template
// ========================================

#if PRODUCT_TEMPLATE
	#define CLOCK_PRESCALER				1
	#define CLOCK_CLKOUT_ENABLE			0			// Clock output on CLKOUT pin
	#define CLOCK_CONFIG_DONE
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if PRODUCT_AVRIOT
	#define CLOCK_PRESCALER				1
	#define CLOCK_CLKOUT_ENABLE			0			// Clock output on CLKOUT pin
	#define CLOCK_CONFIG_DONE
#endif

// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if PRODUCT_CURIOSITY_M4809
	#define CLOCK_PRESCALER				1
	#define CLOCK_CLKOUT_ENABLE			0			// Clock output on CLKOUT pin
	#define CLOCK_CONFIG_DONE
#endif

// ========================================
// Dev Board Curiosity ATtiny3217
// ========================================

#if PRODUCT_CURIOSITY_T3217
	#define CLOCK_PRESCALER				1
	#define CLOCK_CLKOUT_ENABLE			0			// Clock output on CLKOUT pin
	#define CLOCK_CONFIG_DONE
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if PRODUCT_XNANO
	#define CLOCK_PRESCALER				1
	#define CLOCK_CLKOUT_ENABLE			0			// Clock output on CLKOUT pin
	#define CLOCK_CONFIG_DONE
#endif

// ========================================
// Error handling
// ========================================

#ifndef CLOCK_CONFIG_DONE
	#error "Missing config"
#endif

#endif /* CLOCK_CONFIG_H_ */