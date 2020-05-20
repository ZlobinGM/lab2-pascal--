#include "conditional postfix.cpp"
#include <gtest.h>

TEST(CondPostfix, one_plus_one)
{
	EXPECT_EQ(2, 1 + 1);
}

TEST(CondPostfix, constructor_by_default)
{
	ASSERT_NO_THROW(CondPostfix aritm);
}

TEST(CondPostfix, can_define_operation)
{
	CondPostfix aritm;

	ASSERT_NO_THROW(aritm.IsOperation("or"));
	ASSERT_EQ(aritm.IsOperation("or"), true);

	ASSERT_NO_THROW(aritm.IsOperation("and"));
	ASSERT_EQ(aritm.IsOperation("and"), true);

	ASSERT_NO_THROW(aritm.IsOperation("not"));
	ASSERT_EQ(aritm.IsOperation("not"), true);

	ASSERT_NO_THROW(aritm.IsOperation("="));
	ASSERT_EQ(aritm.IsOperation("="), true);

	ASSERT_NO_THROW(aritm.IsOperation("<>"));
	ASSERT_EQ(aritm.IsOperation("<>"), true);

	ASSERT_NO_THROW(aritm.IsOperation("<="));
	ASSERT_EQ(aritm.IsOperation("<="), true);

	ASSERT_NO_THROW(aritm.IsOperation("("));
	ASSERT_EQ(aritm.IsOperation("("), false);

	ASSERT_NO_THROW(aritm.IsOperation(")"));
	ASSERT_EQ(aritm.IsOperation(")"), false);

	ASSERT_NO_THROW(aritm.IsOperation("a"));
	ASSERT_EQ(aritm.IsOperation("a"), false);

	ASSERT_NO_THROW(aritm.IsOperation("bcde"));
	ASSERT_EQ(aritm.IsOperation("bcde"), false);
}

TEST(CondPostfix, can_define_digit)
{
	CondPostfix aritm;
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

TEST(CondPostfix, can_make_to_postfix)
{
	CondPostfix cond;
	vector<string> infix = { "1","and","2","=", "8","mod", "6","or", "0" };
	vector<string> postfix = { "1","2","2.000000","=", "and","0", "or" };

	ASSERT_NO_THROW(cond.ToPostfix(infix));
	ASSERT_EQ(cond.GetPostfix(), postfix);
}

TEST(CondPostfix, can_calculate)
{
	CondPostfix cond;
	vector<string> infix = { "1","and","2","=", "8","mod", "6","or", "0" };
	bool res = true;
	cond.ToPostfix(infix);

	ASSERT_NO_THROW(cond.Calculate());
	ASSERT_EQ(cond.Calculate(), res);
}