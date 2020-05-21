#pragma once
#include "compiler.cpp"
#include "analytical module.cpp"
#include <gtest.h>

TEST(Compiler, one_plus_one)
{
	EXPECT_EQ(2, 1 + 1);
}

TEST(Compiler, can_create_compiler)
{
	ASSERT_NO_THROW(Compiler());
}

TEST(AnalyticalMod, can_process_program_simple)
{
	ifstream ifile;
	ifile.open("../code3.txt");

	AnalyticalMod amod;
	amod.Read(ifile);
	amod.SyntaxConntrol();
	HierList<string> list;
	list = move(*amod.CreateHierList());
	Compiler comp;
	comp.ProcessProgram(list);

	ASSERT_NO_THROW(amod.SyntaxConntrol());
}

TEST(AnalyticalMod, can_process_program_advanced)
{
	ifstream ifile;
	ifile.open("../code1.1.txt");

	AnalyticalMod amod;
	amod.Read(ifile);
	amod.SyntaxConntrol();
	HierList<string> list;
	list = move(*amod.CreateHierList());
	Compiler comp;
	comp.ProcessProgram(list);

	ASSERT_NO_THROW(amod.SyntaxConntrol());
}