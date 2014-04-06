#ifndef _PRINTASINTEGERCOMMAND_
#define _PRINTASINTEGERCOMMAND_

#include "Command.hpp"

class PrintAsIntegerCommand : public Command {
public:
	PrintAsIntegerCommand( ) {}
	virtual ~PrintAsIntegerCommand() { 
	}
	
	virtual void execute( MemoryInterface *global ) {
		Object *obj  = global->top( );
		
		std::cout << obj->toString();
	}
};

#endif // _PRINTASINTEGERCOMMAND_