#ifndef _ADDCOMMAND_
#define _ADDCOMMAND_

#include <stdexcept>

#include "Command.hpp"

#include "..\BaseTypes\Object.hpp"
#include "..\BaseTypes\Integer.hpp"


class AddCommand : public Command {
public:
	AddCommand( ) {}
	virtual ~AddCommand() { 
		this->global = 0;
	}
	
	virtual void execute( StackInterface *global ) {
		this->global = global;
		
		const int first  = getNumberValue( );
		const int second = getNumberValue( );
		
		Object *result = new Integer( first + second );
		
		this->global->push( result );
	}
	
	Object* getArgument( ) {
		Object *object = global->top();
		global->pop();
		
		return object;
	}
	
	int getNumberValue( ) {
		Integer *number = dynamic_cast<Integer*>( getArgument() );
		if ( 0 == number ) {
			throw std::runtime_error("AddCommand parameter value are not compatible.");
		}
		
		return number->get();
	}
private:
	StackInterface *global;
};


#endif // _ADDCOMMAND_