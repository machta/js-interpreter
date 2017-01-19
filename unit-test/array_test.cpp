#include "testcommon.h"

TEST(array_test, literal)
{
	TestCommon::testExpression(9, "var array = [1, 3, 5]; var sum = 0; for (i = 0; i < 3; i++) sum = sum + array[i]; sum;");
}

TEST(array_test, index_access)
{
	TestCommon::testExpression(4, "var array = [1, 3, 5]; array[2] = 0; var sum = 0; for (i = 0; i < 3; i++) sum = sum + array[i]; sum;");
}
