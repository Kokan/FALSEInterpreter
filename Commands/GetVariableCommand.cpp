#include "GetVariableCommand.hpp"

#include <stdexcept>

GetVariableCommand::GetVariableCommand( const std::string &varName )
: variableName( varName ) {
}

GetVariableCommand::~GetVariableCommand() {
}

void GetVariableCommand::execute( MemoryInterface *global ) {
	Object *value = global->get( variableName );
	
	if ( nullptr == value ) {
		throw std::runtime_error( "Variable not exists." );
	}
	
	global->push( value );
}