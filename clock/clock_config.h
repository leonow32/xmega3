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
// Demo Display SH1106
// ========================================

#if PRODUCT_SH1106
	#define CLOCK_PRESCALER				1
	#define CLOCK_CLKOUT_ENABLE			0			// Clock output on CLKOUT pin
	#define CLOCK_CONFIG_DONE
#endif

// ========================================
// Demo Display SSD1309
// ========================================

#if PRODUCT_SSD1309
	#define CLOCK_PRESCALER				1
	#define CLOCK_CLKOUT_ENABLE			0			// Clock output on CLKOUT pin
	#define CLOCK_CONFIG_DONE
#endif

// ========================================
// Demo Display SSD1351
// ========================================

#if PRODUCT_SSD1351
	#define CLOCK_PRESCALER				1
	#define CLOCK_CLKOUT_ENABLE			0			// Clock output on CLKOUT pin
	#define CLOCK_CONFIG_DONE
#endif

// ========================================
// Demo Display SSD1681
// ========================================

#if PRODUCT_SSD1681
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
// Dev Board Curiosity ATtiny1627
// ========================================

#if PRODUCT_CURIOSITY_T1627
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
// GameBox4809
// ========================================

#if PRODUCT_GAMEBOX4809
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