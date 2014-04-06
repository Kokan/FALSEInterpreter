#include <iostream>

#include "Object.hpp"
#include "Bool.hpp"
#include "Integer.hpp"



int main() {
	Object *b = new Bool();
	
	std::cout << b->toString() << std::endl;
	
	b = new Integer();
	
	std::cout << b->toString() << std::endl;
	
	b = new Integer(5);
	
	std::cout << b->toString() << std::endl;
	
	Bool *booltype = dynamic_cast<Bool*>( b );
	if ( 0 == booltype ) {
		std::cout << "The type is not Bool" << std::endl;
		return 1;
	}
	std::cout << booltype->get() << std::endl;
	
	return 0;
}