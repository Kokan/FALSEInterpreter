#include "DuplicateCommand.hpp"


DuplicateCommand::DuplicateCommand( ) {
}

DuplicateCommand::~DuplicateCommand() {
}

void DuplicateCommand::execute( MemoryInterface *global ) {
	Object *object = global->top();
	
	global->push( object->clone() );
}