#ifndef _EQUALCOMMAND_
#define _EQUALCOMMAND_

#include "Command.hpp"
#include "..\BaseTypes\Bool.hpp"


class EqualCommand : public Command {
public:
	EqualCommand( ) {}
	virtual ~EqualCommand() { 
	}
	
	virtual void execute( MemoryInterface *global ) {
		Object *first  = global->top( );
		global->pop();
		Object *second = global->top( );
		global->pop();
		
		global->push( new Bool( first->equal( second ) ) );
	}
};

#endif // _EQUALCOMMAND_