#ifndef _SIMPLEMEMORY_
#define _SIMPLEMEMORY_

#include <memory>

#include "BaseTypes\Object.hpp"
#include "MemoryInterface.hpp"

#include <map>

class SimpleMemory : public MemoryInterface {
public:
	SimpleMemory(StackInterface *s) : MemoryInterface(s) { }
	virtual ~SimpleMemory() {}
	
	virtual Object* get( const std::string &variableName ) const {
		if ( isContains(variableName) ) {
			return variables.at(variableName);
		}
		return nullptr;
	}
	
	virtual void    set( const std::string &variableName, Object *value ) {
		std::map<std::string,Object*>::const_iterator old = variables.find( variableName );
		if ( variables.end() != old ) {
			std::unique_ptr<Object> remove( variables.erase( old )->second );
		}
		
		variables[variableName] = value;
	}

private:
	bool isContains( const std::string &variableName ) const {
		return ( variables.count(variableName) > 0 );
	}

	std::map<std::string,Object*> variables;
};


#endif // _SIMPLEMEMORY_