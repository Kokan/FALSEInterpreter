#include "SimpleStack.hpp"

#include <vector>
#include <stack>
#include <stdexcept>

SimpleStack::SimpleStack() {
}

SimpleStack::~SimpleStack() {
}

Object* SimpleStack::top() const {
	if ( size() == 0 ) {
		throw StackIsEmpty();
	}
	
	return container.top();
}

void    SimpleStack::pop() {
	if ( size() == 0 ) {
		throw StackIsEmpty();
	}
	
	container.pop();
}

void SimpleStack::push(Object *o ) {
	container.push( o );
}

SimpleStack::size_type SimpleStack::size() const {
	return container.size();
}