#ifndef _IFCOMMAND_
#define _IFCOMMAND_

#include <stdexcept>

#include "Command.hpp"
#include "..\BaseTypes\Bool.hpp"
#include "SubroutineCommand.hpp"


class IFCommand : public Command {
public:
	IFCommand( ) {}
	virtual ~IFCommand() { 
	}
	
	virtual void execute( MemoryInterface *global ) {
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
};

#endif // _IFCOMMAND_