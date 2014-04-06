#ifndef _RUNSUBROUTINECOMMAND_
#define _RUNSUBROUTINECOMMAND_

#include "Command.hpp"


class RunSubroutineCommand : public Command {
public:
	RunSubroutineCommand( ) {}
	virtual ~RunSubroutineCommand() { 
	}
	
	virtual void execute( StackInterface *global ) {
		Object *subObject = global->top( );
		global->pop();
		
		SubroutineCommand *sub = dynamic_cast<SubroutineCommand*>( subObject );
		if ( 0 == sub ) {
			throw 0;
		}
		
		sub->run( global );
	}
};

#endif // _RUNSUBROUTINECOMMAND_