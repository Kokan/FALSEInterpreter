#ifndef _GET_VARIABLE_COMMAND_
#define _GET_VARIABLE_COMMAND_

#include "Command.hpp"


class GetVariableCommand : public Command {
public:
	GetVariableCommand( const std::string &varName );
	virtual ~GetVariableCommand();
	
	virtual void execute( MemoryInterface *global );
private:
	const std::string variableName;
};

#endif // _GET_VARIABLE_COMMAND_