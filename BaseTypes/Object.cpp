#include "Object.hpp"

std::ostream& operator<<( std::ostream &out, const Object &o ) {
	return ( out << o.toString() );
}