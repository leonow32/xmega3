#ifndef CONSOLE_DEMO_H_
#define CONSOLE_DEMO_H_

// ========================================
// Includes
// ========================================

#if COMPONENT_CONSOLE
	#include	"../console/console.h"
#else
	#error		"This module requires CONSOLE component"
#endif

#if COMPONENT_PRINT
	#include	"../print/print.h"
#else
	#error		"This module requires PRINT component"
#endif

// ========================================
// Console Commands
// ========================================

#if CONSOLE_USE_DEMO_COMMANDS
	void		Console_CmdArgs(uint8_t argc, uint8_t * argv[]);
	void		Console_CmdEcho(uint8_t argc, uint8_t * argv[]);
	void		Console_CmdHex8(uint8_t argc, uint8_t * argv[]);
	void		Console_CmdHex16(uint8_t argc, uint8_t * argv[]);
	void		Console_CmdHex32(uint8_t argc, uint8_t * argv[]);
	void		Console_CmdDec8(uint8_t argc, uint8_t * argv[]);
	void		Console_CmdDec16(uint8_t argc, uint8_t * argv[]);
	void		Console_CmdDec32(uint8_t argc, uint8_t * argv[]);
	void		Console_CmdHexString(uint8_t argc, uint8_t * argv[]);
	void		Console_CmdAsciiString(uint8_t argc, uint8_t * argv[]);
	void		Console_CmdAsciiCharacter(uint8_t argc, uint8_t * argv[]);
#endif


#endif /* CONSOLE_DEMO_H_ */