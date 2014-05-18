#ifndef _MEMORYINTERFACE_
#define _MEMORYINTERFACE_

#include "StackInterface.hpp"

class Object;

class MemoryInterface {
public:
	MemoryInterface(StackInterface *s);
	virtual ~MemoryInterface();
	
	virtual Object* get( const std::string &variableName ) const          = 0;
	virtual void    set( const std::string &variableName, Object *value ) = 0;
	
	Object* top() const;
	void    pop();
	void    push( Object *obj );
	virtual StackInterface::size_type size( ) const;

protected:
	StackInterface *stack;
};


#endif // _MEMORYINTERFACE_
