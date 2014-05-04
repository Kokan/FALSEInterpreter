#include "../VirtualMachine.hpp"
#include "../SimpleMemory.hpp"
#include "../SimpleStack.hpp"

#include "../Commands/PushCommand.hpp"
#include "../Commands/ArithmeticCommands.hpp"
#include "../Commands/SubroutineCommand.hpp"
#include "../Commands/RunSubroutineCommand.hpp"
#include "../Commands/SetVariableCommand.hpp"
#include "../Commands/GetVariableCommand.hpp"

#include "../BaseTypes/Integer.hpp"
#include "../BaseTypes/Bool.hpp"

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
	
	{   const std::string testName = "Nested Subroutines";
	
		std::vector<Command*> program;
		std::vector<Command*> sub0;
		std::vector<Command*> sub1;
		std::vector<Command*> sub2;
		
		sub0.push_back( new PushCommand(new Integer(0)) );
		
		sub1.push_back( new PushCommand(new Integer(1)) );
		sub1.push_back( new SubroutineCommand(sub0) );
		
		sub2.push_back( new PushCommand(new Integer(2)) );
		sub2.push_back( new SubroutineCommand(sub1) );
		
		program.push_back( new SubroutineCommand(sub2) );
		program.push_back( new RunSubroutineCommand() );
		program.push_back( new RunSubroutineCommand() );
		program.push_back( new RunSubroutineCommand() );
		
		std::vector<Object*> expected;
		expected.push_back(new Integer(0));
		expected.push_back(new Integer(1));
		expected.push_back(new Integer(2));
		
		report.testVM( testName, program, expected );
	}
		
	{   const std::string testName = "Increment value Subroutine";
		
		std::vector<Command*> program;
		std::vector<Command*> increment_prg;
		std::vector<Object*> expected;
		
		Object *integer10 = new Integer(10);
		Object *integer11 = new Integer(11);
		
		increment_prg.push_back( new PushCommand(new Integer(1)) );
		increment_prg.push_back( new AddCommand() );
		
		program.push_back( new PushCommand(integer10) );
		program.push_back( new SubroutineCommand(increment_prg) );
		program.push_back( new RunSubroutineCommand() );
		
		expected.push_back( integer11 );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "SetVariable with empty stack";
	
		std::vector<Command*> program;
		
		program.push_back( new SetVariableCommand("tmp") );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "SetVariable with UpperCase name";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer) );
		program.push_back( new SetVariableCommand("Var") );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "SetVariable with starting Number name";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer) );
		program.push_back( new SetVariableCommand("1var") );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "SetVariable with Number name";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer) );
		program.push_back( new SetVariableCommand("v4r") );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "SetVariable with white-space name";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer) );
		program.push_back( new SetVariableCommand("v ar") );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "SetVariable with special char name";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer) );
		program.push_back( new SetVariableCommand("v@r") );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "SetVariable with Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer) );
		program.push_back( new SetVariableCommand("integer") );
		
		std::vector<Object*> expected;
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "GetVariable uninitialized";
	
		std::vector<Command*> program;
		
		program.push_back( new GetVariableCommand("integer") );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "GetVariable with Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(112)) );
		program.push_back( new SetVariableCommand("integer") );
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new GetVariableCommand("integer") );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(112) );
		expected.push_back( new Bool(false) );
		
		report.testVM( testName, program, expected );
	}
	
	
	return 0;
}