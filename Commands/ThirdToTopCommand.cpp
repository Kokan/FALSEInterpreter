#include "ThirdToTopCommand.hpp"

ThirdToTopCommand::ThirdToTopCommand( ) {
}

ThirdToTopCommand::~ThirdToTopCommand() { 
}
	
void ThirdToTopCommand::execute( MemoryInterface *global ) {
	Object *first  = global->top();
	global->pop();
	Object *second = global->top();
	global->pop();
	Object *third = global->top();
	global->pop();
	
	global->push( second );
	global->push( first );
	global->push( third );
}