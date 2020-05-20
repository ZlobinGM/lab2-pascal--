#include <gtest.h>
#include "arithmetic postfix.cpp"

TEST(ArithmPostfix, one_plus_one)
{
	EXPECT_EQ(2, 1 + 1);
}

TEST(ArithmPostfix, constructor_by_default)
{
	ASSERT_NO_THROW(ArithmPostfix aritm);
}

TEST(ArithmPostfix, can_define_operation)
{
	ArithmPostfix aritm;

	ASSERT_NO_THROW(aritm.IsOperation("+"));
	ASSERT_EQ(aritm.IsOperation("+"), true);

	ASSERT_NO_THROW(aritm.IsOperation("-"));
	ASSERT_EQ(aritm.IsOperation("-"), true);

	ASSERT_NO_THROW(aritm.IsOperation("mod"));
	ASSERT_EQ(aritm.IsOperation("mod"), true);

	ASSERT_NO_THROW(aritm.IsOperation("div"));
	ASSERT_EQ(aritm.IsOperation("div"), true);

	ASSERT_NO_THROW(aritm.IsOperation("*"));
	ASSERT_EQ(aritm.IsOperation("*"), true);

	ASSERT_NO_THROW(aritm.IsOperation("/"));
	ASSERT_EQ(aritm.IsOperation("/"), true);

	ASSERT_NO_THROW(aritm.IsOperation("("));
	ASSERT_EQ(aritm.IsOperation("("), false);

	ASSERT_NO_THROW(aritm.IsOperation(")"));
	ASSERT_EQ(aritm.IsOperation(")"), false);

	ASSERT_NO_THROW(aritm.IsOperation("a"));
	ASSERT_EQ(aritm.IsOperation("a"), false);

	ASSERT_NO_THROW(aritm.IsOperation("bcde"));
	ASSERT_EQ(aritm.IsOperation("bcde"), false);
}

TEST(ArithmPostfix, can_define_digit)
{
	ArithmPostfix aritm;
	string s;

	ASSERT_NO_THROW(aritm.IsDigit("1"));
	ASSERT_EQ(aritm.IsDigit("1"), true);

	ASSERT_NO_THROW(aritm.IsDigit("0"));
	ASSERT_EQ(aritm.IsDigit("0"), true);

	ASSERT_NO_THROW(aritm.IsDigit("0.55"));
	ASSERT_EQ(aritm.IsDigit("0.55"), true);

	ASSERT_NO_THROW(aritm.IsDigit("a"));
	ASSERT_EQ(aritm.IsDigit("a"), false);

	ASSERT_NO_THROW(aritm.IsDigit("bcde"));
	ASSERT_EQ(aritm.IsDigit("bcde"), false);
}

TEST(ArithmPostfix, can_make_to_postfix)
{
	ArithmPostfix aritm;
	vector<string> infix = { "1","+","2","*", "8","+", "7","mod", "6" };
	vector<string> postfix = { "1","2","8","*", "+","7", "6","mod", "+" };

	ASSERT_NO_THROW(aritm.ToPostfix(infix));
	ASSERT_EQ(aritm.GetPostfix(), postfix);
}

TEST(ArithmPostfix, can_calculate)
{
	ArithmPostfix aritm;
	vector<string> infix = { "1","+","2","*", "8","+", "7","mod", "6" };
	vector<string> postfix = { "1","2","8","*", "+","7", "6","mod", "+" };
	double res = 18;
	aritm.ToPostfix(infix);

	ASSERT_NO_THROW(aritm.Calculate());
	ASSERT_EQ(aritm.Calculate(), res);
}