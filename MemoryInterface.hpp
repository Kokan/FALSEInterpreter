#ifndef _MEMORYINTERFACE_
#define _MEMORYINTERFACE_

#include "BaseTypes\Object.hpp"
#include "StackInterface.hpp"


class MemoryInterface {
public:
	MemoryInterface(StackInterface *s) : stack(s) { }
	virtual ~MemoryInterface() {}
	
	virtual Object* get( const std::string &variableName ) const          = 0;
	virtual void    set( const std::string &variableName, Object *value ) = 0;
	
	Object* top() const         { return stack->top(); }
	void    pop()               { stack->pop();        }
	void    push( Object *obj ) { stack->push(obj);    }
	virtual StackInterface::size_type size( ) const { return stack->size(); }

protected:
	StackInterface *stack;
};


#endif // _MEMORYINTERFACE_