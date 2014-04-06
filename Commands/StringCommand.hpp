#ifndef _STRINGCOMMAND_
#define _STRINGCOMMAND_

#include <stdexcept>

#include "Command.hpp"

class StringCommand : public Command {
public:
	StringCommand( const std::string &msg ) : content(msg) {}
	virtual ~StringCommand() { 
	}
	
	virtual void execute( MemoryInterface *global ) {
		std::cout << content << std::endl;
		global->size();//FIX: unused variable msg
	}
private:
	const std::string content;
};

#endif // _STRINGCOMMAND_