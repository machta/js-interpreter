#ifndef TESTCOMMON_H
#define TESTCOMMON_H

#include "gtest/gtest.h"
#include <string>

class TestCommon
{
public:
	static void testCode(double n, const std::string& code);
	static void testCode(int n, const std::string& code)
	{
		testCode(static_cast<double>(n), code);
	}
	static void testCode(bool b, const std::string& code);
	static void testCode(const std::string& answer, const std::string& code);
	static void testCode(const char* answer, const std::string& code)
	{
		testCode(std::string(answer), code);
	}
};

#endif // TESTCOMMON_H
