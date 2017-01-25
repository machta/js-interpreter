#include "testcommon.h"

TEST(control_flow_test, for_loop)
{
	TEST_EXPRESSION(10, "var a = 5; for (i = 0; i < 5; i++) a = a + 1; a;");
	TEST_EXPRESSION(5, "var a = 5; for (i = 0; i < 5; i++) var b = a + 1; a;");
	TEST_EXPRESSION(10, "var a = 5; for (i = 0; i < 5; i++) var a = a + 1; a;");
}

TEST(control_flow_test, while_do)
{
	TEST_EXPRESSION(65, "var a = 2; var i = 4; while (i >= 0) {a = a*2; i = i - 1;} a + 1;");
	TEST_EXPRESSION(33, "var a = 2; var i = 4; do {a = a*2; i = i - 1;} while (i > 0); a + 1;");
}

TEST(control_flow_test, if_else)
{
	TEST_EXPRESSION(10, "var a = 5; if (a > 10) a = a + 1; a*2;");
	TEST_EXPRESSION(14, "var a = 5; if (a > 10) a = a + 1; else { a = a + 2;} a*2;");
}

TEST(control_flow_test, ternary)
{
	TEST_EXPRESSION(10, "var c = 5; var a = c>=5 ? 2*c : 2*2*c; a;");
	TEST_EXPRESSION(25, "var c = 5; var a = 1>10 ? 20*c : c*c; a;");
	TEST_EXPRESSION(50, "var c = 5; var a = (1>10 ? 20*c : c*c)*2; a;");
}

TEST(control_flow_test, break_statement)
{
	TEST_EXPRESSION(10, "var a = 0; for (b = 0; b < 10; b++){ a++;} a;");

	TEST_EXPRESSION(5, "var a = 0; while(true){ if (a >= 5) {break;} a++;} a;");

	TEST_EXPRESSION(5, "var a = 0; var b = 0; while(b < 10){ b++; if (a >= 5) break; a++;} a;");

	TEST_EXPRESSION(5, "var a = 0; for (b = 0; b < 10; b++){ if (a >= 5) {break;} a++;} a;");
	TEST_EXPRESSION(5, "var a = 0; for (b = 0; b < 10; b++){ if (a >= 5)  break;  a++;} a;");

	//TEST_EXPRESSION(5, "var a = 0; for (;;){ if (a >= 5) break;} a;"); // Weird undefined phantom variable.
}

TEST(control_flow_test, continue_statement)
{
	TEST_EXPRESSION(5, "var a = 0; var b = 0; while(b < 10){ b++; if (a >= 5) {continue;} a++;} a;");
	TEST_EXPRESSION(5, "var a = 0; var b = 0; while(b < 10){ b++; if (a >= 5)  continue;  a++;} a;");

	TEST_EXPRESSION(5, "var a = 0; for (b = 0; b < 10; b++){ if (a >= 5) {continue;} a++;} a;");
	TEST_EXPRESSION(5, "var a = 0; for (b = 0; b < 10; b++){ if (a >= 5)  continue;  a++;} a;");
}
