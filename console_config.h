// Wersja 0.22

#ifndef COMMAND_CONFIG_H_
#define COMMAND_CONFIG_H_


#if B_AVRIOT
	// Definicje konfiguracyjne
	#define		CMD_LINE_BUFFER_LENGTH			250
	#define		CMD_MAX_ARGUMENTS				10

	// Reakcje interpretera
	#define		CMD_USE_ACK_NAK					1			// Wysy�anie znaku ACK/NAK po poprawnym lub niepoprawnym zinterpretowaniu polecenia

	// Human-machine interface
	#define		CMD_USE_ALL						1			// Polecenie "all" wy�wietlaj�ce wszystkie dost�pne polecenia
	#define		CMD_USE_HELP					1			// Je�eli polecenie zostanie wpisane bez argument�w, to wy�wietli si� pomoc na ich temat; mo�na wy��czy�, by zaoszcz�dzi� miejsce
#endif


#endif /* COMMAND_CONFIG_H_ */