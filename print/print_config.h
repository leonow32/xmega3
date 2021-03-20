// Wersja 0.01

#ifndef PRINT_CONFIG_H_
#define PRINT_CONFIG_H_

// ========================================
// Template
// ========================================

#if P_TEMPLATE
	
	// Czy u¿ywaæ jednego strumienia wyjœciowego zawsze czy ma byæ mo¿liwoœæ zmiany
	#define PRINT_USE_STREAM_SINGLE					0
	#define PRINT_USE_STREAM_MULTI					1
	
	// Domyœlny strumieñ wyjœciowy
	#define PRINT_DEFAULT_STREAM					Uart_Write
	
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if P_AVRIOT
	
	// Czy u¿ywaæ jednego strumienia wyjœciowego zawsze czy ma byæ mo¿liwoœæ zmiany
	#define PRINT_USE_STREAM_SINGLE					0
	#define PRINT_USE_STREAM_MULTI					1
	
	// Domyœlny strumieñ wyjœciowy
	#define PRINT_DEFAULT_STREAM					Uart2_Write
	
#endif

// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if P_CURIO4809
	
	// Czy u¿ywaæ jednego strumienia wyjœciowego zawsze czy ma byæ mo¿liwoœæ zmiany
	#define PRINT_USE_STREAM_SINGLE					0
	#define PRINT_USE_STREAM_MULTI					1
	
	// Domyœlny strumieñ wyjœciowy
	#define PRINT_DEFAULT_STREAM					Uart2_Write
	
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if P_XNANO
	
	// Czy u¿ywaæ jednego strumienia wyjœciowego zawsze czy ma byæ mo¿liwoœæ zmiany
	#define PRINT_USE_STREAM_SINGLE					0
	#define PRINT_USE_STREAM_MULTI					1
	
	// Domyœlny strumieñ wyjœciowy
	#define PRINT_DEFAULT_STREAM					Uart_Write
	
#endif

// Kontrola b³êdów
#if PRINT_USE_STREAM_SINGLE && PRINT_USE_STREAM_MULTI
	#error "Can't use PRINT_USE_STREAM_SINGLE and PRINT_USE_STREAM_MULTI at the same time"
#endif


#endif /* PRINT_CONFIG_H_ */