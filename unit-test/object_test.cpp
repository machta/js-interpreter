#include "testcommon.h"

TEST(object_test, property)
{
	TEST_EXPRESSION(10, "var c = 2; var a = { property: 5*c }; a.property;");

	//TEST_EXPRESSION(10, "var c = 2; var a = { property: 5*c }; a.['property'];"); // This doesn't parse.
}
