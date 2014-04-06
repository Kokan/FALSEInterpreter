#include <vector>
#include <iostream>
#include <memory>

#include "..\VirtualMachine.hpp"
#include "..\SimpleMemory.hpp"
#include "..\SimpleStack.hpp"


#include "..\Commands\PushCommand.hpp"
#include "..\Commands\ArithmeticCommands.hpp"
#include "..\Commands\DuplicateCommand.hpp"
#include "..\Commands\DeleteCommand.hpp"
#include "..\Commands\SwapItemCommand.hpp"
#include "..\Commands\SubroutineCommand.hpp"
#include "..\Commands\RunSubroutineCommand.hpp"
#include "..\Commands\EqualCommand.hpp"
#include "..\Commands\PrintAsIntegerCommand.hpp"
#include "..\Commands\PrintAsCharCommand.hpp"
#include "..\Commands\LogicalNotCommand.hpp"
#include "..\Commands\IFCOmmand.hpp"
#include "..\Commands\WhileCommand.hpp"
#include "..\Commands\SetVariableCommand.hpp"
#include "..\Commands\GetVariableCommand.hpp"

#include "..\BaseTypes\Integer.hpp"
#include "..\BaseTypes\Bool.hpp"

std::vector<Object*> StackToArray( MemoryInterface *memory ) {
	std::vector<Object*> data;
	
	while ( memory->size() > 0 ) {
		data.push_back( memory->top() );
		
		memory->pop();
	}
	
	return data;
}

class TestSummary {
public:
	TestSummary()
	: ok( 0 ), failed( 0 ), all( 0 )
	{ }
	
	~TestSummary() {
		result();
	}

	void testVM( const std::string &testName, const std::vector<Command*> &program, const std::vector<Object*> &expected ) {
		std::unique_ptr<StackInterface> stack( new SimpleStack );
		std::unique_ptr<MemoryInterface> memory( new SimpleMemory(stack.get()) );
		
		VirtualMachine main( program, memory.get() );
			
		try {
			main.execute();
		}
		catch (...) {
			testFAILED(testName);
			return;
		}
		
		if ( isStackEqual( expected, memory.get() ) ) {
			testOK(testName);
		}
		else {
			testFAILED(testName);
		}
	}

	void testVMFAIL( const std::string &testName, const std::vector<Command*> &program, const std::vector<Object*> &expected ) {
		std::unique_ptr<StackInterface> stack( new SimpleStack );
		std::unique_ptr<MemoryInterface> memory( new SimpleMemory(stack.get()) );
		
		try {
			VirtualMachine main( program, memory.get() );
			
			main.execute();
		}
		catch (...) {
			testOK(testName);
			return;
		}
		
		expected.size();
		
		testFAILED(testName);
	}

private:
	bool isStackEqual( const std::vector<Object*> &expected, MemoryInterface *memory ) {
		std::vector<Object*> result = StackToArray( memory );
		
		if ( result.size() != expected.size() ) {
			return false;
		}
		for ( unsigned int ind = 0; ind < result.size(); ++ind ) {
			if ( expected[ind]->toString() != result[ind]->toString() ) {
				return false;
			}
		}
		
		return true;
	}
	
	void testOK( const std::string &testName ) {
		std::cout << "test " << testName << " is [OK]" << std::endl;
		++all;
		++ok;
	}
	
	void testFAILED( const std::string &testName ) {
		std::cout << "test " << testName << " is [FAILED]" << std::endl;
		++all;
		++failed;
	}
		
	void result() {
		std::cout << ok << "/" << all << " tests are correct." << std::endl;
		
		if ( ok == all ) {
			std::cout << "[OK]" << std::endl;
		}
		else {
			std::cout << "[FAILED]" << std::endl;
		}
	}
	
	unsigned int ok;
	unsigned int failed;
	unsigned int all;
};


int main() {
	TestSummary report;
	
	
	{   const std::string testName = "EmptyProgram";
	
		std::vector<Command*> program;
		std::vector<Object*> expected;
	
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "PushCommand Single Value";
	
		std::vector<Command*> program;
		std::vector<Object*> expected;
		Object* integer6 = new Integer(6);
		
		program.push_back( new PushCommand( integer6 ) );
		expected.push_back( integer6 );
			
		report.testVM( testName, program, expected );
	}	
	
	{   const std::string testName = "PushCommand Multiple Value";
	
		std::vector<Command*> program;
		std::vector<Object*> expected;
		Object* integer3 = new Integer(3);
		Object* integer2 = new Integer(2);
		Object* integer1 = new Integer(1);
		
		program.push_back( new PushCommand( integer3 ) );
		program.push_back( new PushCommand( integer2 ) );
		program.push_back( new PushCommand( integer1 ) );
		
		expected.push_back( integer1 );
		expected.push_back( integer2 );
		expected.push_back( integer3 );			
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "AddCommand with 2 Integer";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		Object* integer3 = new Integer(3);
		Object* integer2 = new Integer(2);
		Object* integer1 = new Integer(1);
		
		program.push_back( new PushCommand( integer1 ) );
		program.push_back( new PushCommand( integer2 ) );
		program.push_back( new AddCommand() );
		
		expected.push_back( integer3 );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "AddCommand with not valid argument";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		Object* integer2  = new Integer(2);
		Object* boolvalue = new Bool();
		
		program.push_back( new PushCommand( boolvalue ) );
		program.push_back( new PushCommand( integer2 ) );
		program.push_back( new AddCommand() );
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Duplicate Nothing";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
					
		program.push_back( new DuplicateCommand() );
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Duplicate For Integer";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		
		Object *integer = new Integer(3);
		
		program.push_back( new PushCommand(integer) );
		program.push_back( new DuplicateCommand() );
		
		expected.push_back( integer );
		expected.push_back( integer );
			
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Duplicate For Bool";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		
		Object *boolvalue = new Bool();
		
		program.push_back( new PushCommand(boolvalue) );
		program.push_back( new DuplicateCommand() );
		
		expected.push_back( boolvalue );
		expected.push_back( boolvalue );
				
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Delete Nothing";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
			
		program.push_back( new DeleteCommand() );
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Delete Top Element";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		
		Object *boolvalue = new Bool();
		
		program.push_back( new PushCommand(boolvalue) );
		program.push_back( new DeleteCommand() );
		
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Swap Nothing";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		
		program.push_back( new SwapItemCommand() );
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Swap One Item";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		
		Object *integer = new Integer(19);
		
		program.push_back( new PushCommand(integer) );
		program.push_back( new SwapItemCommand() );
		
		expected.push_back( integer );
		
		report.testVMFAIL( testName, program, expected );
	}	
	
	{   const std::string testName = "Swap Two Same Item";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
			
		Object *integer19 = new Integer(19);
		Object *integer11 = new Integer(11);
		
		program.push_back( new PushCommand(integer19) );
		program.push_back( new PushCommand(integer11) );
		program.push_back( new SwapItemCommand() );
		
		expected.push_back( integer19 );
		expected.push_back( integer11 );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Swap Two BaseType Item";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		
		Object *boolvalue = new Bool();
		Object *integer11 = new Integer(11);
		
		program.push_back( new PushCommand(boolvalue) );
		program.push_back( new PushCommand(integer11) );
		program.push_back( new SwapItemCommand() );
		
		expected.push_back( boolvalue );
		expected.push_back( integer11 );
			
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "LogicalNotCommand with empty stack";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		
		program.push_back( new LogicalNotCommand() );
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "LogicalNotCommand with not Bool value";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		
		program.push_back( new PushCommand(new Integer(7)) );
		program.push_back( new LogicalNotCommand() );
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "LogicalNotCommand with true";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		
		program.push_back( new PushCommand(new Bool(false)) );
		program.push_back( new LogicalNotCommand() );
		
		expected.push_back( new Bool(true) );
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Empty Subroutine";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		
		program.push_back( new SubroutineCommand() );
		program.push_back( new RunSubroutineCommand() );
		
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
		
	{   const std::string testName = "EqualCommand with empty stack";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
			
		program.push_back( new EqualCommand() );
		
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "EqualCommand with one element on stack";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		
		program.push_back( new PushCommand(new Integer(0)) );
		program.push_back( new EqualCommand() );
				
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "EqualCommand with same object";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
			
		Object *integer6 = new Integer(6);
		
		program.push_back( new PushCommand(integer6) );
		program.push_back( new PushCommand(integer6) );
		program.push_back( new EqualCommand() );
					
		expected.push_back( new Bool(true) );			
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "If true";
		
		std::vector<Command*> program;
		std::vector<Command*> increment_prg;
		std::vector<Object*> expected;
		
		Object *integer10 = new Integer(10);
		Object *integer11 = new Integer(11);
		
		increment_prg.push_back( new PushCommand(new Integer(1)) );
		increment_prg.push_back( new AddCommand() );
		
		program.push_back( new PushCommand(integer10) );
		program.push_back( new SubroutineCommand(increment_prg) );
		program.push_back( new PushCommand(new Bool(true)) );
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
		program.push_back( new SubroutineCommand(increment_prg) );
		program.push_back( new PushCommand(new Bool(false)) );
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
		
		//add_sub.push_back( new PrintAsIntegerCommand() );
		add_sub.push_back( new AddCommand() );
		add_sub.push_back( new SwapItemCommand() );
		
		unsigned int sum = 0;
		for ( unsigned int i = 0; i < 10; ++i ) {
			program.push_back( new PushCommand(new Integer(i)) );
			sum += i;
		}
		
		program.push_back( new SubroutineCommand(add_sub) );
		program.push_back( new SubroutineCommand(until_zero) );
		program.push_back( new WhileCommand() );
		program.push_back( new DeleteCommand() );
		
		expected.push_back( new Integer(sum) );			
			
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Set Variable with empty stack";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
				
		program.push_back( new SetVariableCommand("a") );
			
		report.testVMFAIL( testName, program, expected );
	}
	
	{   const std::string testName = "Set Variable and Get back";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
		
		Object *integer112 = new Integer(112);
		Object *integer113 = new Integer(113);
		
		program.push_back( new PushCommand(integer112) );
		program.push_back( new PushCommand(integer113) );
		program.push_back( new SetVariableCommand("a") );
		program.push_back( new SetVariableCommand("b") );
		program.push_back( new GetVariableCommand("b") );
		
		expected.push_back(integer112);
		
		report.testVM( testName, program, expected );
	}
	
	{   const std::string testName = "Get Not Existing Variable";
		
		std::vector<Command*> program;
		std::vector<Object*> expected;
				
		program.push_back( new GetVariableCommand("b") );
		
		report.testVMFAIL( testName, program, expected );
	}
	
	return 0;
}