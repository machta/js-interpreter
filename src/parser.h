#ifndef PARSER_H
#define PARSER_H

#include <jast/expression.h>

#include <string>

class Parser
{
public:
	Parser();
	~Parser();

	jast::Expression* makeAST(std::string code, std::string* errorMessage);
};

#endif // PARSER_H
