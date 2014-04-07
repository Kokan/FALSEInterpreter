#ifndef _VIRTUALMACHINE_
#define _VIRTUALMACHINE_

#include <vector>

#include "MemoryInterface.hpp"
#include "Commands\Command.hpp"
#include "Commands\SubroutineCommand.hpp"

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