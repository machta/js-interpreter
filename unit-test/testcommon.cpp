#include "testcommon.h"

#include "parser.h"
#include "interpreter.h"

using namespace std;

namespace
{

const double ABSOLUTE_ERROR = 0.000001;

string execute(const string& code)
{
	Parser p;

	grok::parser::Expression* e = p.makeAST(code);

	ValueContext context;

	Interpreter interpreter(&context);
	e->Accept(&interpreter);

	delete e;
	return interpreter.lastStatementToString();
}

} // namespace

void TestCommon::testExpression(double n, const string& code)
{
	double res = stod(execute(code));
	EXPECT_NEAR(n, res, ABSOLUTE_ERROR);
}

void TestCommon::testExpression(bool b, const string& code)
{
	int res = -1;
	string str = execute(code);

	if (str == "false")
		res = 0;
	else if (str == "true")
		res = 1;

	if (b)
		EXPECT_EQ(res, 1);
	else
		EXPECT_EQ(res, 0);
}

void TestCommon::testExpression(const string& answer, const string& code)
{
	string str = execute(code);
	EXPECT_EQ(answer, str);
}
