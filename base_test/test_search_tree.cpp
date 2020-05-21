#pragma once
#include "search tree.h"
#include <gtest.h>

TEST(NodeTree, one_plus_one)
{
	EXPECT_EQ(2, 1 + 1);
}

TEST(NodeTree, constructor_by_default)
{
	ASSERT_NO_THROW(NodeTree<string> snode);
}

TEST(NodeTree, use_destructor)
{
	NodeTree<string> snode;
	ASSERT_NO_THROW(snode.~NodeTree());
}

TEST(NodeTree, constructor_init)
{
	int p = 100;

	ASSERT_NO_THROW(NodeTree<int> inode("name1", p));
}

TEST(NodeTree, can_insert_data)
{
	int p = 100;
	NodeTree<int> inode("name1", p);

	ASSERT_EQ(inode.data, p);
}

TEST(NodeTree, can_set_left_child)
{
	int p = 100;
	NodeTree<int> inode1("name1", p);
	NodeTree<int> inode2("name2", p + 10);

	ASSERT_NO_THROW(inode1.SetChild(&inode2, true));
}

TEST(NodeTree, can_set_right_child)
{
	int p = 100;
	NodeTree<int> inode1("name1", p);
	NodeTree<int> inode2("name2", p + 10);

	ASSERT_NO_THROW(inode1.SetChild(&inode2, false));
}

TEST(NodeTree, can_get_child)
{
	int p = 100;
	NodeTree<int> inode1("name1", p);
	NodeTree<int> inode2("name2", p + 10);

	inode1.SetChild(&inode2, true);

	ASSERT_NO_THROW(inode1.GetChild(true));
}

TEST(NodeTree, cant_get_child)
{
	int p = 100;
	NodeTree<int> inode1("name1", p);

	ASSERT_EQ(inode1.GetChild(true), nullptr);
}

TEST(NodeTree, can_get_childs_data)
{
	int p = 100;
	NodeTree<int> inode1("name1", p);
	NodeTree<int> inode2("name2", p + 10);

	inode1.SetChild(&inode2, true);

	ASSERT_EQ(inode1.GetChild(true)->data, p + 10);
}

TEST(NodeTree, can_get_parent)
{
	int p = 100;
	NodeTree<int> inode1("name1", p);
	NodeTree<int> inode2("name2", p + 10);

	inode1.SetChild(&inode2, true);

	ASSERT_NO_THROW(inode2.GetParent());
}

TEST(NodeTree, cant_get_parent)
{
	int p = 100;
	NodeTree<int> inode1("name1", p);

	ASSERT_EQ(inode1.GetParent(), nullptr);
}

TEST(NodeTree, can_get_parent_data)
{
	int p = 100;
	NodeTree<int> inode1("name1", p);
	NodeTree<int> inode2("name2", p + 10);

	inode1.SetChild(&inode2, true);

	ASSERT_EQ(inode2.GetParent()->data, p);
}

TEST(SearchTree, one_plus_one)
{
	EXPECT_EQ(2, 1 + 1);
}

TEST(SearchTree, constructor_by_default)
{
	ASSERT_NO_THROW(SearchTree<string> stree);
}

TEST(SearchTree, use_destructor)
{
	SearchTree<string> stree;
	ASSERT_NO_THROW(stree.~SearchTree());
}

TEST(SearchTree, insert_in_tree)
{
	SearchTree<int> itree;
	int p = 100;

	ASSERT_NO_THROW(itree.Insert("name1", p));
}

TEST(SearchTree, cant_insert_same_name)
{
	SearchTree<int> itree;
	int p1 = 100;
	int p2 = 200;

	itree.Insert("name1", p1);
	ASSERT_ANY_THROW(itree.Insert("name1", p2));
}

TEST(SearchTree, can_find_in_search_tree)
{
	SearchTree<int> itree;
	int p = 100;

	itree.Insert("name1", p);

	ASSERT_EQ(*itree.Find("name1"), p);
}

TEST(SearchTree, cant_find_if_not_in_search_tree)
{
	SearchTree<int> itree;
	int p = 100;

	itree.Insert("name1", p);

	ASSERT_EQ(itree.Find("name2"), nullptr);
}

TEST(SearchTree, can_get_right_count)
{
	SearchTree<int> itree;
	int p = 100;

	itree.Insert("name1", p);
	itree.Insert("name2", p);
	itree.Insert("name3", p);

	ASSERT_EQ(itree.GetCount(), 3);

	itree.Insert("name4", p);

	ASSERT_NE(itree.GetCount(), 3);
}

TEST(SearchTree, can_get_empty_if_empty)
{
	SearchTree<int> itree;
	int p = 100;

	ASSERT_TRUE(itree.IsEmpty());

	itree.Insert("name1", p);

	ASSERT_FALSE(itree.IsEmpty());
}

TEST(SearchTree, can_get_height_of_tree)
{
	SearchTree<int> itree;
	int p = 100;

	ASSERT_NO_THROW(itree.GetHeight());

	ASSERT_EQ(0, itree.GetHeight());

	itree.Insert("name1", p);

	ASSERT_EQ(1, itree.GetHeight());

	itree.Insert("name2", p);

	ASSERT_EQ(2, itree.GetHeight());
}

TEST(SearchTree, can_balance_tree_simple)
{
	SearchTree<int> itree;
	int p = 100;

	itree.Insert("name1", p);
	itree.Insert("name2", p);
	itree.Insert("name3", p);

	ASSERT_EQ(2, itree.GetHeight());
}

TEST(SearchTree, can_balance_tree)
{
	SearchTree<int> itree;
	int p = 100;

	itree.Insert("name1", p);
	itree.Insert("name2", p);
	itree.Insert("name3", p);
	itree.Insert("name4", p);
	itree.Insert("name5", p);
	itree.Insert("name6", p);

	ASSERT_EQ(3, itree.GetHeight());
}