#ifndef _DELETECOMMAND_
#define _DELETECOMMAND_

#include <stdexcept>

#include "Command.hpp"


class DeleteCommand : public Command {
public:
	DeleteCommand( ) {}
	virtual ~DeleteCommand() { 
	}
	
	virtual void execute( StackInterface *global ) {
		global->pop();
	}
};


#endif // _DELETECOMMAND_