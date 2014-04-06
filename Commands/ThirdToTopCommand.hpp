#ifndef _THIRDTOTOPCOMMAND_
#define _THIRDTOTOPCOMMAND_

#include "Command.hpp"


class ThirdToTopCommand : public Command {
public:
	ThirdToTopCommand( ) {}
	virtual ~ThirdToTopCommand() { 
	}
	
	virtual void execute( MemoryInterface *global ) {
		Object *first  = global->top();
		global->pop();
		Object *second = global->top();
		global->pop();
		Object *third = global->top();
		global->pop();
		
		global->push( second );
		global->push( first );
		global->push( third );
	}
};


#endif // _THIRDTOTOPCOMMAND_