// Version 2.0.0

#if COMPONENT_MEM25

#include "mem25.h"

// Init chip select pin
void Mem25_Init(void) {
	MEM25_CHIP_DESELECT;
	MEM25_CS_INIT;
}

// 
void Mem25_Sleep(void) {
	// przed wejœciem w staaktualnie nie odbywa siê zapis do pamiêci przy pomocy Mem25_IsBusy() lub Mem25_WaitForReady()
	MEM25_CHIP_SELECT;
	Spi_1(MEM25_SLEEP);
	MEM25_CHIP_DESELECT;
}

void Mem25_Wake(void) {
	// po wybudzeniu czekaæ na gotowoœæ przy pomocy Mem25_WaitForReady()
	MEM25_CHIP_SELECT;
	Spi_1(MEM25_WAKE);
	MEM25_CHIP_DESELECT;
}

void Mem25_WriteEnable(void) {
	MEM25_CHIP_SELECT;
	Spi_1(MEM25_WRITE_ENABLE);
	MEM25_CHIP_DESELECT;
}

void Mem25_WriteDisble(void) {
	MEM25_CHIP_SELECT;
	Spi_1(MEM25_WRITE_DISABLE);
	MEM25_CHIP_DESELECT;
}

void Mem25_ChipErase(void) {
	// po skasowaniu scalaka czekaæ na gotowoœæ przy pomocy Mem25_WaitForReady()
	MEM25_CHIP_SELECT;
	Spi_1(MEM25_WRITE_ENABLE);
	MEM25_CHIP_DESELECT;
	
	MEM25_CHIP_SELECT;
	Spi_1(MEM25_ERASE_CHIP);
	MEM25_CHIP_DESELECT;
}

uint8_t Mem25_StatusRead(void) {
	uint8_t Status;
	MEM25_CHIP_SELECT;
	Status = Spi_2(MEM25_STATUS_READ, 0);
	MEM25_CHIP_DESELECT;
	return Status;
}

void Mem25_StatusWrite(uint8_t Status) {
	MEM25_CHIP_SELECT;
	Status = Spi_2(MEM25_STATUS_WRITE, Status);
	MEM25_CHIP_DESELECT;
}

bool Mem25_IsBusy(void) {
	uint8_t Status;
	MEM25_CHIP_SELECT;
	Status = Spi_2(MEM25_STATUS_READ, 0);
	MEM25_CHIP_DESELECT;
	return Status & 0b00000001;
}

void SpiFlash_WaitForReady(void) {
	MEM25_CHIP_SELECT;
	while(Spi_2(MEM25_STATUS_READ, 0) & 0b00000001);
	MEM25_CHIP_DESELECT;
}

uint8_t Mem25_Read(uint16_t Address) {
	uint8_t Data;
	MEM25_CHIP_SELECT;
	Data = Spi_4(MEM25_READ, (Address & 0xFF00) >> 8, Address & 0x00FF, 0);
	MEM25_CHIP_DESELECT;
	return Data;
}

void Mem25_Read(uint16_t Address, uint8_t * Buffer, uint16_t Length) {
	MEM25_CHIP_SELECT;
	Spi_3(MEM25_READ, (Address & 0xFF00) >> 8, Address & 0x00FF);
	Spi_Transmit(Buffer, Buffer, Length);
	MEM25_CHIP_DESELECT;
}

void Mem25_Write(uint16_t Address, uint8_t Byte) {
	// sprawdzanie czy pamiêæ jest gotowa do zapisu
	SpiFlash_WaitForReady();
	
	// Write enable latch
	Mem25_WriteEnable();
	
	// zapis w³aœciwy
	MEM25_CHIP_SELECT;
	Spi_4(MEM25_WRITE, (Address & 0xFF00) >> 8, Address & 0x00FF, Byte);
	MEM25_CHIP_DESELECT;
}

void Mem25_Write(uint16_t Address, const uint8_t * Buffer, uint16_t Length) {
	// Nie uwzglêdnia stronicowania pamiêci!!!
	
	// Sprawdzanie czy pamiêæ jest gotowa do zapisu
	SpiFlash_WaitForReady();
	
	// Write enable latch
	Mem25_WriteEnable();
	
	// Zapis w³aœciwy
	MEM25_CHIP_SELECT;
	Spi_3(MEM25_WRITE, (Address & 0xFF00) >> 8, Address & 0x00FF);
	//Spi_Stream(Buffer, Buffer, Length);
	Spi_Write(Buffer, Length);
	MEM25_CHIP_DESELECT;
}

void Mem25_WriteMultiPage(uint16_t Address, const uint8_t * Buffer, uint16_t Length) {
	uint16_t AddressEnd = Address + Length - 1;
	uint16_t PageStart = Address / MEM25_PAGE_SIZE;
	uint16_t PageEnd = AddressEnd / MEM25_PAGE_SIZE;
	uint16_t ActualPage = PageStart;
	uint16_t ActualPageEnd;
	uint16_t ActualStart = Address;
	uint16_t ActualEnd;
	uint16_t ActualLength;
	
	// pêtla obejmuj¹ca wszystkie wyliczone strony
	while(ActualPage <= PageEnd) {
		
		// wyznaczenie adresu koñca, czy do koñca strony czy do koñca transakcji, jeœli koniec transakcji jest mniejszy ni¿ koniec strony
		ActualPageEnd = MEM25_PAGE_SIZE * (ActualPage+1) - 1;
		if(AddressEnd <= ActualPageEnd) {
			// koniec transakcji jest na tej stronie
			ActualEnd = AddressEnd;
			} 
			else {
			// Koniec transakcji jest póŸniej
			ActualEnd = ActualPageEnd;
		}
		ActualLength = ActualEnd - ActualStart + 1;
		
		// zapis do pamiêci
		Mem25_Write(ActualStart, Buffer, ActualLength);
		Buffer = Buffer + ActualLength;
		
		// zwiêkszenie wskaŸników
		ActualPage++;
		ActualStart = ActualEnd + 1;
	}
}

#if MEM25_INCLUDE_DUMP
void Mem25_Dump(uint16_t Start, uint16_t Length) {
	
	uint8_t Buffer[16];
	
	uint16_t i = Start & 0xFFF0;
	
	// rozpoczêcie transmisji
	MEM25_CHIP_SELECT;
	Spi_3(MEM25_READ, (i & 0xFF00) >> 8, i & 0x00FF);
	
	// wyœwietlenie nag³ówka
	Print("\n\rADDR:  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F");
	
	do {
		// odczytanie 16 bajtów
		Spi_Transmit(Buffer, Buffer, 16);
		
		// Przejœcie do nowej linii
		Print_NL();
		
		// wyœwietlenie adresu
		Print_Hex(i, ':');
		Print(' ');
		
		// wyœwietlenie HEX
		for(uint8_t h=0; h<=15; h++) {
			Print_Hex(*(Buffer+h), ' ');
		}
		
		// wyœwietlenie ASCII
		for(uint8_t h=0; h<=15; h++) {
			if((*(Buffer+h) >= ' ') && (*(Buffer+h) < 127)) {			// omijanie znaków specjanych <32 i <127
				Uart_Write(*(Buffer+h));
			} 
			else {
				Uart_Write(' ');
			}
		}
		
		// inkrementacja adresu
		i += 16;
	} while(i <= Start+Length-1 && i != 0);		// i != 0 zabezpiecza przed przekrêceniem sie licznika po 0xFFFF
	
	MEM25_CHIP_DESELECT;
}

#endif

#endif 