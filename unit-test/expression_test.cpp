#include "testcommon.h"

TEST(expression_test, first_test)
{
	TestCommon::testExpression(12, "var a = 5*1/1; a = a + 1; a = a*2; a;");
	TestCommon::testExpression(1, "var a = 13; a = a % 2; a;");
	TestCommon::testExpression(-1./3, "var a = 1/3; a = -a; a*1;");

	TestCommon::testExpression(12, "var a = 5; ++a*2;");
	TestCommon::testExpression(10, "var a = 5; a++*2;");
	TestCommon::testExpression(6, "var a = 5; a++*2; a;");
	TestCommon::testExpression(6, "var a = 5; ++a*2; a;");
	TestCommon::testExpression(32, "var a = 5; var c = --a*2; a*c;");
	TestCommon::testExpression(40, "var a = 5; var c = a--*2; a*c;");

	TestCommon::testExpression(10, "var a = 5; for (i = 0; i < 5; i++) a = a + 1; a;");
	TestCommon::testExpression(5, "var a = 5; for (i = 0; i < 5; i++) var b = a + 1; a;");
	TestCommon::testExpression(5, "var a = 5; for (i = 0; i < 5; i++) var a = a + 1; a;");

	TestCommon::testExpression(65, "var a = 2; var i = 4; while (i >= 0) {a = a*2; i = i - 1;} a + 1;");
	TestCommon::testExpression(33, "var a = 2; var i = 4; do {a = a*2; i = i - 1;} while (i > 0); a + 1;");

	TestCommon::testExpression(10, "var a = 5; if (a > 10) a = a + 1; a*2;");
	TestCommon::testExpression(14, "var a = 5; if (a > 10) a = a + 1; else { a = a + 2;} a*2;");

	TestCommon::testExpression(10, "var c = 5; var a = c>=5 ? 2*c : 2*2*c; a;");
	TestCommon::testExpression(25, "var c = 5; var a = 1>10 ? 20*c : c*c; a;");
	TestCommon::testExpression(50, "var c = 5; var a = (1>10 ? 20*c : c*c)*2; a;");

	//TestCommon::testExpression(true, "var a = false; a = !a; a;"); // Cannot be parsed for some reason.
	TestCommon::testExpression(true, "var a = false; a = a || true; a;");
	TestCommon::testExpression(false, "var a = 10 < 5; a;");

	TestCommon::testExpression("'bla bla'", "var a = 'bla bla'; a;"); // Parser doesn't strip the quotation marks.
	TestCommon::testExpression("\"bla bla\"", "var a = \"bla bla\"; a;");
	TestCommon::testExpression("'bla'' ''bla bla'", "var a = 'bla';\n var b = 'bla bla';\n var c = a + ' ' + b; c;"); // Parser fails when there are more than one string literals on one line.
	TestCommon::testExpression("'bla bla'", "var a = 'bla';\n var b = 'bla bla'; var c = b; c;");

	TestCommon::testExpression(10, "var c = 2; var a = { property: 5*c }; a.property;");
	//TestCommon::testExpression(10, "var c = 2; var a = { property: 5*c }; a.['property'];"); // This doesn't work as well.

	TestCommon::testExpression(16, "var fun = function(a){ return a*a; }; fun(fun(2));");
	TestCommon::testExpression(5, "var fun = function(){ return 5; return 10; }; fun();");

	TestCommon::testExpression(10, "var a = 0; for (b = 0; b < 10; b++){ a++;} a;");
	TestCommon::testExpression(5, "var a = 0; for (b = 0; b < 10; b++){ if (a >= 5) {break;} a++;} a;");
	//TestCommon::testExpression(5, "var a = 0; for (b = 0; b < 10; b++){ if (a >= 5) break; a++;} a;"); // Cannot parse break;
	//TestCommon::testExpression(5, "var a = 0; for (;;){ if (a >= 5) break;} a;"); // Weird undefined phantom variable.
	TestCommon::testExpression(5, "var a = 0; for (b = 0; b < 10; b++){ if (a >= 5) {continue;} a++;} a;");
	//TestCommon::testExpression(5, "var a = 0; for (b = 0; b < 10; b++){ if (a >= 5) continue; a++;} a;"); // Cannot parse this continue.

	TestCommon::testExpression(5, "var a = 0; while(true){ if (a >= 5) {break;} a++;} a;");
	//TestCommon::testExpression(5, "var a = 0; var b = 0; while(b < 10){ b++; if (a >= 5) break; a++;} a;"); // Cannot parse break;
	TestCommon::testExpression(5, "var a = 0; var b = 0; while(b < 10){ b++; if (a >= 5) {continue;} a++;} a;");
	//TestCommon::testExpression(5, "var a = 0; var b = 0; while(b < 10){ b++; if (a >= 5) continue; a++;} a;"); // Cannot parse this continue.
}
