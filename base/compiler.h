#ifndef __COMPILER_H__
#define __COMPILER_H__

#include "hierarchical list.h"
#include "search tree.h"
#include "search tree.cpp"
#include "arithmetic postfix.h"
#include "conditional postfix.h"
#include <iostream>
#include <vector>

using namespace std;

class Compiler
{
	SearchTree<int> int_var;
	SearchTree<int> int_const;
	SearchTree<double> double_var;
	SearchTree<double> double_const;
	HierList<string> code;

	void DoBeginEndBlock();
	void DoIfBlock();
	void AssigningValue();

	void CreateVar();
	void CreateConst();
	void ExecuteRead();
	void ExecuteWrite();
	double CalculateArithm(vector<string>& expression);
	bool CalculateCond(vector<string>& expression);
public:
	void ProcessProgram(HierList<string>& code);
};
#endif
