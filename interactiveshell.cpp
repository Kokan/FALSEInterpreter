#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <cstdlib>


#include "BaseTypes/Object.hpp"
#include "BaseTypes/Integer.hpp"
#include "BaseTypes/Bool.hpp"


#include "Commands/Command.hpp"
#include "Commands/PushCommand.hpp"
#include "Commands/ArithmeticCommands.hpp"
#include "Commands/NegationCommand.hpp"
#include "Commands/DuplicateCommand.hpp"
#include "Commands/DeleteCommand.hpp"
#include "Commands/SwapItemCommand.hpp"
#include "Commands/ThirdToTopCommand.hpp"
#include "Commands/SubroutineCommand.hpp"
#include "Commands/RunSubroutineCommand.hpp"
#include "Commands/EqualCommand.hpp"
#include "Commands/StringCommand.hpp"
#include "Commands/PrintAsIntegerCommand.hpp"
#include "Commands/PrintAsCharCommand.hpp"
#include "Commands/ReadIntegerCommand.hpp"
#include "Commands/LogicalNotCommand.hpp"
#include "Commands/IFCOmmand.hpp"
#include "Commands/WhileCommand.hpp"
#include "Commands/SetVariableCommand.hpp"
#include "Commands/GetVariableCommand.hpp"

#include "StackInterface.hpp"
#include "SimpleStack.hpp"
#include "MemoryInterface.hpp"
#include "SimpleMemory.hpp"




bool is_number(const std::string &s) {
	std::string::const_iterator start = s.begin();
	if ( '-' == *start || '+' == *start ) {
		++start;
	}
  return (s.end() - start) > 0 && std::all_of(start, s.end(), ::isdigit);
}

int to_number(const std::string &s) {
	std::string tmp(s);
	int sign = 1;
	if ( '-' == tmp[0] ) {
		sign = -1;
		tmp = tmp.substr(1);
	}
	else if ( '+' == tmp[0] ) {
		sign = +1;
		tmp = tmp.substr(1);
	}
  return sign*atoi( tmp.c_str() );
}




void print(const std::string &out ) {
	std::cout << std::endl << "FALSE> " << out;
}

bool peekForText( std::istream &is, const std::string &text ) {
	std::string::size_type index = 0;
	
	while ( index < text.size() && is.peek() == text[index] ) {
		is.ignore(1);
		++index;
	}
	
	return text.size() > 0 && index == text.size();
}


void run( std::istream &is, const bool shell ) {
	std::unique_ptr<StackInterface>  stack( new SimpleStack() );
	std::unique_ptr<MemoryInterface> global( new SimpleMemory(stack.get()) );
	
	char current;
	std::string command="";
	if ( shell ) print("");
	std::vector<std::vector<Command*>> subprg;
	while ( (is.get(current)) ) {
		Command *cmd = 0;
		command = current;
		
		if ( ::isdigit(current) ) {
			
			while ( ::isdigit(is.peek()) ) {
				command += is.get();
			}
			
			cmd = new PushCommand(new Integer(to_number(command)));
			command = "";
		}
		else if ( 'f' == current && peekForText(is,"alse") ) {
			is.ignore(1,'\n');
			cmd = new PushCommand(new Bool(false));
		}
		else if ( 't' == current && peekForText(is,"rue") ) {
			is.ignore(1,'\n');
			cmd = new PushCommand(new Bool(true));
		}
		else if ('+' == current ) {
			cmd = new AddCommand();
		}
		else if ('-' == current ) {
			cmd = new SubCommand();
		}
		else if ('*' == current ) {
			cmd = new MultiplyCommand();
		}
		else if ('/' == current ) {
			cmd = new DivideCommand();
		}
		else if ('_' == current ) {
			cmd = new NegationCommand();
		}
		else if ('$' == current ) {
			cmd = new DuplicateCommand();
		}
		else if ('@' == current ) {
			cmd = new ThirdToTopCommand();
		}
		else if ('=' == current ) {
			cmd = new EqualCommand();
		}
		else if ('~' == current ) {
			cmd = new LogicalNotCommand();
		}
		else if ('\\' == current ) {
			cmd = new SwapItemCommand();
		}
		else if ('%' == current ) {
			cmd = new DeleteCommand();
		}
		else if ('.' == current ) {
			cmd = new PrintAsIntegerCommand();
		}
		else if (',' == current ) {
			cmd = new PrintAsCharCommand();
		}
		else if ('^' == current ) {
			cmd = new ReadIntegerCommand();
		}
		else if ('[' == current ) {
			subprg.push_back( std::vector<Command*>() );
		}
		else if (']' == current ) {
			cmd = new SubroutineCommand( subprg.back() );
			subprg.erase( subprg.end()-1 );
		}
		else if ('!' == current ) {
			cmd = new RunSubroutineCommand( );
		}
		else if ('?' == current ) {
			cmd = new IFCommand( );
		}
		else if ('#' == current ) {
			cmd = new WhileCommand( );
		}
		else if ( isalpha(current) ) {
			command = current;
			while ( ':' != is.peek() &&  ';' != is.peek() ) {
				command += is.get();
			}
			bool isRead = ':' == is.get();
			
			if ( isRead ) {
				cmd = new SetVariableCommand( command );
			}
			else {
				cmd = new GetVariableCommand( command );
			}
		}
		else if ('"' == current ) {
			command = "";
			while ( is.peek() != '"' ) {
				command += is.get();
			}
			is.ignore(1,'"');
			cmd = new StringCommand( command );
		}
		else if ('{' == current ) {
			//Comment skip it
			while ( is.peek() != '}' ) {
				is.ignore(1);
			}
			is.ignore(1);
			cmd = 0;
		}
		else if ( '\n' == current ) {
			if ( shell ) print("");
		}
		else if ( isspace(current) ) {
			//Skip it
		}
		else {
			std::cerr << "'" << command << "' unsupported command" << std::endl;
		}
		
		try {
			if ( 0 != cmd ) {
				if ( subprg.size() > 0 ) {
					subprg.back().push_back( cmd );
				}
				else {
					cmd->execute(global.get());
				}
			}
		}
		catch ( std::exception &e ) {
			std::cerr << "Runtime error: " << e.what() << std::endl;
		}
		
		
	}
}


int main( const int argn, const char *arg[] ) {
	if ( 2 == argn ) {
		std::ifstream ifs(arg[1]);
		
		if (!ifs) {
			std::cerr << "Cannot open file " << arg[1] << "!" << std::endl;
			return 1;
		}
		
		run( ifs, false );
	}
	else {
		run( std::cin, true );
	}
	
	return 0;
}