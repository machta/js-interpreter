#include "testcommon.h"

TEST(expression_test, assignment)
{
	TEST_EXPRESSION(true, "var x = 6, y = 3; (x + y) == 9 && x - y == 3;");
}

TEST(expression_test, binary_op)
{
	TEST_EXPRESSION(12, "var a = 5*1/1; a = a + 1; a = a*2; a;");
	TEST_EXPRESSION(1, "var a = 13; a = a % 2; a;");
	TEST_EXPRESSION(-1./3, "var a = 1/3; a = -a; a*1;");

	// Reference.
	TEST_EXPRESSION(150, "var x = 100 + 50;");
	TEST_EXPRESSION(7, "var x = 5; var y = 2; var z = x + y;");

	TEST_EXPRESSION(3, "var x = 5; var y = 2; var z = x - y;");

	TEST_EXPRESSION(10, "var x = 5; var y = 2; var z = x * y;");

	TEST_EXPRESSION(2.5, "var x = 5; var y = 2; var z = x / y;");

	TEST_EXPRESSION(1, "var x = 5; var y = 2; var z = x % y;");
}

TEST(expression_test, unary_op)
{
	TEST_EXPRESSION(12, "var a = 5; ++a*2;");
	TEST_EXPRESSION(10, "var a = 5; a++*2;");
	TEST_EXPRESSION(6, "var a = 5; a++*2; a;");
	TEST_EXPRESSION(6, "var a = 5; ++a*2; a;");
	TEST_EXPRESSION(32, "var a = 5; var c = --a*2; a*c;");
	TEST_EXPRESSION(40, "var a = 5; var c = a--*2; a*c;");

	// Reference.
	TEST_EXPRESSION(6, "var x = 5; x++; var z = x; z;");

	TEST_EXPRESSION(4, "var x = 5; x--; var z = x; z;");
}

TEST(expression_test, comparison)
{
	// Reference.
	TEST_EXPRESSION(false, "var x = 5; x == 8;");
	TEST_EXPRESSION(true, "var x = 5; x == 5;");
	TEST_EXPRESSION(true, "var x = 5; x == '5';");
	TEST_EXPRESSION(true, "var x = 5; x == \"5\";");

	TEST_EXPRESSION(true, "var x = 5; x === 5;");
	TEST_EXPRESSION(false, "var x = 5; x === '5';");

	TEST_EXPRESSION(true, "var x = 5; x != 8;");

	TEST_EXPRESSION(false, "var x = 5; x !== 5;");
	TEST_EXPRESSION(true, "var x = 5; x !== '5';");
	TEST_EXPRESSION(true, "var x = 5; x !== 8;");

	TEST_EXPRESSION(false, "var x = 5; x > 8;");

	TEST_EXPRESSION(true, "var x = 5; x < 8;");

	TEST_EXPRESSION(false, "var x = 5; x >= 8;");

	TEST_EXPRESSION(true, "var x = 5; x <= 8;");

	TEST_EXPRESSION(true, "2 < 12;");
	TEST_EXPRESSION(true, "2 < '12';");
	TEST_EXPRESSION(false, "2 < 'John';");
	TEST_EXPRESSION(false, "2 > 'John';");
	TEST_EXPRESSION(false, "2 == 'John';");
	TEST_EXPRESSION(false, "'2' < '12';");
	TEST_EXPRESSION(true, "'2' > '12';");
	TEST_EXPRESSION(false, "'2' == '12';");
	TEST_EXPRESSION(false, "'2' == '1';");
	TEST_EXPRESSION(true, "'1' == '1';");
}

TEST(expression_test, logical_op)
{
	TEST_EXPRESSION(true, "var a = false; a = a || true; a;");
	TEST_EXPRESSION(true, "var a = false; a = !a; a;");

	// Reference.
	TEST_EXPRESSION(true, "var x = 6, y = 3; (x < 10 && y > 1);");

	TEST_EXPRESSION(false, "var x = 6, y = 3; (x == 5 || y == 5);");

	TEST_EXPRESSION(true, "var x = 6, y = 3; !(x == y);");
}

TEST(expression_test, bitwise_op)
{
	// Reference.
	TEST_EXPRESSION(1, "5 & 1;");

	TEST_EXPRESSION(5, "5 | 1;");
	TEST_EXPRESSION(5, "4 | 1;");

	TEST_EXPRESSION(-6, "~5;");
	TEST_EXPRESSION(5, "~(-6);");
	//TEST_EXPRESSION(5, "~-6;"); // Parses with bad precedence.

	TEST_EXPRESSION(4, "5 ^ 1;");

	TEST_EXPRESSION(10, "5 << 1;");

	TEST_EXPRESSION(2, "5 >> 1;");
	TEST_EXPRESSION(-3, "(-5) >> 1;");
	//TEST_EXPRESSION(-3, "-5 >> 1;"); // Parses with bad precedence.

	TEST_EXPRESSION(2, "5 >>> 1;");
	TEST_EXPRESSION(2147483645, "(-5) >>> 1;");
	//TEST_EXPRESSION(2147483645, "-5 >>> 1;"); // Parses with bad precedence.
}

TEST(expression_test, precedence)
{
	// Reference.
	TEST_EXPRESSION(250, "var x = 100 + 50 * 3;");
	TEST_EXPRESSION(450, "var x = (100 + 50) * 3;");
	TEST_EXPRESSION(147, "var x = 100 + 50 - 3;");
}
