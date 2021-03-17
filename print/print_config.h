// Wersja 0.01

#ifndef PRINT_CONFIG_H_
#define PRINT_CONFIG_H_


#if B_XNANO
	
	// Czy u�ywa� jednego strumienia wyj�ciowego zawsze czy ma by� mo�liwo�� zmiany
	#define PRINT_USE_STREAM_SINGLE					0
	#define PRINT_USE_STREAM_MULTI					1
	
	// Domy�lny strumie� wyj�ciowy
	#define PRINT_DEFAULT_STREAM					Uart_Write
	
#endif


#if TEMPLATE
	
	// Czy u�ywa� jednego strumienia wyj�ciowego zawsze czy ma by� mo�liwo�� zmiany
	#define PRINT_USE_STREAM_SINGLE					0
	#define PRINT_USE_STREAM_MULTI					1
	
	// Domy�lny strumie� wyj�ciowy
	#define PRINT_DEFAULT_STREAM					Uart_Write
	
#endif


// Kontrola b��d�w
#if PRINT_USE_STREAM_SINGLE && PRINT_USE_STREAM_MULTI
	#error "Can't use PRINT_USE_STREAM_SINGLE and PRINT_USE_STREAM_MULTI at the same time"
#endif


#endif /* PRINT_CONFIG_H_ */