#include "..\VirtualMachine.hpp"
#include "..\SimpleMemory.hpp"
#include "..\SimpleStack.hpp"

#include "..\Commands\PushCommand.hpp"
#include "..\Commands\ArithmeticCommands.hpp"
#include "..\Commands\NegationCommand.hpp"

#include "..\BaseTypes\Integer.hpp"
#include "..\BaseTypes\Bool.hpp"

#include "TestSummary.hpp"

int main() {
	TestSummary report;
	
	
	{   const std::string testName = "Add with empty stack";
	
		std::vector<Command*> program;
		
		program.push_back( new AddCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Add with 1 item in the stack";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(1)) );
		program.push_back( new AddCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
		
	{   const std::string testName = "Add with 2 Bool";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new AddCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
		
	{   const std::string testName = "Add with Bool and Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new PushCommand(new Integer(1)) );
		program.push_back( new AddCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Add with 2 positive Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(20)) );
		program.push_back( new PushCommand(new Integer(13)) );
		program.push_back( new AddCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(33) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Add with 2 negative Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(-5)) );
		program.push_back( new PushCommand(new Integer(-10)) );
		program.push_back( new AddCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(-15) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Add with positive and negative Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(+5)) );
		program.push_back( new PushCommand(new Integer(-10)) );
		program.push_back( new AddCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(-5) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Sub with empty stack";
	
		std::vector<Command*> program;
		
		program.push_back( new SubCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Sub with 1 item in the stack";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(1)) );
		program.push_back( new SubCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
		
	{   const std::string testName = "Sub with 2 Bool";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new SubCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
		
	{   const std::string testName = "Sub with Bool and Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new PushCommand(new Integer(1)) );
		program.push_back( new SubCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Sub with 2 positive Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(20)) );
		program.push_back( new PushCommand(new Integer(13)) );
		program.push_back( new SubCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(7) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Sub with 2 negative Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(-5)) );
		program.push_back( new PushCommand(new Integer(-10)) );
		program.push_back( new SubCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(5) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Sub with positive and negative Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(+5)) );
		program.push_back( new PushCommand(new Integer(-10)) );
		program.push_back( new SubCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(15) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Multiply with empty stack";
	
		std::vector<Command*> program;
		
		program.push_back( new MultiplyCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Multiply with 1 item in the stack";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(1)) );
		program.push_back( new MultiplyCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
		
	{   const std::string testName = "Multiply with 2 Bool";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new MultiplyCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
		
	{   const std::string testName = "Multiply with Bool and Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new PushCommand(new Integer(1)) );
		program.push_back( new MultiplyCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Multiply with 2 positive Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(20)) );
		program.push_back( new PushCommand(new Integer(13)) );
		program.push_back( new MultiplyCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(260) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Multiply with 2 negative Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(-5)) );
		program.push_back( new PushCommand(new Integer(-10)) );
		program.push_back( new MultiplyCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(50) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Multiply with positive and negative Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(+5)) );
		program.push_back( new PushCommand(new Integer(-10)) );
		program.push_back( new MultiplyCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(-50) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Multiply with positive with zero";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(+5)) );
		program.push_back( new PushCommand(new Integer(0)) );
		program.push_back( new MultiplyCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(0) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Multiply with negative with zero";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(+5)) );
		program.push_back( new PushCommand(new Integer(0)) );
		program.push_back( new MultiplyCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(0) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Multiply with zero with zero";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(0)) );
		program.push_back( new PushCommand(new Integer(0)) );
		program.push_back( new MultiplyCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(0) );
		
		report.testVM( testName, program, expected );
	}
		
	{   const std::string testName = "Divide with empty stack";
	
		std::vector<Command*> program;
		
		program.push_back( new DivideCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Divide with 1 item in the stack";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(1)) );
		program.push_back( new DivideCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
		
	{   const std::string testName = "Divide with 2 Bool";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new DivideCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
		
	{   const std::string testName = "Divide with Bool and Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new PushCommand(new Integer(1)) );
		program.push_back( new DivideCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Divide with 2 positive Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(20)) );
		program.push_back( new PushCommand(new Integer(10)) );
		program.push_back( new DivideCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(2) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Divide with 2 negative Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(-10)) );
		program.push_back( new PushCommand(new Integer(-5)) );
		program.push_back( new DivideCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(2) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Divide with positive and negative Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(-10)) );
		program.push_back( new PushCommand(new Integer(+5)) );
		program.push_back( new DivideCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(-2) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Divide with zero with positive";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(0)) );
		program.push_back( new PushCommand(new Integer(+5)) );
		program.push_back( new DivideCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(0) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Divide with zero with negative";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(0)) );
		program.push_back( new PushCommand(new Integer(+5)) );
		program.push_back( new DivideCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(0) );
		
		report.testVM( testName, program, expected );
	}
	{   const std::string testName = "Negation with empty stack";
	
		std::vector<Command*> program;
		
		program.push_back( new NegationCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Negation with 1 item in the stack";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(1)) );
		program.push_back( new NegationCommand() );
		
		std::vector<Object*> expected;
		expected.push_back(new Integer(-1));
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Negation with Bool";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new NegationCommand() );
		
		std::vector<Object*> expected;
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Negation with negative Integer";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(-10)) );
		program.push_back( new NegationCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(10) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Negation with zero";
	
		std::vector<Command*> program;
		
		program.push_back( new PushCommand(new Integer(0)) );
		program.push_back( new NegationCommand() );
		
		std::vector<Object*> expected;
		expected.push_back( new Integer(0) );
		
		report.testVM( testName, program, expected );
	}
	
	return 0;
}