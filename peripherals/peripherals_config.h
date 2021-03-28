#ifndef PERIPHERALS_CONFIG_H_
#define PERIPHERALS_CONFIG_H_

// ========================================
// Template
// ========================================

#if P_TEMPLATE
	
	// Demos
	#define		PERIPHERALS_USE_DEMO_TASKS				1
	#define		PERIPHERALS_USE_DEMO_COMMANDS			1
	
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if P_AVRIOT
	
	// Demos
	#define		PERIPHERALS_USE_DEMO_TASKS				1
	#define		PERIPHERALS_USE_DEMO_COMMANDS			1
	
	// LED diodes
	#define		LED_RED_ON				VPORTD.OUT	|=  PIN0_bm
	#define		LED_RED_OFF				VPORTD.OUT	&= ~PIN0_bm
	#define		LED_RED_TGL				VPORTD.OUT	^=  PIN0_bm
	#define		LED_RED_INIT			VPORTD.DIR	|=	PIN0_bm;	PORTD.PIN0CTRL = PORT_INVEN_bm;
	
	#define		LED_YELLOW_ON			VPORTD.OUT	|=  PIN1_bm
	#define		LED_YELLOW_OFF			VPORTD.OUT	&= ~PIN1_bm
	#define		LED_YELLOW_TGL			VPORTD.OUT	^=  PIN1_bm
	#define		LED_YELLOW_INIT			VPORTD.DIR	|=	PIN1_bm;	PORTD.PIN1CTRL = PORT_INVEN_bm;
	
	#define		LED_GREEN_ON			VPORTD.OUT	|=  PIN2_bm
	#define		LED_GREEN_OFF			VPORTD.OUT	&= ~PIN2_bm
	#define		LED_GREEN_TGL			VPORTD.OUT	^=  PIN2_bm
	#define		LED_GREEN_INIT			VPORTD.DIR	|=	PIN2_bm;	PORTD.PIN2CTRL = PORT_INVEN_bm;
	
	#define		LED_BLUE_ON				VPORTD.OUT	|=  PIN3_bm
	#define		LED_BLUE_OFF			VPORTD.OUT	&= ~PIN3_bm
	#define		LED_BLUE_TGL			VPORTD.OUT	^=  PIN3_bm
	#define		LED_BLUE_INIT			VPORTD.DIR	|=	PIN3_bm;	PORTD.PIN3CTRL = PORT_INVEN_bm;
	
	// Buttons
	#define		KEY_SW0_READ			(VPORTF.IN	&	PIN6_bm)
	#define		KEY_SW0_INIT			PORTF.PIN6CTRL = PORT_INVEN_bm | PORT_PULLUPEN_bm;
	
	#define		KEY_SW1_READ			(VPORTF.IN	&	PIN5_bm)
	#define		KEY_SW1_INIT			PORTF.PIN5CTRL = PORT_INVEN_bm | PORT_PULLUPEN_bm;
	
	// Inne piny
	#define		PWM_ON					VPORTD.OUT	|=  PIN4_bm
	#define		PWM_OFF					VPORTD.OUT	&= ~PIN4_bm
	#define		PWM_INIT				VPORTD.DIR	|=	PIN4_bm
	
	#define		INT_ON					VPORTD.OUT	|=  PIN6_bm
	#define		INT_OFF					VPORTD.OUT	&= ~PIN6_bm
	#define		INT_INIT				VPORTD.DIR	|=	PIN6_bm
#endif

// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if P_CURIO4809
	
	// Demos
	#define		PERIPHERALS_USE_DEMO_TASKS				1
	#define		PERIPHERALS_USE_DEMO_COMMANDS			1
	
	// LED diodes
	#define		LED_YELLOW_ON			VPORTF.OUT	|=  PIN5_bm
	#define		LED_YELLOW_OFF			VPORTF.OUT	&= ~PIN5_bm
	#define		LED_YELLOW_TGL			VPORTF.OUT	^=  PIN5_bm
	#define		LED_YELLOW_INIT			VPORTF.DIR	|=	PIN5_bm;	PORTF.PIN5CTRL = PORT_INVEN_bm;
	
	// Buttons
	#define		KEY_SW0_READ			(VPORTF.IN	&	PIN6_bm)
	#define		KEY_SW0_INIT			PORTF.PIN6CTRL = PORT_INVEN_bm | PORT_PULLUPEN_bm;
	
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if P_XNANO
	
	// Demos
	#define		PERIPHERALS_USE_DEMO_TASKS				1
	#define		PERIPHERALS_USE_DEMO_COMMANDS			1
	
	// LED diodes
	#define		LED_YELLOW_ON			VPORTB.OUT	|=  PIN5_bm
	#define		LED_YELLOW_OFF			VPORTB.OUT	&= ~PIN5_bm
	#define		LED_YELLOW_TGL			VPORTB.OUT	^=  PIN5_bm
	#define		LED_YELLOW_INIT			VPORTB.DIR	|=	PIN5_bm;	PORTB.PIN5CTRL = PORT_INVEN_bm;
	
	// Buttons
	#define		KEY_SW0_READ			(VPORTB.IN	&	PIN4_bm)
	#define		KEY_SW0_INIT			PORTB.PIN4CTRL = PORT_INVEN_bm | PORT_PULLUPEN_bm;
	
#endif



#endif /* PERIPHERALS_CONFIG_H_ */