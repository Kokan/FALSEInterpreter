#ifndef _DELETECOMMAND_
#define _DELETECOMMAND_

#include <stdexcept>

#include "Command.hpp"


class DeleteCommand : public Command {
public:
	DeleteCommand( );
	virtual ~DeleteCommand();
	
	virtual void execute( MemoryInterface *global );
};


#endif // _DELETECOMMAND_