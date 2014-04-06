#ifndef _SIMPLE_STACK_
#define _SIMPLE_STACK_

#include <vector>
#include <stack>
#include <stdexcept>

#include "StackInterface.hpp"

class SimpleStack : public StackInterface {
public:
	SimpleStack() {}
	virtual ~SimpleStack() {}
	
	virtual Object* top() const      { if ( size() == 0 ) throw StackIsEmpty(); return container.top();  }
	virtual void    pop()            { if ( size() == 0 ) throw StackIsEmpty(); container.pop();         }
	virtual void    push(Object *o ) { container.push( o );     }
	virtual size_type size() const   { return container.size(); }
private:
	std::stack<Object*, std::vector<Object*> > container;
};


#endif // _SIMPLE_STACK_