#ifndef _EQUALCOMMAND_
#define _EQUALCOMMAND_

#include "Command.hpp"

class EqualCommand : public Command {
public:
	EqualCommand( );
	virtual ~EqualCommand();
	
	virtual void execute( MemoryInterface *global );
};

#endif // _EQUALCOMMAND_