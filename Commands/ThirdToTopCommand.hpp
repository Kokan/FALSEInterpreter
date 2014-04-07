#ifndef _THIRDTOTOPCOMMAND_
#define _THIRDTOTOPCOMMAND_

#include "Command.hpp"


class ThirdToTopCommand : public Command {
public:
	ThirdToTopCommand( );
	virtual ~ThirdToTopCommand();
	
	virtual void execute( MemoryInterface *global );
};


#endif // _THIRDTOTOPCOMMAND_