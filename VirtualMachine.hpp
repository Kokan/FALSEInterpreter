#ifndef _VIRTUALMACHINE_
#define _VIRTUALMACHINE_

#include <iostream>
#include <vector>
#include <iterator>

#include "Commands\Command.hpp"
#include "Commands\SubroutineCommand.hpp"
#include "MemoryInterface.hpp"

class VirtualMachine {
public:
	VirtualMachine( const std::vector<Command*> &prg, MemoryInterface *memory )
	: globalVariables( memory ), program( prg )
	{ }
	virtual ~VirtualMachine() {
		
		if ( globalVariables->size() > 0 ) {
			printStack();
		}
	}
	
	void execute() {
		program.run( globalVariables );
	}
	
protected:
	void printStack() {
		std::cout << "[ ";
		while ( globalVariables->size() > 0 ) {
			std::cout << globalVariables->top()->toString() << " ";
			
			globalVariables->pop();
		}
		std::cout << "]";
	}
	
private:
	MemoryInterface *globalVariables;
	SubroutineCommand program;
};

#endif // _VIRTUALMACHINE_