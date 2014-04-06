#ifndef _LOGICALNOTCOMMAND_
#define _LOGICALNOTCOMMAND_

#include "Command.hpp"
#include "..\BaseTypes\Bool.hpp"


class LogicalNotCommand : public Command {
public:
	LogicalNotCommand( ) {}
	virtual ~LogicalNotCommand() { 
	}
	
	virtual void execute( StackInterface *global ) {
		Object *object  = global->top( );
		global->pop();
		
		Bool *boolvalue = dynamic_cast<Bool*>(object);
		if ( 0 == boolvalue ) {
			throw std::runtime_error("LogicalNotCommand expecting Bool value.");
		}
		
		global->push( new Bool( !boolvalue->get() ) );
	}
};

#endif // _LOGICALNOTCOMMAND_