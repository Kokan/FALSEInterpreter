#include "VirtualMachine.hpp"

#include <iostream>
#include <vector>
#include <iterator>

VirtualMachine::VirtualMachine( const std::vector<Command*> &prg, MemoryInterface *memory )
: globalVariables( memory ), program( prg ) {
}

VirtualMachine::~VirtualMachine() {
	if ( globalVariables->size() > 0 ) {
		printStack();
	}
}

void VirtualMachine::execute() {
	program.run( globalVariables );
}

void VirtualMachine::printStack() {
	std::cout << "[ ";
	while ( globalVariables->size() > 0 ) {
		std::cout << globalVariables->top()->toString() << " ";
		
		globalVariables->pop();
	}
	std::cout << "]";
}