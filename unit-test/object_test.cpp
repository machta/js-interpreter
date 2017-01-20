#include "testcommon.h"

TEST(object_test, property)
{
	TEST_EXPRESSION(10, "var c = 2; var a = { property: 5*c }; a.property;");

	//TEST_EXPRESSION(10, "var c = 2; var a = { property: 5*c }; a.['property'];"); // This doesn't parse.
}

TEST(object_test, method)
{
	TEST_EXPRESSION(5, "var o = { fun: function(){return 5;}}; o.fun();");

	TEST_EXPRESSION(15, "var fun = function(){return 5;}, fun2 = function(){return 10;}; fun() + fun2();");
	TEST_EXPRESSION(15, "var o = { fun: function(){return 5;}, fun2: function(){return 10;}}; o.fun() + o.fun2();");

	TEST_EXPRESSION(50, "var o = { fun: function(){return 5;}, property: 10}; o.fun()*o.property;");
}
