#include "NegationCommand.hpp"
#include "../BaseTypes/Integer.hpp"

#include <stdexcept>


NegationCommand::NegationCommand( ) {
}

NegationCommand::~NegationCommand() {
	this->global = 0;
}
	
void NegationCommand::execute( MemoryInterface *global ) {
	this->global = global;
	
	const int value = getNumberValue( );
	
	Object *result = new Integer( -1*value );
	
	this->global->push( result );
}
	
Object* NegationCommand::getArgument( ) {
	Object *object = global->top();
	global->pop();
	
	return object;
}
	
int NegationCommand::getNumberValue( ) {
	Integer *argument = dynamic_cast<Integer*>( getArgument() );
	if ( 0 == argument ) {
		throw std::runtime_error( "NegationCommand parameter value are not compatible.");
	}
	
	return argument->get();
}