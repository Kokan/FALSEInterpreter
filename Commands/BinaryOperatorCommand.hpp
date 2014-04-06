#ifndef _BINARY_OPERATOR_COMMAND_
#define _BINARY_OPERATOR_COMMAND_

#include <stdexcept>

#include "Command.hpp"

#include "..\BaseTypes\Object.hpp"

template<typename BinaryOperator, typename ArgumentType>
class BinaryOperatorCommand : public Command {
public:
	BinaryOperatorCommand( ) {}
	virtual ~BinaryOperatorCommand() { 
		this->global = 0;
	}
	
	virtual void execute( MemoryInterface *global ) {
		this->global = global;
		
		const int first  = getNumberValue( );
		const int second = getNumberValue( );
		
		Object *result = new ArgumentType( binary_op(first,second) );
		
		this->global->push( result );
	}
	
	Object* getArgument( ) {
		Object *object = global->top();
		global->pop();
		
		return object;
	}
	
	int getNumberValue( ) {
		ArgumentType *argument = dynamic_cast<ArgumentType*>( getArgument() );
		if ( 0 == argument ) {
			throw std::runtime_error( "BinaryOperatorCommand parameter value are not compatible.");
		}
		
		return argument->get();
	}
private:
	MemoryInterface *global;
	BinaryOperator binary_op;
};


#endif // _BINARY_OPERATOR_COMMAND_