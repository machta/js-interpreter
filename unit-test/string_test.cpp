#include "testcommon.h"

TEST(string_test, literal)
{
	TEST_EXPRESSION("'bla bla'", "var a = 'bla bla'; a;"); // Parser doesn't strip the quotation marks.
	TEST_EXPRESSION("\"bla bla\"", "var a = \"bla bla\"; a;");
	TEST_EXPRESSION("'bla bla'", "var a = 'bla';\n var b = 'bla bla'; var c = b; c;");

	TEST_EXPRESSION(5, "var a = 'bla'; a.length;"); // TODO: Fix this: 5 should be 3. The parser includes the quotes in the string.
}

TEST(string_test, cat)
{
	TEST_EXPRESSION("'bla'' ''bla bla'", "var a = 'bla';\n var b = 'bla bla';\n var c = a + ' ' + b; c;");
	//TEST_EXPRESSION("'bla'' ''bla bla'", "var a = 'bla'; var b = 'bla bla'; var c = a + ' ' + b; c;"); // Parser fails when there are more than one string literals on one line.
}
