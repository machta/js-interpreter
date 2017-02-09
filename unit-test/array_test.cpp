#include "testcommon.h"

TEST(array_test, literal)
{
	TEST_EXPRESSION(90, "var array = [10, 30, 50]; var sum = 0; for (i = 0; i < 3; i++) sum = sum + array[i]; sum;");
	TEST_EXPRESSION(9, "var array; array = [1, 3, 5]; var sum = 0; for (i = 0; i < 3; i++) sum = sum + array[i]; sum;");
}

TEST(array_test, index_access)
{
	TEST_EXPRESSION(4, "var array = [1, 3, 5]; array[2] = 0; var sum = 0; for (i = 0; i < 3; i++) sum = sum + array[i]; sum;");

	TEST_EXPRESSION("undefined", "var array = [1, 3, 5]; array[3];");

	TEST_EXPRESSION(10, "var array = [1, 3, 5]; array[10] = 10; array[10];");
	TEST_EXPRESSION(11, "var array = [1, 3, 5]; array[10] = 10; array.length;");
}
