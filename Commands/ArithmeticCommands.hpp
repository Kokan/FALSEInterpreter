#ifndef _ARITHMETICCOMMAND_
#define _ARITHMETICCOMMAND_

#include <functional>

#include "Command.hpp"
#include "../BaseTypes/Integer.hpp"
#include "BinaryOperatorCommand.hpp"

typedef BinaryOperatorCommand<std::plus<int>,Integer>       AddCommand;
typedef BinaryOperatorCommand<std::minus<int>,Integer>      SubCommand;
typedef BinaryOperatorCommand<std::multiplies<int>,Integer> MultiplyCommand;
typedef BinaryOperatorCommand<std::divides<int>,Integer>    DivideCommand;


#endif // _ARITHMETICCOMMAND_