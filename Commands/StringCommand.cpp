#include "StringCommand.hpp"

#include <iostream>
#include <stdexcept>

StringCommand::StringCommand( const std::string &msg )
: content(msg) {
}

StringCommand::~StringCommand() { 
}
	
void StringCommand::execute( MemoryInterface *global ) {
	std::cout << content << std::endl;
	global->size();//FIX: unused variable msg
}