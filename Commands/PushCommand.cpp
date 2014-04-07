#include "PushCommand.hpp"


PushCommand::PushCommand( Object *link )
: obj( link ) {
	if ( 0 == obj ) {
		throw NullPointerException();
	}
}

PushCommand::~PushCommand() {
	obj = 0;
}

void PushCommand::execute( MemoryInterface *global ) {
	global->push( obj );
}