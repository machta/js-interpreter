#include "testcommon.h"

#include "parser.h"
#include "interpreter.h"

using namespace std;

namespace
{

const double ABSOLUTE_ERROR = 0.000001;

Value execute(const string& code)
{
	Parser p;
	ValueContext context;

	grok::parser::Expression* e = p.makeAST(code);

	Interpreter interpreter(&context);
	e->Accept(&interpreter);

	delete e;
	return interpreter.lastStatementValue();
}

} // namespace

void TestCommon::testExpression(double n, const string& code)
{
	Value res = execute(code);
	EXPECT_DOUBLE_EQ(n, res.toNumber());
	//EXPECT_NEAR(n, res.toNumber(), ABSOLUTE_ERROR);
}

void TestCommon::testExpression(int n, const string& code)
{
	Value res = execute(code);
	EXPECT_DOUBLE_EQ(static_cast<double>(n), res.toNumber());
}

void TestCommon::testExpression(bool b, const string& code)
{
	Value res = execute(code);
	EXPECT_EQ(b, res.toBoolean());
}

void TestCommon::testExpression(const string& answer, const string& code)
{
	Value res = execute(code);
	EXPECT_EQ(answer, res.toString());
}
