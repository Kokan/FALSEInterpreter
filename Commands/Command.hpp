#ifndef _COMMAND_
#define _COMMAND_

#include "..\StackInterface.hpp"


class Command {
public:
	Command() {}
	virtual ~Command() {}
	
	virtual void execute( StackInterface *global ) = 0;
};

#endif // _COMMAND_