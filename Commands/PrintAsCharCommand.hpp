#ifndef _PrintAsCharCommand_
#define _PrintAsCharCommand_

#include "Command.hpp"

class PrintAsCharCommand : public Command {
public:
	PrintAsCharCommand( );
	virtual ~PrintAsCharCommand();
	
	virtual void execute( MemoryInterface *global );
};

#endif // _PrintAsCharCommand_