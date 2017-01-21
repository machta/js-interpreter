#include "testcommon.h"

TEST(string_test, literal)
{
	TEST_EXPRESSION("bla bla", "var a = 'bla bla'; a;");
	TEST_EXPRESSION("bla bla", "var a = 'bla'; var b = 'bla bla';");

	TEST_EXPRESSION("bla bla", "var a = \"bla bla\"; a;");
	TEST_EXPRESSION("bla bla", "var a = 'bla';\n var b = 'bla bla'; var c = b; c;");
	TEST_EXPRESSION("bla bla", "var a = 'bla'; var b = 'bla bla'; var c = b; c;");

	TEST_EXPRESSION(3, "var a = 'bla'; a.length;");
}

TEST(string_test, cat)
{
	TEST_EXPRESSION("bla bla bla", "var a = 'bla';\n var b = 'bla bla';\n var c = a + ' ' + b; c;");
	TEST_EXPRESSION("bla bla bla", "var a = 'bla';\n var b = 'bla bla'; var c = a + ' ' + b; c;");
	TEST_EXPRESSION("bla bla bla", "var a = 'bla'; var b = 'bla bla';\n var c = a + ' ' + b; c;");
	TEST_EXPRESSION("bla bla bla", "var a = 'bla'; var b = 'bla bla'; var c = a + ' ' + b; c;");
}
