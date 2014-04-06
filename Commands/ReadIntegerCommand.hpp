#ifndef _READINTEGERCOMMAND_
#define _READINTEGERCOMMAND_

#include <iostream>

#include "Command.hpp"
#include "..\BaseTypes\Integer.hpp"

class ReadIntegerCommand : public Command {
public:
	ReadIntegerCommand( ) {}
	virtual ~ReadIntegerCommand() { 
	}
	
	virtual void execute( MemoryInterface *global ) {
		char byte;
		Object *obj  = nullptr;
		
		std::cin >> byte;
		std::cin.ignore(256,'\n');
		
		if ( std::cin ) {
			obj = new Integer((int)byte);
			global->push( obj );
		}
	}
};

#endif // _READINTEGERCOMMAND_