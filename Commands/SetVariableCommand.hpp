#ifndef _SET_VARIABLE_COMMAND_
#define _SET_VARIABLE_COMMAND_

#include <stdexcept>
#include <algorithm>
#include <cctype>

#include "Command.hpp"

class SetVariableCommand : public Command {
public:
	SetVariableCommand( const std::string &varName ) : variableName( varName ) {}
	virtual ~SetVariableCommand() { 
	}
	
	virtual void execute( MemoryInterface *global ) {
		if ( !isValidName() ) {
			throw std::runtime_error("SetVariableCommand invalid variable name. Name must be '[a-z]+' .");
		}
		Object *value = global->top( );
		global->pop();
		
		global->set( variableName, value );
	}
private:
	bool isValidName( ) const {
		return std::all_of( variableName.begin(), variableName.end(), islower );
	}
	
	const std::string variableName;
};

#endif // _SET_VARIABLE_COMMAND_