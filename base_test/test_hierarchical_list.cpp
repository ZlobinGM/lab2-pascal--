#include "hierarchical list.h"
#include <gtest.h>

using namespace std;

TEST(HierList, one_plus_one)
{
	EXPECT_EQ(2, 1 + 1);
}

TEST(HierList, constructor_by_default)
{
	ASSERT_NO_THROW(HierList<string> shierlist);
}

TEST(HierList, constructor_copy)
{
	HierList<string> shierlist1;
	ASSERT_NO_THROW(HierList<string>(shierlist1));
}

TEST(HierList, use_destructor)
{
	HierList<string> shierlist;
	ASSERT_NO_THROW(shierlist.~HierList());
}

TEST(HierList, can_use_operator_move_assing)
{
	HierList<string> shierlist1;
	HierList<string> shierlist2;

	ASSERT_NO_THROW(shierlist2 = move(shierlist1));
}

TEST(HierList, can_insert_next)
{
	HierList<string> shierlist;
	string str1 = "string1";

	ASSERT_NO_THROW(shierlist.InsertNext(str1));

	ASSERT_EQ(shierlist.ReadCurrent(), str1);
}

TEST(HierList, can_insert_down)
{
	HierList<string> shierlist;
	string str1 = "string1";
	string str2 = "string2";

	shierlist.InsertNext(str1);

	ASSERT_NO_THROW(shierlist.InsertDown(str2));

	shierlist.GoDown();

	ASSERT_EQ(shierlist.ReadCurrent(), str2);
}

TEST(HierList, cant_insert_down)
{
	HierList<string> shierlist;
	string str1 = "string1";

	ASSERT_ANY_THROW(shierlist.InsertDown(str1));
}

TEST(HierList, can_read_current)
{
	HierList<string> shierlist;
	string str1 = "string1";

	shierlist.InsertNext(str1);

	ASSERT_NO_THROW(shierlist.ReadCurrent());

	ASSERT_EQ(shierlist.ReadCurrent(), str1);
}

TEST(HierList, cant_read_current)
{
	HierList<string> shierlist;
	ASSERT_ANY_THROW(shierlist.ReadCurrent());
}

TEST(HierList, can_go_next)
{
	HierList<string> shierlist;
	string str1 = "string1";
	string str2 = "string2";
	string str3 = "string3";

	shierlist.InsertNext(str1);

	shierlist.InsertNext(str2);

	ASSERT_NO_THROW(shierlist.GoNext());
	ASSERT_EQ(shierlist.ReadCurrent(), str2);

	shierlist.InsertNext(str3);
	shierlist.GoNext();

	ASSERT_EQ(shierlist.ReadCurrent(), str3);
}

TEST(HierList, cant_go_next)
{
	HierList<string> shierlist;
	string str1 = "string1";

	shierlist.InsertNext(str1);

	ASSERT_EQ(shierlist.GoNext(), false);
}

TEST(HierList, can_go_down)
{
	HierList<string> shierlist;
	string str1 = "string1";
	string str2 = "string2";
	string str3 = "string3";

	shierlist.InsertNext(str1);

	shierlist.InsertDown(str2);

	ASSERT_NO_THROW(shierlist.GoDown());
	ASSERT_EQ(shierlist.ReadCurrent(), str2);

	shierlist.InsertDown(str3);
	shierlist.GoDown();

	ASSERT_EQ(shierlist.ReadCurrent(), str3);
}

TEST(HierList, cant_go_down)
{
	HierList<string> shierlist;
	string str1 = "string1";

	shierlist.InsertNext(str1);

	ASSERT_EQ(shierlist.GoDown(), false);
}

TEST(HierList, can_go_up)
{
	HierList<string> shierlist;
	string str1 = "string1";
	string str2 = "string2";
	string str3 = "string3";

	shierlist.InsertNext(str1);

	shierlist.InsertDown(str2);
	shierlist.GoDown();
	shierlist.InsertDown(str3);
	shierlist.GoDown();

	ASSERT_NO_THROW(shierlist.GoUp());
	ASSERT_EQ(shierlist.ReadCurrent(), str2);
}

TEST(HierList, cant_go_up)
{
	HierList<string> shierlist;
	string str1 = "string1";

	shierlist.InsertNext(str1);

	ASSERT_EQ(shierlist.GoUp(), false);
}

TEST(HierList, can_go_first)
{
	HierList<string> shierlist;
	string str1 = "string1";
	string str2 = "string2";
	string str3 = "string3";

	shierlist.InsertNext(str1);

	shierlist.InsertDown(str2);
	shierlist.GoDown();
	shierlist.InsertDown(str3);
	shierlist.GoDown();

	ASSERT_NO_THROW(shierlist.GoFirst());
	ASSERT_EQ(shierlist.ReadCurrent(), str1);
}