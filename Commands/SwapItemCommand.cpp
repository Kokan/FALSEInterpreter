#include "SwapItemCommand.hpp"

SwapItemCommand::SwapItemCommand( ) {
}

SwapItemCommand::~SwapItemCommand() { 
}
	
void SwapItemCommand::execute( MemoryInterface *global ) {
	Object *first  = global->top();
	global->pop();
	Object *second = global->top();
	global->pop();
	
	global->push( first );
	global->push( second );
}