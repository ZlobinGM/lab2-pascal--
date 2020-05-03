#ifndef __COMPILER_H__
#define __COMPILER_H__

#include "hierarchical list.h"
#include "search tree.h"

using namespace std;

class Compiler
{
	SearchTree<int> int_var;
	SearchTree<const int> int_const;
	SearchTree<double> double_var;
	SearchTree<const double> double_const;
	HierList<string> code;
public:
	void ProcessProgram();
	void CreateVar(string str);
	void CreateConst(string str);
	void ExecuteRead(string str);
	void ExecuteWrite(string str);
	double CalculateArithm(string substr);
	bool CalculateCond(string substr);
};
#endif
