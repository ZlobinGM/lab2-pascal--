#pragma once
#include "analytical module.h"
#include <gtest.h>

TEST(AnalyticalMod, one_plus_one)
{
	EXPECT_EQ(2, 1 + 1);
}

TEST(AnalyticalMod, can_create_analytical_module)
{
	ASSERT_NO_THROW(AnalyticalMod());
}

TEST(AnalyticalMod, can_read_from_file)
{
	ifstream ifile;
	ifile.open("../code.txt");
	AnalyticalMod amod;

	ASSERT_NO_THROW(amod.Read(ifile));
}

TEST(AnalyticalMod, dont_throw_if_correct)
{
	ifstream ifile;
	ifile.open("../code1.txt");
	AnalyticalMod amod;
	amod.Read(ifile);

	ASSERT_NO_THROW(amod.SyntaxConntrol());
}

TEST(AnalyticalMod, throw_if_undeclered_var)
{
	ifstream ifile;
	ifile.open("../code.txt");
	AnalyticalMod amod;
	amod.Read(ifile);

	ASSERT_ANY_THROW(amod.SyntaxConntrol());
}

TEST(AnalyticalMod, throw_if_loose_brackets)
{
	ifstream ifile;
	ifile.open("../error_code1.txt");
	AnalyticalMod amod;
	amod.Read(ifile);

	ASSERT_ANY_THROW(amod.SyntaxConntrol());
}

TEST(AnalyticalMod, throw_if_loose_begin)
{
	ifstream ifile;
	ifile.open("../error_code2.txt");
	AnalyticalMod amod;
	amod.Read(ifile);

	ASSERT_ANY_THROW(amod.SyntaxConntrol());
}

TEST(AnalyticalMod, throw_if_loose_end)
{
	ifstream ifile;
	ifile.open("../error_code2.1.txt");
	AnalyticalMod amod;
	amod.Read(ifile);

	ASSERT_ANY_THROW(amod.SyntaxConntrol());
}

TEST(AnalyticalMod, throw_if_loose_if)
{
	ifstream ifile;
	ifile.open("../error_code3.txt");
	AnalyticalMod amod;
	amod.Read(ifile);

	ASSERT_ANY_THROW(amod.SyntaxConntrol());
}

TEST(AnalyticalMod, throw_if_loose_then)
{
	ifstream ifile;
	ifile.open("../error_code3.1.txt");
	AnalyticalMod amod;
	amod.Read(ifile);

	ASSERT_ANY_THROW(amod.SyntaxConntrol());
}

TEST(AnalyticalMod, throw_if_const_uninit)
{
	ifstream ifile;
	ifile.open("../error_code4.txt");
	AnalyticalMod amod;
	amod.Read(ifile);

	ASSERT_ANY_THROW(amod.SyntaxConntrol());
}

TEST(AnalyticalMod, throw_if_no_const_type)
{
	ifstream ifile;
	ifile.open("../error_code5.txt");
	AnalyticalMod amod;
	amod.Read(ifile);

	ASSERT_ANY_THROW(amod.SyntaxConntrol());
}

TEST(AnalyticalMod, throw_if_no_var_type)
{
	ifstream ifile;
	ifile.open("../error_code5.1.txt");
	AnalyticalMod amod;
	amod.Read(ifile);

	ASSERT_ANY_THROW(amod.SyntaxConntrol());
}

TEST(AnalyticalMod, throw_if_ununic_name)
{
	ifstream ifile;
	ifile.open("../error_code6.txt");
	AnalyticalMod amod;
	amod.Read(ifile);

	ASSERT_ANY_THROW(amod.SyntaxConntrol());
}

TEST(AnalyticalMod, throw_if_use_uninit_var)
{
	ifstream ifile;
	ifile.open("../error_code7.txt");
	AnalyticalMod amod;
	amod.Read(ifile);

	ASSERT_ANY_THROW(amod.SyntaxConntrol());
}

TEST(AnalyticalMod, throw_if_loose_quotation_mark)
{
	ifstream ifile;
	ifile.open("../error_code8.txt");
	AnalyticalMod amod;
	amod.Read(ifile);

	ASSERT_ANY_THROW(amod.SyntaxConntrol());
}