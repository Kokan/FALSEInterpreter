#include "ReadIntegerCommand.hpp"
#include "../BaseTypes/Integer.hpp"

#include <iostream>


ReadIntegerCommand::ReadIntegerCommand( ) {
}

ReadIntegerCommand::~ReadIntegerCommand() { 
}

void ReadIntegerCommand::execute( MemoryInterface *global ) {
	Object *obj  = new Integer((int)std::cin.get());
	global->push( obj );
}