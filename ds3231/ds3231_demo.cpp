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




#endif
#endif
