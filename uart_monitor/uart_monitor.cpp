#if COMPONENT_UART_MONITOR

#include "uart_monitor.h"


// Initialize
void UartMonitor_Init(void) {
	TaskAddMs(UartMonitor_Task, UART_MONITOR_READ_PERIOD);
}


// System task to periodically check if something is in UART buffer and display it
task_t UartMonitor_Task(runmode_t RunMode) {
	
	// Variables
	static uint8_t PrevoiusCount = 0;
	
	// Normal execution
	if(RunMode == Run) {
		uint8_t BufferCount = Uart_ReceivedCnt(&UART_MONITOR_PERIPHERAL);
		
		if(PrevoiusCount != BufferCount) {
			PrevoiusCount = BufferCount;
			return TaskOK;
		}
		else {
			if(BufferCount != 0) {
				// Copy to temporaty buffer
				uint8_t Buffer[UART_RX_BUFFER_LENGTH];
				for(uint8_t i=0; i<BufferCount; i++) {
					Buffer[i] = Uart_Read(&UART_MONITOR_PERIPHERAL);
				}
				
				// Display result
				Print_Format(ForegroundMagentaBright);
				Print("\r\nUART Rx[");
				Print_Dec(BufferCount);
				Print("]: ");
				
				// Display buffer as HEX
				Print_Format(ForegroundMagenta);
				for(uint8_t i=0; i<BufferCount; i++) {
					Print_Hex(Buffer[i], ' ');
				}
				
				// Display buffer as ASCII
				Print_Format(ForegroundCyan);
				for(uint8_t i=0; i<BufferCount; i++) {
					if(Buffer[i] >= ' ' && Buffer[i] <= '~') {
						Print(Buffer[i]);
					}
					else {
						Print(255);
					}
				}
				PrevoiusCount = 0;
				
				Console_PromptShow();
			}
		}
	}
	
	// Constructor
	else if(RunMode == FirstRun) {
		Uart_RxBufferFlush(&UART_MONITOR_PERIPHERAL);
	}
	
	// Destructor
	else if(RunMode == Close) {
		
	}
	
	// Identification
	#if OS_USE_TASK_IDENTIFY
	else if(RunMode == Identify) {
		Print("UartMonitor");
	}
	#endif
	
	return TaskOK;
}


// Send data via UART
void UartMonitor_CmdSend(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("uart txt [a/h]");
		#endif
		return;
	}
	
	// Argument 2 - input type Ascii or Hex
	Parse_t (*ParserPointer)(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength, const uint8_t MinLength);
	if(argv[2]) {
		if(*argv[2] == 'h') {
			ParserPointer = Parse_HexString;
		}
		else {
			ParserPointer = Parse_AsciiString;
		}
	}
	else {
		ParserPointer = Parse_AsciiString;
	}
	
	// Argument 1 - data to write in format apecified in argument 1
	uint8_t Buffer[128];
	uint8_t BufferLength;
	if(ParserPointer(argv[1], Buffer, &BufferLength, sizeof(Buffer), 1)) return;
	
	if(ParserPointer == Parse_AsciiString) {
		Buffer[BufferLength-1] = CR;
		Buffer[BufferLength] = LF;
		BufferLength++;
	}
	
	// Print data to send
	Print_Format(ForegroundWhiteBright);
	Print("UART_Tx[");
	Print_Dec(BufferLength);
	Print("]: ");
	Print_Format(FormatReset);
	Print_HexString(Buffer, BufferLength, ' ');
	
	// Exectue command
	for(uint8_t i=0; i<BufferLength; i++) {
		Uart_Write(Buffer[i], &UART_MONITOR_PERIPHERAL);
	}
}


#endif