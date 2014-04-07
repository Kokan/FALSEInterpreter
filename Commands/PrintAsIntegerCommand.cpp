#include "PrintAsIntegerCommand.hpp"

#include <iostream>


PrintAsIntegerCommand::PrintAsIntegerCommand( ) {
}

PrintAsIntegerCommand::~PrintAsIntegerCommand() { 
}
	
void PrintAsIntegerCommand::execute( MemoryInterface *global ) {
	Object *obj  = global->top( );
	global->pop();
	
	std::cout << obj->toString();
}