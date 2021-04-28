#if COMPONENT_DS3231
#include "ds3231_demo.h"
#if DS3231_USE_DEMO_COMMANDS


// Debug errors
void DS3231_Debug(DS3231_t Result) {
	switch(Result) {
		case DS3231_OK:			Print_ResponseOK();			break;
		case DS3231_Error:		Print_ResponseError();		break;
	}
}


void DS3231_CmdRead(uint8_t argc, uint8_t * argv[]) {
	time_t Time;
	DS3231_t Result;
	Result = DS3231_Read(&Time);
	if(Result) {
		DS3231_Debug(Result);
		return;
	}
	Print_Time(&Time);
}


void DS3231_CmdWrite(uint8_t argc, uint8_t * argv[]) {
	time_t Time;
	if(Parse_Time(argv[1], &Time)) return;
	DS3231_Debug(DS3231_Write(&Time));
}


#endif
#endif
