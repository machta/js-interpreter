#include "parser.h"

#include "parser/parser.h"
#include "parser/ast-builder.h"
#include "parser/astfactory.h"
#include "parser/lexinfo.h"
#include "parser/source-locator.h"
#include "parser/token.h"

using namespace std;

grok::parser::Expression* Parser::makeAST(string code)
{
	grok::parser::ParserContext ctx{};

	// create a LexerInfo object, will store information about string
	grok::parser::LexerInfo lex;

	// create a locator object this will help in printing position of errors
	grok::parser::SourceLocator locator(&lex);

	// ASTFactory object factory for AST nodes
	grok::parser::ASTFactory *factory = grok::parser::ASTFactory::GetFactoryInstance();

	// create an ASTBuilder object for building ast
	grok::parser::ASTBuilder *builder = new grok::parser::ASTBuilder(&ctx, factory, &locator);

	grok::parser::Parser *parser = new grok::parser::Parser(&ctx, builder, &lex);
	grok::parser::Expression *ast = nullptr;

	// TODO: Save the above objects, so that they don't have to be created every time.
	try
	{
		ast = grok::parser::ParseProgram(parser, code);
	}
	catch (std::exception &)
	{
		std::cout << "\x1b[33mError\x1b[0m" << std::endl; // TODO: Change the error output format here.
		grok::parser::LexerInfo::Restart();
		ast = nullptr;
	}

	delete parser;
	delete builder;

	return ast;
}

