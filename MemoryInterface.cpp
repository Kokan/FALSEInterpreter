#include "MemoryInterface.hpp"

MemoryInterface::MemoryInterface(StackInterface *s)
: stack(s) {
}

MemoryInterface::~MemoryInterface() {
}

Object* MemoryInterface::top() const {
	return stack->top();
}

void MemoryInterface::pop() {
	stack->pop();
}

void MemoryInterface::push( Object *obj ) {
	stack->push(obj);
}

StackInterface::size_type MemoryInterface::size() const {
	return stack->size();
}
