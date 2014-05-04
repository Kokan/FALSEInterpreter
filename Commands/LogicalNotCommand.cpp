#include "LogicalNotCommand.hpp"
#include "../BaseTypes/Bool.hpp"

#include <stdexcept>

LogicalNotCommand::LogicalNotCommand( ) {
}

LogicalNotCommand::~LogicalNotCommand() { 
}

void LogicalNotCommand::execute( MemoryInterface *global ) {
	Object *object  = global->top( );
	global->pop();
	
	Bool *boolvalue = dynamic_cast<Bool*>(object);
	if ( 0 == boolvalue ) {
		throw std::runtime_error("LogicalNotCommand expecting Bool value.");
	}
	
	global->push( new Bool( !boolvalue->get() ) );
}