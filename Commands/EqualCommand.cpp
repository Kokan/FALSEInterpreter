#include "EqualCommand.hpp"
#include "..\BaseTypes\Bool.hpp"


EqualCommand::EqualCommand( ) {
}

EqualCommand::~EqualCommand() { 
}
	
void EqualCommand::execute( MemoryInterface *global ) {
	Object *first  = global->top( );
	global->pop();
	Object *second = global->top( );
	global->pop();
	
	global->push( new Bool( first->equal( second ) ) );
}