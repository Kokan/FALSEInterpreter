#ifndef _SUBROUTINECOMMAND_
#define _SUBROUTINECOMMAND_

#include <vector>

#include "Command.hpp"
#include "..\BaseTypes\Object.hpp"


class SubroutineCommand : public Command, public Object {
public:
	SubroutineCommand( );
	SubroutineCommand( const std::vector<Command*> &prg );
	virtual ~SubroutineCommand();
	
	virtual void execute( MemoryInterface *global );
	
	void run( MemoryInterface *global );
	
	virtual std::string toString()       const;
	virtual Object*     clone()          const;
	virtual bool        equal(Object *o) const;
	
private:
	std::vector<Command*> code;
};

#endif // _SUBROUTINECOMMAND_