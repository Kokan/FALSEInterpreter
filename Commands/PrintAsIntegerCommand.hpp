#ifndef _PRINTASINTEGERCOMMAND_
#define _PRINTASINTEGERCOMMAND_

#include "Command.hpp"

class PrintAsIntegerCommand : public Command {
public:
	PrintAsIntegerCommand( );
	virtual ~PrintAsIntegerCommand();
	
	virtual void execute( MemoryInterface *global );
};

#endif // _PRINTASINTEGERCOMMAND_