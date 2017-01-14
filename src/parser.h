#ifndef PARSER_H
#define PARSER_H

#include <parser/expression.h>

#include <string>

class Parser
{
public:
	Parser()
	{}

	grok::parser::Expression* makeAST(std::string code);
};

#endif // PARSER_H
