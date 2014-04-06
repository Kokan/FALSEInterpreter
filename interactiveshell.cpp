#include <iostream>
#include <algorithm>
#include <cstdlib>


#include "BaseTypes\Object.hpp"
#include "BaseTypes\Integer.hpp"
#include "BaseTypes\Bool.hpp"


#include "Commands\Command.hpp"
#include "Commands\PushCommand.hpp"
#include "Commands\AddCommand.hpp"
#include "Commands\DuplicateCommand.hpp"
#include "Commands\DeleteCommand.hpp"
#include "Commands\SwapItemCommand.hpp"
#include "Commands\SubroutineCommand.hpp"
#include "Commands\RunSubroutineCommand.hpp"
#include "Commands\EqualCommand.hpp"
#include "Commands\PrintAsIntegerCommand.hpp"
#include "Commands\LogicalNotCommand.hpp"
#include "Commands\IFCOmmand.hpp"
#include "Commands\WhileCommand.hpp"

#include "StackInterface.hpp"
#include "SimpleStack.hpp"




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
	std::cout << "FALSE> " << out ;	
}



int main( ) {
	StackInterface *global = new SimpleStack();
	
	std::string line;
	print("");
	while ( getline(std::cin,line) ) {
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
		else if ("$" == line ) {
			cmd = new DuplicateCommand();
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
		else {
			std::cerr << "'" << line << "' unsupported command" << std::endl;
		}
		
		try {
			if ( 0 != cmd )
				cmd->execute(global);
		}
		catch ( std::exception &e ) {
			std::cerr << "Runtime error: " << e.what() << std::endl;
		}
		
		print("");
	}
	
	
	return 0;
}