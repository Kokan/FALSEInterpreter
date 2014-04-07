#ifndef _SET_VARIABLE_COMMAND_
#define _SET_VARIABLE_COMMAND_

#include "Command.hpp"

class SetVariableCommand : public Command {
public:
	SetVariableCommand( const std::string &varName );
	virtual ~SetVariableCommand();
	
	virtual void execute( MemoryInterface *global );
private:
	bool isValidName( ) const;
	
	const std::string variableName;
};

#endif // _SET_VARIABLE_COMMAND_