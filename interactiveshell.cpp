#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <cstdlib>


#include "BaseTypes\Object.hpp"
#include "BaseTypes\Integer.hpp"
#include "BaseTypes\Bool.hpp"


#include "Commands\Command.hpp"
#include "Commands\PushCommand.hpp"
#include "Commands\ArithmeticCommands.hpp"
#include "Commands\DuplicateCommand.hpp"
#include "Commands\DeleteCommand.hpp"
#include "Commands\SwapItemCommand.hpp"
#include "Commands\ThirdToTopCommand.hpp"
#include "Commands\SubroutineCommand.hpp"
#include "Commands\RunSubroutineCommand.hpp"
#include "Commands\EqualCommand.hpp"
#include "Commands\StringCommand.hpp"
#include "Commands\PrintAsIntegerCommand.hpp"
#include "Commands\PrintAsCharCommand.hpp"
#include "Commands\ReadIntegerCommand.hpp"
#include "Commands\LogicalNotCommand.hpp"
#include "Commands\IFCOmmand.hpp"
#include "Commands\WhileCommand.hpp"
#include "Commands\SetVariableCommand.hpp"
#include "Commands\GetVariableCommand.hpp"

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


void run( std::istream &is, const bool shell ) {
	std::unique_ptr<StackInterface>  stack( new SimpleStack() );
	std::unique_ptr<MemoryInterface> global( new SimpleMemory(stack.get()) );
	
	std::string line;
	if ( shell ) print("");
	std::vector<std::vector<Command*>> subprg;
	while ( getline(is,line) ) {
		Command *cmd = 0;
		if ( is_number(line) ) {
			cmd = new PushCommand(new Integer(to_number(line)));
		}
		else if ( "false" == line ) {
			cmd = new PushCommand(new Bool(false));
		}
		else if ( "true" == line ) {
			cmd = new PushCommand(new Bool(true));
		}
		else if ("+" == line ) {
			cmd = new AddCommand();
		}
		else if ("-" == line ) {
			cmd = new SubCommand();
		}
		else if ("*" == line ) {
			cmd = new MultiplyCommand();
		}
		else if ("/" == line ) {
			cmd = new DivideCommand();
		}
		else if ("$" == line ) {
			cmd = new DuplicateCommand();
		}
		else if ("@" == line ) {
			cmd = new ThirdToTopCommand();
		}
		else if ("=" == line ) {
			cmd = new EqualCommand();
		}
		else if ("~" == line ) {
			cmd = new LogicalNotCommand();
		}
		else if ("\\" == line ) {
			cmd = new SwapItemCommand();
		}
		else if ("%" == line ) {
			cmd = new DeleteCommand();
		}
		else if ("." == line ) {
			cmd = new PrintAsIntegerCommand();
		}
		else if ("," == line ) {
			cmd = new PrintAsCharCommand();
		}
		else if ("^" == line ) {
			cmd = new ReadIntegerCommand();
		}
		else if ("[" == line ) {
			subprg.push_back( std::vector<Command*>() );
		}
		else if ("]" == line ) {
			cmd = new SubroutineCommand( subprg.back() );
			subprg.erase( subprg.end()-1 );
		}
		else if ("!" == line ) {
			cmd = new RunSubroutineCommand( );
		}
		else if ("?" == line ) {
			cmd = new IFCommand( );
		}
		else if ("#" == line ) {
			cmd = new WhileCommand( );
		}
		else if (std::string::npos != line.find(':') ) {
			std::string varName( line.begin(), line.begin()+line.find(':') );
			cmd = new SetVariableCommand( varName );
		}
		else if (std::string::npos != line.find(';') ) {
			std::string varName( line.begin(), line.begin()+line.find(';') );
			cmd = new GetVariableCommand( varName );
		}
		else if ('"' == line[0] ) {
			cmd = new StringCommand( line );
		}
		else if ('{' == line[0] ) {
			//Comment skip it
			cmd = 0;
		}
		else {
			std::cerr << "'" << line << "' unsupported command" << std::endl;
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
		
		if ( shell ) print("");
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