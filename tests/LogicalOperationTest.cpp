#include "../VirtualMachine.hpp"
#include "../SimpleMemory.hpp"
#include "../SimpleStack.hpp"

#include "../Commands/PushCommand.hpp"
#include "../Commands/LogicalNotCommand.hpp"
#include "../Commands/EqualCommand.hpp"

#include "../BaseTypes/Integer.hpp"
#include "../BaseTypes/Bool.hpp"

#include "TestSummary.hpp"

int main() {
	TestSummary report;
	
	
	{   const std::string testName = "Equal with empty stack";
	
		std::vector<Command*> program;
		
		program.push_back( new EqualCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Equal with 1 item in the stack";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new EqualCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Equal with 2 different type with different value in the stack";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(5)) );
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new EqualCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Bool(false) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Equal with 2 different type with same value in the stack";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(0)) );
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new EqualCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Bool(false) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Equal with 2 same type with different value in the stack";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Bool(true)) );
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new EqualCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Bool(false) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Equal with 2 same type with same value in the stack";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new EqualCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Bool(true) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Not with empty stack";
	
		std::vector<Command*> program;
		
		program.push_back( new LogicalNotCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Not with not Bool value";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(2)) );
		program.push_back( new LogicalNotCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Not with Bool true";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Bool(true)) );
		program.push_back( new LogicalNotCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Bool(false) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Not with Bool false";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new LogicalNotCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Bool(true) );
		
		report.testVM( testName, program, expected );
	}
	
	
	return 0;
}