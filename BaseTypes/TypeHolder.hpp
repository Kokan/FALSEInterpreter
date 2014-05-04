#ifndef _TYPE_HOLDER_OBJECT_
#define _TYPE_HOLDER_OBJECT_

#include "../StringConverter.hpp"
#include "Object.hpp"

template<typename Type>
class TypeHolder : public Object {
public:

	TypeHolder( const Type initValue = 0 )
	: value( initValue ) 
	{}
	
	virtual ~TypeHolder() {}
	
	virtual std::string toString()       const { return to_string( value ); }
	virtual Object*     clone()          const { return new TypeHolder( get() ); }
	virtual bool        equal(Object *o) const {
		TypeHolder *toTypeHolder = dynamic_cast<TypeHolder*>(o);
		if ( 0 == toTypeHolder ) {
			return false;
		}
		
		if ( toTypeHolder->get() == this->get() ) {
			return true;
		}
		
		return false;
	}
	
	Type get() const { return value; }
	
protected:
	const Type value;
};

#endif // _TYPE_HOLDER_OBJECT_