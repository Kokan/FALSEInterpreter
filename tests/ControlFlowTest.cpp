#include <vector>
#include <iostream>
#include <memory>

#include "..\VirtualMachine.hpp"
#include "..\SimpleMemory.hpp"
#include "..\SimpleStack.hpp"


#include "..\Commands\PushCommand.hpp"
#include "..\Commands\EqualCommand.hpp"
#include "..\Commands\LogicalNotCommand.hpp"
#include "..\Commands\SwapItemCommand.hpp"
#include "..\Commands\DuplicateCommand.hpp"
#include "..\Commands\DeleteCommand.hpp"
#include "..\Commands\ArithmeticCommands.hpp"
#include "..\Commands\SubroutineCommand.hpp"
#include "..\Commands\IFCOmmand.hpp"
#include "..\Commands\WhileCommand.hpp"

#include "..\BaseTypes\Integer.hpp"
#include "..\BaseTypes\Bool.hpp"

#include "TestSummary.hpp"

int main() {
	TestSummary report;
	
		
	{   const std::string testName = "If true";
		
		std::vector<Command*> program;
		std::vector<Command*> increment_prg;
		std::vector<Object*> expected;
		
		Object *integer10 = new Integer(10);
		Object *integer11 = new Integer(11);
		
		increment_prg.push_back( new PushCommand(new Integer(1)) );
		increment_prg.push_back( new AddCommand() );
		
		program.push_back( new PushCommand(integer10) );
		program.push_back( new PushCommand(new Bool(true)) );
		program.push_back( new SubroutineCommand(increment_prg) );
		program.push_back( new IFCommand() );
		
		expected.push_back( integer11 );
			
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "If false";
		
		std::vector<Command*> program;
		std::vector<Command*> increment_prg;
		std::vector<Object*> expected;
		
		Object *integer10 = new Integer(10);
		
		increment_prg.push_back( new PushCommand(new Integer(1)) );
		increment_prg.push_back( new AddCommand() );
		
		program.push_back( new PushCommand(integer10) );
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new SubroutineCommand(increment_prg) );
		program.push_back( new IFCommand() );
		
		expected.push_back( integer10 );
			
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "If condition is not Bool value";
		
		std::vector<Command*> program;
		std::vector<Command*> increment_prg;
		std::vector<Object*> expected;
		
		program.push_back( new SubroutineCommand() );
		program.push_back( new PushCommand(new Integer(6)) );
		program.push_back( new IFCommand() );
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "If body is not Subroutine value";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		
		program.push_back( new PushCommand(new Bool(true)) );
		program.push_back( new DuplicateCommand() );
		program.push_back( new IFCommand() );
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "If stack is empty";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
			
		program.push_back( new IFCommand() );
			
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "While stack is empty";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
			
		program.push_back( new WhileCommand() );
			
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "While body is empty";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		
		program.push_back( new PushCommand(new Bool(true)) );
		program.push_back( new WhileCommand() );
			
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "While stack is empty";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
			
		program.push_back( new WhileCommand() );
			
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "While sum stack";
		
		std::vector<Command*> program;
		std::vector<Command*> until_zero;
		std::vector<Command*> add_sub;
		std::vector<Object*> expected;
		
		until_zero.push_back( new DuplicateCommand() );
		until_zero.push_back( new PushCommand(new Integer(0)) );
		until_zero.push_back( new EqualCommand() );
		until_zero.push_back( new LogicalNotCommand() );
		
		add_sub.push_back( new AddCommand() );
		add_sub.push_back( new SwapItemCommand() );
		
		unsigned int sum = 0;
		for ( unsigned int i = 0; i < 10; ++i ) {
			program.push_back( new PushCommand(new Integer(i)) );
			sum += i;
		}
		
		program.push_back( new SubroutineCommand(until_zero) );
		program.push_back( new SubroutineCommand(add_sub) );
		program.push_back( new WhileCommand() );
		program.push_back( new DeleteCommand() );
		
		expected.push_back( new Integer(sum) );			
			
		report.testVM( testName, program, expected );
	}

	
	return 0;
}