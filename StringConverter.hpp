#ifndef _STRING_CONVERTER_
#define _STRING_CONVERTER_

#include <string>
#include <sstream>

template<typename T>
std::string to_string( const T &value ) {
	std::stringstream ss;
	ss << std::boolalpha << value;
	
	return ss.str();
};

#endif // _STRING_CONVERTER_