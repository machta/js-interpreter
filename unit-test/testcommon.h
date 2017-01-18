#ifndef TESTCOMMON_H
#define TESTCOMMON_H

#include "gtest/gtest.h"
#include <string>

class TestCommon
{
public:
	static void testExpression(double n, const std::string& code);
	static void testExpression(int n, const std::string& code)
	{
		testExpression(static_cast<double>(n), code);
	}
	static void testExpression(bool b, const std::string& code);
	static void testExpression(const std::string& answer, const std::string& code);
	static void testExpression(const char* answer, const std::string& code)
	{
		testExpression(std::string(answer), code);
	}
};

#endif // TESTCOMMON_H
