#ifndef _RUNSUBROUTINECOMMAND_
#define _RUNSUBROUTINECOMMAND_

#include <stdexcept>

#include "Command.hpp"

class RunSubroutineCommand : public Command {
public:
	RunSubroutineCommand( ) {}
	virtual ~RunSubroutineCommand() { 
	}
	
	virtual void execute( MemoryInterface *global ) {
		Object *subObject = global->top( );
		global->pop();
		
		SubroutineCommand *sub = dynamic_cast<SubroutineCommand*>( subObject );
		if ( 0 == sub ) {
			throw std::runtime_error("RunSubroutine expecting subroutine.");
		}
		
		sub->run( global );
	}
};

#endif // _RUNSUBROUTINECOMMAND_