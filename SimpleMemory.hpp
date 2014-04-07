#ifndef _SIMPLEMEMORY_
#define _SIMPLEMEMORY_

#include <map>

#include "BaseTypes\Object.hpp"
#include "MemoryInterface.hpp"


class SimpleMemory : public MemoryInterface {
public:
	SimpleMemory(StackInterface *s);
	virtual ~SimpleMemory();
	
	virtual Object* get( const std::string &variableName ) const;
	virtual void    set( const std::string &variableName, Object *value );

private:
	bool isContains( const std::string &variableName ) const;

	std::map<std::string,Object*> variables;
};


#endif // _SIMPLEMEMORY_