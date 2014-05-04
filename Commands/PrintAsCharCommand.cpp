#include "PrintAsCharCommand.hpp"

#include <iostream>
#include <stdexcept>

#include "../BaseTypes/Integer.hpp"

PrintAsCharCommand::PrintAsCharCommand( ) {
}

PrintAsCharCommand::~PrintAsCharCommand() { 
}


void PrintAsCharCommand::execute( MemoryInterface *global ) {
	Object *obj  = global->top( );
	global->pop();
	
	Integer *number = dynamic_cast<Integer*>(obj);
	if ( 0 == number ) {
		throw std::runtime_error( "PrintAsCharCommand only supports Integer print." );
	}
	std::cout << (char)number->get();
}