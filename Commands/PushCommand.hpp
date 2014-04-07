#ifndef _PUSHCOMMAND_
#define _PUSHCOMMAND_

#include "Command.hpp"

class NullPointerException {};

class PushCommand : public Command {
public:
	PushCommand( Object *link );
	virtual ~PushCommand();
	
	virtual void execute( MemoryInterface *global );
	
private:
	Object *obj;
};


#endif // _PUSHCOMMAND_