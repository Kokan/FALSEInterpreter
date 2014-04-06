#ifndef _INTEGER_
#define _INTEGER_

#include "..\StringConverter.hpp"
#include "Object.hpp"


class Integer : public Object {
public:

	Integer( const int initValue = 0 )
	: value( initValue ) 
	{}
	
	virtual ~Integer() {}
	
	virtual std::string toString()       const { return to_string( value ); }
	virtual Object*     clone()          const { return new Integer( get() ); }
	virtual bool        equal(Object *o) const {
		Integer *toInteger = dynamic_cast<Integer*>(o);
		if ( 0 == toInteger ) {
			return false;
		}
		
		if ( toInteger->get() == this->get() ) {
			return true;
		}
		
		return false;
	}
	
	int get() const { return value; }
	
protected:
	const int value;
};

#endif // _INTEGER_