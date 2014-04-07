#include "..\VirtualMachine.hpp"
#include "..\SimpleMemory.hpp"
#include "..\SimpleStack.hpp"

#include "..\Commands\PushCommand.hpp"
#include "..\Commands\SubroutineCommand.hpp"
#include "..\Commands\RunSubroutineCommand.hpp"
#include "..\Commands\SetVariableCommand.hpp"
#include "..\Commands\GetVariableCommand.hpp"

#include "..\BaseTypes\Integer.hpp"
#include "..\BaseTypes\Bool.hpp"

#include "TestSummary.hpp"

int main() {
	TestSummary report;
	
	
	{   const std::string testName = "Empty Subroutine";
	
		std::vector<Command*> program;
		std::vector<Command*> sub;
		
		program.push_back( new SubroutineCommand(sub) );
		program.push_back( new RunSubroutineCommand() );
		
		std::vector<Object*> expected;
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "SetVariable with empty stack";
	
		std::vector<Command*> program;
		
		program.push_back( new SetVariableCommand("tmp") );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "SetVariable with invalid variable name";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer) );
		program.push_back( new SetVariableCommand("Var") );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	
	return 0;
}