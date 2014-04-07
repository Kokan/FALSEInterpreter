#ifndef _SIMPLE_STACK_
#define _SIMPLE_STACK_

#include <vector>
#include <stack>
#include <stdexcept>

#include "StackInterface.hpp"

class SimpleStack : public StackInterface {
public:
	SimpleStack();
	virtual ~SimpleStack();
	
	virtual Object* top() const;
	virtual void    pop();
	virtual void    push(Object *o );
	virtual size_type size() const;
private:
	std::stack<Object*, std::vector<Object*> > container;
};


#endif // _SIMPLE_STACK_