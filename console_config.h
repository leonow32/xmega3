// Wersja 0.22

#ifndef COMMAND_CONFIG_H_
#define COMMAND_CONFIG_H_


#if B_AVRIOT
	// Definicje konfiguracyjne
	#define		CMD_LINE_BUFFER_LENGTH			250
	#define		CMD_MAX_ARGUMENTS				10

	// Reakcje interpretera
	#define		CMD_USE_ACK_NAK					1			// Wysy³anie znaku ACK/NAK po poprawnym lub niepoprawnym zinterpretowaniu polecenia

	// Human-machine interface
	#define		CMD_USE_ALL						1			// Polecenie "all" wyœwietlaj¹ce wszystkie dostêpne polecenia
	#define		CMD_USE_HELP					1			// Je¿eli polecenie zostanie wpisane bez argumentów, to wyœwietli siê pomoc na ich temat; mo¿na wy³¹czyæ, by zaoszczêdziæ miejsce
#endif


#endif /* COMMAND_CONFIG_H_ */