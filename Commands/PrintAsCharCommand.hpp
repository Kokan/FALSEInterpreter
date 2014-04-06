#ifndef _PrintAsCharCommand_
#define _PrintAsCharCommand_

#include <iostream>
#include <stdexcept>

#include "Command.hpp"
#include "..\BaseTypes\Integer.hpp"

class PrintAsCharCommand : public Command {
public:
	PrintAsCharCommand( ) {}
	virtual ~PrintAsCharCommand() { 
	}
	
	virtual void execute( MemoryInterface *global ) {
		Object *obj  = global->top( );
		
		Integer *number = dynamic_cast<Integer*>(obj);
		if ( 0 == number ) {
			throw std::runtime_error( "PrintAsCharCommand only supports Integer print." );
		}
		std::cout << (char)number->get();
	}
};

#endif // _PrintAsCharCommand_