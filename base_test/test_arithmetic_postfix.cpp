#include "arithmetic postfix.cpp"
#include <gtest.h>

TEST(ArithmPostfix, one_plus_one)
{
	EXPECT_EQ(2, 1 + 1);
}