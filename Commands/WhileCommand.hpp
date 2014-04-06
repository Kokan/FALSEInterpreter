#ifndef _WHILECOMMAND_
#define _WHILECOMMAND_

#include <stdexcept>

#include "Command.hpp"
#include "..\BaseTypes\Bool.hpp"
#include "SubroutineCommand.hpp"


class WhileCommand : public Command {
public:
	WhileCommand( ) {}
	virtual ~WhileCommand() {
		condition = 0;
		body      = 0;
	}
	
	virtual void execute( StackInterface *global ) {
		Object *conditionObject = global->top( );
		global->pop();
		Object *subObject = global->top();
		global->pop();
		
		condition = dynamic_cast<SubroutineCommand*>( conditionObject );
		if ( 0 == condition ) {
			throw std::runtime_error( "WhileCommand condition must be SubroutineCommand." );
		}
		
		body = dynamic_cast<SubroutineCommand*>( subObject );
		if ( 0 == body ) {
			throw std::runtime_error( "WhileCommand body must be SubroutineCommand." );
		}
		
		while ( getConditionResult(global) ) {
			body->run( global );
		}
	}
	
	bool getConditionResult( StackInterface *global ) {
		condition->run(global);
		
		Object *conditionResultObject = global->top();
		global->pop();
		
		Bool *conditionResult = dynamic_cast<Bool*>(conditionResultObject);
		if ( 0 == conditionResult ) {
			throw std::runtime_error( "WhileCommand condition subroutine must return with Bool." );
		}
		
		return conditionResult->get();
	}
private:
	SubroutineCommand *condition;
	SubroutineCommand *body;
};

#endif // _WHILECOMMAND_