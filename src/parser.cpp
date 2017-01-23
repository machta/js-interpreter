#include "parser.h"

#include "parser/parser.h"
#include "parser/ast-builder.h"
#include "parser/astfactory.h"
#include "parser/lexinfo.h"
#include "parser/source-locator.h"
#include "parser/token.h"

using namespace std;

Parser::Parser()
{
	ctx = new grok::parser::ParserContext();
	lex = new grok::parser::LexerInfo();
	locator = new grok::parser::SourceLocator(lex);
	factory = grok::parser::ASTFactory::GetFactoryInstance();
	builder = new grok::parser::ASTBuilder(ctx, factory, locator);
	parser = new grok::parser::Parser(ctx, builder, lex);
}

Parser::~Parser()
{
	delete parser;
	delete builder;
}

grok::parser::Expression* Parser::makeAST(string code, string* errorMessage)
{
	grok::parser::Expression* ast = nullptr;

	try
	{
		ast = grok::parser::ParseProgram(parser, code);
	}
	catch (exception& e)
	{
		//std::cout << "\x1b[33mError\x1b[0m" << std::endl; // TODO: Change the error output format here.
		grok::parser::LexerInfo::Restart();
		ast = nullptr;
		*errorMessage = e.what();
	}

	return ast;
}

