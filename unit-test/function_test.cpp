#include "testcommon.h"

TEST(function_test, first_test)
{	
	// Ad-hoc.
	TestCommon::testExpression(16, "var fun = function(a){ return a*a; }; fun(fun(2));");
	TestCommon::testExpression(5, "var fun = function(){ return 5; return 10; }; fun();");
}
