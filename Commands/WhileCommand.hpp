#ifndef _WHILECOMMAND_
#define _WHILECOMMAND_

#include "Command.hpp"
#include "SubroutineCommand.hpp"


class WhileCommand : public Command {
public:
	WhileCommand( );
	virtual ~WhileCommand();
	
	virtual void execute( MemoryInterface *global );
	
	bool getConditionResult( MemoryInterface *global );
private:
	SubroutineCommand *condition;
	SubroutineCommand *body;
};

#endif // _WHILECOMMAND_