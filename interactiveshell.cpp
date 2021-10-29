#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <optional>


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
#include "Commands/IFCommand.hpp"
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

enum class Token {
 Eof,
 Error,

 Digit,
 LogicConst,
 Add,
 Sub,
 Mul,
 Div,
 Neg,
 Dup,
 Not,
 Swap,
 Rot,
 Eq,
 Del,
 PrintInt,
 PrintCh,
 ReadInt,
 ReadCh,

 FuncStart,
 FuncEnd,
 FuncRun,
 If,
 While,

 Var,
 ReadVar,
 WriteVar,

 StringLit
};

std::pair<Token, std::optional<std::string>>
lexer( std::istream &is )
{
	char current;
	if (!is.get(current)) {
		return std::make_pair(Token::Eof, std::nullopt);
	}

	if ( ::isdigit(current) ) {
		std::string command = "";
		command = current;

		while ( ::isdigit(is.peek()) ) {
			command += is.get();
		}

		return std::make_pair(Token::Digit, command);
	}

	if ( 'f' == current && peekForText(is,"alse") ) {
		is.ignore(1,'\n');
		return std::make_pair(Token::LogicConst, "false");
	}
	if ( 't' == current && peekForText(is,"rue") ) {
		is.ignore(1,'\n');
		return std::make_pair(Token::LogicConst, "true");
	}
	if ('+' == current ) {
		return std::make_pair(Token::Add, std::nullopt);
	}
	if ('-' == current ) {
		return std::make_pair(Token::Sub, std::nullopt);
	}
	if ('*' == current ) {
		return std::make_pair(Token::Mul, std::nullopt);
	}
	if ('/' == current ) {
		return std::make_pair(Token::Div, std::nullopt);
	}
	if ('_' == current ) {
		return std::make_pair(Token::Neg, std::nullopt);
	}
	if ('$' == current ) {
		return std::make_pair(Token::Dup, std::nullopt);
	}
	if ('@' == current ) {
		return std::make_pair(Token::Rot, std::nullopt);
	}
	if ('=' == current ) {
		return std::make_pair(Token::Eq, std::nullopt);
	}
	if ('~' == current ) {
		return std::make_pair(Token::Not, std::nullopt);
	}
	if ('\\' == current ) {
		return std::make_pair(Token::Swap, std::nullopt);
	}
	if ('%' == current ) {
		return std::make_pair(Token::Del, std::nullopt);
	}
	if ('.' == current ) {
		return std::make_pair(Token::PrintInt, std::nullopt);
	}
	if (',' == current ) {
		return std::make_pair(Token::PrintCh, std::nullopt);
	}
	if ('^' == current ) {
		return std::make_pair(Token::ReadInt, std::nullopt);
	}
	if ('[' == current ) {
		return std::make_pair(Token::FuncStart, std::nullopt);
	}
	if (']' == current ) {
		return std::make_pair(Token::FuncEnd, std::nullopt);
	}
	if ('!' == current ) {
		return std::make_pair(Token::FuncRun, std::nullopt);
	}
	if ('?' == current ) {
		return std::make_pair(Token::If, std::nullopt);
	}
	if ('#' == current ) {
		return std::make_pair(Token::While, std::nullopt);
	}
	if ( isalpha(current) ) {
		std::string command = "";
		command = current;
		while ( isalpha(is.peek()) ) {
			command += is.get();
		}
		return std::make_pair(Token::Var, command);
	}
	if (':' == current) {
		return std::make_pair(Token::ReadVar, std::nullopt);
	}
	if (';' == current) {
		return std::make_pair(Token::WriteVar, std::nullopt);
	}
	if ('"' == current ) {
		std::string command = "";
		command = "";
		while ( is.peek() != '"' ) {
			command += is.get();
		}
		is.ignore(1,'"');
		return std::make_pair(Token::StringLit, command);
	}
	if ('{' == current ) {
		//Comment skip it
		while ( is.peek() != '}' ) {
			is.ignore(1);
		}
		is.ignore(1);

		//skip it, recursive call to obtain next token if any
		return lexer( is );
	}
	if ( isspace(current) ) {
		//skip it, recursive call to obtain next token if any
		return lexer( is );
	}

	std::stringstream err;
	err << "'" << current << "' unsupported command" << std::endl;

	return std::make_pair(Token::Error, err.str());
}

std::vector<Command*>
tree( std::istream &is ) {
	std::vector<Command*> prog;

	std::vector<std::vector<Command*>> subprg;
	std::pair<Token,std::optional<std::string>> token = lexer( is );
	std::optional<std::string> last_var = std::nullopt;
	while ( (token.first != Token::Eof) && (token.first != Token::Error) ) {
		Command *cmd = nullptr;

		switch (token.first) {
			case Token::Digit:
				cmd = new PushCommand(new Integer(to_number(token.second.value())));
			break;
			case Token::LogicConst:
				cmd = new PushCommand(new Bool("true" == token.second.value()));
			break;
			case Token::Add:
				cmd = new AddCommand();
			break;
			case Token::Sub:
				cmd = new SubCommand();
			break;
			case Token::Mul:
				cmd = new MultiplyCommand();
			break;
			case Token::Div:
				cmd = new DivideCommand();
			break;
			case Token::Neg:
				cmd = new NegationCommand();
			break;
			case Token::Dup:
				cmd = new DuplicateCommand();
			break;
			case Token::Rot:
				cmd = new ThirdToTopCommand();
			break;
			case Token::Eq:
				cmd = new EqualCommand();
			break;
			case Token::Not:
				cmd = new LogicalNotCommand();
			break;
			case Token::Swap:
				cmd = new SwapItemCommand();
			break;
			case Token::Del:
				cmd = new DeleteCommand();
			break;
			case Token::PrintInt:
				cmd = new PrintAsIntegerCommand();
			break;
			case Token::PrintCh:
				cmd = new PrintAsCharCommand();
			break;
			case Token::ReadInt:
				cmd = new ReadIntegerCommand();
			break;
			case Token::ReadCh:
				throw std::string("not implemented");
			break;

			case Token::FuncStart:
				subprg.push_back( std::vector<Command*>() );
			break;
			case Token::FuncEnd:
				cmd = new SubroutineCommand( subprg.back() );
				subprg.erase( subprg.end()-1 );
			break;
			case Token::FuncRun:
				cmd = new RunSubroutineCommand();
			break;

			case Token::If:
				cmd = new IFCommand();
			break;
			case Token::While:
				cmd = new WhileCommand();
			break;
			case Token::Var:
				last_var = token.second.value();
			break;
			case Token::ReadVar:
				cmd = new SetVariableCommand(last_var.value());
				last_var.reset();
			break;
			case Token::WriteVar:
				cmd = new GetVariableCommand(last_var.value());
				last_var.reset();
			break;
			case Token::StringLit:
				cmd = new StringCommand( token.second.value() );
			break;

			case Token::Eof:
			case Token::Error:
				throw std::string("Not reachable");
			break;
		}

		token = lexer( is );

		if (cmd==nullptr)
		{
			continue;
		}

		if ( subprg.size() > 0 ) {
			subprg.back().push_back( cmd );
		}
		else {
			prog.push_back( cmd );
		}
	}
	if ( token.first == Token::Error ) {
		std::cerr << "Error: " << token.second.value_or("(empty)") << std::endl;
	}

	return prog;
}

void run( std::istream &is, const bool shell ) {
	std::unique_ptr<StackInterface>  stack( new SimpleStack() );
	std::unique_ptr<MemoryInterface> global( new SimpleMemory(stack.get()) );

	if ( shell ) print("");

	std::vector<Command*> prog = tree( is );

	for (int i = 0; i < prog.size(); ++i ) {
		Command *cmd = prog[i];

		try {
			cmd->execute(global.get());
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
