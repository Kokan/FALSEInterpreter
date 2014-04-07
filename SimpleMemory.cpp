#include "SimpleMemory.hpp"

#include <memory>


SimpleMemory::SimpleMemory(StackInterface *s)
 : MemoryInterface(s) {
 }
 
 SimpleMemory::~SimpleMemory() {
 }
	
Object* SimpleMemory::get( const std::string &variableName ) const {
	if ( isContains(variableName) ) {
		return variables.at(variableName);
	}
	return nullptr;
}
	
void SimpleMemory::set( const std::string &variableName, Object *value ) {
	std::map<std::string,Object*>::const_iterator old = variables.find( variableName );
	if ( variables.end() != old ) {
		std::unique_ptr<Object> remove( variables.erase( old )->second );
	}
	
	variables[variableName] = value;
}

bool SimpleMemory::isContains( const std::string &variableName ) const {
	return ( variables.count(variableName) > 0 );
}