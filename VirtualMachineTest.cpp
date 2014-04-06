
#include "VirtualMachine.hpp"
#include "SimpleStack.hpp"


#include "Commands\PushCommand.hpp"
#include "Commands\AddCommand.hpp"
#include "Commands\DuplicateCommand.hpp"
#include "Commands\DeleteCommand.hpp"
#include "Commands\SwapItemCommand.hpp"
#include "Commands\SubroutineCommand.hpp"
#include "Commands\RunSubroutineCommand.hpp"
#include "Commands\EqualCommand.hpp"
#include "Commands\PrintAsIntegerCommand.hpp"
#include "Commands\LogicalNotCommand.hpp"
#include "Commands\IFCOmmand.hpp"
#include "Commands\WhileCommand.hpp"

#include "BaseTypes\Integer.hpp"
#include "BaseTypes\Bool.hpp"

std::vector<Object*> StackToArray( StackInterface *stack ) {
	std::vector<Object*> data;
	
	while ( stack->size() > 0 ) {
		data.push_back( stack->top() );
		
		stack->pop();
	}
	
	return data;
}

bool testVM( const std::vector<Command*> &program, const std::vector<Object*> &expected ) {
	StackInterface* stack = new SimpleStack();
	
	VirtualMachine main( program, stack );
	
	main.execute();
	
	std::vector<Object*> result = StackToArray( stack );
	
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

class TestSummary {
public:
	TestSummary()
	: ok( 0 ), failed( 0 ), all( 0 )
	{ }
	
	~TestSummary() {
		result();
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
	
private:	
	void result() {
		std::cout << ok << "/" << all << " tests are correct." << std::endl;
	}

	unsigned int ok;
	unsigned int failed;
	unsigned int all;
};


int main() {
	TestSummary report;
	
	
	{   const std::string testName = "EmptyProgram";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			if ( testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}
	
	{   const std::string testName = "PushCommand Single Value";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			Object* integer6 = new Integer(6);
			
			program.push_back( new PushCommand( integer6 ) );
			expected.push_back( integer6 );
			
			if ( testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}	
	
	{   const std::string testName = "PushCommand Multiple Value";
		try
		{
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
			
			if ( testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}
	
	{   const std::string testName = "AddCommand with 2 Integer";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			Object* integer3 = new Integer(3);
			Object* integer2 = new Integer(2);
			Object* integer1 = new Integer(1);
			
			program.push_back( new PushCommand( integer1 ) );
			program.push_back( new PushCommand( integer2 ) );
			program.push_back( new AddCommand() );
			
			expected.push_back( integer3 );
			
			if ( testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}
	
	{   const std::string testName = "AddCommand with not valid argument";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			Object* integer2  = new Integer(2);
			Object* boolvalue = new Bool();
			
			program.push_back( new PushCommand( boolvalue ) );
			program.push_back( new PushCommand( integer2 ) );
			program.push_back( new AddCommand() );
			
			testVM( program, expected );
			report.testFAILED( testName );
		}
		catch (...) {
			report.testOK( testName );
		}
	}
	
	{   const std::string testName = "Duplicate Nothing";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
						
			program.push_back( new DuplicateCommand() );
			
			testVM( program, expected );
			report.testFAILED( testName );
		}
		catch (...) {
			report.testOK( testName );
		}
	}
	
	{   const std::string testName = "Duplicate For Integer";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			Object *integer = new Integer(3);
			
			program.push_back( new PushCommand(integer) );
			program.push_back( new DuplicateCommand() );
			
			expected.push_back( integer );
			expected.push_back( integer );
						
			
			if (testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}
	
	{   const std::string testName = "Duplicate For Bool";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			Object *boolvalue = new Bool();
			
			program.push_back( new PushCommand(boolvalue) );
			program.push_back( new DuplicateCommand() );
			
			expected.push_back( boolvalue );
			expected.push_back( boolvalue );
						
			
			if (testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}
	
	{   const std::string testName = "Delete Nothing";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			
			program.push_back( new DeleteCommand() );
			
			testVM( program, expected );
			report.testFAILED( testName );
		}
		catch (...) {
			report.testOK( testName );
		}
	}
	
	{   const std::string testName = "Delete Top Element";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			Object *boolvalue = new Bool();
			
			program.push_back( new PushCommand(boolvalue) );
			program.push_back( new DeleteCommand() );
			
			
			if (testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}
	
	{   const std::string testName = "Swap Nothing";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			program.push_back( new SwapItemCommand() );
			
			
			testVM( program, expected );
			report.testFAILED( testName );
		}
		catch (...) {
			report.testOK( testName );
		}
	}
	
	{   const std::string testName = "Swap One Item";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			Object *integer = new Integer(19);
			
			program.push_back( new PushCommand(integer) );
			program.push_back( new SwapItemCommand() );
			
			expected.push_back( integer );
			
			testVM( program, expected );
			report.testFAILED( testName );
		}
		catch (...) {
			report.testOK( testName );
		}
	}	
	
	{   const std::string testName = "Swap Two Same Item";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			Object *integer19 = new Integer(19);
			Object *integer11 = new Integer(11);
			
			program.push_back( new PushCommand(integer19) );
			program.push_back( new PushCommand(integer11) );
			program.push_back( new SwapItemCommand() );
			
			expected.push_back( integer19 );
			expected.push_back( integer11 );
			
			if (testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}
	
	{   const std::string testName = "Swap Two BaseType Item";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			Object *boolvalue = new Bool();
			Object *integer11 = new Integer(11);
			
			program.push_back( new PushCommand(boolvalue) );
			program.push_back( new PushCommand(integer11) );
			program.push_back( new SwapItemCommand() );
			
			expected.push_back( boolvalue );
			expected.push_back( integer11 );
			
			if (testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}
	
	{   const std::string testName = "LogicalNotCommand with empty stack";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			program.push_back( new LogicalNotCommand() );
			
			
			testVM( program, expected );
			report.testOK( testName );
		}
		catch (...) {
			report.testOK( testName );
		}
	}
	
	{   const std::string testName = "LogicalNotCommand with not Bool value";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			program.push_back( new PushCommand(new Integer(7)) );
			program.push_back( new LogicalNotCommand() );
			
			
			testVM( program, expected );
			report.testOK( testName );
		}
		catch (...) {
			report.testOK( testName );
		}
	}
	
	{   const std::string testName = "LogicalNotCommand with true";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			program.push_back( new PushCommand(new Bool(false)) );
			program.push_back( new LogicalNotCommand() );
			
			expected.push_back( new Bool(true) );
			
			if ( testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}
	
	{   const std::string testName = "Empty Subroutine";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			program.push_back( new SubroutineCommand() );
			program.push_back( new RunSubroutineCommand() );
			
			if (testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}
	
	{   const std::string testName = "Increment value Subroutine";
		try
		{
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
			
			if (testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}
		
	{   const std::string testName = "EqualCommand with empty stack";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			
			program.push_back( new EqualCommand() );
			
			testVM( program, expected );
			report.testFAILED( testName );
		}
		catch (...) {
			report.testOK( testName );
		}
	}
	
	{   const std::string testName = "EqualCommand with one element on stack";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			program.push_back( new PushCommand(new Integer(0)) );
			program.push_back( new EqualCommand() );
					
			
			testVM( program, expected );
			report.testFAILED( testName );
		}
		catch (...) {
			report.testOK( testName );
		}
	}
	
	{   const std::string testName = "EqualCommand with same object";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			Object *integer6 = new Integer(6);
			
			program.push_back( new PushCommand(integer6) );
			program.push_back( new PushCommand(integer6) );
			program.push_back( new EqualCommand() );
					
			expected.push_back( new Bool(true) );			
			
			if ( testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}
	
	{   const std::string testName = "If true";
		try
		{
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
			
			if (testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}
	
	{   const std::string testName = "If false";
		try
		{
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
			
			if (testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}
	
	{   const std::string testName = "If condition is not Bool value";
		try
		{
			std::vector<Command*> program;
			std::vector<Command*> increment_prg;
			std::vector<Object*> expected;
			
			program.push_back( new SubroutineCommand() );
			program.push_back( new PushCommand(new Integer(6)) );
			program.push_back( new IFCommand() );
			
			
			testVM( program, expected );
			report.testFAILED( testName );
		}
		catch (...) {
			report.testOK( testName );
		}
	}
	
	{   const std::string testName = "If body is not Subroutine value";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			program.push_back( new PushCommand(new Bool(true)) );
			program.push_back( new DuplicateCommand() );
			program.push_back( new IFCommand() );
			
			
			testVM( program, expected );
			report.testFAILED( testName );
		}
		catch (...) {
			report.testOK( testName );
		}
	}
	
	{   const std::string testName = "If stack is empty";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			program.push_back( new IFCommand() );
			
			
			testVM( program, expected );
			report.testFAILED( testName );
		}
		catch (...) {
			report.testOK( testName );
		}
	}
	
	{   const std::string testName = "While stack is empty";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			program.push_back( new WhileCommand() );
			
			
			testVM( program, expected );
			report.testFAILED( testName );
		}
		catch (...) {
			report.testOK( testName );
		}
	}
	
	{   const std::string testName = "While body is empty";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			program.push_back( new PushCommand(new Bool(true)) );
			program.push_back( new WhileCommand() );
			
			
			testVM( program, expected );
			report.testFAILED( testName );
		}
		catch (...) {
			report.testOK( testName );
		}
	}
	
	{   const std::string testName = "While stack is empty";
		try
		{
			std::vector<Command*> program;
			std::vector<Object*> expected;
			
			program.push_back( new WhileCommand() );
			
			
			testVM( program, expected );
			report.testFAILED( testName );
		}
		catch (...) {
			report.testOK( testName );
		}
	}
	
	{   const std::string testName = "While sum stack";
		try
		{
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
			
			if ( testVM( program, expected ) ) {
				report.testOK( testName );
			}
			else {
				report.testFAILED( testName );
			}
		}
		catch (...) {
			report.testFAILED( testName );
		}
	}
	
	return 0;
}
/*


17
7
6
5
4
3
2
1
0
*/