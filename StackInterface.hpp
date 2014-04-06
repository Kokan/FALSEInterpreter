#ifndef _STACK_INTERFACE_
#define _STACK_INTERFACE_

#include <stdexcept>

#include "BaseTypes\Object.hpp"

class StackInterface {
public:
	typedef unsigned int size_type;
	
	class StackIsFull : public std::out_of_range {
	public:
		StackIsFull() noexcept
		: std::out_of_range("Stack Size Limit Reached.")
		{}
		virtual ~StackIsFull() {}
	};
	
	class StackIsEmpty : public std::out_of_range {
	public:
		StackIsEmpty() noexcept
		: std::out_of_range("Stack is empty cannot remove anything.")
		{}
		virtual ~StackIsEmpty() {}
	};
	
	StackInterface() {}
	virtual ~StackInterface() {}
	
	virtual Object* top() const            = 0;
	virtual void    pop()                  = 0;
	virtual void    push(Object *o )       = 0;
	
	virtual size_type size() const         = 0;
};

#endif // _STACK_INTERFACE_
