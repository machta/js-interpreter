#include "testcommon.h"

TEST(string_test, literal)
{
	TestCommon::testExpression("'bla bla'", "var a = 'bla bla'; a;"); // Parser doesn't strip the quotation marks.
	TestCommon::testExpression("\"bla bla\"", "var a = \"bla bla\"; a;");
	TestCommon::testExpression("'bla bla'", "var a = 'bla';\n var b = 'bla bla'; var c = b; c;");
}

TEST(string_test, cat)
{
	TestCommon::testExpression("'bla'' ''bla bla'", "var a = 'bla';\n var b = 'bla bla';\n var c = a + ' ' + b; c;");
	//TestCommon::testExpression("'bla'' ''bla bla'", "var a = 'bla'; var b = 'bla bla'; var c = a + ' ' + b; c;"); // Parser fails when there are more than one string literals on one line.
}
