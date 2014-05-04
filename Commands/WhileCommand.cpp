#include "WhileCommand.hpp"
#include "../BaseTypes/Bool.hpp"

#include <stdexcept>

WhileCommand::WhileCommand( ) {
}

WhileCommand::~WhileCommand() {
	condition = 0;
	body      = 0;
}
	
void WhileCommand::execute( MemoryInterface *global ) {
	Object *subObject = global->top();
	global->pop();
	Object *conditionObject = global->top( );
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
	
bool WhileCommand::getConditionResult( MemoryInterface *global ) {
	condition->run(global);
	
	Object *conditionResultObject = global->top();
	global->pop();
	
	Bool *conditionResult = dynamic_cast<Bool*>(conditionResultObject);
	if ( 0 == conditionResult ) {
		throw std::runtime_error( "WhileCommand condition subroutine must return with Bool." );
	}
	
	return conditionResult->get();
}