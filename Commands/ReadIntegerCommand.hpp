#ifndef _READINTEGERCOMMAND_
#define _READINTEGERCOMMAND_

#include "Command.hpp"

class ReadIntegerCommand : public Command {
public:
	ReadIntegerCommand( );
	virtual ~ReadIntegerCommand();
	
	virtual void execute( MemoryInterface *global );
};

#endif // _READINTEGERCOMMAND_