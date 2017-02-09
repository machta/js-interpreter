#include "testcommon.h"

TEST(built_in_test, console)
{
	TEST_EXPRESSION(2, "var a = 2; console.log(a); a;");
	TEST_EXPRESSION(1, "console.log('5*5*5 = ' + 5*5*5); 1;");
}

TEST(built_in_test, math)
{
	TEST_EXPRESSION(4, "Math.sqrt(16);");
	TEST_EXPRESSION(3, "Math.sqrt(9);");
	TEST_EXPRESSION(2, "Math.sqrt(2)*Math.sqrt(2);");
	TEST_EXPRESSION(sqrt(2), "Math.sqrt(2);");
}
