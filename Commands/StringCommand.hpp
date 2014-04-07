#ifndef _STRINGCOMMAND_
#define _STRINGCOMMAND_

#include "Command.hpp"

class StringCommand : public Command {
public:
	StringCommand( const std::string &msg );
	virtual ~StringCommand();
	
	virtual void execute( MemoryInterface *global );
private:
	const std::string content;
};

#endif // _STRINGCOMMAND_