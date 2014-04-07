#ifndef _INTERFACE_OBJECT_
#define _INTERFACE_OBJECT_

#include <string>
#include <ostream>

class Object {
public:
	Object() {}
	virtual ~Object() {}
	
	virtual std::string toString()       const = 0;
	virtual Object*     clone()          const = 0;
	virtual bool        equal(Object *o) const = 0;
};

std::ostream& operator<<( std::ostream &out, const Object &o );

#endif // _INTERFACE_OBJECT_