#ifndef _COMMAND_
#define _COMMAND_

#include "../MemoryInterface.hpp"


class Command {
public:
	Command();
	virtual ~Command();
	
	virtual void execute( MemoryInterface *global ) = 0;
};

#endif // _COMMAND_