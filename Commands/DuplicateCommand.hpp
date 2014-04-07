#ifndef _DUPLICATECOMMAND_
#define _DUPLICATECOMMAND_

#include "Command.hpp"


class DuplicateCommand : public Command {
public:
	DuplicateCommand( );
	virtual ~DuplicateCommand();
	
	virtual void execute( MemoryInterface *global );
};


#endif // _DUPLICATECOMMAND_