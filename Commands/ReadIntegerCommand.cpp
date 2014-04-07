#include "ReadIntegerCommand.hpp"
#include "..\BaseTypes\Integer.hpp"

#include <iostream>


ReadIntegerCommand::ReadIntegerCommand( ) {
}

ReadIntegerCommand::~ReadIntegerCommand() { 
}

void ReadIntegerCommand::execute( MemoryInterface *global ) {
	char byte;
	Object *obj  = nullptr;
	
	std::cin >> byte;
	std::cin.ignore(256,'\n');
	
	if ( std::cin ) {
		obj = new Integer((int)byte);
		global->push( obj );
	}
}