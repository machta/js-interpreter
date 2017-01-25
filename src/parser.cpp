#include "parser.h"

#include "jast/parser.h"
#include "jast/ast-builder.h"
#include "jast/astfactory.h"
#include "jast/source-locator.h"
#include "jast/token.h"

#include <sstream>

using namespace std;

Parser::Parser()
{}

Parser::~Parser()
{}

jast::Expression* Parser::makeAST(string code, string* errorMessage)
{
	// TODO: save some of these objects for later.
	stringstream ss(code);
	jast::Scanner scanner(ss);
	jast::Tokenizer lex(&scanner);

	jast::ParserContext ctx{};
	jast::ASTFactory *factory = jast::ASTFactory::GetFactoryInstance();
	jast::SourceLocator locator(&lex);
	jast::ASTBuilder *builder = new jast::ASTBuilder(&ctx, factory, &locator);

	jast::Parser *parser = new jast::Parser(&ctx, builder, &lex);
	//lex.reset(&scanner); // Undefined reference.

	jast::Expression* ast = nullptr;

	try
	{
		ast = jast::ParseProgram(parser);
	}
	catch (exception& e)
	{
		ast = nullptr;
		*errorMessage = e.what();
	}

	return ast;
}

