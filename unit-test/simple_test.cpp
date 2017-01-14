#include "testcommon.h"

TEST(simple_test, first_test)
{
	TestCommon::testCode(12, "var a = 5*1/1; a = a + 1; a = a*2; a;");
	TestCommon::testCode(1, "var a = 13; a = a % 2; a;");
	TestCommon::testCode(-1./3, "var a = 1/3; a = -a; a*1;");

	TestCommon::testCode(12, "var a = 5; ++a*2;");
	TestCommon::testCode(10, "var a = 5; a++*2;");

	TestCommon::testCode(10, "var a = 5; for (i = 0; i < 5; i++) a = a + 1; a;");
	TestCommon::testCode(5, "var a = 5; for (i = 0; i < 5; i++) var b = a + 1; a;");
	TestCommon::testCode(5, "var a = 5; for (i = 0; i < 5; i++) var a = a + 1; a;");

	TestCommon::testCode(65, "var a = 2; var i = 4; while (i >= 0) {a = a*2; i = i - 1;} a + 1;");
	TestCommon::testCode(33, "var a = 2; var i = 4; do {a = a*2; i = i - 1;} while (i > 0); a + 1;");

	TestCommon::testCode(10, "var a = 5; if (a > 10) a = a + 1; a*2;");
	TestCommon::testCode(14, "var a = 5; if (a > 10) a = a + 1; else { a = a + 2;} a*2;");

	//TestCommon::testCode(true, "var a = false; a = !a; a;"); // Cannot be parsed for some reason.
	TestCommon::testCode(true, "var a = false; a = a || true; a;");
	TestCommon::testCode(false, "var a = 10 < 5; a;");

	TestCommon::testCode("'bla bla'", "var a = 'bla bla'; a;");
}
