#include "testcommon.h"

TEST(object_test, property)
{
	TEST_EXPRESSION(10, "var c = 2; var a = { property: 5*c }; a.property;");

	TEST_EXPRESSION(10, "var a = {property: 5}; var b = {property:10}; a.property = b; a.property.property;");
	TEST_EXPRESSION(10, "var a = {aa: 5}; var b = {bb:10}; a.aa = b; a.aa.bb;");
	TEST_EXPRESSION(10, "var a = {b: 5}; var b = {a:10}; a.b = b; a.b.a;");

	TEST_EXPRESSION(true, "var a = {property: 5}; a.property = a; a.property == a.property.property;");

	//TEST_EXPRESSION(10, "var c = 2; var a = { property: 5*c }; a.['property'];"); // This doesn't parse.
}

TEST(object_test, method)
{
	TEST_EXPRESSION(5, "var o = { fun: function(){return 5;}}; o.fun();");

	TEST_EXPRESSION(15, "var fun = function(){return 5;}, fun2 = function(){return 10;}; fun() + fun2();");
	TEST_EXPRESSION(15, "var o = { fun: function(){return 5;}, fun2: function(){return 10;}}; o.fun() + o.fun2();");

	TEST_EXPRESSION(50, "var o = { fun: function(){return 5;}, property: 10}; o.fun()*o.property;");
}

TEST(object_test, reference)
{
	TEST_EXPRESSION(true, "var a = { property: 5 }; var b = a; b.property = 10; a.property == b.property;");
	TEST_EXPRESSION(10, "var a = { property: 5 }; var b = a; b.property = 10; a.property;");

	TEST_EXPRESSION(true, "var a = { property: 5 }; var b = a; a == b;");
	TEST_EXPRESSION(false, "var a = { property: 5 }; var b = 5; a == b;");
	TEST_EXPRESSION(true, "var a = { property: 5 }; var b = 5; a.property == b;");

	TEST_EXPRESSION(10, "var a = { property: 5 }; var b = { property: a }; b.property.property = 10; a.property;");
}
