#ifndef _BOOL_
#define _BOOL_

#include "..\StringConverter.hpp"
#include "Object.hpp"


class Bool : public Object {
public:

	Bool( const bool initValue = false )
	: value( initValue ) 
	{}
	
	virtual ~Bool() {}
	
	virtual std::string toString() const { return to_string( value ); }
	virtual Object*     clone()    const { return new Bool( get() ); }
	virtual bool        equal(Object *o) const {
		Bool *toBool = dynamic_cast<Bool*>(o);
		if ( 0 == toBool ) {
			return false;
		}
		
		if ( toBool->get() == this->get() ) {
			return true;
		}
		
		return false;
	}
	
	bool get() const { return value; }
	
protected:
	const bool value;
};

#endif // _BOOL_