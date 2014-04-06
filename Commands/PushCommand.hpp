#ifndef _PUSHCOMMAND_
#define _PUSHCOMMAND_

#include "Command.hpp"

class NullPointerException {};

class PushCommand : public Command {
public:
	PushCommand( Object *link )
	: obj( link )
	{
		if ( 0 == obj ) {
			throw NullPointerException();
		}
	}
	virtual ~PushCommand() { obj = 0;}
	
	virtual void execute( MemoryInterface *global ) {
		global->push( obj );
	}
	
private:
	Object *obj;
};


#endif // _PUSHCOMMAND_