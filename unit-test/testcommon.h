#ifndef TESTCOMMON_H
#define TESTCOMMON_H

#include "valuecontext.h"

#include "gtest/gtest.h"
#include <string>

#define TEST_EXPRESSION(a_, b_) {SCOPED_TRACE("\n"); TestCommon::testExpression(a_, b_);}
#define RUN_EXPRESSION(a_) TestCommon::runExpression(a_)

class TestCommon
{
public:
	static void testExpression(double n, const std::string& code);
	static void testExpression(int n, const std::string& code);
	static void testExpression(bool b, const std::string& code);
	static void testExpression(const std::string& answer, const std::string& code);
	static void testExpression(const char* answer, const std::string& code)
	{
		testExpression(std::string(answer), code);
	}
	static Value runExpression(const std::string& code);
};

#endif // TESTCOMMON_H
