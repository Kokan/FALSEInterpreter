#ifndef _NEGATION_COMMAND_
#define _NEGATION_COMMAND_

#include <stdexcept>

#include "Command.hpp"

#include "../BaseTypes/Object.hpp"

class NegationCommand : public Command {
public:
	NegationCommand( );
	virtual ~NegationCommand();
	
	virtual void execute( MemoryInterface *global );
	
	Object* getArgument( );
	int getNumberValue( );
	
private:
	MemoryInterface *global;
};


#endif // _NEGATION_COMMAND_