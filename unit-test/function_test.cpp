#include "testcommon.h"

TEST(function_test, first_test)
{	
	// Ad-hoc.
	TestCommon::testExpression(16, "var fun = function(a){ return a*a; }; fun(fun(2));");
	TestCommon::testExpression(5, "var fun = function(){ return 5; return 10; }; fun();");
}

TEST(function_test, scope)
{
	// Ad-hoc.
	TestCommon::testExpression(2, "var a = 5; var fun = function(a){ return a; }; fun(2);");
	TestCommon::testExpression(5, "var a = 5; var fun = function(){ return a; }; fun(2);");
	TestCommon::testExpression(5, "var a = 5; var fun = function(a){ return fun2(); }; var fun2 = function() { return a; }; fun(2);");
	TestCommon::testExpression(2, "var a = 5; var fun = function(){ return a; }; if (true) { var a = 2; } fun();");
	TestCommon::testExpression(2, "var a = 5; var fun = function(){ return b; }; if (true) { var b = 2; } fun();");

	TestCommon::testExpression(2, "var fun = function(){ var a = 5; if(true) {var a = 2;} return a; }; fun();");

	//TestCommon::testExpression(2, "var fun = function() { var a = 5; return fun2(); }; var fun2 = function() { return a; }; fun();"); // undeclared variable error
	TestCommon::testExpression(10, "var a = 0; for (i = 0; i < 10; i++) a++; i;");
	//TestCommon::testExpression(true, "var fun = function() { var a = 0; for (i = 0; i < 10; i++) a++; return i; }; fun(); i == 10;"); // i is not propagated to the global scope
	//TestCommon::testExpression(2, "var fun = function() { var a = 0; for (var i = 0; i < 10; i++) a++; return i; }; fun(); i == 10;"); // i undefined
}

// TODO: Automatic global vars
