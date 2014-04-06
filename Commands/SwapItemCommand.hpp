#ifndef _SWAPITEMCOMMAND_
#define _SWAPITEMCOMMAND_

#include "Command.hpp"


class SwapItemCommand : public Command {
public:
	SwapItemCommand( ) {}
	virtual ~SwapItemCommand() { 
	}
	
	virtual void execute( StackInterface *global ) {
		Object *first  = global->top();
		global->pop();
		Object *second = global->top();
		global->pop();
		
		global->push( first );
		global->push( second );
	}
};


#endif // _SWAPITEMCOMMAND_