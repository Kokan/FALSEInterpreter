#ifndef _TESTSUMMARY_
#define _TESTSUMMARY_

#include <vector>
#include <iostream>
#include <memory>


#include "../VirtualMachine.hpp"
#include "../SimpleMemory.hpp"
#include "../SimpleStack.hpp"



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

#endif // _TESTSUMMARY_