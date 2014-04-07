#include "IFCommand.hpp"
#include "..\BaseTypes\Bool.hpp"
#include "SubroutineCommand.hpp"

#include <stdexcept>

IFCommand::IFCommand( ) {
}

IFCommand::~IFCommand() {
}
	
void IFCommand::execute( MemoryInterface *global ) {
	Object *subObject = global->top();
	global->pop();
	Object *conditionObject = global->top( );
	global->pop();
	
	Bool *condition = dynamic_cast<Bool*>( conditionObject );
	if ( 0 == condition ) {
		throw std::runtime_error( "IFCommand condition must be Bool." );
	}
	
	SubroutineCommand *sub = dynamic_cast<SubroutineCommand*>( subObject );
	if ( 0 == sub ) {
		throw std::runtime_error( "IFCommand body must be SubroutineCommand." );
	}
	
	if ( condition->get() ) {
		sub->run( global );
	}
}