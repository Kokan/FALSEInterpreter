#ifndef _SET_VARIABLE_COMMAND_
#define _SET_VARIABLE_COMMAND_

#include "Command.hpp"


class SetVariableCommand : public Command {
public:
	SetVariableCommand( const std::string &varName ) : variableName( varName ) {}
	virtual ~SetVariableCommand() { 
	}
	
	virtual void execute( MemoryInterface *global ) {
		Object *value = global->top( );
		global->pop();
		
		global->set( variableName, value );
	}
private:
	const std::string variableName;
};

#endif // _SET_VARIABLE_COMMAND_