/*
CHANGELOG
2.0.0		Converted to new repo
1.09	+	Dodanie zapisywania b��d�w w logu
1.08	*	Optymalizacja EEPROM_Fill() i EEPROM_Erase(). U�ycie kontrolera NVM do kasowania ca�ej pami�ci zamiast pojedynczych bajt�w
1.07	+	Funckja operuj�ce na pojedynczych bitach
		+	uint8_t	EEPROM_ReadBit(uint8_t Address, uint8_t BitMask);
		+	EEres_t EEPROM_BitSet(uint8_t Address, uint8_t BitMask);
		+	EEres_t EEPROM_BitClr(uint8_t Address, uint8_t BitMask);
1.06	*	Oczyszczenie kodu i optymalizacja
1.05	+	Zmiana definicji EEPROM_VALID i EEPROM_INVALID na enum
1.04	+	Dodanie pliku eeprom_map.h
1.03	*	Zako�czenie prac nad obs�ug� potr�jnej redundancji
1.02	+	Dodanie pliku konfiguracyjnego eeprom_config.h
		+	Dodanie obs�ugi potr�jnej redundancji
1.01	*	Uporz�dkowanie kodu
1.00	+	Pierwsza wersja

UWAGI
		-	Obs�uguje pami�ci EEPROM o rozmiarze max 256B ze wzgl�du na adresowanie 8-bitowe
		-	Biblioteka wykorzystuje bajtowy dost�p do EEPROM, nie wykorzystuje stronicowania pami�ci
		
DO ZROBIENIA
		-	Automatyczne raportowanie b��d�w potr�jnej redundancji do logu
*/


#ifndef EEPROM_H_
#define EEPROM_H_

#include	<avr/eeprom.h>
#include	<avr/interrupt.h>
#include	"eeprom_config.h"


void		EEPROM_Init(void);
uint8_t		EEPROM_Read(uint8_t Address);
void		EEPROM_Read(uint8_t Address, uint8_t * Array, size_t ArrayLength);
void		EEPROM_Write(uint8_t Address, uint8_t Data);
void		EEPROM_Write(uint8_t Address, uint8_t * Array, size_t ArrayLength);
void		EEPROM_Erase(void);
void		EEPROM_Fill(uint8_t Pattern);


#endif /* EEPROM_H_ */
