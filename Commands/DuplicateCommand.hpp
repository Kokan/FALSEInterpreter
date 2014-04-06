#ifndef _DUPLICATECOMMAND_
#define _DUPLICATECOMMAND_

#include <stdexcept>

#include "Command.hpp"


class DuplicateCommand : public Command {
public:
	DuplicateCommand( ) {}
	virtual ~DuplicateCommand() { 
	}
	
	virtual void execute( MemoryInterface *global ) {
		Object *object = global->top();
		
		global->push( object->clone() );
	}
};


#endif // _DUPLICATECOMMAND_