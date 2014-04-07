#include "..\VirtualMachine.hpp"
#include "..\SimpleMemory.hpp"
#include "..\SimpleStack.hpp"


#include "..\Commands\PushCommand.hpp"
#include "..\Commands\DuplicateCommand.hpp"
#include "..\Commands\DeleteCommand.hpp"
#include "..\Commands\SwapItemCommand.hpp"
#include "..\Commands\ThirdToTopCommand.hpp"

#include "..\BaseTypes\Integer.hpp"
#include "..\BaseTypes\Bool.hpp"

#include "TestSummary.hpp"

int main() {
	TestSummary report;
	
	
	{   const std::string testName = "Duplicate Top Item with empty stack";
	
		std::vector<Command*> program;
		
		program.push_back( new DuplicateCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Duplicate Top Item with Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(1)) );
		program.push_back( new DuplicateCommand() );
		
		std::vector<Object*> expected;
		expected.push_back(new Integer(1));
		expected.push_back(new Integer(1));
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Delete Top Item with empty stack";
	
		std::vector<Command*> program;
		
		program.push_back( new DeleteCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Delete Top Item with Bool";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Bool) );
		program.push_back( new DeleteCommand() );
		
		std::vector<Object*> expected;
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Swap Top Item with empty stack";
	
		std::vector<Command*> program;
		
		program.push_back( new SwapItemCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Swap Top Item with 1 item in the stack";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(2)) );
		program.push_back( new SwapItemCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Swap Top Item with same type";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(1)) );
		program.push_back( new PushCommand(new Integer(2)) );
		program.push_back( new SwapItemCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(1) );
		expected.push_back( new Integer(2) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Swap Top Item with different type";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(1)) );
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new SwapItemCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(1) );
		expected.push_back( new Bool(false) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Third to the top with empty stack";
	
		std::vector<Command*> program;
		
		program.push_back( new ThirdToTopCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Third to the top with 1 item in the stack";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(1)) );
		program.push_back( new ThirdToTopCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Third to the top with 2 item in the stack";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(1)) );
		program.push_back( new PushCommand(new Integer(2)) );
		program.push_back( new ThirdToTopCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Third to the top with 3 item in the stack";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(1)) );
		program.push_back( new PushCommand(new Integer(2)) );
		program.push_back( new PushCommand(new Integer(4)) );
		program.push_back( new ThirdToTopCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(1) );
		expected.push_back( new Integer(4) );
		expected.push_back( new Integer(2) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Third to the top with more item in the stack";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(10)) );
		program.push_back( new PushCommand(new Integer(7)) );
		program.push_back( new PushCommand(new Integer(9)) );
		program.push_back( new PushCommand(new Integer(5)) );
		program.push_back( new ThirdToTopCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(7) );
		expected.push_back( new Integer(5) );
		expected.push_back( new Integer(9) );
		expected.push_back( new Integer(10) );
		
		report.testVM( testName, program, expected );
	}
	/*
	{   const std::string testName = "Copie nth with 0 to top with empty stack";
	
		std::vector<Command*> program;
		
		program.push_back( new CopyCommand(0) );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}*/
	
	return 0;
}