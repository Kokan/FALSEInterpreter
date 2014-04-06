#ifndef _PRINTASINTEGERCOMMAND_
#define _PRINTASINTEGERCOMMAND_

#include "Command.hpp"

class PrintAsIntegerCommand : public Command {
public:
	PrintAsIntegerCommand( ) {}
	virtual ~PrintAsIntegerCommand() { 
	}
	
	virtual void execute( StackInterface *global ) {
		Object *obj  = global->top( );
		
		std::cout << obj->toString() << std::endl;
	}
};

#endif // _PRINTASINTEGERCOMMAND_