// Wersja 1.01

#ifndef CLOCK_CONFIG_H_
#define CLOCK_CONFIG_H_


#if B_AVRIOT
	#define CLOCK_PRESCALER				1
	#define CLOCK_CLKOUT_ENABLE			0			// Wyjœcie zagara na pinie CLKOUT
#endif


#if B_XNANO
	#define CLOCK_PRESCALER				1
	#define CLOCK_CLKOUT_ENABLE			0			// Wyjœcie zagara na pinie CLKOUT
#endif


#endif /* CLOCK_CONFIG_H_ */