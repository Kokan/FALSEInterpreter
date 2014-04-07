#ifndef _SWAPITEMCOMMAND_
#define _SWAPITEMCOMMAND_

#include "Command.hpp"


class SwapItemCommand : public Command {
public:
	SwapItemCommand( );
	virtual ~SwapItemCommand();
	
	virtual void execute( MemoryInterface *global );
};


#endif // _SWAPITEMCOMMAND_