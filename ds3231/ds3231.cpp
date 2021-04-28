// Version 2.0.0

#if COMPONENT_DS3231

#include "ds3231.h"


// Init
void DS3231_Init(void) {
	
	#if DS3231_SYNC_SYSTEM_TIME
		time_t Time;
		if(DS3231_Read(&Time) == DS3231_OK) {
			Os_Time = Time;
		}
	#endif
	
	return;
}


// Read time
DS3231_t DS3231_Read(time_t * Time) {
	
	// Read data
	uint8_t Buffer[7];
	if(I2C_Start(DS3231_ADDRESS_WRITE)) {
		I2C_Stop();
		return DS3231_Error;
	}
	
	// Register address
	if(I2C_Write(0x00)) {
		I2C_Stop();
		return DS3231_Error;
	}
	
	if(I2C_Start(DS3231_ADDRESS_READ)) {
		I2C_Stop();
		return DS3231_Error;
	}
	
	for(uint8_t i = 0; i < sizeof(Buffer); i++) {
		Buffer[i] = I2C_Read();
	}
	
	I2C_Stop();
	
	// Parse result
	uint8_t DateAsNumbers[6];
	uint8_t DateAsNumbersIndex = 0;
	for(uint8_t i=0; i<sizeof(Buffer); i++) {
		uint8_t Temp = Buffer[i];
		DateAsNumbers[DateAsNumbersIndex++] = ((Temp & 0xF0) >> 4) * 10 + (Temp & 0x0F);
		if(i==2) {
			i++;
		}
	}
	
	// Calculate time
	tm NewTime;
	NewTime.tm_year		= DateAsNumbers[5] + 100;
	NewTime.tm_mon		= DateAsNumbers[4] - 1;
	NewTime.tm_mday		= DateAsNumbers[3];
	NewTime.tm_hour		= DateAsNumbers[2];
	NewTime.tm_min		= DateAsNumbers[1];
	NewTime.tm_sec		= DateAsNumbers[0];
	*Time = mk_gmtime(&NewTime);
	
	return DS3231_OK;
}

// Write time
DS3231_t DS3231_Write(time_t * Time) {
	
	tm TimeStruct;
	if(*Time == 0xFFFFFFFF) *Time = 0;
	gmtime_r(Time, &TimeStruct);
	
	uint8_t DateAsNumbers[7];
	DateAsNumbers[0] = TimeStruct.tm_sec;
	DateAsNumbers[1] = TimeStruct.tm_min;
	DateAsNumbers[2] = TimeStruct.tm_hour;
	DateAsNumbers[3] = TimeStruct.tm_wday;
	DateAsNumbers[4] = TimeStruct.tm_mday;
	DateAsNumbers[5] = TimeStruct.tm_mon + 1;
	DateAsNumbers[6] = TimeStruct.tm_year - 100;
	
	uint8_t Buffer[8];
	Buffer[0] = 0x00;
	for(uint8_t i = 0; i < sizeof(DateAsNumbers); i++) {
		uint8_t NibbleL = (DateAsNumbers[i] % 10);
		uint8_t NibbleH = ((DateAsNumbers[i] - NibbleL)/10);
		Buffer[i+1] = (NibbleH << 4) | NibbleL;
	}
	
	DS3231_t Result = DS3231_OK;
	
	if(I2C_Start(DS3231_ADDRESS_WRITE)) {
		Result = DS3231_Error;
		goto Stop;
	}
	
	for(uint8_t i = 0; i< sizeof(Buffer); i++) {
		if(I2C_Write(Buffer[i])) {
			Result = DS3231_Error;
			goto Stop;
		}
	}
	
	Stop:
	I2C_Stop();
	return Result;
}




#endif
