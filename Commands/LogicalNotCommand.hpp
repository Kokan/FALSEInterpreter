#ifndef _LOGICALNOTCOMMAND_
#define _LOGICALNOTCOMMAND_

#include "Command.hpp"
#include "..\BaseTypes\Bool.hpp"


class LogicalNotCommand : public Command {
public:
	LogicalNotCommand( );
	virtual ~LogicalNotCommand();
	
	virtual void execute( MemoryInterface *global );
};

#endif // _LOGICALNOTCOMMAND_