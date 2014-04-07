#ifndef _RUNSUBROUTINECOMMAND_
#define _RUNSUBROUTINECOMMAND_

#include "Command.hpp"

class RunSubroutineCommand : public Command {
public:
	RunSubroutineCommand( );
	virtual ~RunSubroutineCommand();
	
	virtual void execute( MemoryInterface *global );
};

#endif // _RUNSUBROUTINECOMMAND_