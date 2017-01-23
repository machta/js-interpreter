#ifndef PARSER_H
#define PARSER_H

#include <parser/expression.h>

#include <string>

namespace grok { namespace parser
{
class ParserContext;
class LexerInfo;
class ASTFactory;
class ASTBuilder;
class Parser;
}
}

class Parser
{
	grok::parser::ParserContext* ctx;
	grok::parser::LexerInfo* lex;
	grok::parser::SourceLocator* locator;
	grok::parser::ASTFactory* factory;
	grok::parser::ASTBuilder* builder;
	grok::parser::Parser* parser;


public:
	Parser();
	~Parser();

	grok::parser::Expression* makeAST(std::string code, std::string* errorMessage);
};

#endif // PARSER_H
