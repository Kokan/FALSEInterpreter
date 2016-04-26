#ifndef _IFCOMMAND_
#define _IFCOMMAND_

#include "Command.hpp"


class IFCommand : public Command {
public:
	IFCommand( );
	virtual ~IFCommand();
	
	virtual void execute( MemoryInterface *global );
};

#endif // _IFCOMMAND_