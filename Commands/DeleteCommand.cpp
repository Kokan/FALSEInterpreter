#include "DeleteCommand.hpp"

DeleteCommand::DeleteCommand( ) {
}

DeleteCommand::~DeleteCommand() { 
}

void DeleteCommand::execute( MemoryInterface *global ) {
	global->pop();
}