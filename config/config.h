/*
UWAGI I POMYS£Y
		-	

CHANGELOG
1.00	*	Obs³uga wszystkich procesorów z architektur¹ xmega3 (stan na 2019.01.01)
		
*/

#ifndef GENERAL_CONFIG_H_
#define GENERAL_CONFIG_H_

// Wybór procesora
#if B_AVRIOT
	#define HW_CPU_ATtinyXX12					0
	#define HW_CPU_ATtinyXX14					0
	#define HW_CPU_ATtinyXX16					0
	#define HW_CPU_ATtinyXX17					0
	#define HW_CPU_ATmegaXX08_28pin				0
	#define HW_CPU_ATmegaXX08_32pin				1
	#define HW_CPU_ATmegaXX09					0
#endif


// Komunikaty o b³êdach
#if HW_CPU_ATtinyXX12 + HW_CPU_ATtinyXX14 + HW_CPU_ATtinyXX16 + HW_CPU_ATtinyXX17 + HW_CPU_ATmegaXX09 + HW_CPU_ATmegaXX08_28pin + HW_CPU_ATmegaXX08_32pin > 1
	#error "Selected more than one CPU"
#endif

#endif /* GENERAL_CONFIG_H_ */