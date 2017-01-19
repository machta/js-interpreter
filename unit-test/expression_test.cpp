#include "testcommon.h"

// TestCommon::testExpression(, "");

TEST(expression_test, assignment)
{
	// Ad-hoc.
	TestCommon::testExpression(true, "var x = 6, y = 3; (x + y) == 9 && x - y == 3;");
}

TEST(expression_test, binary_op)
{
	// Ad-hoc.
	TestCommon::testExpression(12, "var a = 5*1/1; a = a + 1; a = a*2; a;");
	TestCommon::testExpression(1, "var a = 13; a = a % 2; a;");
	TestCommon::testExpression(-1./3, "var a = 1/3; a = -a; a*1;");

	// Reference.
	TestCommon::testExpression(150, "var x = 100 + 50;");
	TestCommon::testExpression(7, "var x = 5; var y = 2; var z = x + y;");

	TestCommon::testExpression(3, "var x = 5; var y = 2; var z = x - y;");

	TestCommon::testExpression(10, "var x = 5; var y = 2; var z = x * y;");

	TestCommon::testExpression(2.5, "var x = 5; var y = 2; var z = x / y;");

	TestCommon::testExpression(1, "var x = 5; var y = 2; var z = x % y;");
}

TEST(expression_test, unary_op)
{
	// Ad-hoc.
	TestCommon::testExpression(12, "var a = 5; ++a*2;");
	TestCommon::testExpression(10, "var a = 5; a++*2;");
	TestCommon::testExpression(6, "var a = 5; a++*2; a;");
	TestCommon::testExpression(6, "var a = 5; ++a*2; a;");
	TestCommon::testExpression(32, "var a = 5; var c = --a*2; a*c;");
	TestCommon::testExpression(40, "var a = 5; var c = a--*2; a*c;");

	// Reference.
	TestCommon::testExpression(6, "var x = 5; x++; var z = x; z;");

	TestCommon::testExpression(4, "var x = 5; x--; var z = x; z;");
}

TEST(expression_test, comparison)
{
	// Reference.
	TestCommon::testExpression(false, "var x = 5; x == 8;");
	TestCommon::testExpression(true, "var x = 5; x == 5;");
	//TestCommon::testExpression(true, "var x = 5; x == '5';");
	//TestCommon::testExpression(true, "var x = 5; x == \"5\";");

	TestCommon::testExpression(true, "var x = 5; x === 5;");
	//TestCommon::testExpression(false, "var x = 5; x === '5';");

	TestCommon::testExpression(true, "var x = 5; x != 8;");

	TestCommon::testExpression(false, "var x = 5; x !== 5;");
	//TestCommon::testExpression(true, "var x = 5; x !== '5';");
	TestCommon::testExpression(true, "var x = 5; x !== 8;");

	TestCommon::testExpression(false, "var x = 5; x > 8;");

	TestCommon::testExpression(true, "var x = 5; x < 8;");

	TestCommon::testExpression(false, "var x = 5; x >= 8;");

	TestCommon::testExpression(true, "var x = 5; x <= 8;");

	TestCommon::testExpression(true, "2 < 12;");
	/*TestCommon::testExpression(true, "2 < '12';");
	TestCommon::testExpression(false, "2 < 'John';");
	TestCommon::testExpression(false, "2 > 'John';");
	TestCommon::testExpression(false, "2 == 'John'");
	TestCommon::testExpression(false, "'2' < '12';");
	TestCommon::testExpression(true, "'2' > '12';");
	TestCommon::testExpression(false, "'2' == '12';");
	TestCommon::testExpression(false, "'2' == '1';");
	TestCommon::testExpression(true, "'1' == '1';");*/
}

TEST(expression_test, logical_op)
{
	// Ad-hoc.
	TestCommon::testExpression(true, "var a = false; a = a || true; a;");
	//TestCommon::testExpression(true, "var a = false; a = !a; a;"); // Cannot be parsed for some reason.

	// Reference.
	TestCommon::testExpression(true, "var x = 6, y = 3; (x < 10 && y > 1);");

	TestCommon::testExpression(false, "var x = 6, y = 3; (x == 5 || y == 5);");

	//TestCommon::testExpression(true, "var x = 6, y = 3; !(x == y);"); // Parse error.
}

TEST(expression_test, bitwise_op)
{
	// Reference.
	TestCommon::testExpression(1, "5 & 1;");

	TestCommon::testExpression(5, "5 | 1;");
	TestCommon::testExpression(5, "4 | 1;");

	//TestCommon::testExpression(-6, "~5;");
	//TestCommon::testExpression(5, "~-6;");

	TestCommon::testExpression(4, "5 ^ 1;");

	//TestCommon::testExpression(10, "5 << 1;");

	//TestCommon::testExpression(2, "5 >> 1;");

	//TestCommon::testExpression(2, "5 >>> 1;"); // Not supported.
}

TEST(expression_test, precedence)
{
	// Reference.
	TestCommon::testExpression(250, "var x = 100 + 50 * 3;");
	TestCommon::testExpression(450, "var x = (100 + 50) * 3;");
	TestCommon::testExpression(147, "var x = 100 + 50 - 3;");
}
