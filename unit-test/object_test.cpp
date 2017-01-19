#include "testcommon.h"

TEST(object_test, property)
{
	TestCommon::testExpression(10, "var c = 2; var a = { property: 5*c }; a.property;");

	//TestCommon::testExpression(10, "var c = 2; var a = { property: 5*c }; a.['property'];"); // This doesn't parse.
}
