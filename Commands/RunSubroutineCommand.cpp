#include "RunSubroutineCommand.hpp"
#include "SubroutineCommand.hpp"

#include <stdexcept>


RunSubroutineCommand::RunSubroutineCommand( ) {
}

RunSubroutineCommand::~RunSubroutineCommand() { 
}

void RunSubroutineCommand::execute( MemoryInterface *global ) {
	Object *subObject = global->top( );
	global->pop();
	
	SubroutineCommand *sub = dynamic_cast<SubroutineCommand*>( subObject );
	if ( 0 == sub ) {
		throw std::runtime_error("RunSubroutine expecting subroutine.");
	}
	
	sub->run( global );
}