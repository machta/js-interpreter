#include "testcommon.h"

TEST(function_test, first_test)
{	
	TEST_EXPRESSION(16, "var fun = function(a){ return a*a; }; fun(fun(2));");
	TEST_EXPRESSION(5, "var fun = function(){ return 5; return 10; }; fun();");
}

TEST(function_test, scope)
{
	TEST_EXPRESSION(2, "var a = 5; var fun = function(a){ return a; }; fun(2);");
	TEST_EXPRESSION(5, "var a = 5; var fun = function(){ return a; }; fun(2);");
	TEST_EXPRESSION(5, "var a = 5; var fun = function(a){ return fun2(); }; var fun2 = function() { return a; }; fun(2);");
	TEST_EXPRESSION(2, "var a = 5; var fun = function(){ return a; }; if (true) { var a = 2; } fun();");
	TEST_EXPRESSION(2, "var a = 5; var fun = function(){ return b; }; if (true) { var b = 2; } fun();");

	TEST_EXPRESSION(2, "var fun = function(){ var a = 5; if(true) {var a = 2;} return a; }; fun();");

	//TEST_EXPRESSION(2, "var fun = function() { var a = 5; return fun2(); }; var fun2 = function() { return a; }; fun();"); // undeclared variable error
	TEST_EXPRESSION(10, "var a = 0; for (i = 0; i < 10; i++) a++; i;");
	//TEST_EXPRESSION(true, "var fun = function() { var a = 0; for (i = 0; i < 10; i++) a++; return i; }; fun(); i == 10;"); // i is not propagated to the global scope
	//TEST_EXPRESSION(2, "var fun = function() { var a = 0; for (var i = 0; i < 10; i++) a++; return i; }; fun(); i == 10;"); // i undefined
}
// TODO: Automatic global variable assignment.

TEST(function_test, recursion)
{
	TEST_EXPRESSION(5, "var fib = function(n) {	if (n <= 2) return 1; return fib(n - 2) + fib(n - 1); }; fib(5);");
	TEST_EXPRESSION(4181, "var fib = function(n) { if (n <= 2) return 1; return fib(n - 2) + fib(n - 1); }; fib(19);");
}
