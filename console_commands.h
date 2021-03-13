// Wersja 0.19


#ifndef CONSOLE_COMMANDS_H_
#define CONSOLE_COMMANDS_H_


#include	"console.h"

#if C_CONSOLE_DEMO
	#include	"console_demo.h"
	#include	"command_demo.h"
#endif

// Nag³ówki plików, których funkcje s¹ wywo³ywane przez wiersz poleceñ
#if C_UCOSMOS
	#include	"uCosmos.h"
#endif

#if C_I2C_MASTER
	#include	"i2c_master.h"
#endif

#if C_EEPROM_DEMO
	#include	"eeprom_demo.h"
#endif

#if C_PERIPHERALS
	#include	"peripherals.h"
#endif

#if C_ADC
 #include	"adc.h"
#endif

#if C_ATECC608
 #include	"atecc608_demo.h"
#endif

#if C_BOOT
 #include	"boot.h"
#endif

#if C_BUZZER
 #include	"buzzer.h"
#endif

#if C_CARDLIST
 #include	"cardlist.h"
#endif

#if C_CARDLIST_EXTERNAL
 #include	"cardlist_external.h"
#endif

#if C_EEPROM
 #include	"eeprom_demo.h"
#endif

#if C_FLASH
 #include	"flash_demo.h"
#endif

#if C_IO
 #include	"io.h"
#endif

#if C_LOCKDRV
 #include	"lockdrv.h"
#endif

#if C_LOG
 #include	"log.h"
#endif

#if C_PASSWORD
 #include	"password.h"
#endif

#if C_RN4870
 #include	"bluetooth_rn4870_demo.h"
#endif

#if C_SPIMEM
 #include	"spi_mem.h"
 #include	"spi_mem_demo.h"
#endif

#if C_SPI_FLASH
 #include	"spi_flash_demo.h"
#endif

#if C_RC
 #include	"rc522.h"
#endif

#if C_MR
 #include	"mr.h"
#endif

#if C_NDEF
 #include	"ndef.h"
#endif

#if C_RFID_NODE
 #include	"rfid_node.h"
#endif

#if C_RFID_MASTER
 #include	"rfid_master.h"
#endif

#if C_HALKO
 #include	"halko.h"
#endif

#if C_SAFCARD
 #include	"safcard_node.h"
#endif

#if C_WIFI
 #include	"wifi.h"
#endif


// Tablica wszystkich poleceñ obs³ugiwanych przez interpreter
const Console_NamePointer_t Console_CommandList[] = {
	
//	{"lr",				Test_LongReply},
//	{"echo",			DemoCmd_Echo},
		
// Systemowe
#if OS_TASK_MONITOR_USE
	{"`",				Os_Monitor},
#endif
	
#if CMD_USE_ALL
	{"all",				Console_ShowAllCommands},		
#endif

#if OS_USE_TIME_COMMAND && OS_USE_TIME
	{"time",			Os_TimePrint},
	//{"t",			Test_LongReply},
#endif	

#if OS_USE_TIMESET_COMMAND && OS_USE_TIME
	{"timeset",			Os_TimeSet},
#endif
	
	{"reset",			Os_ResetExecute},

#if OS_USE_WATCHDOG_DIS_COMMAND
//	{"wdt0",			Os_WatchdogDisable},
#endif

#if C_I2C_MASTER
	{"i2c-scan",		I2C_Scan},
#endif

#if C_ADC
	
	#if ADC_USE_CMD_ALL
	{"v",				ADC_CmdMeasureAll},
	#endif
	
	#if ADC_USE_VCPU
//	{"vcpu",			ADC_CmdMeasureCpuVoltage},
	#endif
	
	#if ADC_USE_TEMP
//	{"temp",			ADC_CmdMeasureTemperature},
	#endif
	
	#if B_HALKO_v100
//	{"vbat",			ADC_CmdMeasureBatteryVoltage},
//	{"vusb",			ADC_CmdMeasureUSBVoltage},
//	{"vdc",				ADC_CmdMeasureDCVoltage},
	#endif
	
#endif

#if B_HALKO_v100
	{"io",				Peripherals_IO},
#endif
	
// Testowe
// 	{"arg",			DemoCmd_ArgumentsShow},
// 	{"hex8",		DemoCmd_Hex8},
// 	{"hex16",		DemoCmd_Hex16},
// 	{"hex32",		DemoCmd_Hex32},
// 	{"hex64",		DemoCmd_Hex64},
// 	{"hexstr",		DemoCmd_HexString},
// 	{"dec8",		DemoCmd_Dec8},
// 	{"dec16",		DemoCmd_Dec16},
// 	{"dec32",		DemoCmd_Dec32},
// 	{"dec64",		DemoCmd_Dec64},
// 	{"hexstr2",		Uart_Demo_HEXstring},	
// 	{"arg",			ConsoleDemo_ArgumentsShow},
// 	{"i32",			DemoCmd_Int32},
	
//	{"e",			DemoCmd_Echo},
	
#if C_ATECC608 & 1
	{"serial",			ATECC608_Demo_SerialRead},
		
// 	{"sha",				ATECC608_Demo_SHA256},
// 	{"hmac",			ATECC608_Demo_HMAC}, 
// 	{"tkget",			ATECC608_Demo_TempKeyCheck},
// 	{"tkset",			ATECC608_Demo_TempKeySet},
// 	
 	{"rand",			ATECC608_Demo_Random},
// 	{"at-ver",			ATECC608_Demo_VersionRead},
// 	{"lockget",			ATECC608_Demo_LockGet},
// 	{"LOCKSET",			ATECC608_Demo_LockSet},
// 	{"selftest",		ATECC608_Demo_SelfTest},
// 	{"keysval",			ATECC608_Demo_KeysValidCheck},
// 	{"aes",				ATECC608_Demo_AES},
// 	{"conf",			ATECC608_Demo_ConfigRead},
//	{"confw",			ATECC608_Demo_ConfigWrite},
// 	{"counter",			ATECC608_Demo_Counter},
// 	
// 	{"readslots",		ATECC608_Demo_SlotReadAll},
// 	{"a-read",			ATECC608_Demo_Read},
// 	{"a-write",			ATECC608_Demo_Write},
//	{"a-writepriv",		ATECC608_Demo_WritePriv},
//	{"a-writepub",		ATECC608_Demo_WritePub},
// 	{"conf-tab",		ATECC608_Demo_DumpConfigToTable},
// 	{"conf-slots",		ATECC608_Demo_SlotKeyConfigShowList},
// 	
// 	{"cmd",				ATECC608_Demo_Command},
// 
// 	
// 	{"slotread",		ATECC608_Demo_SlotRead},
// 	{"slotclr",			ATECC608_Demo_SlotClear},
// 	{"slotclr?",		ATECC608_Demo_SlotClearCheck},
// 	{"slotconf",		ATECC608_Demo_SlotConfigShow},
// 
// 	{"a-sleep",			ATECC608_Demo_Sleep},
// 
// 	{"genkeypub",		ATECC608_Demo_GenKeyPublic},
// 	{"genkeypriv",		ATECC608_Demo_GenKeyPrivate},
// 	{"ecdh",			ATECC608_Demo_ECDH},
// 
// 	{"mdb",				ATECC608_Demo_MesDigBufSet},
// 	{"sign",			ATECC608_Demo_Sign},
// 	{"verify",			ATECC608_Demo_Verify},
// 
// 	{"mac",				ATECC608_Demo_GenerateMAC},
// 	{"checkmac",		ATECC608_Demo_CheckMAC},
// 
// 	{"xorb",			ATECC608_Demo_XorStringWithByte},
// 	{"xors",			ATECC608_Demo_XorStringWithString},
// 	{"base64e",			ATECC608_Demo_Base64Encode},
// 	{"base64d",			ATECC608_Demo_Base64Decode},
// 	{"hash",			ATECC608_Demo_HashMemory},
#endif		
	
		
		
//	{"",		},
//	{"",		},
//	{"",		},
//	{"",		},
//	{"",		},
//	{"",		},
//	{"",		},
//	{"",		},
//	{"",		},
//	{"",		},
//	{"",		},
//	{"",		},
	
	
// Peripherals
#if C_BUZZER
	{"buzz",			Buzzer_Cmd},
//	{"buzzdemo",		Buzzer_Demo},
#endif

#if B_RPM_v005	
	{"ioset",			Peripherals_Demo_ioset},
	{"ioget",			Peripherals_Demo_ioget},
	{"power",			Peripherals_Demo_power},
#endif

#if B_AVRIOT
	
//	{"remote",			AVRIOT_CmdRemoteCommand},
//	{"test",			AVRIOT_Test},
		
// 	{"r-prompt",		RemoteDemo_GetPrompt},
// 	{"r-send",			RemoteDemo_SendCommand},
// 	{"r-status",		RemoteDemo_RemoteStatus},
// 	{"echo-loop",		RemoteDemo_CmdEchoLoop},
// 	{"echo-loop2",		RemoteDemo_EchoLoop2_Cmd},
// 	{"echo-loop3",		RemoteDemo_EchoLoop3},
// 		
// 	{"e8",				RemoteDemo_EchoHex8},
// 	{"e16",				RemoteDemo_EchoHex16},
// 	{"e32",				RemoteDemo_EchoHex32},
// 	{"es",				RemoteDemo_EchoHexStr},
//	{"r-resend",		Remote_Resend},


	{"led",				Peripherals_Demo_ioset},
	{"ioget",			Peripherals_Demo_ioget},
	
// 	{"uart-write",		Peripherals_Uart_Write},
// 	{"uart-read",		Peripherals_Uart_Read},
// 	{"uart-status",		Peripherals_Uart_Status},
// 	{"uart-clear",		Peripherals_Uart_Clear},
// 	{"uart-dis",		Peripherals_Uart_Disable},
// 	{"uart-en",			Peripherals_Uart_Enable},
#endif


// Sterownik zamka
#if C_LOCKDRV 

	#if LD_MASTER
	
// 	{"l-prompt",		LD_GetPrompt},
// 	{"l-send",			LD_SendCommand},
// 	{"l-status",		LD_RemoteStatus},

//	{"l-cfg",			LD_CmdConfig},
//	{"l-open",			LD_CmdOpen},
		
	#endif

	#if LD_SLAVE
	
	{"l-cfg",			LD_CmdConfig},
	{"l-open",			LD_CmdOpen},
	
	#endif
	
		
#endif	

// PIR
#if B_RPM_v005
	{"pir",				PIR_CmdPir},
#endif

// Oszczêdzanie energii
	//{"osslp",			Peripherals_OsSleepTest},
	//{"powerdown",		Peripherals_Demo_powerdown},

// Testowe z peripherals
#if B_XNANO
	{"e",				Peripherals_Echo},
	{"callback",		ConsoleDemo_CmdRemoteCommand},
#endif
	
	
// £adowarka baterii 
#if C_MCP73871
	{"b-stat",			Bat_CmdStatusPrint},
	{"charge",			Bat_ChargeSet},
	{"b-volt",			Power_MeasureBatVoltage},
		
	{"vcpu",			Power_CmdMeasureCpuVoltage},
	
	{"temp",			Power_CmdMeasureTemperature},
#endif


// BOOT
#if C_BOOT
	{"boot",			Boot_CmdUpdate},
#endif
			
			
// EEPROM
#if C_EEPROM
//	{"ee",				EEPROM_Demo_DumpEEPROM},
//  {"ee-w",			EEPROM_Demo_WriteByte},
//  {"ee-r",			EEPROM_Demo_ReadByte},
// 	{"ee-init",			EEPROM_Demo_Init},
// 	{"ee-crc",			EEPROM_Demo_CRC},
// 	{"ee-v",			EEPROM_Demo_Valid},
// 	{"ee-er",			EEPROM_Demo_Erase},
// 	{"ee-fill",			EEPROM_Demo_Fill},
#endif
		

// Flash
#if C_FLASH
	{"f-dump",			Flash_Demo_Dump},
//	{"f-status",		Flash_Demo_Status}, 
// 	{"f-bound",			Flash_Demo_PageBoundariesGet},
// 	{"f-cmd",			Flash_Demo_NvmCommand},
// 	{"f-wb",			Flash_Demo_WriteByte},
 //	{"f-wa",			Flash_Demo_WriteArray},
// 	{"f-er",			Flash_Demo_ErasePage},
// 	{"f-erb",			Flash_Demo_EraseBytes},  
// 	{"f-tp",			Flash_Demo_TestPattern},
#endif

// IO
#if C_IO & B_LOCK_v001
	{"io",				IO_CmdSet},
	{"sense",			IO_CmdPowerSense},
	{"sleep",			IO_CmdSleep},
#endif

// Card list
#if C_CARDLIST
	{"list-use",		CL_CmdUse},
	{"list-cnt",		CL_CmdCount},
	{"list-read",		CL_CmdRead},
	{"list-add",		CL_CmdAdd},
	//{"list-find",		CL_CmdFind},
	{"list-del",		CL_CmdDelete},
	{"list-delall",		CL_CmdDeleteAll},
#endif

// Card list na zewnêtrznej pamiêci Flash
#if C_CARDLIST_EXTERNAL
	{"list-use",		CLE_CmdUse},
	{"list-gfmp",		CLE_CmdGetFreeMemPointer},
	{"list-cnt",		CLE_CmdCount},
	{"list-read",		CLE_CmdListRead},
	{"list-find",		CLE_CmdFind},
	{"list-add",		CLE_CmdAdd},
	{"list-delall",		CLE_CmdDeleteAll},
#endif

// Password
#if C_PASSWORD
// 	{"pass-set",		Password_CmdSet},
// 	{"pass-auth",		Password_CmdAuth},
// 	{"pass-lock",		Password_CmdLock},
// 	{"pass-del",		Password_CmdDel},
	
//	{"pass-check",		Password_CmdCheck},
#endif


#if C_LOG		

	{"log",				Log_CmdRead},							// Odczytanie logu
//	{"log-cnt",			Log_CmdCount},							// Liczba wpisów w logu
	{"log-cfg",			Log_CmdExportTriggerConfig},
		
	{"log-exp",			Log_CmdExportStart},					// Rozpoczêcie eksportu logów, zwraca liczbê wpisów do odczytania
	{"log-get",			Log_CmdExportGet},						// Odczytanie pojedynczego wpisu z logu
	{"log-end",			Log_CmdExportEnd},						// Koniec eksportu
	{"log-fail",		Log_CmdExportFail},						// Nie uda³o siê wyeksportowaæ logów, ustaw wskaŸniki tak jak by³y wczeœniej
		
	#if LOG_DEBUG_COMMANDS_USE
	{"log-stat",		Log_CmdStatus},							// Debug
	{"log-zero",		Log_CmdZeroHeadTail},					// Debug
	{"log-dump",		Log_CmdDump},							// Debug
	{"log-add",			Log_CmdAdd},							// Debug	
	#endif
#endif

	
// Bluetooth
#if C_RN4870
// 	{"btpower",			RN4870_Demo_Power},
// 	{"btcmd",			RN4870_Demo_CmdEnter},
// 	{"bt",				RN4870_Demo_CmdSend},
// 	{"btscript",		RN4870_Demo_CmdScript},
// 	{"doorlock",		RN4870_Demo_DoorLock},
// 	{"relaya",			RN4870_Demo_RelayA},
// 	{"relayb",			RN4870_Demo_RelayB},
#endif


// SpiMem
#if C_SPIMEM
	{"smdump",			SpiMem_Demo_Dump},
#endif

// SpiFlash
#if C_SPI_FLASH
	{"F-id",			SpiFlash_Demo_IdRead},
	{"F-wren",			SpiFlash_Demo_WREN},
	{"F-rs",			SpiFlash_Demo_StatusRead},
	{"F-ws",			SpiFlash_Demo_StatusWrite},	
		
	{"F-rb",			SpiFlash_Demo_ReadByte},
	{"F-ra",			SpiFlash_Demo_ReadArray},
		
	{"F-wb",			SpiFlash_Demo_WriteByte},
	{"F-wa",			SpiFlash_Demo_WriteArray},
		
	{"F-es",			SpiFlash_Demo_EraseSector},
	{"F-dump",			SpiFlash_Demo_Dump},
#endif


// RFID Node
#if C_RFID_NODE
	{"rcv",				RfidNode_Version},
	{"listr",			RfidNode_ListRead},
	{"lista",			RfidNode_ListAdd},
	{"list0",			RfidNode_ListClear},
#endif		


// RFID Master
#if C_RFID_MASTER	
	{"rfman",			RPM_CmdRFManager},
	
	{"r-prompt",		RFID_GetPrompt},
	{"r-send",			RFID_SendCommand},
 	{"r-status",		RFID_RemoteStatus},
	
// 	{"r-clear",			RPM_RemoteBufferClear},
// 	{"r-print",			RPM_RemoteBufferPrint},
// 	{"r-s",				RPM_RemoteBufferAppendString},
// 	{"r-d",				RPM_RemoteBufferAppendDec},
// 	{"r-h",				RPM_RemoteBufferAppendHex8},
// 	{"r-hs",			RPM_RemoteBufferAppendHexString},
	
	{"scantime",		RPM_CmdScanTime},
	{"card",			RPM_CmdCard},
	
	
	
	//{"conf-ready",		WIFI_CmdConfReady},
	

	
	//{"time-error",		RPM_CmdTimeError},		// Wysy³ane z SAMW
	
	//{"wifi-error",		RPM_CmdTimeError},		// Wysy³ane z SAMW
		
//	{"rfid-add",		RPM_ListAdd},
		
//	{"rfid-sync-cfg",	RPM_Sync_ConfigCmd},
		
	//{"rfid-log-cnt",	RPM_Test_LogCnt},
		
	
		
	// Polecenia otrzymywane z p³ytki RFID
//	{"log-cnt",			RPM_Test_LogCnt},
	
	
	
	// Konfiguracja
//	{"config-start",	RPM_CmdConfigStart},
	{"conf-ready",		RPM_CmdConfigReady},

	// Œci¹ganie czasu
//	{"time-start",		RPM_CmdTimeStart},			// Wysy³ane z MIFARE v002
	{"w-time",			RPM_CmdWTime},				// Czas z WIFI
	
	// Eksport logów
	{"log-ready",		RPM_CmdLogReady},
	{"log-a",			RPM_CmdLogA},
	{"log-x",			RPM_CmdLogX},
		
	// Œci¹ganie listy kart z serwera
	{"list-ready",		RPM_CmdListReady},
		
	// Pomiar RSSI
	{"w-rssi",			RPM_CmdWRssi},
		
	{"r-ready",			RPM_CmdRReady},
		
	// Testowe
	{"4812to4710",		UID_CmdConvert4812to4710},
	{"4710to4812",		UID_CmdConvert4710to4812},
		
	// Obs³uga p³ytki RFID
	{"r-on",			RFID_CmdPowerOn},
	{"r-off",			RFID_CmdPowerOff},
		
#endif

// HALKO Reader
#if C_HALKO
	{"h",				HALKO_CmdHalkoManager},
	
	#if V_HALKO_RFID
	{"spi1",			HALKO_SpiOn},
	{"spi0",			HALKO_SpiOff},
	#endif
	
	// Polecenia wspólne
	{"conf-init",		HALKO_CmdConfigInit},				// SAM inicjalizuje konfiguracjê przez hotspot
	{"conf-ready",		HALKO_CmdConfigReady},				// Potwierdzenie konfiguracji z SAM		
	{"sam-ready",		HALKO_CmdSamReady},					// Gotoœæ SAM do komunikacji przez konsolê
		
	// Polecenia przysy³ane przez WIFI - dotyczy RFI
	#if V_HALKO_RFID
	{"w-time",			HALKO_CmdWTime},					// Czas œci¹gniêty z serwera
	{"w-rssi",			HALKO_CmdWRssi},					// Wynik pomiaru RSSI
	{"conf-ready",		HALKO_CmdConfigReady},				// Potwierdzenie konfiguracji z WIFI
	{"list-ready",		HALKO_CmdListReady},				// Potwierdzenie gotowoœci do œci¹gniêcia listy przez WIFI
	{"log-ready",		HALKO_CmdLogReady},					// Potwierdzenie gotowoœci do wys³ania logów na serwer
	{"log-a",			HALKO_CmdLogA},						// Koniec eksportu logów
	{"log-x",			HALKO_CmdLogX},						// B³¹d podczas eksportu logu
	#endif
		
	// Polecenia przysy³ane przez WIFI - Smart Storage
	#if V_HALKO_SS
	{"dooropen",		HALKO_CmdDoorOpen},					// Wysy³ane z SAM w momencie otrzymania polecenia z serwera przez MQTT
	{"mqtt-ready",		HALKO_CmdMqttReady},				// Gotowe po³¹czenie z AWS, start raportów i miganie zielonymi diodami
	{"w-error",			HALKO_CmdError},					// B³¹d WIFI
	#endif
#endif

// MRUSB MIFARE Reader USB/RS232
#if C_MR	
	
	// !! testowe, póŸniej skasowaæ
// 	{"rci",				MR_RC_Init},
// 	{"r-dump",			RC_DebugRegisterDump},
// 	{"r-r",				RC_DebugRegisterRead},
// 	{"r-w",				RC_DebugRegisterWrite},
 	{"picc",			MR_CmdRCPICC},					
		
//	{"sysinfo",			MR_SystemInfo},
//	{"ver",				MR_CmdVer},
	
	{"autoscan",		MR_CmdAutoScanning},
	
	#if MR_CONF_CMD_USE
	{"conf-y",			MR_CmdConfY},
	{"conf-g",			MR_CmrConfG},
	{"conf-r",			MR_CmdConfR},
	{"conf-b",			MR_CmdConfB},
	{"conf-o",			MR_CmdConfO},
	{"conf-n",			MR_CmdConfN},
	{"description",		MR_CmdDescription},
	#endif
	
	#if MR_UID_FORMATS_CMD_USE
	{"uid-format",		MR_CmdUidFormat},
	{"uid-hexspaces",	MR_CmdUidHexSpaces},	
	{"uid-order",		MR_CmdUidOrder},
	#endif
		
	{"led",				MR_CmdLed},
	
	#if B_MRUSB_v100
	{"io",				MR_CmdIO},
	#endif
				
	{"period",			MR_CmdPeriod},
	{"scanning",		MR_CmdScanning},
	
	{"ant",				MR_CmdAntenna},
	{"pcdver",			MR_CmdVersionPCD},
		
	#if C_MR == 1
	{"gain",			MR_CmdGain},
	{"stop",			MR_CmdStopCrypto1},
	{"reqa",			MR_CmdREQA},
	{"wupa",			MR_CmdWUPA},
	{"cl",				MR_CmdCLx},
	{"sel",				MR_CmdSELx},
	{"raw",				MR_CmdRAW},
	{"raw7",			MR_CmdRAW7},
	{"halt",			MR_CmdHALT},	
	{"xor",				MR_CmdXOR},
	{"crc",				MR_CmdCRC},
	#endif
		
	{"uid",				MR_CmdUid},
	
	#if MR_TYPE_CMD_USE
	{"type",			MR_CmdType},
	#endif

	#if C_MR == 1
	{".read",			MR_PiccCmdRead},					// !! nowe
	{".write",			MR_PiccCmdWrite},					// !! nowe
	{".cwrite",			MR_PiccCmdCompWrite},				// !! nowe
	{".getver",			MR_PiccCmdGetVersion},				// !! nowe
	#endif
	
	#if C_MR == 1
	{"vget",			MR_CmdClassicValueGet},				
	{"vset",			MR_CmdClassicValueSet},				
	{"vinc",			MR_CmdClassicValueIncrement},		
	{"vdec",			MR_CmdClassicValueDecrement},	
	#endif
	
	#if C_MR == 1
	{"bd",				MR_CmdBackdoor},				// !!@ nowe	
	{"bdt",				MR_BackdoorTest},
	{"bdr",				MR_CmdBackdoorClassicRepair},
	#endif
	
//	{"u-setkey",		MR_CmdNtagKeyConfigure},
//	{"fread",			MR_CmdUltralightFastRead},			// !!
//	{"u-writeb",		MR_CmdUltralightWriteBocks},		// !! nowe
	{"erase",			MR_CmdAutoEraseMem},				// !! nowe
	
//	{"read",			MR_CmdAutoRead},
//	{"write",			MR_CmdAutoWrite},
	{"dump",			MR_CmdAutoDump},
	{"auth",			MR_CmdAutoAuth},
//	{"key",				MR_CmdAutoSetKey},
	{"cnt",				MR_CmdUltralightCounterRead},
		
	#if MR_ULNTAG_BRUTE_FORCE_USE
	{"brute",			MR_CmdUltralightAuthBruteForce},
	#endif
				
	//{"test",			MR_CmdProductionTest},
		
	#if 0
	{"m-prompt",		MR_GetPrompt},
	{"m-send",			MR_SendCommand},	
	{"m-status",		MR_RemoteStatus},
	{"m-clear",			MR_RemoteBufferClear},
	{"m-print",			MR_RemoteBufferPrint},
	#endif
#endif


// NDEF
#if C_NDEF
	
	// Debugowe
	{"n-used",			NDEF_CmdMemoryUsed},
//	{"n-cnt",			NDEF_CmdRecordCount},
//	{"n-type",			NDEF_CmdRecordGetType},
//	{"n-len",			NDEF_CmdRecordLength},
//	{"n-find",			NDEF_CmdRecordFindByType},
//	{"n-fill",			NDEF_TestWrite},					// Zapis wszystkich stron pamiêci podanym bajtem	
		
	// U¿ytkowe
	{"n-load",			NDEF_CmdBufferLoadNTAG216},			// Odczyt metod¹ fastread tylko NTAG216
	{"n-save",			NDEF_CmdBufferSaveNTAG216},			// Zapis bufora RAM na kartê NTAG216 przy pomocy tasków
	{"n-show",			NDEF_CmdShowAllRecords},			// Wyœwietlenie wszystkich rekordów
	{"n-dump",			NDEF_CmdBufferDump},				// Wyœwietlenie bufora RAM i tablicy rekordów
	
	{"n-add",			NDEF_CmdRecordAdd},
	{"n-del",			NDEF_CmdRecordDelete},
	{"n-clear",			NDEF_CmdBufferClear},
	
	// Bezpieczeñstwo
	#if NDEF_USE_AES || NDEF_USE_HMAC
	{"n-seclev",		NDEF_CmdSecurityLevelRead},
	#endif
	
	#if NDEF_USE_AES
//	{"n-aes-set",		NDEF_CmdKeyAESset},
//	{"n-aes-get",		NDEF_CmdKeyAESget},
//	{"n-encrypt",		NDEF_CmdBufferEncrypt},
//	{"n-decrypt",		NDEF_CmdBufferDecrypt},
	#endif
	
	#if NDEF_USE_HMAC
//	{"n-hmac-set",		NDEF_CmdKeyHMACset},
//	{"n-hmac-get",		NDEF_CmdKeyHMACget},
	{"n-keygen",		NDEF_CmdPasswordGenerate},
	#endif

#endif


// SAFCARD
#if C_SAFCARD
	{"id",				Safcard_CmdId},
//	{"s-adr",			Safcard_CmdFindFreeAddress},
//	{"s-ind",			Safcard_CmdFindFreeIndex},
//	{"s-timeread",		Safcard_CmdReadRelativeTimeFromCard},
//	{"s-logadd",		Safcard_CmdLogAdd},
//	{"s-logcnt",		Safcard_CmdLogCount},
	{"s-logclr",		Safcard_CmdLogClear},
	{"s-log",			Safcard_CmdLog},
	
	// Przepustki	
	{"s-add",			Safcard_CmdRecordPermitAdd},
	{"s-del",			Safcard_CmdRecordPermitDelete},
	{"s-val",			Safcard_CmdRecordPermitValidate},	
		
	// Rekordy konfiguracyjne
	{"s-time",			Safcard_CmdRecordTimeSave},
	{"s-login",			Safcard_CmdRecordLoginSave},
	{"s-name",			Safcard_CmdRecordNameSave},
	
	// Formatowanie SAFCARD
	{"s-blank",			Safcard_CmdConvertCardToSafcardBlank},	
	{"s-ready",			Safcard_CmdConvertCardToSafcardReady},		
	{"s-reset",			Safcard_CmdConvertCardToFactory},
//	{"s-s",				Safcard_CmdBlankCertiticate},
//	{"s-v",				Safcard_CmdCertificateVerify},
	
#endif


// WiFi SAMW25 z programem Safli
#if C_WIFI
//	{"w-power",			WIFI_CmdPower},
//	{"w",				WIFI_Echo},
//	{"w-init",			WIFI_CmdInit},
	
	#if B_RPMv005 || (B_HALKO_v100 && V_HALKO_RFID)
	{"w-error",			WIFI_CmdError},
	{"w-ready",			WIFI_CmdReady},
	#endif
		
	// Saflink
//	{"w-prompt",		WIFI_GetPrompt},
	{"w-send",			WIFI_SendCommand},
	{"w-status",		WIFI_RemoteStatus},
//	{"w-d",				WIFI_ConsoleDebug},
//	{"w",				WIFI_UartTest},
		
	// Manager zadañ
	//{"w-man",			WIFI_CmdManagerStart},
	{"w-on",			WIFI_PowerOn},
	{"w-off",			WIFI_PowerOff},
	//{"w-flags",			WIFI_CmdFlags},
	{"ws",				WIFI_CmdStatus},
		
	//{"wps-ready",		WIFI_CmdWpsReady},
	
	
		
	//{"w-pass",			WIFI_CmdSSIDPASS},
	//{"w-test",			WIFI_Test},
		
// 	{"wp1",				WIFI_TestPower1},
// 	{"wp0",				WIFI_TestPower0},
	{"wr1",				WIFI_TestReset1},
	{"wr0",				WIFI_TestReset0},
#endif


// Testowe

//	{"",		},
//	{"",		},
//	{"mr-init",			DummyInit},				// czy to jeszcze jest potrzebne?
	//{"q",				MR_Testq},
		
	//{"r-xor",			Remote_XOR},
	
	
	
	// CRC
	//{"crc",				Remote_CmdCRC},
	
	
};


#endif /* CONSOLE_COMMAN,DS_H_ */
