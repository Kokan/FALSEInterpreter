#include "SetVariableCommand.hpp"

#include <stdexcept>
#include <algorithm>
#include <cctype>


SetVariableCommand::SetVariableCommand( const std::string &varName )
: variableName( varName ) {
}

SetVariableCommand::~SetVariableCommand() { 
}

void SetVariableCommand::execute( MemoryInterface *global ) {
	if ( !isValidName() ) {
		throw std::runtime_error("SetVariableCommand invalid variable name. Name must be '[a-z]+' .");
	}
	Object *value = global->top( );
	global->pop();
	
	global->set( variableName, value );
}

bool SetVariableCommand::isValidName( ) const {
	return std::all_of( variableName.begin(), variableName.end(), islower );
}