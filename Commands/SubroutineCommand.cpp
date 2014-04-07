#include "SubroutineCommand.hpp"

#include <sstream>


SubroutineCommand::SubroutineCommand( ) {
}

SubroutineCommand::SubroutineCommand( const std::vector<Command*> &prg )
: code(prg) {
}

SubroutineCommand::~SubroutineCommand() { 
}

void SubroutineCommand::execute( MemoryInterface *global ) {
	global->push( this );
}
	
void SubroutineCommand::run( MemoryInterface *global ) {
	for( std::vector<Command*>::iterator command = code.begin(); command != code.end(); ++command ) {
		(*command)->execute( global );
	}
}
	
std::string SubroutineCommand::toString() const {
	return "subroutine";
}

Object* SubroutineCommand::clone() const {
	return new SubroutineCommand( code );
}

bool SubroutineCommand::equal(Object *o) const {
	SubroutineCommand *sub = dynamic_cast<SubroutineCommand*>(o);
	if ( 0 == sub ) {
		return false;
	}
	return false;
}