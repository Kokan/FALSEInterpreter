#include <iostream>

#include "..\BaseTypes\Object.hpp"
#include "..\BaseTypes\TypeHolder.hpp"
#include "..\BaseTypes\Bool.hpp"
#include "..\BaseTypes\Integer.hpp"
#include "..\BaseTypes\Char.hpp"



int main() {
	Object *object;
	
	object = new Bool();
	object = new Integer();
	object = new Char();
	object = new TypeHolder<std::string>("[OK]");
	
	
	std::cout << object->toString() << std::endl;
	
	return 0;
}