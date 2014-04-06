#ifndef _SUBROUTINECOMMAND_
#define _SUBROUTINECOMMAND_

#include <sstream>

#include "Command.hpp"
#include "..\BaseTypes\Object.hpp"


class SubroutineCommand : public Command, public Object {
public:
	SubroutineCommand( ) {}
	SubroutineCommand( const std::vector<Command*> &prg ) : code(prg) {}
	virtual ~SubroutineCommand() { 
	}
	
	virtual void execute( StackInterface *global ) {
		global->push( this );
	}
	
	void run( StackInterface *global ) {
		for( std::vector<Command*>::iterator command = code.begin(); command != code.end(); ++command ) {
			(*command)->execute( global );
		}
	}
	
	virtual std::string toString()       const { return "subroutine"; }
	virtual Object*     clone()          const { return new SubroutineCommand( code ); }
	virtual bool        equal(Object *o) const { 
		SubroutineCommand *sub = dynamic_cast<SubroutineCommand*>(o);
		if ( 0 == sub ) {
			return false;
		}
		return false;
	}
	
private:
	std::vector<Command*> code;
};

#endif // _SUBROUTINECOMMAND_