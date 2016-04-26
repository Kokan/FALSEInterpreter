#ifndef _VIRTUALMACHINE_
#define _VIRTUALMACHINE_

#include <vector>

#include "MemoryInterface.hpp"
#include "Commands/SubroutineCommand.hpp"

class Command;

class VirtualMachine {
public:
	VirtualMachine( const std::vector<Command*> &prg, MemoryInterface *memory );
	virtual ~VirtualMachine();
	
	void execute();
	
protected:
	void printStack();
	
private:
	MemoryInterface *globalVariables;
	SubroutineCommand program;
};

#endif // _VIRTUALMACHINE_
