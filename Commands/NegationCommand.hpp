#ifndef _NEGATION_COMMAND_
#define _NEGATION_COMMAND_

#include <stdexcept>

#include "Command.hpp"

#include "..\BaseTypes\Object.hpp"
#include "..\BaseTypes\Integer.hpp"

class NegationCommand : public Command {
public:
	NegationCommand( ) {}
	virtual ~NegationCommand() { 
		this->global = 0;
	}
	
	virtual void execute( MemoryInterface *global ) {
		this->global = global;
		
		const int value = getNumberValue( );
		
		Object *result = new Integer( -1*value );
		
		this->global->push( result );
	}
	
	Object* getArgument( ) {
		Object *object = global->top();
		global->pop();
		
		return object;
	}
	
	int getNumberValue( ) {
		Integer *argument = dynamic_cast<Integer*>( getArgument() );
		if ( 0 == argument ) {
			throw std::runtime_error( "NegationCommand parameter value are not compatible.");
		}
		
		return argument->get();
	}
private:
	MemoryInterface *global;
};


#endif // _NEGATION_COMMAND_