#ifndef _GET_VARIABLE_COMMAND_
#define _GET_VARIABLE_COMMAND_

#include "Command.hpp"


class GetVariableCommand : public Command {
public:
	GetVariableCommand( const std::string &varName ) : variableName( varName ) {}
	virtual ~GetVariableCommand() { 
	}
	
	virtual void execute( MemoryInterface *global ) {
		Object *value = global->get( variableName );
		
		if ( nullptr == value ) {
			throw std::runtime_error( "Variable not exists." );
		}
		
		global->push( value );
	}
private:
	const std::string variableName;
};

#endif // _GET_VARIABLE_COMMAND_